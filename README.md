# 03-2024 Codeanpassung an die TLE-Traegerplatine
der Code wurde an die von mir entwickelte TLE-Traegerplatine angepasst. Gleichzeitig wurde der Code auf die DF-Player Library Version 1.2.3 aktualisiert. Dabei wurde noch ein Bug beseitigt, der beim LKP-Player und der AiO Plus auftrat.
In der Modifikation Schlummermodus wurde der Candlelight Effekt für die LED-Animation hinzugefügt. Dieser kann durch setzen des defines aktiviert werden und wird dann bei jedem Auflegen der Modifikationskarte Schlummermodus aktiv.
Die TLE-Traegerplatine unterstützt auch die Verwendung von Batterien oder Akkus bis 12V. Die Batterieüberwachung ist im Code an die Batteriespannung anpassbar.

# 03-2023 Zugriff auf die Sd-Karte über den USB-Port als Modifikation (nur AiO oder AiO plus)
Die Funktion des Zugriffs auf die SD-Karte wurde als Modifikationskarte hinzugefügt. 
Das Erstellen der zusätzlichen Modifikationskarte wurde ins Adminmenü integriert.
Beim Auflegen der Modifikationskarte wird der Zugriff auf die interne SD-Karte des Tonuino aktiviert.
Die Bedienung des Tonuino ist bei aktiver Modifikation gesperrt. Durch erneutes Auflegen der Karte
oder Neustart des Tonuino wird der Zugriff auf die SD-Karte wieder gesperrt und die normale Funktion wieder hergestellt.
Das Adminmenü kann jetzt durch die Tastenkombinationen Play-Laut-Leise, oder Play-Vor-Zurück aufgerufen werden.
Dadurch hat der Zustand der Inversion der Tasten keine Auswirkung mehr auf den Start des Adminmenüs per Longpress 3 Tasten.

# 11-2022 Debugging von Jackdetekt für die AiO Plus.
Im Code wurden noch bugs entdeckt. die bei Aktivierung von Jackdetekt den Lautsprecher dauerhaft stumm schalteten.
Das wurde beseitigt und Jackdetekt kann uneingeschränkt genutzt werden.
Außerdem wurde das Setzen der Defines übersichtlicher gestaltet, indem die Hardwareabhängigen Defines in eigene .h Dateien gelegt wurden.
Diese sind durch Karteireiter in der Arduino IDE aufrufbar. Die config-xxx.h dateien müssen im gleichen Ordner gespeichert werden wie die XXX.ino Datei.

# 09-2022 Erweiterung für die Nutzung auf der AiO Plus.
Der code wurde an die neue AiO Plus angepasst, und kann somit auch auf dieser 
benutzt werden. Die Festlegung der Hardware-Plattform (Klassik, AiO, AiO Plus oder Nano Every)
wird in den defines jetzt automatisch gesetzt. Dazu muss nur in der Werzeugleiste im
Boardmanager das zur Hardware-Plattform passende Prozessor-Board ausgewählt werden und die zugehörigen Einstellungen
vorgenommen werden. Die Boardabhängigen defines werden dadurch automatisch gesetzt.
Die anderen Optionen ( 3, 5, Buttons;  Batterieüberwachung; LED Animation usw.) müssen 
über die defines von Hand vorgenommen werden.


# TonUINO-AlwaysQueue-AiO-and-Classic
Diese Version der TonUINO software basiert auf der TonUINO Software von Thorsten Voss.
Die Kernfunktionen entsprechen obiger Software, wodurch die Kompatibilität
der TonUINO RFID Karten gewährleistet ist.
Der Funktionsumfang wurde erweitert und die Struktur des Adminmenüs
verändert sowie um diverse Funktionen erweitert.
Die Software ist so konzipiert, dass sie über defines an die vorhandene Hardware
angepasst werden kann.
Diese Software ist sowohl auf dem Klassischen Tonuino, bestehend aus Einzelkmpoeneten
wie Arduino-Nano, DF-Player mini, RFID Reader MRF522 lauffähig,
als auch auf der neuen AiO Platine.

Für alle Versionen die in der zip datei enthaltenen Ordner advert und mp3 verwenden.
Der Code ist in allen Versionen dentisch und nur über die Defines an verschiedene 
Hardwarekombinationen angepasst.
Über die Defines kann der Code an indiwiduelle Hardwarekonfigurationen angepasst werden.
Die Nutzung der Option Jackdetekt auf der AiO Platine ist nur nach einer Hardwareänderung 
möglich. 
Die Optionen Wecker und Batteriecheck sind auf der AiO ebnfalls nur nach einer
Hardwareänderung nutzbar.
Im letzten Update vom 18.01.2022 wurden Programmabläufe optimiert und Variablenanpassungen
vorgenommen, die zu diversen Warnungen beim Kompilieren geführt hatten.
Dadurch wurde zusätzlicher Programmspeicher gewonnen.
