/*

      Meine Änderungen ( Teilweise über " #define " wähl- oder abwählbar)
    ====================================================================================================
    - Zur Ansteuerung eines KCX Bluetoothmodules wurde die Steuerung über Modifikationskarte hinzugefügt.                        - Every 
      Beim ersten Auflegen der Modifikationskarte BlueTooth wird das Bluetoothmodul eingeschaltet.                                 auf TLE-Traegerplatine
      Beim wiederholten Auflegen wird das Bluetoothmodul wieder ausgeschaltet. Eine aktive Modifikationskarte
      wird durch das Auflegen der BT-Karte deaktiviert und muss ggf. neu aufgelegt werden.
      Ein Pairing zu einem anderen Bluetoothgerät kann bei eingeschaltetem BT und laufender Wiedergabe 
      durch Longpress der Play/Pausetaste gestartet werden. Die Ansage der Tracknummer bleibt erhalten,
      das Pairing wird zusätzlich ausgeführt.
    
    - Beim Auflegen der Modifikationskarte Schlummermodus wird bei aktiviertem define "CandleLight"                              - AiO Plus und Every
      der CandleLight Modus in der LED-Animation aktiv. (Simulation von Kerzenflackern)
      Aus Speicherplatzgründen auf der AiO und in der Klassikversion nicht mit allen Features möglich.
      Kann in den defines getrennt aktiviert, bzw deaktiviert werden.
    
    - Die Software wurde an die neueste DF-Player Bibliothek (1.2.3)angepasst. 
    
    - Die TLE-Traegerplatine kann in der Klassik und Every-Version über define aktiviert werden                                    - Klassik und Every
      die Belegung bzw Funktion einiger Pins wurde verändert. Die Möglichkeit von USB-Stick abzuspielen                              auf TLE-Traegerplatine
      wurde für die TLE-Traegerplatine entfernt.
      Achtung, das gilt nicht für die Klassikplatine von LKP.

    - Das Buttonboard 3x3 wurde in die Tastensperren der Modifiers integriert.                                                      - Alle
    
    - Der Zugriff auf die SD-Karte über den USB-Port kann über eine Modifikationskarte freigegeben werden.                          - AiO/AiOPLUS
      Die Tasten sind in diesem Modifier gesperrt. Der Menüpunkt zum Erstellen der Modiffier-Karte wurde dem
      Adminmenü hinzugefügt.  Über #define aktivierbar.
    
    - Das Adminmenü kann über die 3 Tasten-Kombination Play/Pause-Vor-Zurück, oder Play/Pause-Vol+ Vol-, aufgerufen werden.
      Der Status der Tasteninversion spielt dabei keine Rolle mehr.
    
    - Codeanpassung an die AiOPLUS Platine.                                                                                         - AiOPLUS
    
    - Codeanpassung an den Nano EVERY, Möglichkeit zur Steuerung des DF-Players über HardwareSerial (Serial-1).                     - Klassik mit Nano-Every
    
    - Auswahlmöglichkeit für die Nutzung der Software auf dem AiO Board, oder dem Tonuino aus Einzelkomponenten (TonUINO Klassik)   - (AiO und TonUINO Klassik)
    - Integration der Hilfsroutine für den EEPROM der AiO Platine und Codeanpassung                                                 - (nur für AiO)

    - Das Buttonboard 12 Tasten wurde integriert. Durch #define Buttonboard aktivierbar.                                           - (AiO, Klassik in Arbeit)
      Die 9 Tasten werden über das Adminmenü mit Shortcuts belegt.
    
    - Bei Ausgabe eines Fehlers des Df-Players wird ein Magenta Blinksignal der LED-Animation                                      - (AiO und TonUINO Klassik)
      aktiviert, unabhängig ob die LED-Anim eingeschaltet oder ausgeschaltet ist. Quittierung
      über Druck der Play/Pause-Taste. Kann der Df-Player den nächst folgenden Track der Queue abspielen,
      wird dieser abgespielt und der Fehler zurückgesetzt. 
      Ist keine weitere Wiedergabe möglich wird der Standbytimer aktiviert zum Ausschalten.
    
    - Codeanpssung für die Verwendung des ROBOTDYN DF-Players mit LISP3 Chip.                                                       - Klassik und Every
      Der LISP3 Chip gibt auch nach dem Abspielen von Adverts ein EndOfTrack Event aus, was zum
      Überspringen von Folgetracks führt. Das wird jetzt abgefangen und Folgetracks werden nicht
      mehr übersprungen.

    - LED Animation umgestaltet nach @atomphil. Weichere und fließendere Animation.                                                - (AiO und TonUINO Klassik)
    
    - 5 Tastenfunktion Shortpress und Longpress für alle Tasten. Shortcuts für alle Tasten.                                        - (AiO und TonUINO Klassik) 
        Vol-Tasten - Shortpress schrittweise Vol-Änderung, Longpress continuirliche Vol-änderung.   
        Vor-Zurück Tasten - Shortpress -> 1 Titel vor oder zurück,Longpress -> Sprung mehrerer Titel vor oder zurück.
        Die Anzahl der zu überspringenden Titel ist in den defines voreinstellbar. 
        Titel der einzelnen Sprünge werden kurz angespielt.
    
    - Manuelle Abbrüche im Adminmenü überarbeitet, zum sauberen Ausstieg aus allen Untermenüs.                                      - (AiO und TonUINO Klassik)
    
    - Änderung der Geschwindigkeit der Lautstärkeeinstellung über longPress der Laustärketasten                                     - (AiO und TonUINO Klassik)
      Die Veränderung der Geschw erfolgt nicht mehr über ein delay, sondern über einen Counter.
      Dadurch kann die Geschw bei den Defines am Scetchanfang festgelegt werden. 
      Der Durchlauf der Mainloop wird durch die delays nicht mehr gebremst.
    
    - Management der Batteriemessung abgeschlossen.                                                                                 - (AiO und TonUINO Klassik)
      Glättung der Messwerte durch Mittelwertbildung über 60 Messungen in einer Minute, AiO                                         - (AiO)
      Glättung der Messwerte durch Mittelwertbildung über 10 Messungen in einer Minute, Klassik                                     - (TonUINO Klassik)
    
    - Abschaltung über MOSFET oder Pololu-Switch, ShutDownPin - Anpassbar über defines ,Low oder High aktiv                         - (AiO und TonUINO Klassik)
    
    - Der Powerdown Impuls wird als Impulsfolge HIGH-LOW-HIGH ausgeführt zur Abschaltung über MosFet oder Pololu-Switch             - (nur TonUINO-Klassik)
    
    - Unterstützung USB-Stick als Speichermedium                                                                                    - (nur TonUINO-Klassik)
    
    - USB-Powerschaltung über MOSFET - UsbPowerPin - High aktiv                                                                     - (nur TonUINO-Klassik)
    
    - Animation mit LED-RGB-Ring, Ein- und Ausschaltbar über langen Druck Up + Down                                                 - (AiO und TonUINO Klassik)
    
    - StandBy Timer auf 5 min voreingestellt und aktiviert als Grundeinstellung.                                                    - (AiO und TonUINO Klassik)
    
    - Sleepmodus, Ausfaden der Lautstärke über die letzten 20 Sekunden. Standbytimer schaltet danach sofort aus.                    - (AiO und TonUINO Klassik)
    
    - Sleepmodus, Neue Karte und Tasten ausser Play-Pause und Lauter/Leiser bis zum Ausschalten gesperrt                            - (AiO und TonUINO Klassik)
    
    - Abschaltung der LED-Animation über Standbytimer zur Abschaltung Powerbank Software-only                                       - (nur TonUINO Klassik)
    
    - Verzögerte Zuschaltung des Lautsprechers beim Einschalten, (Klassik über MOSFET) (Unterdrückung Einschaltgeräusch)            - (AiO und TonUINO Klassik)
    
    - Lautsprecher wird bei angeschlossenem Kopfhörer über Software abgeschaltet. Für AiO nur durch Änderung der Platine möglich!   - (nur TonUINO Klassik)
      Die originale Abschaltung bei der AiO erfolgt über die Kopfhörerbuchse (Amp wird direkt abgeschaltet)
    
    - Die Pegel des Kopfhörer Sensors können über #define KHSensLOW umgestellt werden. LOW oder HIGH aktiv.                         - (nur TonUINO Klassik)
    
    - Lautstärkeänderung bei Einstellung über long press button, Geschwindigkeit in den defines festlegbar.                         - (AiO und TonUINO Klassik)
    
    - Menülautstärke kann unabhängig von zuletzt eingestellter Lautstärke auf Startlautstärke oder Festwert gesetzt werden          - (AiO und TonUINO Klassik)
    
    - Reihenfolge der Funktionen im Adminmenü geändert, Ordner mp3 auf der SD Karte muss angepasst werden !!!                       - (AiO und TonUINO Klassik)
    
    - Die Auswahloptionen im Adminmenü werden jetzt umlaufend durchgeschaltet.                                                      - (AiO und TonUINO Klassik)
      D.h. ist die höchste Option erreicht, wird anschließend zu Option 1 weitergeschaltet. 
      In Rückwärtsrichtung von 1 zu höchster Option.
    
    - Bei der Ordnerauswahl werden nur noch die vorhandenen Ordner berücksichtigt. ( Funktioniert nicht mit allen DfMini Playern)   - (AiO und TonUINO Klassik)
    
    - Rechenaufgabe und PIN Eingabe aus Schutzfunktion Adminmenü entfernt                                                           - (AiO und TonUINO Klassik)
    
    - Feedback beim Beenden des Admin-Menues                                                                                        - (AiO und TonUINO Klassik)
    
    - Feedback beim Schreiben von Karten und Konfigurieren der Shortcuts                                                            - (AiO und TonUINO Klassik)
    
    - Feedback auch beim Konfigurieren "Neue Karte" ohne Benutzung des Adminmenüs                                                   - (AiO und TonUINO Klassik)
    
    - Jingle beim Entfernen der Modifikationskarten, Funktion beim Auflegen wird angesagt                                           - (AiO und TonUINO Klassik)
    
    - Hörbuchmodus, Fortschritt wird bei langem Druck der Pausetaste auf Track 1 zurückgesetzt                                      - (AiO und TonUINO Klassik)
   
    - Letzte gespielte Karte wird gespeichert und als Shortcut auf die Play-Taste gelegt                                            - (AiO und TonUINO Klassik)
      Im Adminmenü wird die Konfiguration des Shortcuts für die PlayTaste ausgeblendet, da diese mit lastcard belegt wird.
    
    - TonUINO als Wecker. Ein Uhrenmodul kann den TonUINO einschalten und ein HIGH Signal auf Analogpin A6                          - (AiO und TonUINO Klassik)
      startet das Abspielen eines vorkonfigurierten Shortcuts als Wecksound.
      Konfiguration des Weckershortcuts im Adminmenü integriert.
    
    - Wecker wird auch bei angeschlossenem Kopfhörer (Lautsprecher Aus), über den Lautsprecher abgespielt.                          - (nur TonUINO Klassik)
      Für die AiO ist diese Funktion nur nach einer Änderung an der Platine (Trennung einer Verbindung) nutzbar.                      (AiO nach Hardwareänderung)
    
    - Empfindlichkeit des RFID Lesers kann in der Initialisierung ( "mfrc522.PCD_Init()")geändert werden. Hier auf mittel gesetzt.  - (AiO und TonUINO Klassik)
    
    - Alle Abspielmodi arbeiten jetzt mit einer Queue (Playlist)- "Always queue".                                                   - (AiO und TonUINO Klassik)
    
    - Die Queue in den Modi Party beginnen jetzt bei jedem Start mit einem anderen zufälligen Track.                                - (AiO und TonUINO Klassik)
    
    - Die Queue in den Modi Party werden vor Neustart am Ende neu gemischt.                                                         - (AiO und TonUINO Klassik)
    
    - Die Fehlercodes des DF-Players werden im seriellen Monitor im Klartext angezeigt.                                             - (AiO und TonUINO Klassik)
    
    - Die Batterie bzw. Akkuspannung kann überwacht werden. Bei Erreichen einer ersten Schwelle wird alle 60 sekunden               - (AiO und TonUINO Klassik)
      eine Warnung ausgegeben. Bei Erreichen der Entladeschlusspannung wird eine Warnung ausgegeben
      und der Tonuino mit Ausfaden der Lautstärke über 20 Sekunden ausgeschaltet.
    
    - Die Messung der Batteriespannung wird durch Nutzung der internen Referenzspannung genauer.                                    - (AiO und TonUINO Klassik)
    
    - Weitestgehende Kürzung der Ausgaben über den Ser-Monitor zur Einsparung von Programmspeicher                                  - (AiO und TonUINO Klassik)
    
    - Debug Modus: (Konsole) Die Ausgaben auf den Seriellen Monitor können zur Einsparung von Speicherplatz                         - (AiO und TonUINO Klassik)
      über die defines ausgeschaltet werden. Es werden nur die Meldungen beim Start angezeigt.
      Die weiteren Konsolenausgaben sind auf ein Minimum reduziert.
      Bei aktivierter LED-Animation wird diese im Debug-Modus deaktiviert, um Speicherplatz für die Ausgaben
      in der Konsole frei zu machen. (Ersparnis ca 20% Programmspeicher)

    ************** Bug Fixes **********************************************************
    - Fix, Initialisierung und Zuweisung des Eq Wertes zum Df-Player, Variablenconversion bereinigt.
    - Fix, Adminmenü; Beim Konfigurieren einer neuen Karte wurde die Kartenerkennung nach Auflegen verbessert.
    - Fix, Adminmenü; Bei der Auswahl von Optionen, der Ordner oder Tracks blieb das Menü hängen
           wenn Longpress zu lange gedrückt, bzw. die Taste nicht losgelassen wurde. Problem beseitigt.
    - Fix, Beim Erstellen von Karten und Shortcuts in den Spezialmodi von-bis, kann der EndTrack nicht mehr vor dem StartTrack programmiert werden.
    - Fix, Bei Track zurück um 1, wird der dem Track folgende Rest der Queue abgespielt und bleibt nicht mehr stehen.
    - Fix, Letzte Karte auf Playtaste legen, alle Modi Spezial-von-bis, Start und Endtrack werden jetzt richtig gespeichert
    - Fix, Bei Schutz des Adminmenüs NUR MIT KARTE hängt sich der Tonuino nicht mehr bei 3 Tastendruck auf
    - Fix, ModKarte repeat single track. Rücktaste jetzt auch gesperrt.
    - Fix, ModKarte repeat single track. Im Partymodus wird jetzt der richtige aktuelle Titel abgespielt.
    - Fix, Wiedergabe Spezialmodus Von-Bis-Album, Vor- Rücktasten bleiben jetzt im definierten Ordnerbereich.
    - Fix, Reset beim Einschalten. TonUINO auf default-Werte rücksetzen funktioniert jetzt.
    - Fix, Standby-Timer wird jetzt auch bei manuellem Abbruch des Adminmenüs gestartet.
    - Fix, Bei nicht beendetem Adminmenü wird nach 2 min Inaktivität (TimeOut) das Adminmenü automatisch beendet
           und der Tonuino ausgeschaltet.
    - Fix, Codeanpassung an Bibliothek Df-Player mini Version 1.06 . und höher !!! Diese muss installiert sein !!!

    ************* Änderungen im Adminmenü *********************************************************

     - Das Durchschalten der Optionen erfolgt jetzt umlaufend. Vorwärts und auch rückwärts (rolling)
     - Bei der Erstellung von Karten und Shortcuts in den Spezialmodi von-bis ist das rolling beim EndTrack gesperrt.
     - Die Reihenfolge der Menüpunkte wurde verändert.
     - Die Menüstruktur wurde verändert und mehrere Untermenüs hinzugefügt.
     - Bei der Abfrage ob die Funktion der LS-Tasten umgedreht werden soll, erfolgt der Wechsel immer wenn JA gewählt wird.
     - Die Presets für die Lautstärke wurden um Presets für den Kopfhörer erweitert.
     - Die Einstellungen für den EQ wurden in das Untermenü der Lautstärkeeinstellungen integriert.
     - Bei der Configuration der Shortcuts wurde das Voicemenü an die Option mit oder ohne Wecker angepasst.
     - Bei Nutzung des 12 Buttonboards wurde die Konfiguration der 9 zusätzlichen Shortcuts ins Adminmenü integriert.
     - Wenn die Funktion LastCard genutzt wird, ist die Konfiguration des Shortcuts 0 (PlayTaste) ausgeblendet.
     - Im Adminmenü läuft eine Timeoutfunktion, die nach 2 Minuten Inaktivität das Adminmenü beendet und
       den Tonuino ausschaltet. Das Timeout funktioniert jetzt auch wenn auf das Auflegen einer Karte gewartet wird.
       Bei Nichtauflegen einer angeforderten Karte, wird nach Ablauf der Timeoutzeit der Tonuino abgeschaltet.
     - Bei manuellem Abbruch erfolgt jetzt ein sauberer Ausstieg aus allen Untermenüs. 
     - Die Änderungen erfordern eine Neuordnung und das Hinzufügen von Dateien im advert und mp3 Ordner.
       Es ist erforderlich die dieser Version beigefügten advert und mp3 Ordner verwenden.


    **************************************************************************************************/
      /* MFRC522 RxGain[2:0] masks, defines the receiver's signal voltage gain factor (on the PCD).
    Described in 9.3.3.6 / table 98 of the datasheet at http://www.nxp.com/documents/data_sheet/MFRC522.pdf

     RxGain_min        = 0x00 << 4,  // 000b - 18 dB, minimum, convenience for RxGain_18dB
     RxGain_avg        = 0x04 << 4,  // 100b - 33 dB, average, convenience for RxGain_33dB
     RxGain_max        = 0x07 << 4   // 111b - 48 dB, maximum, convenience for RxGain_48dB

     RxGain_18dB       = 0x00 << 4,  // 000b - 18 dB, minimum
     RxGain_23dB       = 0x01 << 4,  // 001b - 23 dB
     RxGain_18dB_2     = 0x02 << 4,  // 010b - 18 dB, it seems 010b is a duplicate for 000b
     RxGain_23dB_2     = 0x03 << 4,  // 011b - 23 dB, it seems 011b is a duplicate for 001b
     RxGain_33dB       = 0x04 << 4,  // 100b - 33 dB, average, and typical default
     RxGain_38dB       = 0x05 << 4,  // 101b - 38 dB
     RxGain_43dB       = 0x06 << 4,  // 110b - 43 dB
     RxGain_48dB       = 0x07 << 4,  // 111b - 48 dB, maximum

  */
