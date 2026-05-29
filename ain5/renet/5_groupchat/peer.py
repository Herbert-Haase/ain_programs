from ServerCommunication import ServerCommunication
from UDPListener import UDPListener
from P2PManager import P2PManager
import global_variables as g


def main():

    g.list_all_cmds()
    while (True):
        # Test Server Connection
        if g.srvCom is None and len(g.USERLIST) > 0:
            print("\nServer-Verbindung verloren. Bereinige P2P-Subsystem...")
            with g.lock_USERLIST:
                g.USERLIST.clear()

            if g.udpListener:
                g.udpListener.stop()
            if g.p2pManager:
                g.p2pManager.close_all_chats()

        # CLI
        try:
            data = input("$ ")
            if "|" in data:
                cmd, payload = data.split("|", 1)
            else:
                cmd, payload = data, ""
            match cmd:
                case "REGISTER":
                    payload = payload.split("|")
                    if len(payload) == 4:
                        name = payload[0]
                        if g.srvCom:
                            g.srvCom.disconnect()
                        if not g.validate_ip(payload[1]):
                            raise Exception("INVALID_IP")
                        ip = payload[1]
                        if not g.validate_port(payload[2]):
                            raise Exception("INVALID_PORT")
                        udp = int(payload[2])
                        if not g.validate_port(payload[3]):
                            raise Exception("INVALID_PORT")
                        tcp = int(payload[3])
                    # UDPListener
                        g.udpListener = UDPListener(ip=ip, udp=udp, tcp=tcp)
                        g.udpListener.start()
                    # P2PManager
                        g.p2pManager = P2PManager(name=name, ip=ip, tcp=tcp)
                        g.p2pManager.start_server()
                    # ServerCommunication
                        g.srvCom = ServerCommunication(nickname=name, ip=ip, udp_port=udp, tcp_port=tcp)
                        print(f"Trying to connect to the server at:{g.SERVER_IP}:{g.SERVER_PORT}")
                        g.srvCom.connect_and_register(g.SERVER_IP, g.SERVER_PORT)
                    else:
                        raise Exception("INVALID_FORMAT")

                case "LOGOUT":
                    if not payload:
                        if g.srvCom:
                            g.srvCom.disconnect()
                            g.srvCom = None
                    else:
                        raise Exception("INVALID_FORMAT")
                case "BROADCAST":
                    if payload:
                        if g.srvCom:
                            g.srvCom.send_global_message(payload)
                    else:
                        raise Exception("INVALID_FORMAT")
                case "HELP":
                    if not payload:
                        g.list_all_cmds()
                    else:
                        raise Exception("INVALID_FORMAT")
                case "EXIT":
                    if not payload:
                        exit(0)
                    else:
                        raise Exception("INVALID_FORMAT")
                case "USER":
                    if not payload:
                        if g.srvCom:
                            print(g.srvCom)
                    else:
                        raise Exception("INVALID_FORMAT")
                case "USERLIST":
                    if not payload:
                        if g.srvCom:
                            g.srvCom.print_USERLIST()
                    else:
                        raise Exception("INVALID_FORMAT")
                case "HANDSHAKE":
                    with g.lock_USERLIST:
                        if not payload or not g.USERLIST or (payload not in g.USERLIST):
                            raise Exception("Unknown Name")
                    g.p2pManager.send_handshake(payload)
                case "MSG":
                    name, msg = payload.split("|", 1)
                    with g.lock_USERLIST:
                        if not name or not g.USERLIST or (name not in g.USERLIST):
                            raise Exception("Unknown Name")
                        if not msg:
                            raise Exception("INVALID_FORMAT")
                    g.p2pManager.send_message(name, msg)
                case _:
                    print("I could not understand you")
        except Exception as e:
            match str(e):
                case "INVALID_FORMAT": print("INVALID_FORMAT")
                case "INVALID_PORT": print("INVALID_PORT")
                case "INVALID_IP": print("INVALID_IP")
                case "Unknown Name": print("Unknown Name")
                case _: print(f"Python-Fehler: {repr(e)}")

        except KeyboardInterrupt:
            print("Peer wird manuell beendet...")
            exit(0)


if __name__ == "__main__":
    main()
