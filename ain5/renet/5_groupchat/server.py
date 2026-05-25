import time
import threading
import socket
from typing import Any

SERVER_IP = '127.0.0.1'
SERVER_PORT = 50000
server_activity_period = 30
USERLIST = {}
lock_USERLIST = threading.Lock()

t_end = time.time() + server_activity_period  # Ende der Aktivitätsperiode


def listen(sock: socket.socket) -> None:
    print('Listening on Port ', SERVER_PORT, ' for incoming TCP connections')
    sock.listen(1)

    while time.time() < t_end:
        try:
            client_socket, addr = sock.accept()
            t = threading.Thread(target=receive, args=(client_socket, addr))
            t.start()
        except socket.timeout:
            print(f"Timeout after {time.asctime()}")

    sock.close()


def receive(sock: socket.socket, addr: tuple[str, int]) -> None:
    puffer = ""
    while time.time() < t_end:
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
    with lock_USERLIST:
        for nick, user in USERLIST.items():
            if user["tcp_socket"] == sock:
                name_to_remove = nick
                break
        if name_to_remove:
            user_to_remove = USERLIST.pop(name_to_remove, None)

    if name_to_remove and user_to_remove:
        send_userlist_change("REMOVE", name_to_remove, user_to_remove)


def packet_code(data: str, sock: socket.socket, addr: tuple[str, int]) -> None:
    try:
        data = data.split("|")
        match data[0]:
            case "REGISTER":
                if len(data) != 4:
                    raise Exception("INVALID_FORMAT")

                register(data[1], data[2], data[3], sock)
            case "LOGOUT":
                logout(sock)
            case "BROADCAST":
                if len(data) != 2:
                    raise Exception("INVALID_FORMAT")

                broadcast(data[1], sock)
            case _:
                raise Exception("INVALID_FORMAT")
    except Exception as e:
        match str(e):
            case "INVALID_FORMAT": send_back_error("ERROR|INVALID_FORMAT\0", sock)
            case "INVALID_PORT": send_back_error("ERROR|INVALID_PORT\0", sock)


def send_whole_userlist(nickname: str) -> None:
    with lock_USERLIST:
        eintraege = [f"{nick},{info['ip']},{info['udp_port']}" for nick, info in USERLIST.items()]
        update = "USERLIST|" + ";".join(eintraege) + "\0"
        sock = USERLIST[nickname]["tcp_socket"]
    try:
        sock.send(update.encode())
    except socket.error:
        user = {}
        sock.close()
        with lock_USERLIST:
            user = USERLIST.pop(nickname, None)
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
    with lock_USERLIST:
        for nick, active_user in USERLIST.items():
            if nick != name and active_user["tcp_socket"]:
                active_sockets.append((nick, active_user["tcp_socket"]))

    for nick, client_sock in active_sockets:
        try:
            client_sock.send(update.encode())
        except socket.error:
            dead_clients.append(nick)

    if dead_clients:
        with lock_USERLIST:
            for nick in dead_clients:
                if nick in USERLIST:
                    USERLIST[nick]["tcp_socket"].close()
                    dead_users.append(USERLIST.pop(nick, None))

        for nick, d_user in zip(dead_clients, dead_users):
            send_userlist_change("REMOVE", nick, d_user)


def register(nickname: str, ip: str, udp_port: str, sock: socket.socket) -> None:
    user = {}
    try:
        with lock_USERLIST:
            if nickname in USERLIST:
                raise Exception("NAME_ALREADY_USED")
            if int(udp_port) < 0 or int(udp_port) > 65535:
                raise Exception("INVALID_PORT")
            user = {"ip": ip, "udp_port": udp_port, "tcp_socket": sock}
            USERLIST[nickname] = user
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
        with lock_USERLIST:
            for nick, user in USERLIST.items():
                if user["tcp_socket"] == sock:
                    name = nick
            if not name:
                raise Exception("LOGOUT_FAILED")
            loggedout_user = USERLIST.pop(name, None)
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

    with lock_USERLIST:
        for nick, user in USERLIST.items():
            if user["tcp_socket"] == sock:
                nickname = nick
        if not nickname:
            send_back_error("ERROR|INVALID_BROADCAST_FORMAT\0", sock)
            return

        for nick, user in USERLIST.items():
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
        with lock_USERLIST:
            for nick in dead_clients:
                if nick in USERLIST:
                    USERLIST[nick]["tcp_socket"].close()
                    dead_users.append(USERLIST.pop(nick, None))
        for nick, user in zip(dead_clients, dead_users):
            send_userlist_change("REMOVE", nick, user)


def send_back_error(msg: str, sock: socket.socket) -> None:
    try:
        sock.send(msg.encode())
    except socket.error:
        sock.close()
        name_to_remove = None
        user_to_remove = None

        with lock_USERLIST:
            for nick, user in USERLIST.items():
                if user["tcp_socket"] == sock:
                    name_to_remove = nick
                    break
            if name_to_remove:
                user_to_remove = USERLIST.pop(name_to_remove, None)

        if name_to_remove and user_to_remove:
            send_userlist_change("REMOVE", name_to_remove, user_to_remove)


for i in range(100):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind((SERVER_IP, SERVER_PORT))
        print(f"Server erfolgreich an Port {SERVER_PORT} gebunden.")
        break
    except OSError:
        print(f"Port {SERVER_PORT} besetzt, versuche nächsten...")
        SERVER_PORT += 1
        sock.close()
listen(sock)
