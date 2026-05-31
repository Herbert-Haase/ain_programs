import threading
import socket

import global_variables as g


class UDPListener:
    def __init__(self, ip: str, udp: int, tcp: int, sock: socket.socket = None):
        self.__ip = ip
        self.__udp = udp
        self.__tcp = tcp
        self.udp_sock = sock

    def start(self) -> None:
        t = threading.Thread(target=self.listen_to_peer, daemon=True)
        t.start()

    def stop(self) -> None:
        if hasattr(self, "udp_sock") and self.udp_sock:
            try:
                self.udp_sock.close()
            except Exception as e:
                print(f"Python-Fehler: {repr(e)}")

    def listen_to_peer(self) -> None:
        try:
            try:
                self.udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
                self.udp_sock.bind((self.__ip, self.__udp))
                self.udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            except socket.error:
                print("UDP Port bereits besetzt\n$ ", end="")
                self.udp_sock.close()
                return
            while 1:
                message, addr = self.udp_sock.recvfrom(2048)
                self.packet_code_from_peer(message.decode('utf-8'), addr)

        except socket.error:
            print("Peer listening unerwartet abgebrochen\n$ ", end="")
            self.udp_sock.close()
        except KeyboardInterrupt:
            print("Client wird manuell beendet...")
            self.udp_sock.close()

    def packet_code_from_peer(self, msg: str, addr: (str, int)) -> None:
        ip, udp = addr
        msg = msg.rstrip("\0")
        try:
            cmd, data = msg.split("|", 1)
            match cmd:
                case "ERROR":
                    print(f"\nERROR Response from Peer: {data}")
                    return
                case "HANDSHAKE":
                    if "|" in data:
                        print(data)
                        data = data.split("|")
                        if len(data) != 2 or data[0] is None:
                            raise Exception("INVALID_HANDSHAKE_FORMAT")
                        if not g.validate_port(data[1]):
                            raise Exception("INVALID_HANDSHAKE_FORMAT")
                        name, tcp = data
                        with g.lock_USERLIST:
                            if name not in g.USERLIST:
                                raise Exception("UNKNOWN_NICKNAME")
                            g.USERLIST[name]["tcp_port"] = int(tcp)

                            print(f"USER:{name} hat dir eine Chatanfrage gesendet\n$ ")
                            self.udp_sock.sendto(f"HANDSHAKE_RETURN|{self.__tcp}\0".encode("utf-8"), (ip, udp))

                case "HANDSHAKE_RETURN":
                    if not g.validate_port(data):
                        raise Exception("INVALID_HANDSHAKE_FORMAT")
                    for name, event in list(g.p2pManager.PENDING_HANDSHAKES.items()):
                        with g.lock_USERLIST:
                            user = g.USERLIST[name]
                            if (user["ip"] == ip and user["udp_port"] == udp):
                                user["tcp_port"] = int(data)
                                event.set()
                                break

        except Exception as e:
            match str(e):
                case "INVALID_HANDSHAKE_FORMAT":
                    try:
                        self.udp_sock.sendto("ERROR|INVALID_HANDSHAKE_FORMAT\0".encode('utf-8'), (ip, udp))
                    except socket.error:
                        self.udp_sock.close()
                case "ERROR|UNKNOWN_NICKNAME\0":
                    try:
                        self.udp_sock.sendto("ERROR|UNKNOWN_NICKNAME\0".encode('utf-8'), (ip, udp))
                    except socket.error:
                        self.udp_sock.close()
                case _: print(f"Python-Fehler: {repr(e)}")
