import time
import threading
import socket

SERVER_IP = '127.0.0.1'
SERVER_PORT = 50000
server_activity_period = 30
USERLIST = []
lock_USERLIST = threading.Lock()

t_end=time.time()+server_activity_period # Ende der Aktivitätsperiode


def listen(sock):
    sock.bind((SERVER_IP, SERVER_PORT))
    print('Listening on Port ', SERVER_PORT, ' for incoming TCP connections')
    sock.listen(1)

    while time.time()<t_end:
        try:
            client_socket, addr = sock.accept()
            t = threading.Thread(target=receive, args=(client_socket,addr))
            t.start()
        except socket.timeout:
            print(f"Timeout after {time.asctime()}")

    sock.close()

def receive(sock,addr):
    while time.time()<t_end:
        try:
            data = sock.recv(1024)
            if not data:
                print('Connection closed from other side');
                sock.close()
                break
            packet_code(data.decode('utf-8'),addr)

        except socket.timeout:
            print(f"Timeout after {time.asctime()}")

    if sock:
        sock.close()

def packet_code(data,addr):
    try:
        if "|" not in data:
            raise Exception("INVALID_FORMAT")
        data = data.split("|")
        match data[0]:
            case "REGISTER":
                if len(data) != 4 or data[3][-1] != "\0":
                    raise Exception("INVALID_FORMAT")


                register(data[1],data[2],data[3])
            case "LOGOUT":
                logout(addr)
            case "BROADCAST":
                if len(data) != 2 or data[1][-1] == "\0":
                    raise Exception("INVALID_FORMAT")

                data = data.strip('\x00')
                broadcast(addr,data[1])
            case _:
                raise Exception("INVALID_FORMAT")
    except Exception as e:
        match str(e):
            case "INVALID_FORMAT": send_back_error("ERROR|INVALID_FORMAT\0",addr)
            case "INVALID_PORT":   send_back_error("ERROR|INVALID_PORT\0",addr)

def send_whole_userlist(users,addr):
    update = "USERLIST|"
    with lock_USERLIST:
        for user in users:
            update += ",".join(user) + ";"
        update = update[:-1] + "\0"
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
                sock.sendto(update.encode(), addr)

def send_userlist_change(action, user):
    update = f"UPDATE|{action}|" + "|".join(user) + "\0"
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        with lock_USERLIST:
            for user in USERLIST:
                sock.sendto(update.encode(), (user[1], user[2]))


def register(nickname,ip,udp_port):
    try:
        lock_USERLIST.acquire()
        for user in USERLIST:
            if user[0] == nickname:
                raise Exception("NAME_ALREADY_USED")
            if int(udp_port) < 0 or int(udp_port) > 65535:
                raise Exception("INVALID_PORT")
        user = (nickname,ip,udp_port)
        USERLIST.append(user)
        lock_USERLIST.release()
        send_whole_userlist(USERLIST,(ip,udp_port))
    except Exception as e:
        lock_USERLIST.release()
        match str(e):
            case "NAME_ALREADY_USED": send_back_error("ERROR|NAME_ALREADY_USED\0",(ip,udp_port))
            case "INVALID_FORMAT": send_back_error("ERROR|INVALID_FORMAT\0",(ip,udp_port))
            case "NAME_ALREADY_USED": send_back_error("ERROR|INVALID_PORT_ERROR\0",(ip,udp_port))

def logout(addr):
    ip, _ = addr
    try:
        lock_USERLIST.acquire()
        list_len = len(USERLIST)
        USERLIST[:] = [user for user in USERLIST if user[1] != ip]
        if len(USERLIST) == list_len:
            raise Exception("LOGOUT_FAILED")
        lock_USERLIST.release()
    except Exception as e:
        lock_USERLIST.release()
        match str(e):
            case "LOGOUT_FAILED": send_back_error("ERROR|LOGOUT_FAILED\0",addr)

def broadcast(addr, data):
    try:
        ip, _ = addr
        nickname = ""
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            with lock_USERLIST:
                for user in USERLIST:
                    if ip == user[1]:
                        nickname = user[0]
                if not nickname: raise Exception("INVALID_BROADCAST_FORMAT")
                for user in USERLIST:
                    if (user[0] != nickname):
                        msg = f"BROADCAST|{nickname}|{data}\0"
                        sock.sendto(msg.encode(), (user[1], user[2]))
    except Exception as e:
        lock_USERLIST.release()
        match str(e):
            case "INVALID_BROADCAST_FORMAT": send_back_error("ERROR|INVALID_BROADCAST_FORMAT\0",addr)

def send_back_error(msg,addr):
    sock.sendto(msg.encode(), addr)

for i in range(100):
    SERVER_PORT = SERVER_PORT + i
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listen(sock)
