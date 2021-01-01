

/****** Alternative Software *************
   _____         _____ ___ ___ _______
  |_   _|___ ___|  |  |   |   | |     |
    | | | . |   |  |  |- -| | | |  |  |
    |_| |___|_|_|_____|___|_|___|_____|
    Based on TonUINO Version 2.1 und Version 2.2 AiO

    created by Thorsten Voß and licensed under GNU/GPL.
    Information and contribution at https://tonuino.de.

********* Always Queue - AiO oder Classic TonUINO ************************

      Version Thomas Lehnert

      letzte Änderung 2021-01-01

    - Über #define wird ausgewählt, ob die Software auf dem AllinOne-Board,
      oder auf der Hardwareversion aus Einzelkomponenten mit dem Arduino Nano
      benutzt werden soll.

    - Für die AiO Platine müssen folgende Einstellungen vorgenommen werden.
      Die LGT8Fx Bibliotheken müssen in der IDE installiert sein !
      Siehe folgender Link: https://www.leiterkartenpiraten.de/2020/11/21/die-arduino-ide-einrichten/
     
      Boardtyp LGT8F328 unter Logic green Arduino AVR Compatible Boards auswählen
      Clock Source: External (assumes 32MHz crystal)
      Clock: 16 MHz
      Variant: 328P-LQFP (e.g. MiniEVB nano-style and WAVGAT)
      Arduino as ISP: Default (64)
      Korrekten COM Port
      Um den korrekten COM Port auswählen zu können, muss die AiO angeschlossen sein. Der COM Port
      kann sich unterscheiden (siehe Gerätemanager).

   - Für die Nutzung in der Version Classic mit Einzelkomponenten Nano 328P oder Nano 328P(Old Bootlader), je nach Version auswählen.


     !!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!! WICHTIG !!!!!!!!!!!
     !!                                                                                                     !!
     !!   Die Änderungen erfordern eine Neuordnung und das Hinzufügen von Dateien im advert und mp3 Ordner. !!
     !!   Bitte die dieser Version beigefügten advert und mp3 Ordner verwenden.                             !!
     !!                                                                                                     !!
     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  ***********************************************************************************************************
  ***********************************************************************************************************

      Meine Änderungen ( Teilweise über " #define " wähl- oder abwählbar)
    
    - Auswahlmöglichkeit für die Nutzung der Software auf dem AiO Board, oder dem Tonuino aus Einzelkomponenten (TonUINO Classic)  - (AiO und TonUINO Classic)

    - Integration der Hilfsroutine für den EEPROM der AiO Platine und Codeanpassung                                                 - (nur für AiO)

    - Manuelle Abbrüche im Adminmenü überarbeitet, zum sauberen Ausstieg aus allen Untermenüs.                                      - (AiO und TonUINO Classic)

    - Änderung der Geschwindigkeit der Lautstärkeeinstellung über longPress der Laustärketasten                                     - (AiO und TonUINO Classic)
      Die Veränderung der Geschw erfolgt nicht mehr über ein delay, sondern über einen Counter.
      Dadurch kann die Geschw bei den Defines am Scetchanfang festgelegt werden. 
      Der Durchlauf der Mainloop wird durch die delays nicht mehr gebremst.
 
    - Abschaltung über MOSFET oder Pololu-Switch, ShutDownPin                                                                      - (AiO und TonUINO Classic)
    - Der Powerdown Impuls wird verdoppelt zur sicheren Abschaltung über MosFet                                                    - (nur TonUINO-Classic)
    - Animation mit LED-RGB-Ring, Ein- und Ausschaltbar über langen Druck Up + Down                                                - (AiO und TonUINO Classic)
    - StandBy Timer auf 5 min voreingestellt und aktiviert                                                                         - (AiO und TonUINO Classic)
    - Sleepmodus, Ausfaden der Lautstärke über die letzten 20 Sekunden. Standbytimer schaltet danach sofort aus.                   - (AiO und TonUINO Classic)
    - Sleepmodus, Neue Karte und Tasten ausser Play-Pause bis zum Ausschalten gesperrt                                             - (AiO und TonUINO Classic)
    - Abschaltung der LED-Animation über Standbytimer zur Abschaltung Powerbank Software-only                                      - (nur TonUINO Classic)
    - Verzögerte Zuschaltung des Lautsprechers beim Einschalten, (Classic über MOSFET) (Unterdrückung Einschaltgeräusch)           - (AiO und TonUINO Classic)
    - Lautsprecher wird bei angeschlossenem Kopfhörer über Software abgeschaltet. Für AiO nur durch Änderung der Platine möglich!  - (nur TonUINO Classic)
      Die Abschaltung bei der AiO erfolgt über die Kopfhörerbuchse (Amp wird direkt abgeschaltet)
    - Die Pegel des Kopfhörer Sensors können über #define KHSensLOW umgestellt werden. LOW oder HIGH aktiv.                        - (nur TonUINO Classic)
    - Menülautstärke kann unabhängig von zuletzt eingestellter Lautstärke auf Startlautstärke oder Festwert gesetzt werden         - (AiO und TonUINO Classic)
    - Reihenfolge der Funktionen im Adminmenü geändert, Ordner mp3 auf der SD Karte muss angepasst werden !!!                      - (AiO und TonUINO Classic)
    - Die Auswahloptionen im Adminmenü werden jetzt umlaufend durchgeschaltet.                                                     - (AiO und TonUINO Classic)
      D.h. ist die höchste Option erreicht, wird anschließend zu Option 1 weitergeschaltet. In Rückwärtsrichtung von 1 zu höchster Option.
    - Bei der Ordnerauswahl werden nur noch die vorhandenen Ordner berücksichtigt. ( Funktioniert nicht mit allen DfMini Playern)  - (AiO und TonUINO Classic)
    - Rechenaufgabe und PIN Eingabe aus Schutzfunktion Adminmenü entfernt                                                          - (AiO und TonUINO Classic)
    - Feedback beim Beenden des Admin-Menues                                                                                       - (AiO und TonUINO Classic)
    - Feedback beim Schreiben von Karten und Konfigurieren der Shortcuts                                                           - (AiO und TonUINO Classic)
    - Feedback auch beim Konfigurieren "Neue Karte" ohne Benutzung des Adminmenüs                                                  - (AiO und TonUINO Classic)
    - Jingle beim Entfernen der Modifikationskarten, Funktion beim Auflegen wird angesagt                                          - (AiO und TonUINO Classic)
    - Hörbuchmodus, Fortschritt wird bei laufender Wiedergabe bei langem Druck der Pausetaste auf Track 1 zurückgesetzt            - (AiO und TonUINO Classic)
    - Letzte gespielte Karte wird gespeichert und als Shortcut auf die Play-Taste gelegt                                           - (AiO und TonUINO Classic)
      Im Adminmenü wird die Konfiguration des Shortcuts für die PlayTaste ausgeblendet, da diese mit lastcard belegt wird.
    - TonUINO als Wecker. Ein Uhrenmodul schaltet den TonUINO ein und gibt ein Signal auf Analogpin A6                              - (AiO und TonUINO Classic)
      das das Abspielen eines Shortcuts als Wecksound startet.Konfiguration des Weckershortcuts im Adminmenü integriert.
    - Wecker wird auch bei angeschlossenem Kopfhörer (Lautsprecher Aus), über den Lautsprecher abgespielt.                          - (nur TonUINO Classic)
      Für die AiO ist diese Funktion nur nach einer Änderung an der Platine (Trennung einer Verbindung) nutzbar.                      (AiO nach Hardwareänderung)
    - Empfindlichkeit des RFID Lesers kann in der Initialisierung ( "mfrc522.PCD_Init()")geändert werden. Hier auf mittel gesetzt.  - (AiO und TonUINO Classic)
    - Alle Abspielmodi arbeiten jetzt mit einer Queue (Playlist)- "Always queue".                                                   - (AiO und TonUINO Classic)
    - Die Queue in den Modi Party beginnen jetzt bei jedem Start mit einem anderen zufälligen Track.                                - (AiO und TonUINO Classic)
    - Die Queue in den Modi Party werden vor Neustart am Ende neu gemischt.                                                         - (AiO und TonUINO Classic)
    - Die Fehlercodes des DF-Players werden im seriellen Monitor im Klartext angezeigt.                                             - (AiO und TonUINO Classic)
    - Weitestgehende Kürzung der Ausgaben über den Ser-Monitor zur Einsparung von Programmspeicher                                  - (AiO und TonUINO Classic)
    - Debug Modus: (Konsole) Die Ausgaben auf den Seriellen Monitor können zur Einsparung von Speicherplatz                         - (AiO und TonUINO Classic)
      über die defines ausgeschaltet werden. Es werden nur die Meldungen beim Start angezeigt.
      Bei aktivierter LED-Animation wird diese im Debug-Modus deaktiviert, um Speicherplatz für die Ausgaben
      in der Konsole frei zu machen. (Ersparnis ca 20% Programmspeicher)

    ************** Bug Fixes **********************************************************
    - Fix, Bei Track zurück um einen Titel wird die dem zurückgestzten Track folgende Queue weiter abgespielt und bleibt nicht stehen.
    - Fix, Letzte Karte auf Playtaste legen, alle Modi Spezial-von-bis, Start und Endtrack werden jetzt richtig gespeichert
    - Fix, Bei Schutz des Adminmenüs NUR MIT KARTE hängt sich der Tonuino nicht mehr bei 3 Tastendruck auf
    - Fix, ModKarte repeat single track. Rücktaste jetzt auch gesperrt.
    - Fix, ModKarte repeat single track. Im Partymodus wird jetzt der richtige aktuelle Titel abgespielt.
    - Fix, Spezialmodus Von-Bis-Album, Vor- Rücktasten bleiben jetzt im definierten Ordnerbereich.
    - Fix, Reset beim Einschalten. TonUINO auf default-Werte rücksetzen funktioniert jetzt.
    - Fix, Standby-Timer wird jetzt auch bei manuellem Abbruch des Adminmenüs gestartet.
    - Fix, Bei nicht beendetem Adminmenü wird nach 2 min Inaktivität (TimeOut) das Adminmenü automatische beendet
           und der Tonuino ausgeschaltet.
    - Fix, Codeanpassung an Bibliothek Df-Player mini Version 1.06 . und höher !!! Diese muss installiert sein !!!

    ************* Änderungen im Adminmenü *********************************************************

     - Das Durchschalten der Optionen erfolgt jetzt umlaufend. Vorwärts und auch rückwärts
     - Die Reihenfolge der Menüpunkte wurde verändert.
     - Die Menüstruktur wurde verändert und mehrere Untermenüs hinzugefügt.
     - Die Presets für die Lautstärke wurden um Presets für den Kopfhörer erweitert.
     - Die Einstellungen für den EQ wurden in das Untermenü der Lautstärkeeinstellungen integriert.
     - Bei der Configuration der Shortcuts wurde das Voicemenü an die Option mit oder ohne Wecker angepasst.
     - Wenn die Funktion LastCard genutzt wird, ist die Konfiguration des Shortcuts 0 (PlayTaste) ausgeblendet.
     - Im Adminmenü läuft eine Timeoutfunktion, die nach 2 Minuten Inaktivität das Adminmenü beendet und
       den Tonuino ausschaltet. Das Timeout funktioniert jetzt auch wenn auf das Auflegen einer Karte gewartet wird.
       Bei Nichtauflegen einer angeforderten Karte, wird nach Ablauf der Timeoutzeit der Tonuino abgeschaltet.

     - Die Änderungen erfordern eine Neuordnung und das Hinzufügen von Dateien im advert und mp3 Ordner.
       Zur Korrekten Funktion, die dieser Version beigefügten advert und mp3 Ordner verwenden.


***********************************************************************************************************/
// _________________________________________________________________________________________________________

// *************** Auswahl der Tonuino-Variante ** AiO oder TonUINO Classic ********************************
// uncomment or comment the " #define AiO "  to switch enter the AiO Softwareversion or TonUINO Classic

// --------------------- All in One Board ------------------------------------------------------------------
#define AiO                     // Software wird an das AiO Board angepasst
                                // Für den TonUINO Classic " #define AiO " in Kommentar setzen
// _________________________________________________________________________________________________________

// *************************** Auswahl der Zusatzfunktionen ************************************************

// uncomment or comment the " #define .... "  to enable or disable the additional function


// --------------------- Debug Modus --- AiO und Classic ------------------------------------------------------------
#define Konsole                // Zum Einsparen von Programmspeicher wird die Ausgabe
                               // auf den Seriellen Monitor nur bei Freigabe ausgeführt.
                               // Bei aktiver LED-Animation, wird diese deaktiviert, um den Programmspeicher
                               // für die Konsolenausgabe frei zu machen.
                               // Soll die LED-Animation verwendet werden, 
                               // muss die #define Konsole durch in Kommentar "//" setzen deaktiviert werden.
                               
// -------------------- 5 Tasten Support --- AiO und Classic ----------------------------------------------------------
//#define FIVEBUTTONS            // 5 Tasten support
                              // In diesem Modus kann die Batterieüberwachung im TonUINO Classic nicht verwendet werden
                              // wenn A4 von dieser verwendet wird, oder der PrüfPin muss umdeklariert werden.

// -------------------- Zuletzt gespielte Karte als Shortcut speichern --- AiO und Classic -------------------------------
#define LastCard              // Die zuletzt gespielte Karte wird als Shortcut auf die Pause-Taste gelegt 
                              // Shortcuts, Startsound und Weckersound werden dabei nicht berücksichtigt
                              // Die Konfiguration des Shortcuts der PlayTaste wird aus dem Adminmenü ausgeblendet.

// ---------------------- Hörbuch auf Anfang zurücksetzen --- AiO und Classic ---------------------------------------------
#define HB_Reset              // Durch langen Druck der Pausetaste bei laufender Wiedergabe, 
                              // wird im Abspielmodus Hörbuch der Fortschritt des Hörbuches auf Anfang zurückgesetzt

// -------------------- Menülautstärke der Adminfunktionen festlegen --- AiO und Classic ----------------------------------
#define MenueVol                 // Die Menülautstärke wird auf die Startlautstärke Lautsprecher eingestellt.
const uint8_t MenueVolume = 20;  // Bei Deaktivierung von MenueVol wird die Menülautstärke auf diesen Festwert eingestellt.

// ------------------- Zählen der Ordner auf der SD-Karte --- AiO und Classic ---------------------------------------------
#define CountFolders           // Die Anzahl der Ordner des Speichermediums im DfPlayer wird ermittelt
                               // und als Begrenzung bei der Ordnerauswahl verwendet.
                               // Abhängig vom Chipsatz des DfPlayers ist die Funktion nicht immer verfügbar.
                               // Dann deaktivieren ! Es werden dann wieder die Funktionen ohne CountFolders verwendet.
                               // Getestet mit MH-ETLive, IL AA19 und YX5200 24SS - und funktioniert.
                               // AiO Platine funktioniert auch.

// -------------------- Windows SystemVolumeInfo ignorieren --- AiO und Classic -------------------------------------------
#ifdef CountFolders            // Bei CountFolders stört der Windows SystemVolumeInfo Ordner die exakte Funktion.
 #define IgnoreWinSysInf       // Der Windows-Ordner "Windows SystemVolumeInformation" kann auf der SD-Karte
                               // verbleiben und wird ignoriert. Dies ist bei Nutzung der Option CountFolders
                               // wichtig, um die korrekte Ordner Anzahl für die davon abhängigen Funktionen
                               // zu verwenden.
#endif
// -------------------- Abschaltung über Hardware --- AiO und Classic ------------------------------------------------------
#define HW_PowerOff            // Abschaltung über Hardware, wie Mosfet oder Pololu-Switch
                               // Hardwareerweiterung für TonUINO Classc erforderlich. Mosfet oder Pololu-Switch
                               // Auf der AiO Platine ist die erforderliche Hardware bereits vorhanden
  #ifdef HW_PowerOff
    #define LowActive          // Das Ausschaltsignal muss LOW Pegel zum Ausschalten haben.
  #endif                       // Für Pololu-Swich #define LowActive deaktivieren.(HIGH Active)

// -------------------- Abschaltung SoftwareOnly --- nur Classic in Verbindung mit einer Powerbank mit Autoabschaltung ------
//#define SoftPwDown             // Abschaltung Software Only. Die Abschaltung erfolgt durch die Powerbank
                               // durch Unterschreitung des minimalen Laststromes.
                               // Die Stromaufnahme des Tonuino wird auf unter 27 mA reduziert.  

// -------------------- LED Animation mit NEOPixel LED Ring oder Strip --- AiO und Classic ----------------------------------
                               
//#define LED_SR               // LED Animation mit Neopixel LED-Ring oder Strip
     #ifdef Konsole            // Hardwareerweiterung erforderlich: (Neopixel Strip oder Ring)
       #ifdef LED_SR           // Sind die Konsolenausgabe und die LED Animation Definiert, 
        #undef LED_SR          // die LED Animation ausblenden
       #endif
     #endif  
     #ifdef LED_SR                 // Bei definierter LED Animation
  const uint8_t LED_COUNT = 12 ;   // Anzahl an LEDs im Ring oder Strip. Kann hier angepasst werden.
      #define LED_SR_Switch    // Möglichkeit die LED-Animation über gleichzeitigen langen Druck 
                               // der Up-Down Tasten ein- und auszuschalten
    #endif 
   
// -------------------- Lautsprecher abschaltung über Software ---AiO auch über KH Buchse --------------------------------------
#define SpkOnOff              // Aus und Einschalten des Lautsprechers über Software 
                              // zur Unterdrückung des Einschaltgeräusches und
                              // Möglichkeit der Abschaltung beim Anschluss eines Kopfhörers (AiO über KH-Buchse )
                              // Hardwareerweiterung für TonUINO Classic erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
                              // Bei der AiO wird der Verstärker ein bzw. ausgeschaltet

// -------------------- Kopfhörer --- Nur TonUINO Classic --- Für Nutzung mit der AiO ist eine Änderung auf der Platine nötig ---
#ifndef AiO                   // Nur TonUINO classic (Anpassung an AiO nur über Hardwareänderung möglich)
#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
    #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
       #ifndef SpkOnOff       // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
        #define SpkOnOff      // Hardwareerweiterung erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
       #endif                 // Die Startlautstärken werden getrennt über das Adminmenü voreingestellt.
    #endif                    // Die letzten Laustärken werden getrennt bis zum Abschalten temporär gespeichert.
#endif

// ------------------- Festlegen des Sensorpegels für den Kophöreranschluss ---Nur TonUINO Classic --------------------------------
#ifndef AiO                   // Nur TonUINO Classic
#define KHSensLOW             // Der Sensorpegel für den Kopfhöreranschluss ist bei eingestecktem Kopfhörer LOW
                              // Wenn der Sensorpegel bei eingestecktem Kopfhörer HIGH ist, #define deaktivieren
#endif
// ------------------- Weckerfunktion mit Weckermodul --- AiO und Classic ---------------------------------------------------------

//#define Wecker               // Über ein externes Weckeruhrwerk wird eine Weckfunktion aktiviert
                            // TonUINO wird eingeschaltet und ein vordefinierter Shortcut als Wecker abgespielt
#ifdef Wecker               // Der Dialog zum Erstellen des Weckershortcuts wird im Adminmenü aktiviert.
 #ifndef SpkOnOff           // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
   #define SpkOnOff         // Hardwareerweiterung für TonUINO Classic erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
  #endif
#endif

// ------------------- Lese-Empfindlichkeit des RFID-Lesers --- AiO und Classic ----------------------------------------------------
// Bei Leseproblemen des RFID Lesers kann die Leseempfindlichkeit verändert werden.
#define NFCgain_avg           // Mittlere Empfindlichkeit RFID Leser - Default wert
//#define NFCgain_max           // Maximale Empfindlichkeit RFID Leser
//#define NFCgain_min           // Minimale Empfindlichkeit RFID Leser

// ------------------------------------------------------------------------------------------------------------------------------------
const uint8_t setVolChSp = 8 ;  // Vorgabe Geschwindigkeit Volume Änderung bei Lautstärkeeinstellung
                                // über longPress der Lautstärketasten. Wert zwischen 1 und 20. 
                                // Je größer der Wert um so langsamer die Lautstärkeänderung
// ------------------------------------------------------------------------------------------------------------------------------------                                
// ************************************************************************************************
// *************** Einbinden der Bibliotheken *****************************************************

#include <DFMiniMp3.h>
#include <EEPROM.h>
#include <JC_Button.h>
#include <MFRC522.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#ifndef AiO
#include <avr/sleep.h>
#endif
#ifdef LED_SR
#include <Adafruit_NeoPixel.h>
#endif

#ifndef AiO                       // Definitionen für TonUINO Classic

//******************* Definitionen der Pins für TonUINO Classic ****************************

// ------------------ Analog-Pins -------------------------------

#define ButtonPause A0            // Taste Play / Pause

#define ButtonUp A1               // Taste Vor / Lauter
#define ButtonDown A2             // Taste Zurück / Leiser

#ifdef FIVEBUTTONS

#define ButtonFourPin A3          // Taste 4
#define ButtonFivePin A4          // Taste 5

#endif

#ifdef EarPhone
#define EarPhonePin A5            // Kontrollpin Kopfhörer angeschlossen
#endif

#ifdef Wecker
#define WeckerPin A6              // Eingangspin zum Abspielen Wecker-shortcut
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl

// ----------------- Digital-Pins ---------------------------------

#define BusyPin 4                 // Busy Signal vom DF-Player
#define LedPin 5                  // Daten für Neopixel-LED-Ring

#ifdef SpkOnOff
#define SpkOnPin 6                // Lautsprecher Ein/Aus
#endif

#ifdef HW_PowerOff
#define ShutDownPin 7             // Abschaltung ueber MosFet oder Polulo-Switch
#endif

#define RstPin 9                  // MFRC 522 -RST
#define SdaPin 10                 // MFRC 522 -SDA

#endif                            // Ende Definitionen TonUINO Classic


#ifdef AiO
//******************* Definitionen der Pins für AiO ********************************

// Boardbeschreibung des AiO Boards Pin-Belegung und Zuordnung

//  D5, A6 and A7 are wired to the extension port.

//  D6 is wired to the button breakout board (labled WS(D6)).

//  D9 (RST), D10 (SDA), D11 (MOSI), D12 (MISO) and D13 (SCK) are wired to the nfc breakout board.

//  the rest of the pins are hard wired as per below.

//  button0Pin = A0;                      // play/pause/power on

//  button1Pin = A1;                      // prev

//  button2Pin = A2;                      // next

//  button3Pin = A3;                      // vol-

//  button4Pin = A4;                      // vol+

//  onboardSdAccessControlPin = A5;       // control pin of the external sd card access (HIGH = enabled, LOW = disabled)

//  mp3SerialRxPin = 2;                   // mp3 serial rx, wired to tx pin of the mp3 chip

//  mp3SerialTxPin = 3;                   // mp3 serial tx, wired to rx pin of the mp3 chip

//  busyPin = 4;                          // reports play state of the mp3 chip (HIGH = not playing, LOW = playing)

//  powerControlPin = 7;                  // control pin used to power the system (HIGH = power on, LOW = power off)

//  onboardAmpControlPin = 8;             // control pin of the onboard amp (HIGH = amp off, LOW = amp on)



// ---------------- Analog-Pins ----------------------------------

#define ButtonPause A0            // Taste Play / Pause

#define ButtonDown A1             // Taste Zurück / Leiser
#define ButtonUp A2               // Taste Vor / Lauter

#ifdef FIVEBUTTONS

#define ButtonFivePin A3          // Taste 5 - Taste Vor    / Lauter 5 Tastenmodus
#define ButtonFourPin A4          // Taste 4 - Taste Zurück / Leiser 5 Tastenmodus

#endif

#define Access_SD_Pin A5          // Pin zur Freigabe des SD-Kartenzugriffs über USB
                                  // control pin of the external sd card access (HIGH = enabled, LOW = disabled)

#ifdef Wecker
#define WeckerPin A6              // Eingangspin zum Abspielen Wecker-shortcut (Extension Board)
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl (Extension Board)



// ---------------- Digital-Pins ----------------------------------
#define BusyPin 4                 // Busy Signal vom DF-Player

#ifdef EarPhone
#define EarPhonePin 5             // Sensorpin, ob Kopfhörer angeschlossen (Extension Board) 
#endif                            // Auswertung nur möglich wenn die fest verdrahtete Abschaltleitung der KH-Buchse
                                  // aufgetrennt wird und das Signal für den Sensorpin genutzt wird.
#ifdef LED_SR
#define LedPin 6                  // Daten für Neopixel-LED-Ring (ButtonBreakout Board)
#endif

#define ShutDownPin 7             // Ein/Ausschaltsignal
                                  // control pin used to power the system (HIGH = power on, LOW = power off)
#ifdef SpkOnOff
#define SpkOnPin 8                // Verstärker Ein/Ausschalten
#endif                            // control pin of the onboard amp (HIGH = amp off, LOW = amp on)

#define RstPin 9                  // MFRC 522 -RST
#define SdaPin 10                 // MFRC 522 -SDA

#endif
// ****************** Definitionen für letzte gespielte Karte als Shortcut auf Playtaste legen ***********************

#ifdef LastCard
#define folderReg 201             // Ordner
#define modeReg 202               // Abspielmodus
#define specialReg 203            // Starttrack Spezial von-bis
#define specialReg2 204           // Endtrack Spezial von-bis
#endif

// ******************** Definitionen für LED Animation *** by t@on ****************************************************

#ifdef LED_SR

// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LedPin, NEO_GRB + NEO_KHZ800);

// Zählvarbiablen
uint16_t loopCount;                             // Runterzählen der Loops
uint16_t loopCountWait;                         // Definierte Anzahl wieviele Loops runtergezählt werden sollen, also wie lange gewartet wird
uint8_t animCount;                              // Wie oft die einmalige Animation ausgeführt wird bevor es zurück in die Hauptschleife (Animationsmodus 0) geht
uint8_t x;
uint8_t y;
uint8_t z;
uint8_t i;

// Datenvariablen
uint32_t lsrColorUp = strip.Color(0, 255, 0);   // Farbe wird bei Animation nächstes Lied verwendet
uint32_t lsrColorDown = strip.Color(0, 0, 255); // Farbe wird bei Animation Lied zurück verwendet
uint8_t currentDetectedVolume;                  // Speichern der aktuellen Lautstärke für späteren Vergleich
uint8_t lastDetectedVolume;                     // Speichern der Lautstärke um die Animation nur ein mal zu triggern
uint8_t volumeScope;                            // Differenz der von euch eingestellten minimalen und maximalen Lautstärke
uint8_t volumeScopeAmount;                      // Lautstärkenwert in deinem Scope
uint8_t lsrAnimationMode;                       // Animationsmodus - 0: Daueranimation, 1-2 einmalige Animation (als Unterbrechung zu 0)
uint8_t lsrAnimationTrackMode;                  // Bei Animationsmodus Liedwechsel bestimmung der Farbe und Richtung
uint32_t lsrHueCalc;                            // Zwischenspeicher einer Farbe
uint32_t lsrColors;                             // Zwischenspeicher einer Farbe
uint8_t lsrColorR[LED_COUNT];                   // Zwischenspeicher des Rot-Wertes für alle LEDs
uint8_t lsrColorG[LED_COUNT];                   // Zwischenspeicher des Grün-Wertes für alle LEDs
uint8_t lsrColorB[LED_COUNT];                   // Zwischenspeicher des Blau-Wertes für alle LEDs
uint8_t currentDetectedTrack;                   // Speichern des aktuellen Tracks für späteren Vergleich
uint8_t lastDetectedTrack;                      // Speichern des Tracks um die Animation nur ein mal zu triggern

#ifdef LED_SR_Switch
bool lsrSwitch = false;                         // Ein-Ausschalten aktiviert, true wenn up und down Button long press
bool lsrEnable = true;                          // LED-Animation-Freigabe
bool lsrAudioBreak = false;                     // Wiedergabe gestoppt während Ein-Ausschalten LED-Animation .
bool lsrOffByStdby = false;                     // Ausschaltsignal LED-Animation durch Standbytimer Software only
#endif
#endif

// ******************** sonstige Variablen ****************************************************************************
// ----------------Lautstärkemanagement -----------------------
uint8_t SpkVol;                                 // Lautstärke für den Lautsprecher
uint8_t EarVol;                                 // Lautstärke für den Kopfhörer
uint8_t MenuVol = MenueVolume;                  // Lautstärke für das Adminmenü auf Festwert
bool longPressVol = false;                      // VolÄnderung durch longPress
uint8_t countVolCh = 0 ;                        // Zählvariable speed VolÄnderung
bool msgMin = true ;                            // Message minimale Lautstärke erreicht
bool msgMax = true ;                            // Message maximale Lautstärke erreicht

// --------------- Kopfhörer, Lautsprecher und Wecker ------------
#ifdef EarPhone
int Ear;                                        // Abfrageergebnis Pinabfrage EarPhonePin
#endif
#ifdef SpkOnOff
bool SpkisOn = false;                           // Marker Lautsprecher Ein/Aus, Voreinstellung Aus
bool EarFirstTime = true;                       // Marker, ob Kopfhörer das erste mal eingesteckt wird, Voreinstellung JA
#endif
#ifdef Wecker
bool ActWecker = false;                         // Wecker ist aktiviert worden, Voreinstellung NEIN
#endif
bool WeckerPlay = false;                        // Weckershortcut wird gespielt, Voreinstellung NEIN

bool ShortCutIsPlaying = false ;                // Shortcut wird gespielt, Voreinstellung NEIN

bool SETUP = true;                              // ist true solange setup() durchlaufen wird

bool StdBy = false;                             // StanbyTimer aktiviert, Voreinstellung NEIN

// ------------------------ Adminmenü ----------------
uint8_t progmode = 0;                           // Modus für die Programmierung der Karten und shortcuts
unsigned long Minuten = 2;                      // AdmTimeOut Vorgabe, Zeit in Minuten
unsigned long AdmTimeOut = 0;                   // Abgelaufene TimeOutzeit
unsigned long SollAdmTimeOut = Minuten * 60000; // AdmTimeOut Vorgabe Zeit ,Minuten * Millisekunden/minute
bool AbbrActive = false;                        // Adminmenü abgebrochen, Voreinstellung Nein
bool AdjVol = false;                            // Adminmenü in Vol-Einstellungen, Voreinstellung Aus

// ----------------------- Cookies --------------------
#ifndef EarPhone
static const uint32_t myCookie = 202012110;     // Cookie zum Erkennen einer Softwareversion mit geänderter mySettings Struktur
#endif                                          // sorgt für einen automatischen Reset der mySettings bei geänderter Struktur
#ifdef EarPhone
static const uint32_t myCookie = 202012111;     // Cookie zum Erkennen einer Softwareversion mit geänderter mySettings Struktur
#endif                                          // sorgt für einen automatischen Reset der mySettings bei geänderter Struktur

static const uint32_t cardCookie = 322417479;   // Cookie zum Erkennen der TonUINO-RFID Karten
                                                // sorgt für das automatische Starten der Kartenkonfiguration bei neuen Karten

//*********************** Buttons ************************
#define LONG_PRESS 1000                         // langer Druck >= 1 sekunde

Button pauseButton(ButtonPause);
Button upButton(ButtonUp);
Button downButton(ButtonDown);
#ifdef FIVEBUTTONS
Button buttonFour(ButtonFourPin);
Button buttonFive(ButtonFivePin);
#endif
bool ignorePauseButton = false;                 // Taste übergehen, Voreinstellung Nein
bool ignoreUpButton = false;                    // Taste übergehen, Voreinstellung Nein
bool ignoreDownButton = false;                  // Taste übergehen, Voreinstellung Nein
#ifdef FIVEBUTTONS
bool ignoreButtonFour = false;                  // Taste übergehen, Voreinstellung Nein
bool ignoreButtonFive = false;                  // Taste übergehen, Voreinstellung Nein
#endif

//********************* RFID Reader ***********************
// MFRC522
MFRC522 mfrc522(SdaPin, RstPin);                // Create MFRC522
MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
MFRC522::StatusCode status;

// ******************** DF-Player **************************
// DFPlayer Mini
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX   // Digitalpins zur Steuerung des DF-Players
uint8_t numFolders;                                // Anzahl der Ordner im Speichermedium
uint8_t numTracksInFolder;                         // Anzahl der Tracks im Ordner
uint8_t firstTrack;                                // erster Track
uint8_t currentQueueIndex;                         // index in queue[] aktuelle Tracknr in der queue
uint8_t queueSize;                                 // Länge der queue
uint8_t queue[255];                                // max 255 tracks/folder. entries 0..254 and values 1..255 are used.
uint8_t volume;                                    // Lautstärke

struct folderSettings {                            // Struktur der Foldersettigs
  uint8_t folder;                                  // Ordnernummer
  uint8_t mode;                                    // Abspielmodus
  uint8_t special;                                 // Specialmodus Start-track
  uint8_t special2;                                // Specialmodus End-track
};

// this object stores nfc tag data
struct nfcTagObject {                              // Struktur der RFID-Karte
  uint32_t cookie;                                 // Card-ID
  uint8_t version;                                 // Version von my settings
  folderSettings nfcFolderSettings;                // Daten für Ordner,Track und Abspielmodi
  //  uint8_t folder;                              // Ordnernummer
  //  uint8_t mode;                                // Abspielmodus
  //  uint8_t special;                             // Starttrack Mode spezial
  //  uint8_t special2;                            // Enddtrack Mode spezial
};

struct adminSettings                               // admin settings stored in eeprom
{
  uint32_t cookie;
  byte version;                                    // Version der settings
  uint8_t maxVolume;                               // max Lautstärke Lautsprecher
  uint8_t minVolume;                               // min Lautstärke Lautsprecher
  uint8_t initVolume;                              // start Lautstärke Lautsprecher
  #ifdef EarPhone
  uint8_t maxEarVol;                               // max Lautstärke Kopfhörer
  uint8_t minEarVol;                               // min Lautstärke Kopfhörer
  uint8_t initEarVol;                              // start Lautstärke Kopfhörer
  #endif
  uint8_t eq;                                      // equalizer einstellung
  long standbyTimer;                               // standbytimer time
  bool invertVolumeButtons;                        // Funktion LS Tasten umdrehen
  folderSettings shortCuts[5];                     // 5 shortcuts, (3 Tasten, welcomesound + Wecker)
  uint8_t adminMenuLocked;                         // Schutz des Adminmenüs
};

adminSettings mySettings;                          // Hardwareconfigurationen in EEPROM
nfcTagObject myCard;                               // settings für Kartenprogrammierung
folderSettings *myFolder;
unsigned long sleepAtMillis = 0;                   // Variable für den Standbytimer
static uint16_t _lastTrackFinished;

static void nextTrack(uint16_t track);             // Track weiterschalten

uint8_t voiceMenu                                  // Rückgabewert des voiceMenü
  (int numberOfOptions,                            // Anzahl der Optionen
  int startMessage,                                // Tracknummer Startansage
  int messageOffset,                               // Tracknummer der Folgeansage
  bool preview = false,                            // Vorschau aktiv , Voreinstellung NEIN
  int previewFromFolder = 0,                       // Vorschau von Ordner
  int defaultValue = 0,                            // Standartwert
  bool exitWithLongPress = false);                 // Abbruch mit LongPress, Voreinstellung NEIN

bool isPlaying();                                  // Marker Wiedergabe läuft
void writeCard(nfcTagObject nfcTag);               // Funktion Karte schreiben
void dump_byte_array(byte * buffer, byte bufferSize); // Auslesen HEX Daten
void adminMenu(bool fromCard = false);             // Start Adminmenü von Karte, Voreinstellung NEIN
void playShortCut(uint8_t shortCut);               // Shortcut Spielen 
bool knownCard = false;                            // Karte bekannt, Voreinstellung NEIN

// ***************** Error-meldungen des df-players **************************

// implement a notification class,
// its member methods will get called
// used by DFPlayer Mini library during callbacks

class Mp3Notify {
  public:

    static void OnError(uint16_t returnValue)
    {
#ifdef Konsole
      switch (returnValue)
      {
        case DfMp3_Error_Busy: {
            Serial.print(F("1- busy"));               // Es läuft eine Wiedergabe
            break;
          }
        case DfMp3_Error_Sleeping: {
            Serial.print(F("2- sleep"));              // Df Player im Sleepmodus
            break;
          }
        case DfMp3_Error_SerialWrongStack: {
            Serial.print(F("3- memory"));             // Fehler interer Speicher
            break;
          }
        case DfMp3_Error_CheckSumNotMatch: {
            Serial.print(F("4-Hw-communication"));    // Hardware Kommunikationsfehler
            break;
          }
        case DfMp3_Error_FileIndexOut: {
            Serial.print(F("5- file index Out "));    // Dateinummer außerhalb des Bereiches
            break;
          }
        case DfMp3_Error_FileMismatch: {
            Serial.print(F("6- file not found"));     // Datei nicht gefunden
            break;
          }
        case DfMp3_Error_Advertise: {
            Serial.print(F("7- advertise"));         // Fehler beim Abspielen Advert
            break;
          }
        case DfMp3_Error_RxTimeout: {
            Serial.print(F("rx timeout"));           // Zeitüberschreitung RX-Signal
            break;
          }
        case DfMp3_Error_PacketSize: {
            Serial.print(F("packet size"));          // Fehler Sektorgröße
            break;
          }
        case DfMp3_Error_PacketHeader: {
            Serial.print(F("packet header"));        // Fehler Header
            break;
          }
        case DfMp3_Error_PacketChecksum: {
            Serial.print(F("packet checksum"));      // Prüfsummenfehler
            break;
          }
        case DfMp3_Error_General: {
            Serial.print(F("general"));              // allgemeiner Fehler
            break;
          }
        default: {
            Serial.print(F("unknown"));              // unbekannter Fehler
            break;
          }
      }
      Serial.println(F(" error"));
#endif
    }

    // Speichermedium der Sounddateien
    static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
    {
      if (source & DfMp3_PlaySources_Sd) Serial.print("SD Karte ");
      if (source & DfMp3_PlaySources_Usb) Serial.print("USB ");
      if (source & DfMp3_PlaySources_Flash) Serial.print("Flash ");
      Serial.println(action);
    }

    // Track beendet
    static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track)
    {
      delay(100);
      nextTrack(track);
    }

    // Speichermedium online
    static void OnPlaySourceOnline(DfMp3_PlaySources source)
    {
      PrintlnSourceAction(source, "online");
    }

    // Speichermedium bereit
    static void OnPlaySourceInserted(DfMp3_PlaySources source)
    {
      PrintlnSourceAction(source, "bereit");
    }

    // Speichermedium entfernt
    static void OnPlaySourceRemoved(DfMp3_PlaySources source)
    {
      PrintlnSourceAction(source, "entfernt");
    }
};

static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(mySoftwareSerial);

// ************** Initialisierung der queue ******************
void initQueue(uint8_t from, uint8_t to)                    // Von und Bis eingeschlossen
{
  firstTrack = from;                                        // erster Track -> von
  queueSize = to - from + 1;                                // Länge der queue berechnen
  for (uint8_t x = 0; x < queueSize; x++)
    queue[x] = x + from;
}

// ************* Zufallsliste erstellen ***********************
void shuffleQueue()                                         // Queue für die Zufallswiedergabe erstellen
{
  for (uint8_t i = 0; i < queueSize; i++)
  {
    uint8_t j = random(i, queueSize);                       // elems [i .. queueSize] remain, pick one
    uint8_t t = queue[i];
    queue[i] = queue[j];
    queue[j] = t;
  }
}

// ************* Track Index **********************************
uint8_t findQueueIndex(uint8_t track)                       // Track Index finden
{
  for (uint16_t i = 0; i < queueSize; i++)
  {
    if (queue[i] == track) return i;                        // return index with queue[index]==track
  }
  return 0xff;                                              // return 0xff if queue does not contain track
}

// ********** Namen der Abspielmodi *******************************
const PROGMEM char* getModeName(uint8_t mode)
{
  switch (mode)
  {
    case 1:   return PSTR("Hörspielmodus");
    case 2:   return PSTR("Album Modus");
    case 3:   return PSTR("Party Modus");
    case 4:   return PSTR("Einzel Modus");
    case 5:   return PSTR("Hörbuch Modus");
    case 6:   return PSTR("Von-Bis: Hörspiel");
    case 7:   return PSTR("Von-Bis: Album");
    case 8:   return PSTR("Von-Bis: Party");
    case 9:   return PSTR("Adminkarte erstellen");
    default:  return PSTR("?");
  }
}

// *****************************************************************
// helper to print string from PROGMEM pointer
#ifdef Konsole
void Serial_println_F(const PROGMEM char* str) {
  Serial.println((const __FlashStringHelper*)str);
}
void Serial_print_F  (const PROGMEM char* str) {
  Serial.print  ((const __FlashStringHelper*)str);
}
#endif

// ********************************* my Settings ********************
void writeSettingsToFlash() {               // my Settings im EEPROM speichern
#ifdef Konsole
  Serial.println(F("Settings -> Flash"));
#endif
  int address = sizeof(myFolder->folder) * 100;
#ifndef AiO
  EEPROM.put(address, mySettings);
#endif
#ifdef AiO
  EEPROM_put(address, mySettings);
#endif
}

// ******************************* Reset my Settings ****************
void resetSettings() {                     // my Settings auf defaultwerte zurücksetzen
#ifdef Konsole
  Serial.println(F("Reset Settings"));
#endif
  mySettings.cookie = myCookie;
  mySettings.version = 2;
  mySettings.maxVolume = 25;               // max.Lautstärke Lautsprecher
  mySettings.minVolume = 5;                // min.Lautstärke Lautsprecher
  mySettings.initVolume = 15;              // Start-Lautstärke Lautsprecher
#ifdef EarPhone
  mySettings.maxEarVol = 20;               // max.Lautstärke Kopfhörer
  mySettings.minEarVol = 3;                // min.Lautstärke Kopfhörer
  mySettings.initEarVol = 10;              // Start-Lautstärke Kopfhörer
#endif
  mySettings.eq = 1;                       // Equalizer Normal
  mySettings.standbyTimer = 5;             // Standbytimer auf 5 min
  mySettings.invertVolumeButtons = false;  // Funktion der Vol-Tasten umkehren AUS
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Pausetaste
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-taste
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-taste
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Welcomesound
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Weckersound
  mySettings.adminMenuLocked = 0;          // 0 = Adminmenü nicht geschützt,
                                           // 1 = Schutz durch Adminkarte,

  writeSettingsToFlash();                  // Settings im EEPROM speichern
}

// ****************************************************************************
void migrateSettings(int oldVersion) {
  if (oldVersion == 1) {
#ifdef Konsole
    Serial.println(F("ResetSettings"));
    Serial.println(F("1 -> 2"));
#endif
    mySettings.version = 2;
    mySettings.adminMenuLocked = 0;
    writeSettingsToFlash();
  }
}

// ******************* my Settings vom EEPROM laden ***************************
void loadSettingsFromFlash()
{
#ifdef Konsole
  Serial.println(F("load Settings from Flash"));
#endif
  int address = sizeof(myFolder->folder) * 100;
#ifndef AiO
  EEPROM.get(address, mySettings);
#endif
#ifdef AiO
  EEPROM_get(address, mySettings);
#endif
  if (mySettings.cookie != myCookie)
    resetSettings();
  migrateSettings(mySettings.version);

  // ****************** my Settings im Ser Monitor anzeigen *********************
  //#ifdef Konsole
  Serial.print(F("Version: "));
  Serial.println(mySettings.version);

  Serial.print(F("Max Vol.Lsp : "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Min Vol.Lsp : "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Init Vol.Lsp: "));
  Serial.println(mySettings.initVolume);

#ifdef EarPhone 
  Serial.print(F("Max Vol.Ear : "));
  Serial.println(mySettings.maxEarVol);

  Serial.print(F("Min Vol.Ear : "));
  Serial.println(mySettings.minEarVol);

  Serial.print(F("Init Vol. Ear : "));
  Serial.println(mySettings.initEarVol);
#endif
  Serial.print(F("EQ: "));
  Serial.println(mySettings.eq);

  Serial.print(F("StBy Timer: "));
  Serial.println(mySettings.standbyTimer);

  Serial.print(F("Inv.Vol.Buttons: "));
  Serial.println(mySettings.invertVolumeButtons);

  Serial.print(F("Adm.Menu locked: "));
  Serial.println(mySettings.adminMenuLocked);
#ifndef LastCard
  Serial.print(F("ShortCut-0: "));
  Serial.println(mySettings.shortCuts[0].folder);
#endif
#ifdef LastCard
  Serial.print(F("ShortCut-0: "));
  Serial.println(F("Reserviert für Letzte Karte !"));
#endif
  Serial.print(F("ShortCut-1: "));
  Serial.println(mySettings.shortCuts[1].folder);

  Serial.print(F("ShortCut-2: "));
  Serial.println(mySettings.shortCuts[2].folder);

  Serial.print(F("ShortCut-3, Begrüßung : "));
  Serial.println(mySettings.shortCuts[3].folder);
#ifdef Wecker
  Serial.print(F("ShortCut-4, Wecker : "));
  Serial.println(mySettings.shortCuts[4].folder);
#endif
#ifndef Wecker
  Serial.print(F("ShortCut-4: "));
  Serial.println(F("Reserviert für Weckersound !"));
#endif
  Serial.println();
  //#endif
}

// **************** Tasten und RFID Sperren ********************
void LockPause()
{
#ifdef Konsole
  Serial.println(F("Pause -> LOCKED!"));      // Play/Pausetaste speren
#endif
  return true;
}

void LockNext()
{
#ifdef Konsole
  Serial.println(F("Next -> LOCKED!"));      // Nächster Titel sperren
#endif
  return true;
}

void LockPrevious()
{
#ifdef Konsole
  Serial.println(F("Previous -> LOCKED!"));  // Vorhergehender Titel sperren
#endif
  return true;
}

void LockVolUp()
{
#ifdef Konsole
  Serial.println(F("VolumeUp -> LOCKED!"));  // Lautertaste sperren
#endif
  return true;
}

void LockVolDown()
{
#ifdef Konsole
  Serial.println(F("VolumeDown -> LOCKED!")); // Leisertaste sperren
#endif
  return true;
}

void LockRFID()
{
#ifdef Konsole
  Serial.println(F("RFID -> LOCKED!"));       // Neue Karte abspielen sperren
#endif
  return true;
}

//********************** Modifikationskarten *****************************
//************************************************************************

class Modifier {
  public:
    virtual void loop() {}

    virtual bool handlePause() {
      return false;
    }
    virtual bool handleNext() {
      return false;
    }
    virtual bool handlePrevious() {
      return false;
    }
    virtual bool handleNextButton() {
      return false;
    }
    virtual bool handlePreviousButton() {
      return false;
    }
    virtual bool handleVolumeUp() {
      return false;
    }
    virtual bool handleVolumeDown() {
      return false;
    }
    virtual bool handleRFID(nfcTagObject *newCard) {
      return false;
    }
    virtual uint8_t getActive() {
      return 0;
    }
    Modifier() {
    }
};

Modifier *activeModifier = NULL;

//*** Modkarte **** Sleeptimer mit Ausfaden Lautstärke und Tastensperre ************
// Dieses Modifier wird zusätzlich genutzt beim shutdown wenn Batterie leer. Zeit 30 Sekunden.

class SleepTimer : public Modifier
{
  private:
    unsigned long sleepAtMillis = 0;
    unsigned long lastVolCheck = 0;
    uint16_t lastVolume = 0;
#ifdef LED_SR
    unsigned long Brightn = 25;                          // Startwert für Ausfaden der Helligkeit der LED-Animation
#endif

  public:

    void loop()
    {
      if (this->sleepAtMillis > 0 && millis() > this->sleepAtMillis)
      {
#ifdef Konsole
        Serial.println(F("SleepTimer -> SLEEP!"));
#endif
        mp3.pause();

        mySettings.standbyTimer = 99;                     // Setzt die Variable für den Standbytimer auf 99,
                                                          // damit nach Ablauf des Sleeptimers
                                                          // der Standbytimer sofort ausschaltet.

        setstandbyTimer();
        activeModifier = NULL;
        delete this;
      }
      else                                                // Prüfen ob die letzten 20 Sekunden laufen
      {                                                   // Lautstärke ausfaden
        if (isPlaying() && this->sleepAtMillis > 0 && millis() > this->sleepAtMillis - 20000
            && millis() > this->lastVolCheck + 1000)
        {
          if (this->lastVolume <= 0)
          {
            this->lastVolume = volume;
          }
          this->lastVolCheck = millis();
          uint16_t val = this->lastVolume - map(this->lastVolCheck, this->sleepAtMillis - 20000,
                                                this->sleepAtMillis, 0, this->lastVolume);
          mp3.setVolume(val);
#ifdef Konsole
          Serial.print(F("Ausfaden Volume: "));
          Serial.println(val);
#endif
#ifdef LED_SR                                  // Helligkeit der LED Animation ausfaden
          Brightn = (val) ;
          if (Brightn >= 6)
          {
            strip.setBrightness(Brightn);
          }
#endif
        }
      }
    }

    //****************** SleepTimer (Schlummermodus) ***********************
    // Nach Auflegen der Modifikationskarte "Schlummermodus" wird der Tonuino
    // bei laufender Wiedergabe, nach Ablauf der voreingestellten Zeit ausgeschaltet.
    // Tasten und neue Karte sind gesperrt.
    // Die letzten 20 Sekunden wird die Lautstärke gleichmäßig auf 0 verringert.
    // Danach schaltet der Standbytimer sofort AUS.

    //SleepTimer(uint8_t minutes)
    SleepTimer(float minutes)                       // Variablentyp auf float geändert für Werte < 1
    {
#ifdef Konsole
      Serial.print(F("SleepTimer: "));
      Serial.print(minutes);
      Serial.println(F(" min"));
#endif
      this->sleepAtMillis = millis() + minutes * 60000;
      this->lastVolCheck = millis();

      {
        delay(500);
        mp3.playAdvertisement(302);                   //advert-302- Schlummerfunktion aktiviert.
        delay(500);
      }
    }

    //************ Tasten und neue Karte im Sleepmode sperren *************
    //Für Tasten die nicht gesperrt werden sollen, jeweils die 5 zugehörigen Zeilen mit // deaktivieren
    /*  // ---------------------------------------------------------------
        virtual bool handlePause()
        {
          LockPause();           // Play/Pausetaste sperren
        }
    */  // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();             // Next Taste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();         // Zurück Taste sperren
    }
    // ---------------------------------------------------------------
    /*virtual bool handleVolumeUp()
      {
      LockVolUp();         // Lautertaste sperren
      }
      // ---------------------------------------------------------------
      virtual bool handleVolumeDown()
      {
      LockVolDown();      // Leisertaste sperren
      }
      // ---------------------------------------------------------------
    */
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();           // Neue Karte abspielen sperren
    }
    // ---------------------------------------------------------------
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));      // Deaktivieren durch erneutes Auflegen dieser
                                             // oder einer anderen Modifikationskarte
#endif
      return 1;
    }
};

//**** Modkarte ****** Stopptanz *************************************
// Nach Auflegen der Modifikationskarte "Stopptanz" wird die laufende Wiedergabe
// in unregelmäßigen Zeitabständen angehalten und nach kurzer Pause fortgesetzt.
// Lustiges Spiel.

class FreezeDance: public Modifier
{
  private:
    unsigned long nextStopAtMillis = 0;               // Zeitvariable für nächsten Stop
    const uint8_t minSecondsBetweenStops = 15;        // Minimalzeit zwischen den Stops
    const uint8_t maxSecondsBetweenStops = 40;        // Maximalzeit zwischen den Stops

    void setNextStopAtMillis()
    {
      uint16_t seconds = random(this->minSecondsBetweenStops, this->maxSecondsBetweenStops + 1);

#ifdef Konsole
      Serial.print(F("FreezeDance->NextStop in: "));
      Serial.print(seconds);
      Serial.println(" sek");
#endif
      this->nextStopAtMillis = millis() + seconds * 1000;
    }

  public:
    void loop()
    {
      if (this->nextStopAtMillis != 0 && millis() > this->nextStopAtMillis)
      {
#ifdef Konsole
        Serial.println(F(" -> FREEZE!"));
#endif
        if (isPlaying())
        {
          mp3.playAdvertisement(301);               //advert-301- Und Stopp!**Ticken**Nicht bewegen!**Ticken**weiter geht´s!
          delay(500);
        }
        else
        {
          if (StdBy == false)
            setstandbyTimer();
        }
        setNextStopAtMillis();                      // Zeit zum nächsten Stop setzen
      }
    }
    FreezeDance(void)
    {
#ifdef Konsole
      Serial.println(F("FreezeDance "));
#endif
      if (isPlaying())                              // Bei laufender Wiedergabe
      {
        mp3.playAdvertisement(300);                 //advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
      }
      else                                          // Wenn keine Wiedergabe läuft
      {
        mp3.start();                                // Wiedergabe des letzt gespielten Titels starten
        mp3.playAdvertisement(300);                 //advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
      }


      setNextStopAtMillis();
    }
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));               // Deaktivieren durch erneutes Auflegen dieser
#endif                                                // oder einer anderen Modifikationskarte
      return 2;
    }
};

// ****** Modkarte *** TonUINO Sperren *************************************
// Nach Auflegen der Modifikationskarte "TonUINO Sperren"
// sind alle Tasten und neue Karte lesen gesperrt.

class Locked: public Modifier
{
  public:
    // ---------------------------------------------------------------
    virtual bool handlePause()
    {
      LockPause();           // Play/Pausetaste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();              // Next Taste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();         // Zurück Taste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeUp()
    {
      LockVolUp();           // Lautertaste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();         // Leisertaste sperren
    }
    // ---------------------------------------------------------------

    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();             // Neue Karte abspielen sperren
    }
    // ---------------------------------------------------------------

    Locked(void)
    {
#ifdef Konsole
      Serial.println(F("Gesperrt!"));
#endif
      //delay(500);
      mp3.playAdvertisement(303);                     // advert-303- TonUINO ist nun gesperrt.
      //delay(500);

    }
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));               // Deaktivieren durch erneutes Auflegen dieser
#endif                                                // oder einer anderen Modifikationskarte
      return 3;
    }
};

//**** Modkarte ********* Krabblermodus *************************************
// Nach Auflegen der Modifikationskarte "Krabblermodus"
// sind die Tasten gesperrt.
// Alle Tasten gesperrt , nur Karten funktionieren.

class ToddlerMode: public Modifier
{
  public:
    // ---------------------------------------------------------------
    virtual bool handlePause()
    {
      LockPause();           // Play/Pausetaste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();            // Next Taste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();        // Zurück Taste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeUp()
    {
      LockVolUp();           // Lautertaste sperren
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();         // Leisertaste sperren
    }
    /*/ ---------------------------------------------------------------

      virtual bool handleRFID(nfcTagObject *newCard)
      {
      LockRFID();            // Neue Karte abspielen sperren
      }
    */
    // ---------------------------------------------------------------
    ToddlerMode(void)
    {
#ifdef Konsole
      Serial.println(F("ToddlerMode"));
#endif
      if (isPlaying())                            // Wenn Wiedergabe läuft
      {
        mp3.playAdvertisement(304);               // advert-304- Tasten sind nun gesperrt.
      }
      else                                        // wenn keine Wiedergabe läuft
      {
        mp3.start();                              // Start der Wiedergabe des letzt gespielten Titels
        mp3.playAdvertisement(304);               // advert-304- Tasten sind nun gesperrt.
      }

    }
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));            // Deaktivieren durch erneutes Auflegen dieser
#endif                                             // oder einer anderen Modifikationskarte
      return 4;
    }
};

//**** Modkarte ********* KiTa Modus *************************************
// Nach Auflegen der Modifikationskarte "KiTa Modus"
// sind die Vor und Zurück-tasten Gesperrt,
// Eine neue aufliegende Karte wird erst nach Beenden des aktuellen Tracks gespielt.

class KindergardenMode: public Modifier
{
  private:
    nfcTagObject nextCard;
    bool cardQueued = false;

  public:
    virtual bool handleNext()
    {
#ifdef Konsole
      Serial.println(F("NEXT"));
#endif
      //if (this->nextCard.cookie == cardCookie && this->nextCard.nfcFolderSettings.folder != 0 &&
      //this->nextCard.nfcFolderSettings.mode != 0) {
      //myFolder = &this->nextCard.nfcFolderSettings;
      if (this->cardQueued == true)
      {
        this->cardQueued = false;

        myCard = nextCard;
        myFolder = &myCard.nfcFolderSettings;
#ifdef Konsole
        Serial.println(myFolder->folder);
        Serial.println(myFolder->mode);
#endif
        playFolder();
        return true;
      }
      return false;
    }
    //    virtual bool handlePause()
    //    {
    //      LockPause();                            // Pausetaste gesperrt
    //
    //    }
    virtual bool handleNextButton()
    {
      LockNext();                                   // VorTaste gesperrt

    }
    virtual bool handlePreviousButton()
    {
      LockPrevious();                               // ZurückTaste gesperrt

    }


    virtual bool handleRFID(nfcTagObject * newCard)
    {
#ifdef Konsole
      Serial.println(F("RFID -> queued!"));
#endif
      this->nextCard = *newCard;
      this->cardQueued = true;
      if (!isPlaying())                            // wenn laufender Track beendet
      {
        handleNext();
      }
      return true;
    }

    KindergardenMode()
    {
#ifdef Konsole
      Serial.println(F("KitaMode"));
#endif
      //delay(500);
      mp3.playAdvertisement(305);                  // advert-305- KiTa-Modus aktiviert.
      //delay(500);

    }
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));            // Deaktivieren durch erneutes Auflegen dieser
#endif                                             // oder einer anderen Modifikationskarte
      return 5;
    }
};

//**** Modkarte ******** Titel endlos wiederholen *************************************
// Nach Auflegen der Modifikationskarte "Titel endlos wiederholen"
// wird der aktuelle Track endlos wiederholt.

class RepeatSingleModifier: public Modifier
{
  public:
    virtual bool handleNext()
    {


#ifdef Konsole
      Serial.println(F("Titel wiederholen Next -> Track wiederholen"));
#endif
      delay(50);
      if (isPlaying()) return true;

      playCurrentTrack();

      _lastTrackFinished = 0;
      return true;
    }
    virtual bool handlePreviousButton()
    {
#ifdef Konsole
      Serial.println(F("Zurück -> Titel wiederholen"));
#endif
      delay(50);
      if (isPlaying()) return true;

      playCurrentTrack();

      _lastTrackFinished = 0;
      return true;
    }
    RepeatSingleModifier()
    {
#ifdef Konsole
      Serial.println(F("RepeatSingleModifier"));
#endif
      //delay(500);
      mp3.playAdvertisement(306);                     // advert-306 - Titel in Endlosschleife
      //delay(500);
    }
    uint8_t getActive()
    {
#ifdef Konsole
      Serial.println(F("deaktiviert"));               // Deaktivieren durch erneutes Auflegen dieser
#endif                                                // oder einer anderen Modifikationskarte
      return 6;
    }
};

//*********************** Ansage der Lautstärke *************************************
// ****************** Ansage deaktiviert *********************************************
// An modifier can also do somethings in addition to the modified action
// by returning false (not handled) at the end
// This simple FeedbackModifier will tell the volume before changing it and
// give some feedback once a RFID card is detected.

/*class FeedbackModifier: public Modifier
  {
  public:
    virtual bool handleVolumeDown()
    {
      if (volume > mySettings.minVolume)
      {
        //mp3.playAdvertisement(volume - 1);
      }
      else
      {
        //mp3.playAdvertisement(volume);
      }
      delay(500);
      Serial.println(F("FeedbackModifier:Leiser!"));
      return false;
    }
    virtual bool handleVolumeUp()
    {
      if (volume < mySettings.maxVolume)
      {
        //mp3.playAdvertisement(volume + 1);
      }
      else
      {
        //mp3.playAdvertisement(volume);
      }
      delay(500);
      Serial.println(F("Feedback: Lauter!"));
      return false;
    }
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      Serial.println(F("Feedback RFID()"));
      return false;
    }
  };
*/


// **************** aktuellen Titel spielen ********************
void playCurrentTrack()
{
#ifdef Konsole
  Serial.print(F("Play queue index: "));
  Serial.print(currentQueueIndex);                                 // Tracknummer in der Queue
  Serial.print(F(" Track: "));
  Serial.println(queue[currentQueueIndex]);                        // Tracknummer im Ordner
#endif
  mp3.playFolderTrack(myFolder->folder, queue[currentQueueIndex]); // Abspielen des aktuellen Titels in der Queue
}


//*********************** Track vor *** Track zurück *****************************
//********************************************************************************

// ************ Track vor (nächster Titel) *********************
static void nextTrack(uint16_t track)
{
  //Serial.println(track);
  if (activeModifier != NULL)
    if (activeModifier->handleNext() == true)
      return;

  if (track == _lastTrackFinished)
  {
    return;
  }
  _lastTrackFinished = track;

  if (knownCard == false)
  {
    // Wenn eine neue Karte angelernt wird soll das Ende eines Tracks nicht
    // verarbeitet werden
    return;
  }
#ifdef Konsole
  Serial.println();
  Serial_print_F(getModeName(myFolder->mode));
  Serial.println(F(" -> nextTrack "));
#endif
  bool bStop = false;

  switch (myFolder->mode)
  {
    case 1: //Hoerspiel
    case 6: //Hoerspiel-SpezialVonBis
    case 4: //EinzelTitel
      bStop = true;                                               // Stop am Ende des Titels
      break;

    case 2: //Album
    case 7: //Album-SpezialVonBis
      if (currentQueueIndex + 1 < queueSize)                      // letzter Track in Queue?
        currentQueueIndex++;
      else                                                        // Ende der Queue
        bStop = true;                                             // Stop am Ende der Queue
      break;

    case 3: //Party
    case 8: //Party-SpezialVonBis
      currentQueueIndex++;
      if (currentQueueIndex == queueSize)                         // Ende der Queue
      {
#ifdef Konsole
        Serial.println(F(" Ende Queue --> mische neu."));
#endif
        shuffleQueue();                                             // Am Ende der Queue soll neu gemischt werden
        currentQueueIndex = 0;                                      // Ende der Queue -> springe zum Start
      }
      break;

    case 5: //Hoerbuch
      if (currentQueueIndex + 1 < queueSize)                        // letzter Track in Queue?
      {
        currentQueueIndex++;
#ifndef AiO
        EEPROM.update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
#endif
#ifdef Konsole
        Serial.println(F("Fortschritt -> EEPROM"));
#endif
        break;
      }
      else                                                              // Ende der Queue
      {
#ifndef AiO
        EEPROM.update(myFolder->folder, 1);                         // Fortschritt zurücksetzen
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, 1);                         // Fortschritt zurücksetzen
#endif
#ifdef Konsole
        Serial.println(F("EEPROM->Reset Fortschritt"));
#endif
        bStop = true;                                               // Stop am Ende der Queue
        break;
      }

    default:
      return; // do nothing
  }
  // *************** queue zu Ende  ***********
  if (bStop)
  {
#ifdef Konsole
    Serial.println(F("Stop"));
#endif
    mp3.pause();
    setstandbyTimer();
  }
  else
  {
    disablestandbyTimer();
    playCurrentTrack();
  }
  delay(500);
}

//************ Track zurück **( vorheriger Titel) ************************
static void previousTrack()
{
#ifdef Konsole
  Serial.print(F("previousTrack in mode "));
  Serial_println_F(getModeName(myFolder->mode));
#endif



  switch (myFolder->mode)
  {
    /*
      case 1;
      case 6:
       Serial.println(F("Hörspielmodus -> Track von vorne spielen"));

       break;
    */
    case 2: //Album
    case 7: //Album-SpezialVonBis
#ifdef Konsole
      Serial.print(F("Albummodus -> vorheriger Track : "));
#endif
      if (currentQueueIndex > 0) currentQueueIndex--;
      
      break;

    case 3: // Party
    case 8: // Party-SpezialVonBis
      if (currentQueueIndex > 0)
        currentQueueIndex--;

      else
        currentQueueIndex = queueSize - 1;
      break;

    case 4: // Einzel
#ifdef Konsole
      Serial.println(F("Einzel Modus -> Track von vorne spielen"));
#endif
      break;
    case 5: // Hörbuch
#ifdef Konsole
      Serial.println(F("Hörbuch Modus -> vorheriger Track und "
                       "Fortschritt speichern"));
#endif

      if (currentQueueIndex > 0)
      {
        currentQueueIndex--;
#ifndef AiO
        EEPROM.update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
#endif
      }

      break;
    default:
      return; // do nothing

  }
  _lastTrackFinished --;
  disablestandbyTimer();
  playCurrentTrack();
  delay(1000);
}


//**** Funktionen für den Standby Timer (z.B. über Pololu-Switch oder Mosfet) ********************
//*********** Im Schlummermodus wird der StandbyTimer auf 99  gesetzt **********************

void setstandbyTimer()                                                // Standbytimer aktivieren
{

  if (mySettings.standbyTimer != 0)                                   // wenn Wert >0 wird Standbytimer aktiviert
  {
    if (mySettings.standbyTimer == 99)                                // Wenn vom Schlummermodus auf 99 gesetzt, Tonuino sofort ausschalten
    {
#ifdef Konsole
      Serial.println(F("Sleeptimer abgelaufen"));
#endif
      delay(1000);
      ShutDown();
    }
#ifdef Konsole
    Serial.print(F("StdBy Timer ON: "));
    Serial.print(mySettings.standbyTimer);
    Serial.println(F(" min"));
    Serial.println(F(""));
#endif
    sleepAtMillis = millis() + (mySettings.standbyTimer * 60000);     // Standbytimer auf vorgewählte min setzen
    StdBy = true;                                                     // Marker StandByTimer aktiviert
  }
  else
  {
    sleepAtMillis = 0;                                                // Wenn Standbytimer nicht gesetzt ,Standbytimer deaktivieren
    StdBy = false;                                                    // Marker StandByTimer deaktiviert
  }

}

void disablestandbyTimer()                                            // Standbytimer deaktivieren
{
#ifdef Konsole
  Serial.println(F(""));
  Serial.println(F("StdBy Timer OFF"));
#endif
  sleepAtMillis = 0;
  StdBy = false;
}

void checkStandbyAtMillis()                                           // Standbytimer Ablauf prüfen
{
  if (sleepAtMillis != 0 && millis() > sleepAtMillis)                 // wenn Standbyzeit erreicht, Ausschalten
    ShutDown();
}

// ************* Ausschalten **************************
void ShutDown()                                                     // Ausschalten
{
#ifdef Konsole
  Serial.println(F("Power OFF!"));
#endif
  // enter sleep state

#ifdef HW_PowerOff
  mp3.pause();                                                      // Wiedergabe stoppen
#ifndef AiO
  
  digitalWrite(ShutDownPin, LOW);                                   // Ausschalten!, Low Pegel zum Rücksetzen des Einschalt-Flip-Flop
  delay(500);
 
  digitalWrite(ShutDownPin, HIGH);                                  // Ausschalten!, High Pegel zum Rücksetzen des Pololu-Switch
  delay(500);
#endif
  digitalWrite(ShutDownPin, LOW);                                   // Ausschalten!, Low Pegel zum Ausschalten der AiO Platine
  delay(500);
#endif

#ifdef SoftPwDown
  // http://discourse.voss.earth/t/intenso-s10000-powerbank-automatische-abschaltung-software-only/805
  // powerdown to 27mA (powerbank switches off after 30-60s)
#ifdef LED_SR_Switch
  lsrOffByStdby = true;                                             // LED-Animation ausschalten
#endif
  mp3.pause();                                                      // Wiedergabe stoppen  
#ifndef AiO
  mfrc522.PCD_AntennaOff();                                         // Rfid-Reader Antenne ausschalten
  mfrc522.PCD_SoftPowerDown();                                      // Rfid-Reader Stromsparmodus

  mp3.sleep();                                                      // df-Player in sleep-Mode setzen

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();                                                            // Disable interrupts
  sleep_mode();
#endif
#endif
}

//****************** Is Playing ************************
bool isPlaying()
{
  return !digitalRead(BusyPin);
}

//************* Track zu Ende spielen **************************
void waitForTrackToFinish()
{
  long currentTime = millis();
#define TIMEOUT 1000
  do
  {
    mp3.loop();
  }
  while (!isPlaying() && millis() < currentTime + TIMEOUT);
  delay(1000);
  do
  {
    mp3.loop();
  }
  while (isPlaying());
}

//********** Letzte gespielte Karte speichern *************************
// Funktion für LastCard

#ifdef LastCard

bool setupPlayShortcut(folderSettings * theFolder)
{
  theFolder->folder = EEPROM.read(folderReg);       // Auslesen Ordner aus Flash
  theFolder->mode = EEPROM.read(modeReg);           // Auslsen Abspielmodus aus Flash
  theFolder->special = EEPROM.read(specialReg);     // Auslesen Starttrack aus Flash für Mod-Spez VonBis
  theFolder->special2 = EEPROM.read(specialReg2);   // Auslesen Endtrack aus Flash für Mod-Spez VonBis
}

#endif

// ************************************************************************************
// ************************* Tasten auslesen ******************************************
void readButtons()
{
  pauseButton.read();
  upButton.read();
  downButton.read();
#ifdef FIVEBUTTONS
  buttonFour.read();
  buttonFive.read();
#endif
}

// ********* lauter Taste **************
void volumeUpButton()
{
  if (activeModifier != NULL)                       // wenn Modifikation aktiv
    if (activeModifier->handleVolumeUp() == true)   // wenn Taste gesperrt
      return;                                       // kein VolUp

#ifdef SpkOnOff
  if (SpkisOn == true)                                // wenn Lautsprecher an
  {
#endif
    #ifdef Konsole
    if (volume >= mySettings.maxVolume )               // wenn Vol größer oder gleich maxVolume Spk
    {
      if (msgMax == true)
      {
      Serial.println("Max Volume erreicht !");
      msgMax = false ;
      }
    }
    #endif
    if (volume < mySettings.maxVolume)                // wenn Vol kleiner maxVolume Spk
    {
      if (longPressVol == true)                       // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)  
        {
          mp3.increaseVolume();                       // Lautstärke erhöhen
          volume++;                                   // Lautstärkewert erhöhen 
          #ifdef Konsole
          msgMin = true ;
          Serial.print(F("Lauter -> "));
          Serial.println(volume);
          #endif
        }
      }
      else
      {
        mp3.increaseVolume();                          // Lautstärke erhöhen
        volume++;                                      // Lautstärkewert erhöhen
          #ifdef Konsole
          msgMin = true ;
          Serial.print(F("Lauter -> "));
          Serial.println(volume);
          #endif      
      }
    }
    
#ifdef SpkOnOff
  }
#endif
#ifdef EarPhone 
  else                                                 // wenn Lautsprecher aus
  {
    #ifdef Konsole

    {
    if (volume >= mySettings.maxEarVol)               // wenn Vol größer oder gleich maxVolume Ear
     {
     if (msgMax == true)
     Serial.println("Max Volume erreicht !");
     msgMax = false ;
     }
    }
    #endif
    if (volume < mySettings.maxEarVol)                // wenn Vol kleiner maxVolume Ear
        {
      if (longPressVol == true)                       // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)  
        {
          mp3.increaseVolume();                           // Lautstärke erhöhen
          volume++;                                       // Lautstärkewert erhöhen 
          #ifdef Konsole
          msgMin = true ;
          Serial.print(F("Lauter -> "));
          Serial.println(volume);
          #endif
        }
      }
      else
      {
        mp3.increaseVolume();                           // Lautstärke erhöhen
        volume++;                                       // Lautstärkewert erhöhen
          #ifdef Konsole
          msgMin = true ;
          Serial.print(F("Lauter -> "));
          Serial.println(volume);
          #endif
      }
    }
  }
#endif

  countVolCh ++ ;
  if (countVolCh >= setVolChSp) countVolCh = 0 ; 
}
// ******** leiser Taste ************
void volumeDownButton()
{
  if (activeModifier != NULL)                        // wenn Modifikation aktiv
    if (activeModifier->handleVolumeDown() == true)  // wenn Taste gesperrt
      return;                                        // kein VolDown

#ifdef SpkOnOff
  if (SpkisOn == true)                                // wenn Lautsprecher an
  {
#endif    
    #ifdef Konsole
     if (volume <= mySettings.minVolume)               // wenn Vol kleiner oder gleich minVolume 
     {
     if (msgMin == true) 
      {
      Serial.println("Min Volume erreicht !");
      msgMin = false ;
      }
    } 
    #endif
    if (volume > mySettings.minVolume)                // wenn Vol größer min Volume Spk
    {
     if (longPressVol == true)                         // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)  
        {
      mp3.decreaseVolume();                            // Lautstärke verringern
      volume--;                                        // Lautstärkewert verringern
          #ifdef Konsole
          msgMax = true ;
          Serial.print(F("Leiser -> "));
          Serial.println(volume);
          #endif
        }
      }
      else
      {
        mp3.decreaseVolume();                          // Lautstärke verringern
        volume--;                                      // Lautstärkewert veringern
          #ifdef Konsole
          msgMax = true ;
          Serial.print(F("Leiser -> "));
          Serial.println(volume);
          #endif      
      }
    }
#ifdef SpkOnOff
  }
#endif
#ifdef EarPhone 
  else                                                 // wenn Lautsprecher aus
  {
    #ifdef Konsole
    
    if (volume <= mySettings.minEarVol)               // wenn Vol kleiner oder gleich minVolume 
    {
     if (msgMin == true)
     {
     Serial.println("Min Volume erreicht !");
     msgMin = false ;
     }
    }
    #endif
    if (volume > mySettings.minEarVol)                // wenn Vol größer minVolume Ear
        {
      if (longPressVol == true)                       // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)  
        {
          mp3.decreaseVolume();                        // Lautstärke verringern
          volume--;                                    // Lautstärkewert verringern
          #ifdef Konsole
          msgMax = true ;
          Serial.print(F("Leiser -> "));
          Serial.println(volume);
          #endif
        }
      }
      else
      {
        mp3.decreaseVolume();                          // Lautstärke verringern
        volume--;                                      // Lautstärkewert verringern
          #ifdef Konsole
          msgMax = true ;
          Serial.print(F("Leiser -> "));
          Serial.println(volume);
          #endif
      }
    }
  }
#endif

  countVolCh ++ ;
  if (countVolCh >= setVolChSp) countVolCh = 0 ; 
}

// ************ Titel Vorwärts Taste *************
void nextButton()
{
  if (activeModifier != NULL)                           // wenn Modifikation aktiv
    if (activeModifier->handleNextButton() == true)     // wenn Taste gesperrt
      return;                                           // Titel nicht weiter

  nextTrack(_lastTrackFinished + 1);                    // beliebige tracknummer außer _lastTrackFinished

  delay(1000);
}
// ************ Titel Zurück Taste *************
void previousButton()
{
  if (activeModifier != NULL)                            // wenn Modifikation aktiv
    if (activeModifier->handlePreviousButton() == true)  // wenn Taste gesperrt
      return;                                            // Titel nicht zurück

  previousTrack();                                       // Track zurück
  delay(1000);
}

// ***************** Ordner abspielen ******************
void playFolder()
{
#ifdef Konsole
  Serial.print(F("Play Folder: "));
  Serial.println(myFolder->folder);
#endif
  disablestandbyTimer();
  randomSeed(millis() + random(1000));
  knownCard = true;
  _lastTrackFinished = 0;
  numTracksInFolder = mp3.getFolderTrackCount(myFolder->folder);      // Anzahl der Tracks im Ordner
  firstTrack = 1;
#ifdef Konsole
  Serial_println_F(getModeName(myFolder->mode));                      // Anzeige Abspielmodus
  Serial.print(numTracksInFolder);                                    // Anzahl der Tracks
  Serial.print(F(" Dateien in Ordner "));
  Serial.println(myFolder->folder);                                   // Ordner Nr
#endif


  // ****************************************************************************
  // **************** Abspielmodi ***********************************************

  bool randomOrder   = false;                // entweder Tracks in Sortierung oder gemischt abspielen
  bool randomStart   = false;                // entweder Start playback mit erstem track oder einem Zufallstrack
  uint8_t fromTrack  = 1;                    // first track number (file name number) (default 1)
  uint8_t toTrack    = numTracksInFolder;    // last  track number (file name number) (default lastTrack)
  uint8_t firstTrack = 1;                    // track number to play first

  bool printRange    = false;

  switch (myFolder->mode)                     // Abspielmodus einstellen
  {
    case 1:                                   // Hörspielmodus: eine zufällige Datei aus dem Ordner
      randomStart = true;                     // Start mit zufälligem Track -> Ja
      break;

    case 2:                                   // Album Modus: kompletten Ordner spielen
      randomOrder = false;                    // Zufällige Reihenfolge -> Nein
      randomStart  = false;                   // Start mit zufälligem Track -> Nein   
      break;

    case 3:                                   // Party Modus: Ordner in zufälliger Reihenfolge
      randomOrder = true;                     // Zufällige Reihenfolge -> Ja
      randomStart  = true;                    // Start mit zufälligem Track -> Ja
      break;

    case 4:                                   // Einzel Modus: eine Datei aus dem Ordner abspielen
      firstTrack = myFolder->special;         // Tracknr aus myFolder->special
      break;

    case 5:                                   // Hörbuch Modus: kompletten Ordner spielen und Fortschritt merken
      firstTrack = EEPROM.read(myFolder->folder);   // Starttrack aus EEprom Fortschritt auslesen
      break;

    case 6:                                   // Spezialmodus Von-Bis: Hörspiel: eine zufällige Datei aus dem Ordner
      printRange  = true;
      fromTrack   = myFolder->special;        // Start track
      toTrack     = myFolder->special2;       // End track
      randomStart = true;                     // Start mit zufälligem Track -> Ja
      break;

    case 7:                                   // Spezialmodus Von-Bis: Album: alle Dateien zwischen Start und Ende spielen
      printRange = true;
      firstTrack = myFolder->special;         // erster track
      fromTrack  = myFolder->special;         // Start track
      toTrack    = myFolder->special2;        // End track
      randomOrder = false;                    // Zufällige Reihenfolge -> Nein
      randomStart  = false;                   // Start mit zufälligem Track -> Nein
      break;

    case 8:                                   // Spezialmodus Von-Bis: Party Ordner in zufälliger Reihenfolge
      printRange  = true;
      fromTrack   = myFolder->special;        // Start track
      toTrack     = myFolder->special2;       // End track
      randomOrder = true;                     // Zufällige Reihenfolge -> Ja
      randomStart  = true;                    // Start mit zufälligem Track -> Ja
      break;

    default:                                  // unknown mode (e.g. AdminCard) -> exit method
      return;
  }

  if (printRange)                             // Spezial - Bereich im ser Mon ausgeben
  {
#ifdef Konsole
    Serial.print(F("Track "));
    Serial.print(myFolder->special);                       // StartTrack
    Serial.print(F(" bis "));
    Serial.println(myFolder->special2);                    // EndTrack
#endif
  }

  // queue erstellen [fromTrack, toTrack], shuffle if requested
  initQueue(fromTrack, toTrack);
  if (randomOrder) shuffleQueue();

  // festlegen start track and its queue index
  if (randomStart) firstTrack = random(fromTrack, toTrack + 1);
  currentQueueIndex = findQueueIndex(firstTrack);
  if (currentQueueIndex == 0xff) currentQueueIndex = 0;     // if findQueueIndex failed

  playCurrentTrack();                                       // start playing



  // *********************************************************************************
  // ************** Update letzte Karte im EEPROM speichern **************************
  // **********Gespielte Shortcuts sollen nicht als letzte Karte gespeichert werden***

#ifdef LastCard
  if (ShortCutIsPlaying == false)                         // wenn Marker  "shortcut wird nicht gespielt"
  {
#ifndef AiO                                               // TonUINO Classic
    EEPROM.update(folderReg, myFolder->folder);           // EEPROM updaten letzte gespielte Karte
    EEPROM.update(modeReg, myFolder->mode);               // EEPROM update Abspielmodus
    EEPROM.update(specialReg, myFolder->special);         // EEPROM Update Starttrack
    EEPROM.update(specialReg2, myFolder->special2);       // EEPROM update Endtrack
#endif
#ifdef AiO                                                // TonUINO AiO
    EEPROM_update(folderReg, myFolder->folder);           // EEPROM updaten letzte gespielte Karte
    EEPROM_update(modeReg, myFolder->mode);               // EEPROM update Abspielmodus
    EEPROM_update(specialReg, myFolder->special);         // EEPROM Update Starttrack
    EEPROM_update(specialReg2, myFolder->special2);       // EEPROM update Endtrack
#endif
#ifdef Konsole
    Serial.println(F("letzte Karte -> EEPROM !"));
#endif
  }

  ShortCutIsPlaying = false ;                            // Marker rücksetzen "Shortcut wird gespielt"
#endif
}

// ************************************************************************************
// ************ Auf eine Taste oder als Startsound gelegten Track spielen *************

void playShortCut(uint8_t shortCut)
{
#ifdef Konsole
  Serial.print(F("Play ShortCut: "));
  Serial.println(shortCut);
#endif
#ifdef LastCard
  if (shortCut == 0) {                                  // Wenn Shortcut Playtaste abgerufen
    setupPlayShortcut(&mySettings.shortCuts[0]);        // LastCard auf Play legen
#ifdef Konsole
    Serial.println(F("Last Card auf Play gespeichert!"));
#endif
  }
#endif
  if (mySettings.shortCuts[shortCut].folder != 0) {     // wenn ein shortcut gespeichert ist
    myFolder = &mySettings.shortCuts[shortCut];         // aktueller Track -> Gespeichert in shortcut
    ShortCutIsPlaying = true ;                          // Marker setzen "shortcut wird gespielt"
    playFolder();                                       // shortcut spielen
    disablestandbyTimer();
    delay(1000);
  }
  else {                                                // wenn kein shortcut gespeichert ist
#ifdef Konsole
    Serial.println(F("Shortcut nicht belegt!"));
#endif
    ShortCutIsPlaying = false ;                         // Marker setzen "Kein shortcut gespielt"
  }
}

// ************** TimeOutfunktion für das Adminmenü **********************
// **************** Start TimeOut Adminmenü ******************************
void AdmTimeOutStart()
{
  AdmTimeOut = millis();                             // Start der Timeoutzeit
#ifdef Konsole
  Serial.print(F("AdmTimeOut: "));
  Serial.print(Minuten);
  Serial.println(" min");
#endif
  AbbrActive = false;
}
// **************** Abbruch nach TimeOut Adminmenü **********************
void AbbrAdminTimeout()
{

  if ((millis() - AdmTimeOut) >= SollAdmTimeOut)      // Abbruch nach TimeOut
  {
    AdmTimeOut = millis();
    AbbrActive = true;                                // Abbruch ist aktiv
#ifdef Konsole
    Serial.println(F("Abbruch nach TimeOut "));
#endif
    mp3.playMp3FolderTrack(803);                      // 803- Abbruch nach Timeout,Schalte aus
    waitForTrackToFinish();
    delay (5000);
    ShutDown();                                       // Ausschalten
    return;

  }
}
// *******************************************************************************
// ******************** Admin Menü starten ***************************************

void adminMenu(bool fromCard = false)
{
  disablestandbyTimer();

  mp3.pause();
#ifdef Konsole
  Serial.println(F("=== AdminMenu === "));
#endif
  if (fromCard == false)                          // wenn Adminmenü über Tasten aufgerufen
  { // Prüfung auf Schutz, ggF.Entsperren

    // ************ Entsperren des Adminmenüs, wenn geschützt ******************

    // Admin menu gesperrt - Es kann immer mit der admin card gestartet werden
    if (mySettings.adminMenuLocked == 1)            // Nur mit Adminkarte
    {
#ifdef Konsole
      Serial.println(F("Gesperrt!- Nur Adminkarte"));
#endif
      mp3.start();
      return;
    }
    else
    {
      knownCard = false;
    }
  }
  knownCard = false;

  //*********************Admin-Menü-Funktionen auswählen*****************


  int subMenu = voiceMenu(9, 900, 900, false, false, 0, true); // 900- "Willkommen im Adminmenü,Wähle eine Funktion ...(mp3/ 900 - 909)

                                                               // Aufbau des Voicemenüs
                                                               // int subMenu --> Rückgabewert der Nummer des subMenüs
                                                               // = voiceMenu(
                                                               // 9,    (numberOfOptions)  --> Anzahl der subMenüs 9
                                                               // 900,  (startMessage)     --> Tracknummer der Ansage im mp3Ordner 0900
                                                               // 900,  (messageOffset)    --> nachfolgende Ansagen nach dieser Tracknummer 0901-0909
                                                               // false,(preview)          --> Keine Vorschau
                                                               // false,(previewFromFolder)--> Keine Vorschau
                                                               // 0,   ,(defaultValue)     --> von diesem wert ab zählen  1 - 9
                                                               // true) (exitWithLongPress)--> Abbruch mit langem Tastendruck möglich

  if (AbbrActive == true)
    subMenu == 0;

  if (subMenu == 0)
  {
    progmode = 0;
    return;
  }
  if (subMenu >= 4) progmode = 0;

  if (subMenu <= 5 || subMenu >= 7)  AdjVol = false;


  // ************** Karte neu Konfiguriern ***********
  if (subMenu == 1)                                           // 901- "Karte neu Konfigurieren
  {
    progmode = 1;                                             // Kartenart - Neue Karte
    if (AbbrActive == true)
      return;
    resetCard();
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  // ******* Einzelkarten für Ordner festlegen *********************
  else if (subMenu == 2)                                      // 902- "Einzelkarten für Ordner festlegen
  {
    progmode = 2;                                             // Kartenart - Einzelkarte
    if (AbbrActive == true)
      return;
    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.mode = 4;                      // Abspielmodus - Einzelmodus
#ifdef CountFolders
    tempCard.nfcFolderSettings.folder = voiceMenu(numFolders - 2, 301, 0, true);  // Verwende die Lautstärketasten um einen Ordner auszuwählen
#endif                                                                           // numFolders -2 -> Anzahl der ermittelten Ordner - mp3 und advert Ordner

#ifndef CountFolders
    tempCard.nfcFolderSettings.folder = voiceMenu(99, 301, 0, true);             // Verwende die Lautstärketasten um einen Ordner auszuwählen
#endif                                                                           // 001 - 099 setzt die Ordnernummer Kurzer Druck + oder - 1
                                                                                 //                                  Langer Druck + oder - 10
    if (AbbrActive == true)
      return;
    uint8_t special = voiceMenu(mp3.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 321, 0,  // 321- "Startdatei auswählen
                                true, tempCard.nfcFolderSettings.folder);                            // setzt den Start-Track
    if (AbbrActive == true)
      return;
    uint8_t special2 = voiceMenu(mp3.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 322, 0, // 322- "Enddatei auswählen
                                 true, tempCard.nfcFolderSettings.folder, special);                  // setzt den End-Track

    if (AbbrActive == true)
      return;

    mp3.playMp3FolderTrack(939);                // 939 - "OK, bitte lege nun nacheinander die Karten auf die Box.
                                                //      Ich werde die jeweilige Nummer vorher ansagen, damit du nicht durcheinander kommst.
                                                //      Zum Abbrechen einfach eine der Lautstärketasten drücken!

    waitForTrackToFinish();
    for (uint8_t x = special; x <= special2; x++)
    {
      mp3.playMp3FolderTrack(x);
      waitForTrackToFinish();
      tempCard.nfcFolderSettings.special = x;
#ifdef Konsole
      Serial.print("Karte ");
      Serial.print(x);
      Serial.println(F(" auflegen"));
#endif
      AdmTimeOutStart();                                        // Start der Timeoutzeit

      do
      {

        AbbrAdminTimeout();                                     // Abbruch nach Timeout Adminmenü

        readButtons();
        if (upButton.wasReleased() || downButton.wasReleased()) // Lauter oder Leiser-Taste wurde für Abbruch gedrückt?
        {
#ifdef Konsole
          Serial.println(F("Abbruch!"));
#endif
          AbbrActive = true;                                    // Abbruch ist aktiv
          mp3.playMp3FolderTrack(802);                          // 802- "OK, ich habe den Vorgang abgebrochen.
          waitForTrackToFinish();
          setstandbyTimer();
          return;
        }
      } while (!mfrc522.PICC_IsNewCardPresent());             // bleibe in der Schleife solange keine Karte aufgelegt


      if (mfrc522.PICC_ReadCardSerial())                      // RFID Karte wurde aufgelegt
      {
        delay(500);
#ifdef Konsole
        Serial.println(F("schreibe Karte..."));
#endif
        writeCard(tempCard);
        delay(100);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();

      }
    }
  }

  // *********** Modifikationskarten erstellen *********************
  else if (subMenu == 3)                                        // 903- "Modifikationskarte erstellen
  {
    progmode = 3;                                               // Kartenart - Modifikationskarte
    if (AbbrActive == true)
      return;
    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.folder = 0;
    tempCard.nfcFolderSettings.special = 0;
    tempCard.nfcFolderSettings.special2 = 0;
    tempCard.nfcFolderSettings.mode = voiceMenu(6, 970, 970, false, false, 0, true); // 970 - 976
                                                                          //970-Bitte wähle nun deine Modifikationskarte mit den Lautstärketasten aus.

                                                                          //971-Schlummermodus
                                                                          //972-Stopptanz - TonUINO spielt Stopptanz mit dir
                                                                          //    und hält zufällig für dich die Wiedergabe kurz an.
                                                                          //973-TonUINO Sperren
                                                                          //974-Krabbler-Modus - Alle Tasten vom TonUINO werden für die ganz Kleinen gesperrt.
                                                                          //    Karten funktionieren weiterhin.
                                                                          //975-KiTa-Modus - Damit es keinen Streit mehr gibt werden neue Karten
                                                                          //    nicht sofort gespielt sondern erst nachdem das aktuelle Lied vorbei ist.
                                                                          //    Die Vor- und Zurücktasten sind gesperrt.
                                                                          //976-Titel wiederholen - den aktuellen Titel endlos wiederholen.


    if (tempCard.nfcFolderSettings.mode != 0)                     // wenn Option ungleich 0
    {
      if (AbbrActive == true)
        return;
      if (tempCard.nfcFolderSettings.mode == 1)                 // Sleeptimer konfigurieren (Schlummermodus)
      {
        switch (voiceMenu(4, 960, 960))                         // 960- "Nach wievielen Minuten soll der TonUINO ausgeschaltet werden?
        {
          case 1: tempCard.nfcFolderSettings.special = 5; break;      // 961- "5 Minuten
          case 2: tempCard.nfcFolderSettings.special = 15; break;     // 962- "15 Minuten
          case 3: tempCard.nfcFolderSettings.special = 30; break;     // 963- "30 Minuten
          case 4: tempCard.nfcFolderSettings.special = 60; break;     // 964- "60 Minuten
        }
      }
      mp3.playMp3FolderTrack(800);                                // 800- "Bitte lege nun die Karte auf!
      waitForTrackToFinish();

      AdmTimeOutStart();                                          // Start der Timeoutzeit

      do
      {
        AbbrAdminTimeout();                                     // Abbruch nach Timeout Adminmenü

        readButtons();
        if (upButton.wasReleased() || downButton.wasReleased())   // Lauter oder Leiser-Taste gedrückt für Abbruch?
        {
#ifdef Konsole
          Serial.println(F("Abbruch!"));
#endif
          AbbrActive = true;                                    // Abbruch ist aktiv
          mp3.playMp3FolderTrack(802);                          //802- "OK, ich habe den Vorgang abgebrochen.
          waitForTrackToFinish();
          setstandbyTimer();
          return;
        }
      }
      while (!mfrc522.PICC_IsNewCardPresent());               // bleibe in der Schleife solange keine Karte aufgelegt


      if (mfrc522.PICC_ReadCardSerial())                          // RFID Karte wurde aufgelegt
      {
#ifdef Konsole
        Serial.println(F("schreibe Karte..."));
#endif
        writeCard(tempCard);
        delay(100);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();

      }
    }
  }

  // ********* Eine Taste mit einem Shortcut belegen **************
  else if (subMenu == 4)                                      // 904-"Shortcut configurieren ( mit Weckershortcut)
  { // 995-"Shortcut configurieren ( ohne Weckershortcut)

    progmode = 4;                                             // Shortcut
    if (AbbrActive == true)
      return;
#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(4, 940, 940);                // (941-944)    Playtaste/UpTaste/DownTaste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(5, 940, 940);                // (941-945)    Playtaste/UpTaste/DownTaste/WelcomeSound/WeckerSound
#endif
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(3, 940, 941);                // (942-944)     UpTaste/DownTaste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(4, 940, 941);                // (942-945)     UpTaste/DownTaste/WelcomeSound/WeckerSound
#endif
#endif

    if (AbbrActive == true)
      return;

#ifndef LastCard
    setupFolder(&mySettings.shortCuts[shortcut - 1]);         // shortcuts 0 - 3 bzw. 0 - 4, Playtaste/UpTaste/DownTaste/WelcomeSound/(WeckerSound)
#endif

#ifdef LastCard
    setupFolder(&mySettings.shortCuts[shortcut]);             // shortcuts 1 - 3 bzw. 1 - 4, UpTaste/DownTaste/WelcomeSound/(WeckerSound)
#endif                                                        // shortcut 0 , Playtaste wird mit last card belegt.
  }

  // ********** Funktion der Lautstärketasten umdrehen **************
  else if (subMenu == 5)                                            //905- "Funktion der Lautstärketasten umdrehen
  {
    int temp = voiceMenu(2, 930, 930, false);                       //930- "Möchtest du die Funktion der Lautstärketasten umdrehen?
    //Du musst dann die Tasten lange drücken um ein Lied vor oder zurückzugehen.
    if (temp == 2)
    {
      mySettings.invertVolumeButtons = true;                        //931- "Ja
    }
    else
    {
      mySettings.invertVolumeButtons = false;                       //932- "Nein
    }
  }


  // ********** Lautstärke und EQ Einstellungen ändern *********************

  else if (subMenu == 6)                                            // 906- "Einstellungen für die Lautstärke und den Klangcharakter ändern
  {
#ifdef EarPhone
    int VolMenu = voiceMenu(3, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
                                                                    // 910 - Bitte wähle mit den LS Tasten die Einstellung aus und bestätige mit der Pausetaste
                                                                    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
                                                                    // 912 - Einstellungen für die Lautstärke des Kopfhörers ändern
                                                                    // 913 - Den Klangcharakter konfigurieren
#endif
#ifndef EarPhone
    int VolMenu = voiceMenu(2, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
    if (VolMenu == 2) VolMenu = 3;                                  // 910 - Bitte wähle mit den LS Tasten die Einstellung aus und bestätige mit der Pausetaste
                                                                    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
                                                                    // 913 - Den Klangcharakter konfigurieren
#endif
    // ********** Lautstärkeeinstellungen Lautsprecher ***************

    if (VolMenu == 1)                                                 // 911- "Einstellungen für die Lautstärke des lautsprechers  ändern
    {
      int LspMenu = voiceMenu(3, 914, 914, false, false, 0, true);      //(mp3/ 914- 917)
                                                                    // 914 - Bitte wähle mit den LS-Tasten die zu ändernde Lautstärke aus
                                                                    //       und bestätige mit der Pausetaste
                                                                    // 915 - Maximale Lautstärke Lautsprecher
                                                                    // 916 - Minimale Lautstärke Lautsprecher
                                                                    // 917 - Lautstärke des Lautsprechers beim Start

      // ********** Max Lautstärke des Lautsprechers *******************

      if (LspMenu == 1)                                                       // 915 - Maximale Lautstärke Lautsprecher
      {
        AdjVol = true;
        mySettings.maxVolume = voiceMenu(30 - mySettings.minVolume, 933, mySettings.minVolume,  //933 - Bitte wähle mit den LS-Tasten die
                                         false, false, mySettings.maxVolume - mySettings.minVolume) + mySettings.minVolume; //      max. Lautstärke des Lautsprechers aus
      }

      // ********** Min Lautstärke des Lautsprechers *******************

      if (LspMenu == 2)                                                                 // 916 - Minimale Lautstärke Lautsprecher
      {
        AdjVol = true;
        mySettings.minVolume = voiceMenu(mySettings.maxVolume - 1, 934, 0,              // 934 - Bitte wähle mit den LS-Tasten die
                                         false, false, mySettings.minVolume);            //      min. Lautstärke des Lautsprechers aus
      }

      // ********** Initial Lautstärke des Lautsprechers *******************

      if (LspMenu == 3)                                                       // 917 - Lautstärke des Lautsprechers beim Start
      {
        AdjVol = true;
        mySettings.initVolume = voiceMenu(mySettings.maxVolume - mySettings.minVolume + 1, 935, // 935 - Bitte wähle mit den LS-Tasten die
                                          mySettings.minVolume - 1, false, false,               //   Lautstärke des Lautsprechers beim Start aus
                                          mySettings.initVolume - mySettings.minVolume + 1) + mySettings.minVolume - 1;
      }
    }

    // ********** Lautstärkeeinstellungen Kopfhörer ***************
#ifdef EarPhone     
    if (VolMenu == 2)                                                         // 912- "Einstellungen für die Lautstärke des Kopfhörers ändern

    {
      int EarMenu = voiceMenu(3, 918, 918, false, false, 0, true);              //  (mp3/ 918 - 921)
                                                                              // 918 - Bitte wähle mit den LS-Tasten die zu ändernde Lautstärke aus
                                                                              //       und bestätige mit der Pausetaste
                                                                              // 919 - Maximale Lautstärke Kopfhörer
                                                                              // 920 - Minimale Lautstärke Kopfhörer
                                                                              // 921 - Lautstärke des Kopfhörers beim Start

      // ********** Maximale Lautstärke Kopfhörer **************************

      if (EarMenu == 1)                                                       // 919 - Maximale Lautstärke Kopfhörer
      {
        AdjVol = true;
        mySettings.maxEarVol = voiceMenu(30 - mySettings.minEarVol, 936,        //936 - Bitte wähle mit den LS-Tasten die
                                         mySettings.minEarVol, false, false,    //      max. Lautstärke des Kopfhörers aus
                                         mySettings.maxEarVol - mySettings.minEarVol) + mySettings.minEarVol;
      }

      // ********** Minimale Lautstärke Kopfhörer **************************

      if (EarMenu == 2)                                                           // 920 - Minimale Lautstärke Kopfhörer
      {
        AdjVol = true;
        mySettings.minEarVol = voiceMenu(mySettings.maxEarVol - 1, 937,           // 937 - Bitte wähle mit den LS-Tasten die
                                         0, false, false, mySettings.minEarVol);  //       min. Lautstärke des Kopfhörers aus
      }

      // ********** Initial Lautstärke Kopfhörer **************************

      if (EarMenu == 3)                                                         // 921 - Lautstärke des Kopfhörers beim Start
      {
        AdjVol = true;
        mySettings.initEarVol = voiceMenu(mySettings.maxEarVol - mySettings.minEarVol + 1, 938, // 938 - Bitte wähle mit den LS-Tasten die
                                          mySettings.minEarVol - 1, false, false,               //       Lautstärke des Kopfhörers beim Start aus
                                          mySettings.initEarVol - mySettings.minEarVol + 1) + mySettings.minEarVol - 1;
      }
    }
#endif
    // *********** Equalizer konfigurieren ************
    if (VolMenu == 3)                                                         //913- "Den Klangcharakter konfigurieren

    {
      mySettings.eq = voiceMenu(6, 922, 922, false, false, mySettings.eq);   //922- "Bitte wähle eine Einstellung für den Klangcharakter
                                                                             //      mit den Lautstärketasten aus und bestätige sie mit der Pausetaste.
                                                                             //923- "Normal
                                                                             //924- "Pop
                                                                             //925- "Rock
                                                                             //926- "Jazz
                                                                             //927- "Classic
                                                                             //928- "Bass
      mp3.setEq(mySettings.eq - 1);
    }
  }

  // ******** Den Standbytimer konfigurieren **********************
  else if (subMenu == 7)                                    // 907- "StandbyTimer Konfigurieren
  {
    switch (voiceMenu(5, 960, 960))                         // 960-965
    {
      case 1: mySettings.standbyTimer = 5; break;           // 961 - 5 Min
      case 2: mySettings.standbyTimer = 15; break;          // 962 - 15 Min
      case 3: mySettings.standbyTimer = 30; break;          // 963 - 30 Min
      case 4: mySettings.standbyTimer = 60; break;          // 964 - 60 Min
      case 5: mySettings.standbyTimer = 0; break;           // 965 - Kein Standbytimer
    }
  }


  // ********** Das Adminmenü schützen ****************
  else if (subMenu == 8)                                    // 908- "Admin Menü schützen
  {
    int temp = voiceMenu(2, 980, 980, false);               // 980- "Wähle bitte aus ob und wie das Adminmenü geschützt werden soll.
                                                            // 981 - kein Schutz
                                                            // 982 - Nur Adminkarte


    if (temp == 1)                                          //Kein Schutz
    {
      mySettings.adminMenuLocked = 0;
    }

    else if (temp == 2)                                     //Nur Adminkarte
    {
      mySettings.adminMenuLocked = 1;
    }
  }

  // ********** Tonuino zurücksetzen ****************
  else if (subMenu == 9)                                    // 909- "Tonuino zurücksetzen
  {
#ifdef Konsole
    Serial.println(F("Reset -> EEPROM wird gelöscht"));
#endif
#ifndef AiO
    for (int i = 0; i < EEPROM.length(); i++)
    {
      EEPROM.update(i, 0);
    }
#endif
#ifdef AiO
    for (int i = 0; i < 1024; i++)
    {
      EEPROM_update(i, 0);
    }

#endif

    resetSettings();
    mp3.playMp3FolderTrack(999);                          // 999- "Reset wurde durchgeführt!
    waitForTrackToFinish();
  }

  // ********** Änderungen speichern *****************
  if (subMenu >= 4)
  {

    if (AbbrActive == true)
      return;
    writeSettingsToFlash();


    //********Feedback beim Verlassen des Adminmenus *************
    if (progmode == 4)                                        // aktiver Modus Shortcut programmieren
    {
#ifdef Konsole
      Serial.println(F("Shortcut konfiguriert"));
#endif
      mp3.playMp3FolderTrack(403);                            // 403- "OK.Shortcut konfiguriert"
    }
    else if ( progmode != 9)                                  // aktiver Modus ist nicht Shortcut programmieren
      // und nicht Adminkarte erstellen
    {
#ifdef Konsole
      Serial.println(F("Änderungen gespeichert"));
#endif
      mp3.playMp3FolderTrack(998);                            // 998- "OK.Änderungen gespeichert"
    }
    waitForTrackToFinish();

  }
  // ************ Ende Adminmenü ***************************************
  progmode = 0;
  setstandbyTimer();
}

// ************ Sprachmenüs ********************************************


uint8_t voiceMenu(int numberOfOptions,
                  int startMessage,
                  int messageOffset,
                  bool preview = false,
                  int previewFromFolder = 0,
                  int defaultValue = 0,
                  bool exitWithLongPress = false)
{

  uint8_t returnValue = defaultValue;

  // ********* Menülautstärke  festlegen *************
  if (startMessage != 0)

#ifdef MenueVol
    MenuVol = mySettings.initVolume;                      // Auslesen der Startlautstärke aus mySettings
#endif

  mp3.setVolume (MenuVol);                                // Setzen der Menülautstärke
#ifdef Konsole
  Serial.print(F("Menülautstärke:  "));
  Serial.println(MenuVol);
#endif


  mp3.playMp3FolderTrack(startMessage);
#ifdef Konsole
  Serial.print(F("voiceMenu ("));
  Serial.print(numberOfOptions);
  Serial.println(F(" Options)"));
#endif

  // ************** TimeOutfunktion für das Adminmenü ************************

  AdmTimeOutStart();                                      // Start der Timeoutzeit

  do
  {
    if (isPlaying())
      AdmTimeOut = millis();                              // Timeoutzeit erst starten wenn Preview beendet

    if ((millis() - AdmTimeOut) >= SollAdmTimeOut)       // Abbruch nach TimeOut
    {
      if (! isPlaying())
      {

#ifdef Konsole
        Serial.println(F(" Abbruch nach TimeOut "));
#endif
        mp3.playMp3FolderTrack(803);                  // 803- Abbruch nach Timeout,Schalte aus
        waitForTrackToFinish();

        ShutDown();
        return defaultValue;

      }
    }

    if (Serial.available() > 0)
    {
      int optionSerial = Serial.parseInt();
      if (optionSerial != 0 && optionSerial <= numberOfOptions)
        return optionSerial;
    }


    readButtons();
    mp3.loop();

    if (pauseButton.pressedFor(LONG_PRESS))       // Abbruch durch Taste
    {
#ifdef Konsole
      Serial.println(F("manueller Abbruch"));
#endif
      AbbrActive = true;                            // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                  // 802- "OK, ich habe den Vorgang abgebrochen.
      waitForTrackToFinish();
      ignorePauseButton = true;                     // PauseTaste übergehen
      setstandbyTimer();
      //return defaultValue;
      return;
    }
    if (pauseButton.wasReleased())
    {
      if (returnValue != 0)
      {
        AdmTimeOut = millis();                                      // Neustart TimeOut Timer
#ifdef Konsole
        Serial.print(F("Auswahl "));
        Serial.print(returnValue);
        Serial.println(F(" ok"));
#endif
        return returnValue;
      }
      delay(1000);
    }
    // ************ 10-er Schritt** vorwärts **************
    if (upButton.pressedFor(LONG_PRESS))
    {
      AdmTimeOut = millis();                                        // Neustart TimeOut Timer
      if (returnValue == numberOfOptions)                           // Rücksprung zum Anfang der Optionen
        returnValue = 0;
      returnValue = min(returnValue + 10, numberOfOptions);         // 10 Schritte hoch
#ifdef Konsole
      if (AdjVol == false) Serial.println(returnValue);             // wenn nicht Lautstärkeeinstellung, Anzeige Rückgabewert
      else Serial.println(messageOffset + returnValue);             // wenn Lautstärkeeinstellung, Anzeige Rückgabewert + Offset
#endif
      mp3.pause();
#ifndef Wecker
      if (messageOffset + returnValue == 904)                        // Tauschen der Startmessage ohne Weckershortcut
        mp3.playMp3FolderTrack(995);
      else
#endif
#ifndef EarPhone
      if (messageOffset + returnValue == 912)                        // Tauschen der Startmessage ohne Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);
      else
#endif
        
        mp3.playMp3FolderTrack(messageOffset + returnValue);         // Ansage Rückgabewert
      waitForTrackToFinish();

      //************ preview *****************************

      if (preview)
      {
        if (previewFromFolder == 0)
          mp3.playFolderTrack(returnValue, 1);
        else
          mp3.playFolderTrack(previewFromFolder, returnValue);
      }

      ignoreUpButton = true;                                      // Lautertaste übergehen
    }
    else if (upButton.wasReleased())
    {
      AdmTimeOut = millis();                                      // Neustart TimeOut Timer
      if (!ignoreUpButton)
      {
        if (returnValue == numberOfOptions)                       // Rücksprung zum Anfang der Optionen
          returnValue = 0;
        returnValue = min(returnValue + 1, numberOfOptions);      // 1 Schritt weiter
#ifdef Konsole
        Serial.print("Auswahl: ");
        if (AdjVol == false) Serial.println(returnValue);
        else Serial.println(messageOffset + returnValue);
#endif
        mp3.pause();

#ifndef Wecker
        if (messageOffset + returnValue == 904)                     // Tauschen der Startmessage ohne Weckershortcut
          mp3.playMp3FolderTrack(995);
        else
#endif
#ifndef EarPhone
      if (messageOffset + returnValue == 912)                        // Tauschen der Startmessage ohne Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);
      else
#endif
          mp3.playMp3FolderTrack(messageOffset + returnValue);
        if (preview)
        {
          waitForTrackToFinish();
          if (previewFromFolder == 0)
          {
            mp3.playFolderTrack(returnValue, 1);
          }
          else
          {
            mp3.playFolderTrack(previewFromFolder, returnValue);
          }
          delay(1000);
        }
      }
      else
      {
        ignoreUpButton = false;                                 // LauterTaste auswerten
      }
    }
    // ************* 10-er Schritt* zurück ***************

    if (downButton.pressedFor(LONG_PRESS))
    {
      AdmTimeOut = millis();                                    // Neustart TimeOut Timer
      if (returnValue == 1)                                     // Rücksprung zum Ende der Optionen
        returnValue = (numberOfOptions + 1);
      returnValue = max(returnValue - 10, 1);                   // 10 Schritte zurück

#ifdef Konsole
      Serial.print("Auswahl: ");
      if (AdjVol == false) Serial.println(returnValue);         // Nr der Option
      else Serial.println(messageOffset + returnValue);         // Vol-Wert
#endif
      mp3.pause();

#ifndef Wecker
      if (messageOffset + returnValue == 904)                   // Tauschen der Startmessage ohne Weckershortcut
        mp3.playMp3FolderTrack(995);
      else
#endif
#ifndef EarPhone
      if (messageOffset + returnValue == 912)                        // Tauschen der Startmessage ohne Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);
      else
#endif
        mp3.playMp3FolderTrack(messageOffset + returnValue);      // Vol-Wert
      waitForTrackToFinish();

      //************ preview *****************************

      if (preview)
      {
        if (previewFromFolder == 0)
          mp3.playFolderTrack(returnValue, 1);
        else
          mp3.playFolderTrack(previewFromFolder, returnValue);
      }


      ignoreDownButton = true;                                      // LeiserTaste übergehen
    }
    else if (downButton.wasReleased())
    {
      AdmTimeOut = millis();                                        // Neustart TimeOut Timer
      if (!ignoreDownButton)
      {
        if (returnValue == 1)                                       // Rücksprung zum Ende der Optionen
          returnValue = (numberOfOptions + 1);
        returnValue = max(returnValue - 1, 1);                      // 1 Schritt zurück
#ifdef Konsole
        Serial.print("Auswahl: ");
        if (AdjVol == false) Serial.println(returnValue);           // Nr der Option
        else Serial.println(messageOffset + returnValue);           // Volume-Wert
#endif
        mp3.pause();

#ifndef Wecker
        if (messageOffset + returnValue == 904)                      // Tauschen der Startmessage ohne Weckershortcut
          mp3.playMp3FolderTrack(995);
        else
#endif
#ifndef EarPhone
      if (messageOffset + returnValue == 912)                        // Tauschen der Startmessage ohne Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);
      else
#endif
          mp3.playMp3FolderTrack(messageOffset + returnValue);        // Volume-Wert
        if (preview)
        {
          waitForTrackToFinish();
          if (previewFromFolder == 0)
          {
            mp3.playFolderTrack(returnValue, 1);
          }
          else
          {
            mp3.playFolderTrack(previewFromFolder, returnValue);
          }
          delay(1000);
        }
      }
      else
      {
        ignoreDownButton = false;                       // LeiserTaste auswerten
      }
    }
  } while (true);
}

// *********************** Karte neu konfigurieren ***************
void resetCard()
{
  mp3.playMp3FolderTrack(800);                            // 800- "Bitte lege nun die Karte auf!
  delay(1000);
  AdmTimeOutStart();                                      // Start der Timeoutzeit

  do
  {

    AbbrAdminTimeout();                                   // Abbruch nach Timeout Adminmenü

    pauseButton.read();
    upButton.read();
    downButton.read();

    if (upButton.wasReleased() || downButton.wasReleased()) // Vor oder Zurücktaste für Abbruch
    {
#ifdef Konsole
      Serial.print(F("Abbruch!"));
#endif
      AbbrActive = true;                                    // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                          // 802- "OK, ich habe den Vorgang abgebrochen.
      waitForTrackToFinish();
      setstandbyTimer();
      return;
    }
  }

  while (!mfrc522.PICC_IsNewCardPresent());               // bleibe in der Schleife bis Karte aufgelegt

  if (!mfrc522.PICC_ReadCardSerial())
    return;

#ifdef Konsole
  Serial.print(F("Karte wird neu konfiguriert!"));
#endif
  setupCard();
}

bool setupFolder(folderSettings * theFolder)
{
  // Ordner abfragen
#ifdef CountFolders
  theFolder->folder = voiceMenu(numFolders - 2, 301, 0, true, 0, 0, true);  // 301 - Wähle den Ordner aus ( 1 bis numFolders-2)
#endif
#ifndef CountFolders
  theFolder->folder = voiceMenu(99, 301, 0, true, 0, 0, true);      // 301 - Wähle den Ordner aus ( 1 - 99)
#endif
  if (theFolder->folder == 0) return false;

  // Wiedergabemodus abfragen
  if (AbbrActive == true)
    return;
  theFolder->mode = voiceMenu(9, 310, 310, false, 0, 0, true);      // 310 - Wähle den Wiedergabemodus ( Alle Abspielmodi)
                                                                    // 311 - Hörspielmodus
                                                                    // 312 - Albummodus
                                                                    // 313 - Partymodus
                                                                    // 314 - Einzelmodus
                                                                    // 315 - Hörbuchmodus
                                                                    // 316 - Hörspiel-Spezial Von Bis
                                                                    // 317 - Album - Spezial Von Bis
                                                                    // 318 - Party - Spezial Von Bis
                                                                    // 319 - Adminkarte erstellen
  if (theFolder->mode == 0) return false;
  if (progmode == 0)
    if (theFolder->mode <= 8) progmode = 2;

  // Einzelmodus -> Datei abfragen
  if (theFolder->mode == 4)
    theFolder->special = voiceMenu(mp3.getFolderTrackCount(theFolder->folder), 320, 0,   // 320 - Trackauswahl
                                   true, theFolder->folder);


  // Spezialmodus Von-Bis
  if (theFolder->mode == 6 || theFolder->mode == 7 || theFolder->mode == 8)              // Hörsp, Album, Party Spezial Von Bis
  {
    theFolder->special = voiceMenu(mp3.getFolderTrackCount(theFolder->folder), 321, 0,
                                   true, theFolder->folder);                             // StartTrack
    theFolder->special2 = voiceMenu(mp3.getFolderTrackCount(theFolder->folder), 322, 0,
                                    true, theFolder->folder, theFolder->special);        // EndTrack
  }

  // Admin Funktionen
  if (theFolder->mode == 9)
  {
    progmode = 9;                                               // Adminkarte erstellen

    theFolder->folder = 0;
    theFolder->mode = 255;
  }
  return true;
}
// ************ RFID Karte konfigurieren **********************************
void setupCard()
{
  disablestandbyTimer();
  mp3.pause();
#ifdef Konsole
  Serial.println(F(" Setup Card "));
#endif
  nfcTagObject newCard;
  if (setupFolder(&newCard.nfcFolderSettings) == true)
  {
    // Karte ist konfiguriert -> speichern
    mp3.pause();
    do
    {
    }
    while (isPlaying());
    writeCard(newCard);
  }
  delay(2000);
  setstandbyTimer();
}
// ************ RFID Karte lesen **************************************
bool readCard(nfcTagObject * nfcTag)
{
  nfcTagObject tempCard;
  // Show some details of the PICC (that is: the tag/card)
#ifdef Konsole
  Serial.print(F("Card UID:"));
#endif
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
#ifdef Konsole
  Serial.println();
  Serial.print(F("PICC type: "));
#endif
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
#ifdef Konsole
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
#endif
  byte buffer[18];
  byte size = sizeof(buffer);

  // Authenticate using key A
  if ((piccType == MFRC522::PICC_TYPE_MIFARE_MINI ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_1K ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_4K ) )
  {
#ifdef Konsole
    Serial.println(F("Authenticating Classic using key A..."));
#endif
    status = mfrc522.PCD_Authenticate(
               MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }
  else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
    byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the tempCard

    // Authenticate using key A
#ifdef Konsole
    Serial.println(F("Authenticating MIFARE UL..."));
#endif
    status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK)
  {
#ifdef Konsole
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
#endif
    return false;
  }

  // Show the whole sector as it currently is
  // Serial.println(F("Current data in sector:"));
  // mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  // Serial.println();

  // Read data from the block
  if ((piccType == MFRC522::PICC_TYPE_MIFARE_MINI ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_1K ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_4K ) )
  {
#ifdef Konsole
    Serial.print(F("Reading data from block "));
    Serial.print(blockAddr);
    Serial.println(F(" ..."));
#endif
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK)
    {
#ifdef Konsole
      Serial.print(F("MIFARE_Read failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
#endif
      return false;
    }
  }
  else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
    byte buffer2[18];
    byte size2 = sizeof(buffer2);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(8, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
#ifdef Konsole
      Serial.print(F("MIFARE_Read_1 failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
#endif
      return false;
    }
    memcpy(buffer, buffer2, 4);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(9, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
#ifdef Konsole
      Serial.print(F("MIFARE_Read_2 failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
#endif
      return false;
    }
    memcpy(buffer + 4, buffer2, 4);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(10, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
#ifdef Konsole
      Serial.print(F("MIFARE_Read_3 failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
#endif
      return false;
    }
    memcpy(buffer + 8, buffer2, 4);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(11, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
#ifdef Konsole
      Serial.print(F("MIFARE_Read_4 failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
#endif
      return false;
    }
    memcpy(buffer + 12, buffer2, 4);
  }

#ifdef Konsole
  Serial.print(F("Data on Card "));
  Serial.println(F(":"));
#endif
  dump_byte_array(buffer, 16);
#ifdef Konsole
  Serial.println();
  Serial.println();
#endif

  uint32_t tempCookie;
  tempCookie = (uint32_t)buffer[0] << 24;
  tempCookie += (uint32_t)buffer[1] << 16;
  tempCookie += (uint32_t)buffer[2] << 8;
  tempCookie += (uint32_t)buffer[3];

  tempCard.cookie = tempCookie;
  tempCard.version = buffer[4];
  tempCard.nfcFolderSettings.folder = buffer[5];
  tempCard.nfcFolderSettings.mode = buffer[6];
  tempCard.nfcFolderSettings.special = buffer[7];
  tempCard.nfcFolderSettings.special2 = buffer[8];

  if (tempCard.cookie == cardCookie)
  {
    if (activeModifier != NULL && tempCard.nfcFolderSettings.folder != 0)
    {
      if (activeModifier->handleRFID(&tempCard) == true)
      {
        return false;
      }
    }
    // ************* Modifikation ausschalten **************
    if (tempCard.nfcFolderSettings.folder == 0)
    {
      if (activeModifier != NULL)
      {
        if (activeModifier->getActive() == tempCard.nfcFolderSettings.mode)
        {
          activeModifier = NULL;
#ifdef Konsole
          Serial.println(F("modifier removed"));
#endif
          if (isPlaying())
          {
            mp3.playAdvertisement(261);   // Jingle Modifikation AUS
          }
          else
          {
            mp3.start();
            delay(100);
            mp3.playAdvertisement(261);  // Jingle Modifikation AUS
            delay(100);
            mp3.pause();
          }
          delay(100);
          return false;
        }
      }
      // ********Modifikation einschalten *********
      /* if (tempCard.nfcFolderSettings.mode != 0 && tempCard.nfcFolderSettings.mode != 255)
         {
         if (isPlaying())
           {
           //mp3.playAdvertisement(260);  // Jingle Modifikation EIN
           //waitForTrackToFinish();
           delay(100);
           }
         else
           {
           mp3.start();
           delay(100);
           //mp3.playAdvertisement(260);  // Jingle Modifikation EIN
           //waitForTrackToFinish();
           delay(100);
           mp3.pause();
           }
         }*/

      switch (tempCard.nfcFolderSettings.mode )
      {
        case 0:
        case 255:
          mfrc522.PICC_HaltA(); mfrc522.PCD_StopCrypto1(); adminMenu(true);  break;
        case 1: activeModifier = new SleepTimer(tempCard.nfcFolderSettings.special); break;
        case 2: activeModifier = new FreezeDance(); break;
        case 3: activeModifier = new Locked(); break;
        case 4: activeModifier = new ToddlerMode(); break;
        case 5: activeModifier = new KindergardenMode(); break;
        case 6: activeModifier = new RepeatSingleModifier(); break;

      }
      delay(100);
      return false;
    }
    else
    {
      memcpy(nfcTag, &tempCard, sizeof(nfcTagObject));
#ifdef Konsole
      Serial.println( nfcTag->nfcFolderSettings.folder);
#endif
      myFolder = &nfcTag->nfcFolderSettings;
#ifdef Konsole
      Serial.println( myFolder->folder);
#endif
    }
    return true;
  }
  else
  {
    memcpy(nfcTag, &tempCard, sizeof(nfcTagObject));
    return true;
  }
}

//****************** Karte schreiben ********************************
void writeCard(nfcTagObject nfcTag)
{
  MFRC522::PICC_Type mifareType;
  byte buffer[16] = {0x13, 0x37, 0xb3, 0x47,                    // 0x1337 0xb347 magic cookie to
                     // identify our nfc tags
                     0x02,                                      // version 1
                     nfcTag.nfcFolderSettings.folder,           // the folder picked by the user
                     nfcTag.nfcFolderSettings.mode,             // the playback mode picked by the user
                     nfcTag.nfcFolderSettings.special,          // track or function for admin cards
                     nfcTag.nfcFolderSettings.special2,
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                    };

  byte size = sizeof(buffer);

  mifareType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  // Authenticate using key B
  //authentificate with the card and set card specific parameters
  if ((mifareType == MFRC522::PICC_TYPE_MIFARE_MINI ) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_1K ) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_4K ) )
  {
#ifdef Konsole
    Serial.println(F("Authenticating again using key A..."));
#endif
    status = mfrc522.PCD_Authenticate(
               MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }
  else if (mifareType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
    byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the NFCtag

    // Authenticate using key A
#ifdef Konsole
    Serial.println(F("Authenticating UL..."));
#endif
    status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK)
  {
#ifdef Konsole
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
#endif
    mp3.playMp3FolderTrack(401);                              //401- "Oh weh! Das hat leider nicht geklappt!
    waitForTrackToFinish();
    return;
  }

  // Write data to the block
#ifdef Konsole
  Serial.print(F("Writing data into block "));
  Serial.print(blockAddr);
  Serial.println(F(" ..."));
#endif
  dump_byte_array(buffer, 16);
#ifdef Konsole
  Serial.println();
#endif

  if ((mifareType == MFRC522::PICC_TYPE_MIFARE_MINI ) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_1K ) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_4K ) )
  {
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(blockAddr, buffer, 16);
  }
  else if (mifareType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
    byte buffer2[16];
    byte size2 = sizeof(buffer2);

    memset(buffer2, 0, size2);
    memcpy(buffer2, buffer, 4);
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(8, buffer2, 16);

    memset(buffer2, 0, size2);
    memcpy(buffer2, buffer + 4, 4);
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(9, buffer2, 16);

    memset(buffer2, 0, size2);
    memcpy(buffer2, buffer + 8, 4);
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(10, buffer2, 16);

    memset(buffer2, 0, size2);
    memcpy(buffer2, buffer + 12, 4);
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(11, buffer2, 16);
  }

  if (status != MFRC522::STATUS_OK)
  {
#ifdef Konsole
    Serial.print(F("MIFARE_Write failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
#endif
    mp3.playMp3FolderTrack(401);                        //401- "Oh weh! Das hat leider nicht geklappt!
    waitForTrackToFinish();
  }

  else
  {

    if (progmode == 1)
    {
#ifdef Konsole
      Serial.println(F("Konfiguration OK."));
#endif
      mp3.playMp3FolderTrack(400);                         //400- "OK. Ich habe die Karte oder den Shortcut konfiguriert.
    }

    if (progmode == 2)
    {
#ifdef Konsole
      Serial.println(F("Einzelkarte fertig"));
#endif
      mp3.playMp3FolderTrack(402);                        // 402- "OK. Karte fertig"
    }

    if (progmode == 3)
    {
#ifdef Konsole
      Serial.println(F("Modifikationskarte fertig"));
#endif
      mp3.playMp3FolderTrack(404);                        // 404- "OK. Modifikationskarte fertig"
    }

    if (progmode == 9)
    {
#ifdef Konsole
      Serial.println(F("Adminkarte fertig"));
#endif
      mp3.playMp3FolderTrack(409);                        // 409- " Adminkarte erstellt"
    }
  }
  waitForTrackToFinish();

  //Serial.println();
  delay(500);
}

// *************************** Wecker *************************************************
#ifdef Wecker
void wecker()
{
  uint16_t ReadWecker = 0;                    // Variable für den ausgelesenen Wert des WeckerPin

  if (ActWecker == false)                     // Wenn Wecker noch nicht aktiviert wurde
  {
    ReadWecker = analogRead(WeckerPin);       // Weil Analogpin 6 und 7 nicht als Digitalpins verwendet werden können
  }                                           // muss ein Umweg über analogRead() gegangen werden.

  if (ReadWecker >= 512)                      // wenn Analogwert WeckerPin > 2,5V
  {
#ifdef Konsole
    Serial.println(F("Wecker aktiviert! "));
#endif

    SpkOn();                              // Lautsprecher auch bei angeschlossenem Kopfhörer anschalten

    ActWecker = true;                     // Marker setzen: Wecker wurde aktiviert (Erneutes Abspielen
                                          //                des Weckers erst nach Ausschalten des Tonuino möglich)

    playShortCut(4);                      // Wecker abspielen

    if (isPlaying())                      // Solange Wecker spielt
    {
      WeckerPlay = true;                  // Marker setzen - Weckershortcut wird gespielt
    }
  }
  else
  {

    if (SETUP == true)                    // wenn Programmablauf im Setup
    {
      playShortCut(3);                    // Welcomesound spielen
    }
  }


}
#endif


// ************************* Kopfhörer *************************************************

// --------------- Lautsprecher abschalten wenn Kopfhörer angeschlossen -------------------------
// --------------- Bei aktivem Weckersound soll der Lautsprecher nicht ausgeschaltet werden -- nur TonUINO Classic ---
#ifdef EarPhone
void Earphone ()
{
#ifdef Wecker
  if (WeckerPlay == true)
  {
    if (!isPlaying())
    {
      WeckerPlay = false;
    }
  }
  if (WeckerPlay == false)                      // Weckershortcut wird nicht gespielt
  {
#endif
    Ear = digitalRead(EarPhonePin);             // Auslesen Status EarPhonePin

#ifndef KHSensLOW
    if (Ear == HIGH)                            // Wenn Kopfhörer eingesteckt HIGH-Aktiv
#endif

#ifdef KHSensLOW
      if (Ear == LOW)                           // Wenn Kopfhörer eingesteckt LOW-Aktiv
#endif
      {
        if (SpkisOn == true)
          SpkOff();                             // Lautsprecher Ausschalten
      }


    //-------------- Lautsprecher einschalten wenn Kopfhörer getrennt ---------

      else
      {
        if (SpkisOn == false)
          SpkOn();                                 // Lautsprecher Einschalten
      }
  }
#ifdef Wecker
}
#endif
#endif


// ************************** Lautsprecher über Software an und Ausschalten ***************
#ifdef SpkOnOff

// **************************Speaker On *******************

void SpkOn()
{
#ifdef EarPhone
  if (SpkisOn == false) EarVol = volume ;                     // KH-Lautstärke speichern

#ifdef Konsole
  Serial.print(F("Ear-Volume speichern: "));
  Serial.println(EarVol);
#endif
  volume = SpkVol ;                                           // Rücksetzen der Lautstärke auf letzten Lautsprecherwert
  mp3.setVolume(volume);
#ifndef AiO
  digitalWrite(SpkOnPin, HIGH);                               // Lautsprecher über Mosfets Einschalten (Classic)
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, LOW);                                // Verstärker Einschalten (AiO)
#endif
#ifdef Konsole
  Serial.println(F("KH getrennt! Lspr EIN!"));
  Serial.print(F("Spk-Volume: "));
  Serial.println(volume);
#endif
#endif
#ifndef EarPhone
#ifndef AiO
  digitalWrite(SpkOnPin, HIGH);                               // Lautsprecher über Mosfets Einschalten (Classic)
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, LOW);                                // Verstärker Einschalten (AiO)
#endif
#endif
  SpkisOn = true;                                             // Marker setzen-Lautsprecher EIN
}


// **************************Speaker Off *******************

void SpkOff()
{
#ifdef EarPhone
  if (SpkisOn == true)
  {
    SpkVol = volume ;                                           // Spkr-Lautstärke speichern
#ifdef Konsole
    Serial.print(F("Spk-Volume speichern: "));
    Serial.println(SpkVol);
#endif

    if (EarFirstTime == true)
    {
      EarVol = mySettings.initEarVol;                           // Wenn Kh das erste mal eingesteckt,Startlautstärke für Kopfhörer einstellen
      EarFirstTime = false;                                     // Rücksetzen Marker, Kopfhörer das erste mal gesteckt
    }

    volume = EarVol;

    mp3.setVolume(volume);                                      // KH-Lautstärke setzen
#ifndef AiO
    digitalWrite(SpkOnPin, LOW);                                // Lautsprecher über Mosfets Ausschalten (Classic )
#endif
#ifdef AiO
    digitalWrite(SpkOnPin, HIGH);                               // Verstärker Ausschalten AiO
#endif
#ifdef Konsole
    Serial.println(F("KH angeschlossen! Lspr AUS!"));
    Serial.print(F("Ear-Volume: "));
    Serial.println(volume);
#endif
    SpkisOn = false;                                            // Marker setzen-Lautsprecher AUS
  }
#endif
#ifndef EarPhone
#ifndef AiO
  digitalWrite(SpkOnPin, LOW);                                // Lautsprecher über Mosfets Ausschalten (Classic )
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, HIGH);                               // Verstärker Ausschalten AiO
#endif
  SpkisOn = false;                                            // Marker setzen-Lautsprecher AUS
#endif
}

#endif


// ******************** LED-Animation ****************************
#ifdef LED_SR

void LED_Animation()
{
  if (isPlaying())
  {
    bool lsrAudioBreak = false;           // Marker, ob Wiedergabe gestoppt bei Ein-Ausschalten LED Animation
  }

#ifdef LED_SR_Switch                      // Einstieg Abfrage Tasten zur Aktivierung / Deaktivierung LED Animationen

  if (isPlaying())                        // wenn Track gespielt wird
  {
    lsrAudioBreak = false;                // Marker setzen Wiedergabe läuft
  }

  // *********** Led Animation Ein oder Ausschalten ******************
  //************ Vor Taste und Rück Taste langer Druck ***************

  if ( (upButton.pressedFor(LONG_PRESS)
        || downButton.pressedFor(LONG_PRESS) )
       && upButton.isPressed()
       && downButton.isPressed())
  {
    lsrSwitch = true;                 // Marker auf Tasten gedrückt setzen
#ifdef Konsole
    Serial.print(F("LED-Animation: "));
#endif
    ignoreUpButton = true;            // LauterTaste übergehen
    ignoreDownButton = true;          // LeiserTaste übergehen
  }

  // ***************** Einschalten Animation *************

  if (lsrSwitch == true
      && lsrEnable == false
      && (upButton.isReleased() ))
  {
    lsrSwitch = false ;                 // Marker Tasten gedrückt rücksetzen
    lsrEnable = true ;                  // Animation aktivieren
#ifdef Konsole
    Serial.println(F("aktiviert"));
#endif
    if (isPlaying())                    // Wiedergabe muss gestoppt werden, sonst hängt sich der Mp3-Player auf
    {
      mp3.pause();                      // Wiedergabe stoppen --> Fortsetzen der Wiedergabe nach 1.Durchlauf der Animationsschleife
      setstandbyTimer();
      lsrAudioBreak = true;             // Marker Wiedergabe gestoppt
    }
  }

  // ************** Ausschalten Animation über Tasten oder Standbytimer ***************

  if ((lsrSwitch == true
       && lsrEnable == true
       && (upButton.isReleased()))
      || (lsrOffByStdby == true))
  {
    lsrSwitch = false ;                 // Marker Tasten gedrückt rücksetzen
    lsrEnable = false ;                 // Animation deaktivieren
#ifdef Konsole
    Serial.println(F("deaktiviert"));
#endif
    if (isPlaying())                    // Widergabe muss gestoppt werden, sonst hängt sich der Mp3-Player auf
    {
      mp3.pause();                      // Wiedergabe stoppen  --> Fortsetzen der Wiedergabe nach 1.Durchlauf der Animationsschleife
      setstandbyTimer();
      lsrAudioBreak = true;             // Marker Wiedergabe gestoppt setzen
      strip.clear();                    // Strip löschen
      strip.show();
    }
  }

#endif                                  // Ende Abfrage Tasten zur Aktivierung LED Animationen #ifdef LED_SR_Switch

#ifdef LED_SR_Switch                    // Ergebnis Tastenabfrage
  if (lsrEnable == true)                // Wenn wahr, Animationen durchführen
  {
#endif

    //*************LED-Animaion by @tON **** modifiziert ***********************
    ///////////////// Prüfung der einmaligen Animationen /////////////////

    // ----------   Liedänderung erkennen und Animation aktivieren   ---------- //
    currentDetectedTrack = currentQueueIndex;
    if (currentDetectedTrack != lastDetectedTrack)
    {
      strip.clear();
      if (currentQueueIndex > lastDetectedTrack) //nächstes Lied
      {
        lsrAnimationTrackMode = 1;
        lsrColors = lsrColorUp;
      }
      if (currentQueueIndex < lastDetectedTrack) // Lied zurück
      {
        lsrAnimationTrackMode = 2;
        lsrColors = lsrColorDown;
      }
      lsrAnimationMode = 1;
      animCount = strip.numPixels();
      loopCountWait = 5;                 // Geschwindigkeit der Animation, je größer um so langsamer
      y = 0;
    }

    // ----------    Lautstärkenanpassung erkennen und Animation aktivieren    ---------- //
    currentDetectedVolume = volume;
    if (currentDetectedVolume != lastDetectedVolume)
    {
      lsrAnimationMode = 2;
      animCount = strip.numPixels();
      loopCountWait = 6;
      y = 0;
    }

    ///////////////// Dauerhafte Loop Animationen /////////////////

    // ----------   Loop Animation: Default Mode   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == false && knownCard == false)
    {
      loopCountWait = 1;               // Geschwindigkeit der Animation, je größer um so langsamer

      // Farbe & Animation definieren: Alle LEDs leuchten alle abwechselnd  im hue Spektrum
      y++;
      if (y >= (strip.numPixels() * 8) )
      {
        y = 0;
      }
      strip.fill(strip.ColorHSV((y * 65536 / strip.numPixels() / 8) , 255, 30), 0, 0);

      strip.show();
      loopCount = loopCountWait;
    }

    // ----------   Loop Animation: Musik spielt   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == true && knownCard == true)
    {
      loopCountWait = 10;                        // Geschwindigkeit der Animation, je größer um so langsamer

      // Farbe definieren: hue Spektrum (Rainbow)
      do
      {
        for (i = 0; i < strip.numPixels(); i++)
        {
          lsrColors = strip.ColorHSV(i * 65536 / strip.numPixels(), 255, 30);
          strip.setPixelColor(i, lsrColors);
          lsrColorR[i] = (lsrColors >> 16 & 0xFF);
          lsrColorG[i] = (lsrColors >> 8 & 0xFF);
          lsrColorB[i] = (lsrColors & 0xFF);
        }
        x++;
      }
      while (x < strip.numPixels());

      // Animation definieren: Rotation im Uhrzeigersinn
      y++;
      x = 0;
      if (y >= strip.numPixels())
      {
        y = 0;
      }
      do
      {
        for (i = 0; i < strip.numPixels(); i++)
        {
          strip.setPixelColor((i + y) % strip.numPixels(), lsrColorR[i], lsrColorG[i], lsrColorB[i]);
        }
        x++;
      }
      while (x < strip.numPixels());

      strip.show();
      loopCount = loopCountWait;
    }

    // ----------   Loop Animation: Musik pausiert   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == false && knownCard == true)
    {
      loopCountWait = 15;                         // Geschwindigkeit der Animation, je größer um so langsamer

      // Fabre definieren: hue Spektrum (Rainbow)
      strip.clear();                              // Danach nur ein Punkt
      x = 0;
      do
      {
        for (i = 0; i < strip.numPixels(); i++)
        {
          lsrColors = strip.ColorHSV(i * 65536 / strip.numPixels(), 255, 30);
          lsrColorR[i] = (lsrColors >> 16 & 0xFF);
          lsrColorG[i] = (lsrColors >> 8 & 0xFF);
          lsrColorB[i] = (lsrColors & 0xFF);
        }
        x++;
      } while (x < strip.numPixels());

      // Farbe definieren: Füllend ansteigend

      y++;
      if (y >= strip.numPixels())
      {
        y = 0;
        z++;
        strip.clear();
      }
      if (z >= strip.numPixels())
      {
        z = 0;
      }

      x = 0;
      do
      {
        for (i = 0; i < y + 1 ; i++)
        {
          strip.setPixelColor( y , lsrColorR[y], lsrColorG[y], lsrColorB[y]);
        }
        x++;
      }
      while (x < y + 1);

      strip.show();
      loopCount = loopCountWait;
    }

    ///////////////// Einmalige Animationen bei einem Ereignis /////////////////

    // ----------   Einmalige Animation: Liedänderung    ---------- //
    if (lsrAnimationMode == 1 && loopCount == 0)
    {

      // Farbe definieren: oben definiert
      x = 0;
      do
      {
        for (i = 0; i < strip.numPixels(); i++)
        {
          lsrColorR[i] = (lsrColors >> 16 & 0xFF);
          lsrColorG[i] = (lsrColors >> 8 & 0xFF);
          lsrColorB[i] = (lsrColors & 0xFF);
        }
        x++;
      }
      while (x < strip.numPixels());

      // Animation definieren: oben definiert

      if (y >= strip.numPixels())
      {
        strip.clear();
        y = 0;
      }

      if (lsrAnimationTrackMode == 1)
      {
        z = y ;
      }
      if (lsrAnimationTrackMode == 2)
      {
        z = strip.numPixels() - y ;
      }

      x = 0;
      do
      {
        for (i = 0; i < y + 1 ; i++)
        {
          strip.setPixelColor( z , lsrColorR[y], lsrColorG[y], lsrColorB[y]);
        }
        x++;
      }
      while (x < y + 1);

      y++;

      strip.show();

      if (animCount != 0)
      {
        animCount--;
      }

      if (animCount == 0)
      {
        lsrAnimationMode = 0;
      }
      loopCount = loopCountWait ;
    }

    // ----------   Einmalige Animation: Prozentuale Lautstärkenanpassung   ---------- //
    if (lsrAnimationMode == 2 && loopCount == 0)
    {
      if (animCount != 0)
      {
        animCount--;
      }

      if (currentDetectedVolume != lastDetectedVolume)
      {
        loopCountWait = 5;
      }
#ifndef EarPhone
      volumeScope = (mySettings.maxVolume - mySettings.minVolume);
      volumeScopeAmount = (volume - mySettings.minVolume) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs
#endif
#ifdef EarPhone
     if (SpkisOn == false)
      { 
      volumeScope = (mySettings.maxEarVol - mySettings.minEarVol);
      volumeScopeAmount = (volume - mySettings.minEarVol) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs
      }
      else
      {
      volumeScope = (mySettings.maxVolume - mySettings.minVolume);
      volumeScopeAmount = (volume - mySettings.minVolume) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs
      }
#endif
      // Farbe definieren: von grün zu rot
      x = 0;
      do
      {
        for (i = 0; i < strip.numPixels(); i++)
        {
          lsrHueCalc = 21000 / (strip.numPixels() - 1) / (strip.numPixels() - 1);
          lsrColors = strip.ColorHSV(((strip.numPixels() - 1) - i) * (strip.numPixels() - 1) * lsrHueCalc, 255, 30);
          strip.setPixelColor(i, lsrColors);
          lsrColorR[i] = (lsrColors >> 16 & 0xFF);
          lsrColorG[i] = (lsrColors >> 8 & 0xFF);
          lsrColorB[i] = (lsrColors & 0xFF);
        }
        x++;
      }
      while (x < strip.numPixels());

      // Animation definieren: Prozentuale Lautstärkenanpassung
      strip.clear();
      x = 0;
      do
      {
        for (i = 0; i < volumeScopeAmount + 1; i++)
        {
          strip.setPixelColor(i, lsrColorR[i], lsrColorG[i], lsrColorB[i]);
        }
        x++;
      }
      while (x < (volumeScopeAmount + 1));

      strip.show();

      if (animCount == 0)
      {
        //delay(20);
        lsrAnimationMode = 0;
      }
      loopCount = loopCountWait;
    }

    // ----------   Countdown Zähler über den loop als Ersatz zur delay Funktion   ----------
    if (loopCount != 0 ) {
      loopCount--;
    }

    // ----------   Dadurch wird die Änderung der Lautstärke bzw. Track nur ein mal registiert   ----------
    lastDetectedVolume = currentDetectedVolume;
    lastDetectedTrack = currentDetectedTrack;

#ifdef LED_SR_Switch
  }
#endif

  if (lsrAudioBreak == true)    // wenn Wiedergabe von LED On/Off gestoppt
  {
    mp3.start();                 // Wiedergabe fortsetzen
    disablestandbyTimer();
    lsrAudioBreak = false;       // Marker Wiedergabe läuft wieder
  }
}
#endif                           // Ende Abfrage Aktivierung LED Animation (#ifdef LED_SR)

// *************************** Ende LED Animation ******************************************

// *****************************************************************************************
// *****************************************************************************************
//                           SETUP
// *****************************************************************************************
void setup()
{
  SETUP = true;                          // Marker setzen, Setup wird durchlaufen

  Serial.begin(115200);                  // serielle Schnittstelle initialisieren
  // ------------------------------------------------------------------------------------
  // Urheber Infos, Dieser Hinweis darf nicht entfernt werden
#ifndef AiO
  Serial.println(F(" ** TONUINO ** ALWAYS QUEUE **"));
#endif
#ifdef AiO
  Serial.println(F(" ** TONUINO - AiO ** ALWAYS QUEUE **"));
#endif
  Serial.println(F(" ** VERSION THOMAS LEHNERT ** 2021-01-01 **"));
  Serial.println();
#ifndef AiO
  Serial.println(F("Based on TonUINO Version 2.1"));
#endif
#ifdef AiO
  Serial.println(F("Based on TonUINO Version 2.2"));
#endif
  Serial.println(F("created by Thorsten Voß and licensed under GNU/GPL."));
  Serial.println(F("https://tonuino.de.\n"));
  // ------------------------------------------------------------------------------------
#ifdef FIVEBUTTONS
  Serial.println(F("*** 5 Tasten-Modus ***"));
#endif
#ifndef FIVEBUTTONS
  Serial.println(F("*** 3 Tasten-Modus ***"));
#endif
  Serial.println(" ");
  // ------------------------------------------------------------------------------------
  pinMode(BusyPin, INPUT);              // Eingang Busy-Signal vom DF-Player
  pinMode(ButtonPause, INPUT_PULLUP);   // Eingang Pausetaste
  pinMode(ButtonUp, INPUT_PULLUP);      // Eingang Uptaste
  pinMode(ButtonDown, INPUT_PULLUP);    // Eingang Downtaste
#ifdef FIVEBUTTONS
  pinMode(ButtonFourPin, INPUT_PULLUP); // Eingang Taste 4
  pinMode(ButtonFivePin, INPUT_PULLUP); // Eingang Taste 5
#endif
  // ------------------------------------------------------------------------------------
#ifdef EarPhone
#ifdef AiO
  pinMode (EarPhonePin, INPUT);         // Eingang,Sensor ob Kopfhörer angeschlossen?
#endif
#ifndef AiO
  pinMode (EarPhonePin, INPUT_PULLUP);  // Eingang,Sensor ob Kopfhörer angeschlossen?
#endif
#endif
  // ------------------------------------------------------------------------------------
#ifdef HW_PowerOff
#ifndef AiO
  pinMode(ShutDownPin, OUTPUT);         // Ausgang Ausschaltsignal für MosFet oder Polulo-Switch
  #ifdef LowActive
  digitalWrite(ShutDownPin, HIGH);      // Voreinstellung - On
  #endif
  #ifndef LowActive
  digitalWrite(ShutDownPin, LOW);       // Voreinstellung - On
  #endif
#endif
#endif
#ifdef AiO
  pinMode(ShutDownPin, OUTPUT);
  digitalWrite(ShutDownPin, HIGH);      // Spannung AiO einschalten

  pinMode(Access_SD_Pin, OUTPUT);
  digitalWrite(Access_SD_Pin, LOW);     // SD karten Zugang über USB gesperrt
#endif

  // ------------------------------------------------------------------------------------
#ifdef SpkOnOff
  pinMode(SpkOnPin, OUTPUT);            // Ausgang Lautsprecher-Einschaltsignal
#ifndef AiO
  digitalWrite(SpkOnPin, LOW);          // Voreinstellung TonUINO Classic - Speaker Off
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, HIGH);         // Voreinstellung AiO - Speaker Off (Amp Off)
#endif
#endif
  // --------------------------------------------------------------------------------------
  //********* Wert für randomSeed() erzeugen durch das mehrfache Sammeln *****
  // ******** von rauschenden LSBs eines offenen Analogeingangs **************
  uint32_t ADC_LSB;
  uint32_t ADCSeed;
  for (uint8_t i = 0; i < 128; i++)
  {
    ADC_LSB = analogRead(RandomPin) & 0x1;
    ADCSeed ^= ADC_LSB << (i % 32);
  }
  randomSeed(ADCSeed);                   // Zufallsgenerator initialisieren
  // ------------------------------------------------------------------------------------
  // *************** Settings aus EEPROM laden *************
  loadSettingsFromFlash();
  // ------------------------------------------------------------------------------------
  //*************** LED Animation initialisieren ************
#ifdef LED_SR
  strip.begin();
  strip.setBrightness(20);
  strip.show();

  loopCount = 0;
  animCount = 1;
  lastDetectedTrack = 0;
#endif

  // ------------------------------------------------------------------------------------
  //*************** DFPlayer Mini initialisieren ***********************
  mp3.begin();

 delay(2000);   // Zwei Sekunden warten bis der DFPlayer Mini initialisiert ist 

#ifdef CountFolders
  numFolders = (mp3.getTotalFolderCount( ));  // Ordner zählen
#ifdef IgnoreWinSysInf
  numFolders = numFolders - 1;                // Der Windows Ordner System Volume Information wird ignoriert
#endif
  Serial.print("Ordner auf SD: ");
  Serial.println (numFolders);
  Serial.println ();
#endif

  // ------------------------------------------------------------------------------------
  //************* NFC Leser initialisieren *****************************
  SPI.begin();                        // Init SPI bus
  mfrc522.PCD_Init();                 // Init MFRC522


#ifdef NFCgain_avg                                    // Leseempfindlichkeit mittel (default)
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_avg);
  Serial.println(F("mfrc522-> RxGain_avg"));
#endif
#ifdef NFCgain_max                                    // Leseempfindlichkeit maximal
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  Serial.println(F("mfrc522-> RxGain_max"));
#endif
#ifdef NFCgain_min                                    // Leseempfindlichkeit niedrig
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_min);
  Serial.println(F("mfrc522-> RxGain_min"));
#endif

  mfrc522.PCD_DumpVersionToSerial();      // Show details of PCD - MFRC522 Card Reader
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  // ------------------------------------------------------------------------------------
  //************ Lautstärke des Lautsprechers auf Startlautstärke setzen *****************

  mp3.setVolume(mySettings.initVolume);
  mp3.setEq(mySettings.eq - 1);

  volume = mySettings.initVolume;                     // Startlautstärke

  // ------------------------------------------------------------------------------------
  //  ******************* Lautsprecher einschalten ***Hardwareerweiterung erforderlich *****
#ifdef SpkOnOff

  SpkVol = mySettings.initVolume;                     // Variable setzen, Startlautstärke Lautsprecher
#ifdef EarPhone
  EarVol = mySettings.initEarVol;                     // Variable setzen, Startlautstärke für Kopfhörer
#endif
  SpkOn();

  if (SpkisOn == true) mp3.setVolume(mySettings.initVolume);  //Startlautstärke Lautsprecher einstellen
#ifdef EarPhone
  else mp3.setVolume(mySettings.initEarVol);                  //Startlautstärke für Kopfhörer einstellen
#endif
#endif

  // ------------------------------------------------------------------------------------

  //  *************** Manueller Reset beim Einschalten ****************************************

  // RESET --- ALLE DREI KNÖPFE BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden auf DEFAULT gesetzt
  if (digitalRead(ButtonPause) == LOW
      && digitalRead(ButtonUp) == LOW
      && digitalRead(ButtonDown) == LOW)
  {
    Serial.println(F("Reset -> lösche EEPROM"));
#ifndef AiO
    for (int i = 0; i < EEPROM.length(); i++)
    {
      EEPROM.update(i, 0);
    }
#endif
#ifdef AiO
    for (int i = 0; i < 1024; i++)
    {
      EEPROM_update(i, 0);
    }
#endif

    resetSettings();

    mp3.playMp3FolderTrack(999);                    //999 Reset wurde durchgeführt!
    waitForTrackToFinish();
    delay(5000);
  }

  // ------------------------------------------------------------------------------------
  // *************** Standby Timer aktivieren *****************
  setstandbyTimer();

  // ------------------------------------------------------------------------------------
  // *********************** Kopfhörer *****************************************************
#ifdef Wecker
  WeckerPlay = false;
#endif

#ifdef EarPhone
  EarFirstTime = true ;
  Earphone ();
#endif

  // ------------------------------------------------------------------------------------
  // *************  Wecker ** Hardwareerweiterung erforderlich ****************************
#ifdef Wecker
  wecker();
#endif

  // ------------------------------------------------------------------------------------
  // *********** Start Shortcut "at Startup" - e.g. Welcome Sound ************************
#ifndef Wecker
  playShortCut(3);
#endif

  // ------------------------------------------------------------------------------------
  // *************** Freigabe oder Unterdrückung Konsolenausgabe **************************
#ifndef Konsole
  Serial.println ("Weitere Konsolenausgaben deaktiviert");
#endif

  // ------------------------------------------------------------------------------------
  SETUP = false;                          // Marker setzen, Setup ist beendet
}

// ****************** Ende Setup ************************************************
// ******************************************************************************


// *******************************************************************************
//                            MAIN-LOOP
// *******************************************************************************
void loop()
{
  do
  {

    // ************************ Wecker **** Hardwareerweiterung erforderlich ***********************
#ifdef Wecker
    if (ActWecker == false)   // wenn Wecker noch nicht aktiviert worden ist
      wecker();
#endif

    // ******************** Lautsprecher abschalten wenn Kopfhörer angeschlossen *******************
    // **** wenn der Wecker aktiv wird soll der Lautsprecher nicht abgeschaltet werden *************

#ifdef EarPhone
    Earphone ();
#endif

    // ************************ LED Animation ** Hardwareerweiterung erforderlich ******************
#ifdef LED_SR
    LED_Animation();
#endif

    // ************************Prüfen StandbyTimer und aktive Modifikation *************************

    checkStandbyAtMillis();                    // Prüfen standbytimer
    mp3.loop();

    if (activeModifier != NULL)                // Prüfen auf aktive Modifikationskarte
      activeModifier->loop();                  // Modifikation aktivieren

    // ********************** Auswerten der Tasten *************************************************
    // Buttons werden nun über JS_Button behandelt, dadurch kann jede Taste
    // doppelt belegt werden

    readButtons();                             // Tasten auslesen

    // ***************** admin menu über longPress 3 Tasten aktivieren **************************

    if ((pauseButton.pressedFor(LONG_PRESS)
         || upButton.pressedFor(LONG_PRESS)
         || downButton.pressedFor(LONG_PRESS))
        && pauseButton.isPressed()
        && upButton.isPressed()
        && downButton.isPressed())
    {
      mp3.pause();                             // Wiedergabe stoppen
      do
      {
        readButtons();                         // Tasten auslesen
      }

      while (pauseButton.isPressed()
             || upButton.isPressed()
             || downButton.isPressed());

      readButtons();                           // Tasten auslesen
      adminMenu();                             // adminmenü starten
      break;
    }

    // ******************* Pause Taste ****************************************************

    if (pauseButton.wasReleased())                              // wenn Pausetaste gedrückt wurde
    {
      if (activeModifier != NULL)                               // wenn Modifikation aktiv
        if (activeModifier->handlePause() == true)              // wenn akt.Modifikation pause Taste sperrt
          return;                                               // Abbrechen
      if (ignorePauseButton == false)                           // Wenn Taste gelesen
        if (isPlaying())                                        // wenn Wiedergabe
        {
          mp3.pause();                                          // Pause der Wiedergabe
          setstandbyTimer();
        }
        else if (knownCard)                                     // wenn keine Wiedergabe läuft und karte bekannt
        {
          mp3.start();                                          // Wiedergabe starten
          disablestandbyTimer();
        }
      ignorePauseButton = false;                                // Pausetaste auswerten
    }
    else if (pauseButton.pressedFor(LONG_PRESS)
             && ignorePauseButton == false)                     // Langer Druck Pausetaste für Ansage des aktuellen Tracks
    {
      if (activeModifier != NULL)                               // wenn Modifikationskarte aktiv
        if (activeModifier->handlePause() == true)              // wenn Pausetaste gesperrt - Abbruch
          return;
      if (isPlaying())                                          // wenn Wiedergabe läuft
      {
        uint8_t advertTrack = queue[currentQueueIndex];         // Auslesen der Tracknummer für Ansage Tracknr

        // Spezialmodus Von-Bis für Album und Party gibt die Dateinummer relativ zur Startposition wieder
        if (myFolder->mode == 8 || myFolder->mode == 9)         // Spezialmodus Album oder Spezialmodus Party
        {
          advertTrack = advertTrack - myFolder->special + 1;    // Ansage auf relative Track Nr
        }

        //************ Rücksetzen - Hörbuch auf Anfang ****************************
        // Im Hörbuchmodus wird durch langen Druck Pause Taste der Fortschritt auf Anfang gesetzt
#ifdef HB_Reset
        if (myFolder->mode == 5)                                // Hörbuchmodus
        {
          currentQueueIndex = 1;                                // aktueller Track auf 1 setzen
          advertTrack = currentQueueIndex;                      // Ansage auf aktueller Track
          mp3.playAdvertisement(advertTrack);                   // Tracknummer ansagen

#ifndef AiO
          EEPROM.update(myFolder->folder, currentQueueIndex);   // Track 1 im EEProm speichern
#endif
#ifdef AiO
          EEPROM_update(myFolder->folder, currentQueueIndex);   // Track 1 im EEProm speichern
#endif
#ifdef Konsole
          Serial.println(F("Hörbuch Modus -> Anfang"));
#endif
          mp3.playFolderTrack(myFolder->folder, currentQueueIndex);  // aktuellen Track spielen
        }
#endif
        //************** Ende, Rücksetzen - Hörbuch auf Anfang ***********************
        else                                                    // alle anderen Abspielmodi
        {
          mp3.playAdvertisement(advertTrack);                   // Tracknummer ansagen
        }
      }
      else                                                      // wenn keine Wiedergabe läuft
      {
        playShortCut(0);                                        // Shortcut Pausetaste spielen
      }
      ignorePauseButton = true;                                 // PauseTaste übergehen
    }
    // *********** Ende Pausetaste *************************************************

    // *************** Vol + Taste *************************************************

#ifdef LED_SR_Switch
    if (upButton.pressedFor(LONG_PRESS) && lsrSwitch == false)
#endif
#ifndef LED_SR_Switch
    if (upButton.pressedFor(LONG_PRESS))
#endif    
    {
#ifndef FIVEBUTTONS                             // wenn nicht 5 Tasten
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (!mySettings.invertVolumeButtons)    // Vol-Tasten nicht invertiert
        {
          longPressVol = true;                  // VolÄnderung durch longPress
          volumeUpButton();                     // Lauter Taste
        }
        else
        {                                       // sonst
          nextButton();                         // weiter Taste
        }
      }
      else                                      // wenn keine Wiedergabe
      {
        playShortCut(1);                        // Spiele Shortcut 1
      }
      ignoreUpButton = true;                    // LauterTaste übergehen
#endif
    }                                           // Ende if longPress
    else if (upButton.wasReleased())            // wenn Taste gedrückt wurde
    {
      if (!ignoreUpButton)                      // Wenn Taste gelesen
        if (!mySettings.invertVolumeButtons)    // wenn Tasten nicht invertiert
        {
          nextButton();                         // weiter Taste
        }
        else                                    // sonst
        {
          volumeUpButton();                     // Lauter Taste
          longPressVol = false;                 // VolÄnderung durch einfachen Tastendruck
        }
      ignoreUpButton = false;                   // LauterTaste auswerten
    }
    // *********** Ende Vol + Taste ********************************************

    // *************** Vol - Taste *********************************************

#ifdef LED_SR_Switch
    if (downButton.pressedFor(LONG_PRESS) && lsrSwitch == false)
#endif
#ifndef LED_SR_Switch
    if (downButton.pressedFor(LONG_PRESS))
#endif    
    {
#ifndef FIVEBUTTONS                                     // wenn 3 Tasten-Modus
      if (isPlaying())                                  // Bei laufender Wiedergabe
      {
        if (!mySettings.invertVolumeButtons)            // wenn Vol-Tasten nicht invertiert
        {
          longPressVol = true;                          // VolÄnderung durch longPress
          volumeDownButton();                           // Lautstärketaste
        }
        else                                            // wenn Vol-Tasten invertiert
        {
          previousButton();                             // Taste Track zurück
        }
      }
      else                                              // wenn keine Wiedergabe läuft
      {
        playShortCut(2);                                // Shortcut spielen Next-Taste
      }
      ignoreDownButton = true;                          // LeiserTaste übergehen
#endif
    }
    else if (downButton.wasReleased())                  // Wenn Taste betätigt wurde
    {
      if (!ignoreDownButton)                            // Wenn Taste ausgewertet
      {
        if (!mySettings.invertVolumeButtons)            // Wenn Tasten nicht invertiert
        {
          previousButton();                             // Zurück Taste
        }
        else                                            // wenn Tasten invertiert
        {
          volumeDownButton();                           // Leiser Taste
          longPressVol = false;                         // VolÄnderung durch einfachen Tastendruck
        }
      }
      ignoreDownButton = false;                         // LeiserTaste auswerten
    }
    // *********** Ende Vol - Taste ********************************************

    // ********** 5 Tasten-Modus ***********************************************

#ifdef FIVEBUTTONS                              // 5 Tasten-Modus

    // ************ Taste 4 **************************************
    if (buttonFour.wasReleased())               // Taste wurde betätigt
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (!mySettings.invertVolumeButtons)    // wenn Tasten nicht invertiert
        {
          volumeUpButton();                     // Lauter-Taste
          longPressVol = false;                 // VolÄnderung durch einfachen Tastendruck
        }
        else                                    // wenn Tasten invertiert
        {
          nextButton();                         // Next - Taste
        }
      }
      else                                      // wenn Wiedergabe nicht läuft
      {
        playShortCut(1);                        // shortcut Next-Taste spielen
      }
    }

    // ************ Taste 5 ************************************
    if (buttonFive.wasReleased())               // Taste wurde betätigt
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (!mySettings.invertVolumeButtons)    // wenn Tasten nicht invertiert
        {
          volumeDownButton();                   // Leiser-Taste
          longPressVol = false;                 // VolÄnderung durch einfachen Tastendruck
        }
        else                                    // wenn Tasten invertiert
        {
          previousButton();                     // Zurück - Taste
        }
      }
      else                                      // wenn Wiedergabe nicht läuft
      {
        playShortCut(2);                        // shortcut Zurück-Taste spielen
      }
    }
#endif

  }
  // ****************** Ende der Buttons ***********************************

  // **************** RFID-Reader - check Karte aufgelegt ******************

  while (!mfrc522.PICC_IsNewCardPresent());           // bleibe in der Schleife, Solange keine neue Karte aufgelegt

  // RFID Karte wurde aufgelegt

  if (!mfrc522.PICC_ReadCardSerial())                 // wenn Karte nicht lesbar - Abbruch, Rückkehr in Schleife
    return;

  // ************** Karte ist konfiguriert *****************************
  if (readCard(&myCard) == true)                      // wenn Karte lesbar
  {
    // make random a little bit more "random"
    randomSeed(millis() + random(1000));

    if (myCard.cookie == cardCookie                   // überprüfen ob Karte bekannt,
        && myCard.nfcFolderSettings.folder != 0       // ein Ordner konfiguriert,
        && myCard.nfcFolderSettings.mode != 0)        // und ein Abspielmodus festgelegt ist
    {
      playFolder();                                   //Wiedergabe starten
    }
    // ********** neue unbenutzte Karte **********************************
    else if (myCard.cookie != cardCookie)             // wenn Karte leer - neue Karte konfigurieren
    {
      knownCard = false;
      mp3.playMp3FolderTrack(300);                    // 300- "Oh, eine neue Karte"
      waitForTrackToFinish();
      setupCard();                                    // Karte konfigurieren
    }
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
// ************ Main LOOP ENDE *********************************************
// *************************************************************************

// *************************************************************************
// ***************** Hilfsprogramme ****************************************

////////////////////// Dump Byte Array ////////////////////////////////////

// Helper routine to dump a byte array as hex values to Serial.

void dump_byte_array(byte * buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
#ifdef Konsole
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
#endif
  }
}


///////////// Emulation für EEPROM auf dem AiO Board ////////////////////////////

// emulates EEPROM.put() .get() and .update() on LGT8F328P platform
// partially sourced from: https://playground.arduino.cc/Code/EEPROMWriteAnything/

#ifdef AiO
//--------------------------------------------------------------
template <class T> int EEPROM_put(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;

  for (i = 0; i < sizeof(value); i++) EEPROM.write(ee++, *p++);
  return i;
}
//---------------------------------------------------------------
template <class T> int EEPROM_get(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  unsigned int i;

  for (i = 0; i < sizeof(value); i++) *p++ = EEPROM.read(ee++);
  return i;
}
//---------------------------------------------------------------
template <class T> void EEPROM_update(int ee, const T& value)
{
  EEPROM.read(ee) != value ? EEPROM.write(ee, value) : delay(0);
}

#endif
