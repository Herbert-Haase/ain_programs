Aufgabe 1)
Sie sollen das Vokabular eines Textes mit ANTLR4 Lexer-Regeln beschreiben und eine Anwendung erstellen, die einen entsprechenden Text einliest und als Tokenfolge wieder ausgibt (siehe ExprTokenizer.java aus der Vorlesung).

Zwei Texte stehen zur Auswahl (natürlich dürfen Sie auch beide bearbeiten): Informationen aus der Abfahrtstafel Konstanz der Deutschen Bahn in abfahrten-kn.txt oder Angaben zu den Öffnungszeiten der Mainau-Gastronomie in mainau-gastronomie.txt. Die beiden Texte finden Sie auf der Moodle-Seite.

Den Text abfahrten-kn.txt habe ich 2024 aus der Webseite https://www.bahn.de/buchung/abfahrten-ankuenfte für den Bahnhof Konstanz extrahiert. Sie können gerne weitere Abfahrten ergänzen.

Den Text mainau-gastronomie.txt habe ich 2024 aus der Webseite https://www.mainau.de/de/oeffnungszeiten extrahiert. Sie können sich gerne weitere gastronomische Angebote ausdenken.

Welche Vokabular-Kategorien von Folie 2-4 kommen im Text vor? Bedenken Sie dazu, dass ja nicht nur der eine vorgegebene Text erfolgreich zerlegt werden soll, sondern auch andere Beispieltexte der gleichen Art.

Last modified: Friday, 20 March 2026, 11:47 AM


## Bericht:

Für diese Aufgabe wurde der Text mainau-gastronomie.txt ausgewählt. 
Die Entscheidung fiel auf diesen Text, da die Struktur der Öffnungszeiten intuitiver und zugänglicher wirkte als die der Abfahrtstafeln der Deutschen Bahn. Ziel war es, das Vokabular dieses Textes mithilfe von ANTLR4 Lexer-Regeln zu beschreiben und zu tokenisieren.

Der Einstieg erfolgte durch das Ausführen des bereitgestellten Beispiels (ant & ./lrun.sh expr-examples/beispiel-gueltige.txt). Anschließend wurde die Datei ExprTokenizer.java analysiert.
Anfänglich war das Konzept der "hidden channels" im Tokenizer unklar. Nach dem Abgleich mit der Datei ExprLexer.g4 wurde jedoch ersichtlich, dass dieser Kanal genutzt wird, um irrelevante Zeichen wie Leerzeichen, Tabs und Zeilenumbrüche (WS: [ \t\r\n]+ -> channel(HIDDEN);) beim Parsen auszublenden, ohne sie komplett zu löschen.

Die Erstellung der eigenen ExprLexer.g4 Datei begann mit einer Kopie des Basis-Beispiels, welche schrittweise um eigene Einträge erweitert wurde.
Dabei wurden einfache, allgemeine Beispiel-Einträge (wie Digits: ([0-9])+;) aufgrund von Redundanz entfernt und durch präzisere Regeln ersetzt, die genau auf den Text zugeschnitten sind (z. B. TIME: ([0-1]?[0-9] | '2'[0-3]) '.' [0-5][0-9];)

Während der Entwicklung kam es zu einer konzeptionellen Verwechslung zwischen den Aufgabenbereichen eines Lexers und eines Parsers. Durch einen zu starken Fokus auf die Backus-Naur-Form entstanden zunächst skurrile Konstrukte im Lexer, wie beispielsweise TIMESPAN: WEEKDAY BIS WEEKDAY;.

Es wurde erkannt, dass der Lexer lediglich für die Tokenisierung (also das Erkennen der grundlegenden Bausteine/Vokabeln) zuständig ist und solche strukturellen Zusammenhänge zwingend in einen Parser gehören.

Basierend auf dieser Erkenntnis wurde das Vokabular des Lexers erfolgreich in drei übersichtliche Kategorien unterteilt, um den Text (und ähnliche Texte) zuverlässig in Tokens zu zerlegen:Schlüsselwörter (Keywords): Feststehende, mehrfach vorkommende Begriffe im Text. Beispiele hierfür sind BIS: 'bis';, UHR: 'Uhr';, TAEGLICH: 'täglich'; und RUHETAG: 'Ruhetag';.Zeitangaben: Erkennungsmuster für zeitliche Daten. Dazu gehören Wochentage (WEEKDAY) , Monate (MONTH) sowie genaue Uhrzeiten (TIME).Sonstiges (Wörter & Bezeichner): Allgemeine Wörter, die aus beliebigen deutschen Buchstaben bestehen. Hierbei wurde auch darauf geachtet, Sonderzeichen wie das "é" zu berücksichtigen, um Wörter wie "Schlosscafé" korrekt erfassen zu können (WORD: [a-zA-ZäöüÄÖÜßé\-]+;).
