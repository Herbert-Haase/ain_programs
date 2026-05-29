Hier ist die Schritt-für-Schritt-Anleitung, um das Meshnet über das Terminal (CLI) einzurichten und für eure Laborübung zu konfigurieren:

### 1. NordVPN installieren & Dienst starten

Falls noch nicht geschehen, den NordVPN-Client installieren, den Hintergrunddienst aktivieren und deinen User zur Gruppe hinzufügen:

```bash
yay -S nordvpn-bin
sudo systemctl enable --now nordvpnd
sudo usermod -aG nordvpn $USER

```

*(Danach einmal aus- und wieder einloggen oder die Shell neu starten, damit die Gruppenrechte greifen).*

### 2. Einloggen & Meshnet aktivieren

Nutze für den Login die bereitgestellten Daten aus der Vorlesung (`komnetze.htwg+x@gmail.com` und `PasswortfuerdieRNVorlesung`):

```bash
nordvpn login
nordvpn meshnet on

```

*Hinweis:* Der Login-Befehl gibt dir heute meist einen Link aus, den du im Browser öffnen musst, um das Auth-Token zu erhalten.

### 3. Verbindungen und IPs prüfen

Sobald dein Teampartner (oder dein Zweitgerät) mit **demselben** Account eingeloggt ist und Meshnet aktiviert hat, werden die Geräte automatisch gekoppelt. Du siehst sie mit:

```bash
nordvpn meshnet peer list

```

Hier siehst du die vergebene Meshnet-IP (Format: `100.x.x.x`) und den internen Hostnamen (z. B. `ubuntu-desktop.nord`) des Partners.

Prüfe die Verbindung mit einem einfachen Ping auf die `100.x.x.x`-IP des Partners:

```bash
ping 100.x.x.x

```

### 4. Remote-Access (Port-Zugriff) erlauben

Standardmäßig blockiert das Meshnet eingehende Port-Verbindungen. Damit eure Python-Sockets (TCP für Chat, UDP für Handshake) Daten empfangen können, müsst ihr euch gegenseitig den Zugriff erlauben:

```bash
# Erlaubt dem spezifischen Peer den Zugriff auf deine lokalen Ports
nordvpn meshnet peer local allow <partner-hostname-oder-ip>
sudo systemctl stop firewalld

```

*(Alternativ, je nach Version des CLI-Clients, läuft das über `nordvpn meshnet peer update <hostname> --allow-lan-access=true` oder eine interaktive Abfrage).*

### 5. Integration im Python-Code

Damit das P2P-System funktioniert, müsst ihr die Meshnet-IPs anstelle eurer lokalen Netz-IPs (`192.168.x.x`) verwenden:

1. **Server-Host:** In der `global_variables.py` muss die `SERVER_IP` auf die Meshnet-IP desjenigen gesetzt werden, der den Server startet (oder testweise auf `'0.0.0.0'`, damit der Server auf allen Interfaces lauscht).
2. **Peer-Registrierung:** Wenn du den Befehl `REGISTER|Nickname|IP-Adresse|UDP-Port|TCP-Port` ausführst, musst du **deine eigene** `100.x.x.x`-Meshnet-IP mitgeben. Der Server speichert diese in der `USERLIST` und verteilt sie an die anderen Clients. Wenn ein anderer Client dir dann eine Nachricht senden will, nutzt er automatisch den verschlüsselten Meshnet-Tunnel.
