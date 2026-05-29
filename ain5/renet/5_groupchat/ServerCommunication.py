import time
import threading
import socket

import global_variables as g


class ServerCommunication:
    def __init__(self, nickname: str = 'nicky', ip: str = '127.0.0.2', udp_port: int = 60000, tcp_port: int = 50000, sock: socket.socket = None):
        self.__name: str = nickname
        self.__ip: str = ip
        self.__udp: int = udp_port
        self.__tcp: int = tcp_port
        self.__sock: socket.socket = sock

    def __str__(self):
        return f"USER|NAME={self.__name},IP={self.__ip},UDP={self.__udp},TCP={self.__tcp}"

    def print_USERLIST(self):
        with g.lock_USERLIST:
            eintraege = [f"{nick},{info['ip']},{info['udp_port']}" for nick, info in g.USERLIST.items()]
        userlist = "USERLIST|" + ";".join(eintraege) + "\0"
        print(userlist)

    def connect_and_register(self, server_ip: str, server_port: int) -> None:
        register_msg: str = f"REGISTER|{self.__name}|{self.__ip}|{self.__udp}\0"
        connected = False
        current_port = server_port

        try:
            for i in range(100):
                self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                if self.__sock.connect_ex((server_ip, current_port)) == 0:
                    print(f"Server erfolgreich an Port {current_port} erreicht.")
                    connected = True
                    break
                else:
                    print(f"Port {current_port} nicht erreichbar, versuche nächsten...")
                    self.__sock.close()
                    current_port += 1

            if connected:
                self.__sock.send(register_msg.encode('utf-8'))
                t = threading.Thread(target=self.listen_to_server, daemon=True)
                t.start()
            else:
                print(f"Verbindung zum Server fehlgeschlagen (Ports {server_port} bis {current_port - 1} getestet).\n$ ", end="")
                g.srvCom = None

        except socket.timeout:
            print(f"Timeout beim Verbindungsaufbau nach {time.asctime()}\n$ ", end="")
            if self.__sock:
                self.__sock.close()
            g.srvCom = None
        except socket.error:
            print(f"Netzwerkfehler an Port {current_port}.\n$ ", end="")
            if self.__sock:
                self.__sock.close()
            g.srvCom = None
        except KeyboardInterrupt:
            print("Client wird manuell beendet...")
            if self.__sock:
                self.__sock.close()
            g.srvCom = None

    def listen_to_server(self) -> None:
        puffer = ""
        # t_end = time.time() + server_activity_period
        # while time.time() < t_end:
        while True:
            try:
                data = self.__sock.recv(1024).decode('utf-8')
                if not data:
                    print(f"\n[Info] Alte Verbindung für '{self.__name}' sauber beendet.\n$ ", end="")
                    self.__sock.close()
                    if g.srvCom is self:
                        g.srvCom = None
                    break
                puffer += data
                while "\0" in puffer:
                    msg, puffer = puffer.split("\0", 1)
                    self.packet_code_from_server(msg)

            except socket.timeout:
                print(f"Timeout in receive nach {time.asctime()}.\n$ ")
                self.__sock.close()
                if g.srvCom is self:
                    g.srvCom = None
                break
            except socket.error:
                print("\nVerbindung zum Server unerwartet abgebrochen.\n$ ", end="")
                self.__sock.close()
                if g.srvCom is self:
                    g.srvCom = None
                break
            except KeyboardInterrupt:
                print("Client wird manuell beendet...")
                self.__sock.close()
                if g.srvCom is self:
                    g.srvCom = None
                break

    def packet_code_from_server(self, msg: str) -> None:
        errors = ["INVALID_FORMAT", "NAME_ALREADY_USED", "INVALID_PORT", "LOGOUT_FAILED"]
        try:
            cmd, data = msg.split("|", 1)
            match cmd:
                case "ERROR":
                    print(f"\nERROR Response from Server: {data}")
                    if data in errors:
                        if self.__sock:
                            self.__sock.close()
                        if g.srvCom is self:
                            g.srvCom = None

                case "USERLIST":
                    with g.lock_USERLIST:
                        g.USERLIST.clear()
                        users = data.split(";")
                        for user in users:
                            entry = user.split(",")
                            if len(entry) == 3:
                                if not g.validate_ip(entry[1]):
                                    raise Exception("INVALID_FORMAT")
                                if not g.validate_port(entry[2]):
                                    raise Exception("INVALID_FORMAT")
                                g.USERLIST[entry[0]] = {'ip': entry[1], 'udp_port': int(entry[2])}
                            else:
                                raise Exception("INVALID_FORMAT")

                case "UPDATE":
                    data = data.split("|")
                    if len(data) == 4:
                        success: bool
                        if (data[0] == "ADD"):
                            with g.lock_USERLIST:
                                if data[1] in g.USERLIST:
                                    success = False
                                else:
                                    if not g.validate_ip(data[2]):
                                        raise Exception("INVALID_FORMAT")
                                    if not g.validate_port(data[3]):
                                        raise Exception("INVALID_FORMAT")
                                    g.USERLIST[data[1]] = {'ip': data[2], 'udp_port': int(data[3])}
                                    success = True

                        elif (data[0] == "REMOVE"):
                            with g.lock_USERLIST:
                                user = g.USERLIST.pop(data[1], None)
                                if user:
                                    success = True
                                else:
                                    success = False
                        else:
                            raise Exception("INVALID_FORMAT")
                        try:
                            if success:
                                self.__sock.send("SUCCESS\0".encode('utf-8'))
                            else:
                                self.__sock.send("ERROR|INVALID_UPDATE_FORMAT\0".encode('utf-8'))
                        except socket.error:
                            self.__sock.close()
                            if g.srvCom is self:
                                g.srvCom = None
                    else:
                        raise Exception("INVALID_FORMAT")

                case "LOGOUT_SUCCESS":
                    print("Erfolgreich abgemeldet.")
                    if self.__sock:
                        self.__sock.close()
                    g.srvCom = None
                case "BROADCAST":
                    data = data.split("|", 1)
                    if len(data) >= 2:
                        print(f"User: {data[0]} send a Broadcast with: {data[1]}\n$ ")
                    else:
                        try:
                            self.__sock.send("ERROR|INVALID_BROADCAST_FORMAT\0".encode('utf-8'))
                        except socket.error:
                            self.__sock.close()
                            if g.srvCom is self:
                                g.srvCom = None

                case _:
                    raise Exception("INVALID_FORMAT")

        except Exception as e:
            match str(e):
                case "INVALID_FORMAT":
                    try:
                        self.__sock.send("ERROR|INVALID_FORMAT\0".encode('utf-8'))
                    except socket.error:
                        self.__sock.close()
                        if g.srvCom is self:
                            g.srvCom = None
                case _: print(f"Python-Fehler: {repr(e)}")

    def send_global_message(self, text: str) -> None:
        try:
            self.__sock.send(f"BROADCAST|{text}\0".encode('utf-8'))
        except socket.error:
            self.__sock.close()
            if g.srvCom is self:
                g.srvCom = None

    def disconnect(self) -> None:
        try:
            self.__sock.send("LOGOUT\0".encode('utf-8'))
        except socket.error:
            self.__sock.close()
        if g.srvCom is self:
            g.srvCom = None
