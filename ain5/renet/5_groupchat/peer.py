import time
import threading
import socket
from typing import Any

SERVER_IP = '127.0.0.1'
SERVER_PORT = 50000
server_activity_period = 30
USERLIST = {}
srvCom = None
lock_USERLIST = threading.Lock()


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
        with lock_USERLIST:
            eintraege = [f"{nick},{info['ip']},{info['udp_port']}" for nick, info in USERLIST.items()]
        userlist = "USERLIST|" + ";".join(eintraege) + "\0"
        print(userlist)

    def connect_and_register(self, server_ip: str, server_port: int) -> None:
        global srvCom
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
                print(f"Verbindung zum Server fehlgeschlagen (Ports {server_port} bis {current_port-1} getestet).\n$ ", end="")
                srvCom = None

        except socket.timeout:
            print(f"Timeout beim Verbindungsaufbau nach {time.asctime()}\n$ ", end="")
            if self.__sock:
                self.__sock.close()
            srvCom = None
        except socket.error:
            print(f"Netzwerkfehler an Port {current_port}.\n$ ", end="")
            if self.__sock:
                self.__sock.close()
            srvCom = None
        except KeyboardInterrupt:
            print("Client wird manuell beendet...")
            if self.__sock:
                self.__sock.close()
            srvCom = None

    def listen_to_server(self) -> None:
        global srvCom
        puffer = ""
        # t_end = time.time() + server_activity_period
        # while time.time() < t_end:
        while True:
            try:
                data = self.__sock.recv(1024).decode('utf-8')
                if not data:
                    print(f"\n[Info] Alte Verbindung für '{self.__name}' sauber beendet.\n$ ", end="")
                    self.__sock.close()
                    if srvCom is self:
                        srvCom = None
                    break
                puffer += data
                while "\0" in puffer:
                    msg, puffer = puffer.split("\0", 1)
                    self.packet_code_from_server(msg)

            except socket.timeout:
                print(f"Timeout in receive nach {time.asctime()}.\n$ ")
                self.__sock.close()
                if srvCom is self:
                    srvCom = None
                break
            except socket.error:
                print("\nVerbindung zum Server unerwartet abgebrochen.\n$ ", end="")
                self.__sock.close()
                if srvCom is self:
                    srvCom = None
                break
            except KeyboardInterrupt:
                print("Client wird manuell beendet...")
                self.__sock.close()
                if srvCom is self:
                    srvCom = None
                break

    def packet_code_from_server(self, msg: str) -> None:
        global srvCom
        try:
            cmd, data = msg.split("|", 1)
            match cmd:
                case "ERROR":
                    print(f"\nERROR Response from Server: {data}")
                    if self.__sock:
                        self.__sock.close()
                    if srvCom is self:
                        srvCom = None

                case "USERLIST":
                    with lock_USERLIST:
                        USERLIST.clear()
                        users = data.split(";")
                        for user in users:
                            entry = user.split(",")
                            if len(entry) == 3:
                                USERLIST[entry[0]] = {'ip': entry[1], 'udp_port': entry[2]}
                            else:
                                raise Exception("INVALID_FORMAT")

                case "UPDATE":
                    data = data.split("|")
                    if len(data) == 4:
                        success: bool
                        if (data[0] == "ADD"):
                            with lock_USERLIST:
                                if data[1] in USERLIST:
                                    success = False
                                else:
                                    USERLIST[data[1]] = {'ip': data[2], 'udp_port': data[3]}
                                    success = True

                        elif (data[0] == "REMOVE"):
                            with lock_USERLIST:
                                user = USERLIST.pop(data[1], None)
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
                            if srvCom is self:
                                srvCom = None
                    else:
                        raise Exception("INVALID_FORMAT")

                case "LOGOUT_SUCCESS":
                    print("Erfolgreich abgemeldet.")
                    if self.__sock:
                        self.__sock.close()
                    srvCom = None
                case "BROADCAST":
                    data = data.split("|", 1)
                    if len(data) >= 2:
                        print(f"User: {data[0]} send a Broadcast with: {data[1]}\n$ ")
                    else:
                        try:
                            self.__sock.send("ERROR|INVALID_BROADCAST_FORMAT\0".encode('utf-8'))
                        except socket.error:
                            self.__sock.close()
                            if srvCom is self:
                                srvCom = None

                case _:
                    raise Exception("INVALID_FORMAT")

        except Exception as e:
            match str(e):
                case "INVALID_FORMAT":
                    try:
                        self.__sock.send("ERROR|INVALID_FORMAT\0".encode('utf-8'))
                    except socket.error:
                        self.__sock.close()
                        if srvCom is self:
                            srvCom = None

    def send_global_message(self, text: str) -> None:
        global srvCom
        try:
            self.__sock.send(f"BROADCAST|{text}\0".encode('utf-8'))
        except socket.error:
            self.__sock.close()
            if srvCom is self:
                srvCom = None

    def disconnect(self) -> None:
        global srvCom
        try:
            self.__sock.send("LOGOUT\0".encode('utf-8'))
        except socket.error:
            self.__sock.close()
        if srvCom is self:
            srvCom = None


def list_all_cmds():
    print("Server Commands:")
    print("REGISTER|Nickname|IP-Adresse|UDP-Port")
    print("LOGOUT")
    print("BROADCAST|Nachricht")
    print("=================")
    print("Peer Commands:")
    print("HANDSHAKE|Nickname|TCP-Port")
    print("MSG|Nachricht")
    print("=================")
    print("misc commands:")
    print("EXIT (Exits the application, duh)")
    print("HELP (Prints this list of commands)")
    print("USERLIST (Prints all logged in users)")
    print("USER (Prints your current userinfo in case you forgot)")
    print("=================")


list_all_cmds()
while (True):
    try:
        data = input("$ ")
        if "|" in data:
            cmd, payload = data.split("|", 1)
        else:
            cmd, payload = data, ""

        match cmd:
            case "REGISTER":
                payload = payload.split("|")
                if len(payload) == 3:
                    if srvCom:
                        srvCom.disconnect()
                    srvCom = ServerCommunication(nickname=payload[0], ip=payload[1], udp_port=int(payload[2]))
                    srvCom.connect_and_register(SERVER_IP, SERVER_PORT)
                else:
                    raise Exception("INVALID_FORMAT")

            case "LOGOUT":
                if not payload:
                    if srvCom:
                        srvCom.disconnect()
                        srvCom = None
                else:
                    raise Exception("INVALID_FORMAT")
            case "BROADCAST":
                if payload:
                    if srvCom:
                        srvCom.send_global_message(payload)
                else:
                    raise Exception("INVALID_FORMAT")
            case "HELP":
                if not payload:
                    list_all_cmds()
                else:
                    raise Exception("INVALID_FORMAT")
            case "EXIT":
                if not payload:
                    exit(0)
                else:
                    raise Exception("INVALID_FORMAT")
            case "USER":
                if not payload:
                    if srvCom:
                        print(srvCom)
                else:
                    raise Exception("INVALID_FORMAT")
            case "USERLIST":
                if not payload:
                    if srvCom:
                        srvCom.print_USERLIST()
                else:
                    raise Exception("INVALID_FORMAT")
            case "HANDSHAKE":
                payload = payload.split("|")
                if len(payload) == 2:
                    if srvCom:
                        pass
                else:
                    raise Exception("INVALID_FORMAT")
            case "MSG":
                if payload:
                    if srvCom:
                        pass
                else:
                    raise Exception("INVALID_FORMAT")
            case _:
                print("I could not understand you")
    except Exception as e:
        match str(e):
            case "INVALID_FORMAT": print("INVALID_FORMAT")

    except KeyboardInterrupt:
        print("Server wird manuell beendet...")
        exit(0)
