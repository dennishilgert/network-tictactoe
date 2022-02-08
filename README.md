# Vorlesung Programmieren 1
## Anwendungsprojekt Tic Tac Toe über das Netzwerk - Jonas Reif und Dennis Hilgert

## Expose':

### Aufgabenbeschreibung und Funktionsumfang:
Ziel des Projekts soll das Computerspiel Tic Tac Toe sein, welches die Möglichkeit bietet, über zwei sich im gleichen Netzwerk befindlichen Computer gegeneinander zu spielen. 

### Funktion (Anwendersicht):
#### Nach dem Herunterladen aus der GitHub-Repository:
- Konsolenprozess starten und in den heruntergeladenen Ordner navigieren
- Mit der Eingabe “make” in der Konsole eine ausführbare Datei kompilieren
- Starten des Programms mit Eingabe “make run” oder alternativ “./game“

#### Nach Aufforderung durch das Programm: 
- Eingabe von “h“ für den Spielhost oder “c“ für den Spielclient
- Eingabe der Host-IP-Adresse (standardmäßig 127.0.0.1)
- Setzen eines Spielsteins durch die Eingabe der Ziffer des Felds

### Funktion (technische Umsetzung):
Das Programm wird zweimal auf dem gleichen oder jeweils auf einem unterschiedlichen Computer im selben Netzwerk ausgeführt. Beim Start lässt sich durch eine Konsoleneingabe auswählen, ob die Anwendung als Spielhost oder -client agieren soll. Erstgenanntes führt dazu, dass man in der Konsole aufgefordert wird, eine IP-Adresse für den Server-Socket eingeben soll (standardmäßig 127.0.0.1), welche zugleich die Zieladresse für den Client darstellt (sprich auch dementsprechend erreichbar sein muss). Der Server- oder Host-Socket wird anschließend erstellt und an die eingegebene IP-Adresse und den festgelegten Port 5566 gebunden. Abschließend wird der Socket in den Verbindungsmodus gesetzt und wartet in einem eigenen Thread auf eine eingehende Verbindungsanfrage, damit der Haupt-Thread nicht blockiert wird.

Beim Starten als Spielclient wird man nach der oben genannten Host-IP-Adresse gefragt. Sobald diese eingeben ist, wird gleich wie beim Spielhost ein Socket erstellt, welcher in diesem Fall jedoch nicht an die IP-Adresse gebunden, sondern eine Verbindung zu dieser herstellen wird. Bei erfolgreicher Verbindung erfolgt das Senden einer Hallo-Nachricht. Sofern hier keine Fehler auftreten ist die Netzwerkverbindung zwischen den beiden Endpunkten hergestellt.

Die Spieler können nun einen Spielstein auf ein Feld setzen, indem die Ziffer des Feld in der Konsole angegeben wird. Der Spielzug wird nun durch ein Update des Spielfelds in der eigenen Konsole sichtbar. Um die Information über den getätigten Spielzug an den gegnerischen Endpunkt zu übertragen, wird ein Array mit den Werten: Index 0 = “Ziffer des Felds” und Index 1 = “Symbol des Spielers” über die Socket-Verbindung übertragen. Hierdurch ist es dem generischen Endpunkt nun auch möglich, den Spielzug durch ein Update des Spielfelds zu visualisieren.

Durch den Vergleich des Arrays mit den noch vorhandenen Gewinnmöglichkeiten wird am Ende jeder Runde auf einen möglichen Gewinner geprüft.