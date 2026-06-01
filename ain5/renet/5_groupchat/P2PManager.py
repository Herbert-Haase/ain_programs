import threading
import socket

import global_variables as g


class P2PManager:
    def __init__(self, name: str = 'nicky', ip: str = '127.0.0.1', tcp: int = 50000, sock: socket.socket = None):
        self.__name = name
        self.__ip = ip
        self.__tcp = tcp
        self.PENDING_HANDSHAKES = {}  # {name:event}
        self.ACTIVE_CHATS = {}  # {name:socket}
        self.lock_chats = threading.Lock()
        self.srv_sock = sock

    def start_server(self) -> None:
        t = threading.Thread(target=self.__listen_tcp_loop, daemon=True)
        t.start()

    def __listen_tcp_loop(self) -> None:
        try:
            self.srv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.srv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.srv_sock.bind((self.__ip, self.__tcp))
            self.srv_sock.listen(5)

            while True:
                sock, addr = self.srv_sock.accept()
                peer_name = None
                with g.lock_USERLIST:
                    for name, user in g.USERLIST.items():
                        if user["ip"] == addr[0]:
                            peer_name = name
                            break

                if peer_name:
                    with self.lock_chats:
                        self.ACTIVE_CHATS[peer_name] = sock
                    print(f"CHAT: Verbindung von USER:{peer_name} akzeptiert\n$ ")
                    t = threading.Thread(target=self.__receive, args=(peer_name, sock), daemon=True)
                    t.start()
                else:
                    sock.close()
        except socket.error:
            if hasattr(self, 'srv_sock') and self.srv_sock._closed:
                return
            print("__listen_tcp_loop:Verbindungsproblem")
        except socket.timeout:
            print("__listen_tcp_loop:Timeout")
        except KeyboardInterrupt:
            pass
            exit(0)

    def __receive(self, name: str, sock: socket.socket) -> None:
        puffer = ""
        try:
            while True:
                data = sock.recv(2048).decode('utf-8')
                if not data:
                    print(f'\nConnection closed from USER:{name}\n$ ', end="")
                    break
                puffer += data
                while "\0" in puffer:
                    msg, puffer = puffer.split("\0", 1)
                    self.packet_code(msg, name, sock)
        except socket.error:
            print(f"\nCHAT:Netzwerkfehler mit USER:{name}\n$ ", end="")
        finally:
            sock.close()
            with self.lock_chats:
                self.ACTIVE_CHATS.pop(name, None)

    def send_handshake(self, name: str):
        t = threading.Thread(target=self.__wait_handshake, daemon=True, args=(name,))
        t.start()

    def __wait_handshake(self, name: str):
        ip = None
        udp = None
        with g.lock_USERLIST:
            ip = g.USERLIST[name]["ip"]
            udp = g.USERLIST[name]["udp_port"]

        try:
            if g.udpListener and g.udpListener.udp_sock:
                self.PENDING_HANDSHAKES[name] = threading.Event()
                g.udpListener.udp_sock.sendto(f"HANDSHAKE|{self.__name}|{self.__tcp}\0".encode("utf-8"), (ip, udp))
                if self.PENDING_HANDSHAKES[name].wait(timeout=10):
                    self.PENDING_HANDSHAKES.pop(name, None)
                    print(f"Handshake von USER:{name} bestätigt. Warte auf eingehende TCP-Verbindung...\n$ ", end="")
                else:
                    self.PENDING_HANDSHAKES.pop(name, None)
                    print(f"Handshake-Timeout mit USER:{name}\n$ ", end="")
        except socket.error:
            print(f"Handshake mit USER:{name} fehlgeschlagen beim Senden.\n$ ")

    def connect_to_peer(self, name: str, ip: str, tcp: int) -> None:
        t = threading.Thread(target=self.__execute_connect, args=(name, ip, tcp), daemon=True)
        t.start()

    def __execute_connect(self, name: str, ip: str, tcp: int) -> None:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind((self.__ip, 0))
            sock.connect((ip, tcp))

            with self.lock_chats:
                self.ACTIVE_CHATS[name] = sock

            print(f"CHAT: Verbindung mit USER:{name} erfolgreich aufgebaut\n$ ", end="")
            self.__receive(name, sock)

        except socket.error as e:
            print(f"CHAT: Verbindungsaufbau zu USER:{name} fehlgeschlagen: {e}\n$ ", end="")

    def __start_chat(self, name: str, ip: str, tcp: int):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.bind((self.__ip, 0))
            sock.connect((ip, tcp))
            with self.lock_chats:
                self.ACTIVE_CHATS[name] = sock
            print(f"CHAT: Verbindung mit USER:{name} erfolgreich aufgebaut\n$ ", end="")
            self.__receive(name, sock)

        except socket.error:
            print(f"CHAT:Netzwerkfehler mit USER:{name}")

    def packet_code(self, data: str, name: str, sock: socket.socket):
        try:
            if "|" in data:
                cmd, payload = data.split("|", 1)
            if not payload:
                raise Exception("INVALID_MESSAGE_FORMAT")
            match cmd:
                case "MSG":
                    print(f"CHAT:USER:{name} SEND:{payload}\n$ ", end="")
                    sock.send("SUCCESS|MESSAGE_RECEIVED\0".encode('utf-8'))
                case "SUCCESS":
                    print(f"CHAT:USER:{name} hat deine MSG erhalten\n$ ", end="")
                case "ERROR":
                    print(f"CHAT:USER:{name} ERROR:{payload}\n$ ", end="")
                case _:
                    raise Exception("INVALID_MESSAGE_FORMAT")

        except Exception as e:
            match str(e):
                case "INVALID_MESSAGE_FORMAT":
                    sock.send("ERROR|INVALID_MESSAGE_FORMAT\0".encode('utf-8'))
                case _: print(f"Python-Fehler: {repr(e)}")

    def send_message(self, name: str, msg: str):
        try:
            sock = self.ACTIVE_CHATS[name]
            if sock:
                sock.send(f"MSG|{msg}\0".encode('utf-8'))

        except socket.error:
            print(f"CHAT:Netzwerkfehler mit USER:{name}\n$ ", end="")
            sock.close()
            with self.lock_chats:
                self.ACTIVE_CHATS.pop(name)
        except socket.timeout:
            print(f"CHAT:Timeout beim Verbingungsaufbau mit USER:{name}\n$ ", end="")
            sock.close()
            with self.lock_chats:
                self.ACTIVE_CHATS.pop(name)

    def close_all_chats(self) -> None:
        if hasattr(self, 'srv_sock') and self.srv_sock:
            try:
                self.srv_sock.close()
            except Exception as e:
                print(f"Python-Fehler: {repr(e)}")
        with self.lock_chats:
            for name, sock in list(self.ACTIVE_CHATS.items()):
                try:
                    sock.close()
                except socket.error:
                    pass
            self.ACTIVE_CHATS.clear()
