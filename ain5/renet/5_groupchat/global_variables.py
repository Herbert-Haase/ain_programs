import threading
import re

SERVER_IP = '100.118.82.170'
SERVER_PORT = 50000
server_activity_period = 30
USERLIST = {}  # {name:{ip:ip,udp_port:port}}
lock_USERLIST = threading.Lock()

srvCom = None  # classinstance
udpListener = None  # classinstance
p2pManager = None  # classinstance


def list_all_cmds():
    print("Server Commands:")
    print("REGISTER|Nickname|IP-Adresse|UDP-Port|TCP-Port")
    print("LOGOUT")
    print("BROADCAST|Nachricht")
    print("=================")
    print("Peer Commands:")
    print("HANDSHAKE|Nickname")
    print("MSG|Name|Nachricht")
    print("=================")
    print("misc commands:")
    print("EXIT (Exits the application, duh)")
    print("HELP (Prints this list of commands)")
    print("USERLIST (Prints all logged in users)")
    print("USER (Prints your current userinfo in case you forgot)")
    print("=================")


def validate_ip(ip: str) -> bool:
    ip_regex = r'^(?:(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})\.){3}(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})$'
    if re.fullmatch(ip_regex, ip):
        return True
    else:
        return False


def validate_port(port) -> bool:
    try:
        udp_port = int(port)
    except ValueError:
        return False
    if (0 > udp_port or udp_port > 65535):
        return False
    else:
        return True
