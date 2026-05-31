#!/usr/bin/python3

import subprocess
import time
import threading
import socket
from typing import Any
import re
import global_variables as g


class BoundSocket(socket.socket):
    def __init__(self, family=socket.AF_INET, type=socket.SOCK_STREAM, proto=0, fileno=None):
        super().__init__(family, type, proto, fileno)
        self.is_bound = False

    def bind(self, address):
        super().bind(address)
        self.is_bound = True


def get_meshnet_ip(interface_name='nordlynx') -> str:
    try:
        cmd = ["ip", "-4", "addr", "show", "dev", interface_name]
        output = subprocess.check_output(cmd, stderr=subprocess.DEVNULL).decode('utf-8')

        match = re.search(r"inet\s+([0-9.]+)", output)
        if match:
            return match.group(1)
    except subprocess.CalledProcessError:
        pass

    return '0.0.0.0'


def main():

    PORT = g.SERVER_PORT
    # IP = g.SERVER_IP
    SERVER_IP = get_meshnet_ip('nordlynx')

    # t_end = time.time() + g.server_activity_period  # Ende der Aktivitätsperiode

    def listen(sock: socket.socket) -> None:
        print('Listening on Port ', PORT, ' for incoming TCP connections')
        sock.listen(1)

        # while time.time() < t_end:
        while True:
            try:
                client_socket, addr = sock.accept()
                t = threading.Thread(target=receive, daemon=True, args=(client_socket, addr))
                t.start()
            except socket.timeout:
                print(f"Timeout after {time.asctime()}")
            except KeyboardInterrupt:
                print("Server wird manuell beendet...")
                exit(0)

        sock.close()

    def receive(sock: socket.socket, addr: tuple[str, int]) -> None:
        puffer = ""
        # while time.time() < t_end:
        while True:
            try:
                data = sock.recv(1024).decode('utf-8')
                if not data:
                    print('Connection closed from other side')
                    break
                puffer += data
                while "\0" in puffer:
                    msg, puffer = puffer.split("\0", 1)
                    packet_code(msg, sock, addr)

            except socket.timeout:
                print(f"Timeout in receive nach {time.asctime()}")
                break
            except socket.error:
                print(f"Verbindung zu {addr} unerwartet abgebrochen.")
                break
            except KeyboardInterrupt:
                print("Server wird manuell beendet...")
                break

        sock.close()

        name_to_remove = None
        user_to_remove = None
        with g.lock_USERLIST:
            for nick, user in g.USERLIST.items():
                if user["tcp_socket"] == sock:
                    name_to_remove = nick
                    break
            if name_to_remove:
                user_to_remove = g.USERLIST.pop(name_to_remove, None)

        if name_to_remove and user_to_remove:
            send_userlist_change("REMOVE", name_to_remove, user_to_remove)

    def packet_code(data: str, sock: socket.socket, addr: tuple[str, int]) -> None:
        try:
            if "|" in data:
                cmd, payload = data.split("|", 1)
            else:
                cmd, payload = data, ""

            match cmd:
                case "REGISTER":
                    print("REGISTER")
                    if not payload:
                        raise Exception("INVALID_FORMAT")
                    args = payload.split("|")
                    if len(args) != 3:
                        raise Exception("INVALID_FORMAT")
                    register(args[0], args[1], args[2], sock)

                case "LOGOUT":
                    print("LOGOUT")
                    logout(sock)

                case "BROADCAST":
                    if not payload:
                        raise Exception("INVALID_FORMAT")
                    print("BROADCAST")
                    broadcast(payload, sock)

                case "SUCCESS":
                    print("UPDATE_SUCCESS")

                case _:
                    raise Exception("INVALID_FORMAT")

        except Exception as e:
            match str(e):
                case "INVALID_FORMAT":
                    print("INVALID_FORMAT")
                    send_back_error("ERROR|INVALID_FORMAT\0", sock)
                case "INVALID_PORT":
                    print("INVALID_PORT")
                    send_back_error("ERROR|INVALID_PORT\0", sock)
                case _: print(f"Python-Fehler: {repr(e)}")

    def send_whole_userlist(nickname: str) -> None:
        with g.lock_USERLIST:
            eintraege = [f"{nick},{info['ip']},{info['udp_port']}" for nick, info in g.USERLIST.items()]
            update = "USERLIST|" + ";".join(eintraege) + "\0"
            sock = g.USERLIST[nickname]["tcp_socket"]
        try:
            sock.send(update.encode())
        except socket.error:
            user = {}
            sock.close()
            with g.lock_USERLIST:
                user = g.USERLIST.pop(nickname, None)
            if user is None:
                return
            send_userlist_change("REMOVE", nickname, user)

    def send_userlist_change(action: str, name: str, user: dict[str, Any]) -> None:
        if user is None:
            return

        dead_clients = []
        dead_users = []
        update = f"UPDATE|{action}|{name}|{user['ip']}|{user['udp_port']}\0"

        active_sockets = []
        with g.lock_USERLIST:
            for nick, active_user in g.USERLIST.items():
                if nick != name and active_user["tcp_socket"]:
                    active_sockets.append((nick, active_user["tcp_socket"]))

        for nick, client_sock in active_sockets:
            try:
                client_sock.send(update.encode())
            except socket.error:
                dead_clients.append(nick)

        if dead_clients:
            with g.lock_USERLIST:
                for nick in dead_clients:
                    if nick in g.USERLIST:
                        g.USERLIST[nick]["tcp_socket"].close()
                        dead_users.append(g.USERLIST.pop(nick, None))

            for nick, d_user in zip(dead_clients, dead_users):
                send_userlist_change("REMOVE", nick, d_user)

    def register(nickname: str, ip: str, udp_port: str, sock: socket.socket) -> None:
        user = {}
        ip_regex = r'^(?:(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})\.){3}(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})$'
        try:
            with g.lock_USERLIST:
                if nickname in g.USERLIST:
                    raise Exception("NAME_ALREADY_USED")
                try:
                    udp = int(udp_port)
                except ValueError:
                    raise Exception("INVALID_PORT")
                if udp < 0 or udp > 65535:
                    raise Exception("INVALID_PORT")
                if re.fullmatch(ip_regex, ip) is None:
                    raise Exception("INVALID_FORMAT")
                user = {"ip": ip, "udp_port": udp, "tcp_socket": sock}
                g.USERLIST[nickname] = user
            send_whole_userlist(nickname)
            send_userlist_change("ADD", nickname, user)
        except Exception as e:
            match str(e):
                case "NAME_ALREADY_USED": send_back_error("ERROR|NAME_ALREADY_USED\0", sock)
                case "INVALID_FORMAT": send_back_error("ERROR|INVALID_FORMAT\0", sock)
                case "INVALID_PORT": send_back_error("ERROR|INVALID_PORT\0", sock)

    def logout(sock: socket.socket) -> None:
        name = ""
        loggedout_user = {}
        try:
            with g.lock_USERLIST:
                for nick, user in g.USERLIST.items():
                    if user["tcp_socket"] == sock:
                        name = nick
                if not name:
                    raise Exception("LOGOUT_FAILED")
                loggedout_user = g.USERLIST.pop(name, None)
                if not loggedout_user:
                    raise Exception("LOGOUT_FAILED")
                try:
                    sock.send("LOGOUT_SUCCESS\0".encode())
                except socket.error:
                    pass
            send_userlist_change("REMOVE", name, loggedout_user)
        except Exception as e:
            match str(e):
                case "LOGOUT_FAILED": send_back_error("ERROR|LOGOUT_FAILED\0", sock)

        sock.close()

    def broadcast(data: str, sock: socket.socket) -> None:
        dead_clients = []
        nickname = None
        targets = []

        with g.lock_USERLIST:
            for nick, user in g.USERLIST.items():
                if user["tcp_socket"] == sock:
                    nickname = nick
            if not nickname:
                send_back_error("ERROR|INVALID_BROADCAST_FORMAT\0", sock)
                return

            for nick, user in g.USERLIST.items():
                if nick != nickname:
                    targets.append((nick, user["tcp_socket"]))

        msg = f"BROADCAST|{nickname}|{data}\0"
        for nick, client_sock in targets:
            try:
                client_sock.send(msg.encode())
            except socket.error:
                dead_clients.append(nick)

        if dead_clients:
            dead_users = []
            with g.lock_USERLIST:
                for nick in dead_clients:
                    if nick in g.USERLIST:
                        g.USERLIST[nick]["tcp_socket"].close()
                        dead_users.append(g.USERLIST.pop(nick, None))
            for nick, user in zip(dead_clients, dead_users):
                send_userlist_change("REMOVE", nick, user)

    def send_back_error(msg: str, sock: socket.socket) -> None:
        try:
            sock.send(msg.encode())
        except socket.error:
            sock.close()
            name_to_remove = None
            user_to_remove = None

            with g.lock_USERLIST:
                for nick, user in g.USERLIST.items():
                    if user["tcp_socket"] == sock:
                        name_to_remove = nick
                        break
                if name_to_remove:
                    user_to_remove = g.USERLIST.pop(name_to_remove, None)

            if name_to_remove and user_to_remove:
                send_userlist_change("REMOVE", name_to_remove, user_to_remove)

    for _ in range(100):
        try:
            sock = BoundSocket(socket.AF_INET, socket.SOCK_STREAM)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind((SERVER_IP, PORT))
            print(f"Server erfolgreich an {SERVER_IP}:{PORT} gebunden.")
            break
        except OSError:
            print(f"Port {PORT} besetzt, versuche nächsten...")
            PORT += 1
            sock.close()

    if sock and sock.is_bound:
        listen(sock)
    else:
        print(f"Alle Ports von {g.SERVER_PORT} bis {PORT} durchprobiert, keinen Freien gefunden\n")


if __name__ == "__main__":
    main()
