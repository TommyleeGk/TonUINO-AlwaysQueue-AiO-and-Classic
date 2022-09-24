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
