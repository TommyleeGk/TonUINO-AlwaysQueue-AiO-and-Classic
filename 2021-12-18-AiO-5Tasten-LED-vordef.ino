

/****** Alternative Software *************
   _____         _____ ___ ___ _______
  |_   _|___ ___|  |  |   |   | |     |
    | | | . |   |  |  |- -| | | |  |  |
    |_| |___|_|_|_____|___|_|___|_____|
    Based on TonUINO Version 2.1 and Version 2.2 AiO

    created by Thorsten Voß and licensed under GNU/GPL.
    Information and contribution at https://tonuino.de.

********* Always Queue - AiO oder Classic TonUINO ************************

      Version Thomas Lehnert

      letzte Änderung 2021-12-18
   

    - Über #define wird ausgewählt, ob die Software auf dem AiO - Board,
      oder auf dem TonUINO Classic  aus Einzelkomponenten mit dem Arduino Nano
      benutzt werden soll.
    ========================== AiO ========================================================================
    - Für die AiO Platine müssen folgende Einstellungen vorgenommen werden.
      Die LGT8Fx Bibliotheken müssen in der IDE installiert sein !
      Siehe folgender Link: https://www.leiterkartenpiraten.de/2020/11/21/die-arduino-ide-einrichten/
      Für die Batteriemessung die modifizierten LGT8FX Bibliotheken mit Unterstützung des Analogpin 10 installieren.
      Link: https://github.com/jayzakk/lgt8fx/blob/1b0f5c53d1cd24ae76d14d37f0f526694a612431/lgt8f/variants/lgt8fx8p/pins_arduino.h

      Boardtyp LGT8F328 unter Logic green Arduino AVR Compatible Boards auswählen
      Clock Source: External (assumes 32MHz crystal)
      Clock: 16 MHz
      Variant: 328P-LQFP (e.g. MiniEVB nano-style and WAVGAT)
      Arduino as ISP: Default (64)
      Korrekten COM Port
      Um den korrekten COM Port auswählen zu können, muss die AiO angeschlossen sein. 
      Der COM Port kann sich unterscheiden (siehe Gerätemanager).

   ======================= TonUINO - Klassik ================================================================
   - Für die Nutzung in der Version Classic mit Einzelkomponenten, 
     Nano 328P oder Nano 328P(Old Bootlader) je nach Version auswählen.

   ===========================================================================================================
     !!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!! WICHTIG !!!!!!!!!!!
     !!                                                                                                     !!
     !!   Diese Version  erfordert geänderte und erweiterte Dateien im advert und mp3 Ordner.               !!
     !!   Für die korrekte Funktion müssen die dieser Version beigefügten mp3 und advert Ordner verwendet   !!
     !!   werden.                                                                                           !!
     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  ============================================================================================================
   Eine Übersicht aller vorgenommenen Änderungen und Erweiterungen befindet sich am Ende des Scetches.
  ============================================================================================================
  ***********************************************************************************************************/

// ============================================================================================================
// *************** Auswahl der Tonuino-Variante ** AiO oder TonUINO Classic *********************
// uncomment or comment the " #define AiO "  to switch enter the AiO Softwareversion or TonUINO Classic

// ---------------------- All in One Board ----------------------------------------------------------------------
 #define AiO                    // Software wird an das AiO Board angepasst
                                // Für den TonUINO Classic " #define AiO " in Kommentar setzen

// --------------------- Jackdetekt Kopfhörer - AiO ---- nur mit Hardwareänderung --------------------------------
 #ifdef AiO                     // Bei gestecktem Kopfhörer wird das Jackdetekt-Signal ausgewertet 
                                // und der Verstärker nur über die Software stummgeschaltet. Die direkte Stummschaltung
                                // des Verstärkers über die Kopfhörerbuchse ist nicht mehr aktiv.
                                // (über Jumper kann die Originalfunktion wieder aktiviert werden)
  // #define JackdetektAiO        // Nur aktivieren wenn Hardwareänderung für Jackdetekt auf der AiO Platine durchgeführt wurde.
 #endif                         // Ohne HW-Änderung in Kommentar setzen !!!

// __________________________________________________________________________________________________________________

// ******************** Auswahl der Optionen und Zusatzfunktionen ***************************************************

// uncomment or comment the " #define .... "  to enable or disable the additional function

// --------------------- Debug Modus --- AiO und Classic ------------------------------------------------------------
//#define Konsole               // Zum Einsparen von Programmspeicher wird die vollständige Ausgabe
                              // auf den Seriellen Monitor nur bei Freigabe ausgeführt.
                              // Bei aktiver LED-Animation, wird diese deaktiviert, um den Programmspeicher
                              // für die Konsolenausgabe frei zu machen.

// -------------------- 5 Tasten Support --- AiO und Classic ----------------------------------------------------------
#define FIVEBUTTONS           // 5 Tasten support
                              // In diesem Modus kann die Batterieüberwachung im TonUINO Classic nicht verwendet werden
                              // wenn A4 von dieser verwendet wird, oder der PrüfPin muss umdeklariert werden.
                              // Wird das 12-Buttonboard aktiviert, wird der 5 Tastenmodus automatisch deaktiviert.
                              
// -------------------- Support des 12 Buttonboards mit 3 Standarttasten und 9 Zusatztasten für Shortcuts --- AiO und Classic 
//#define Buttonboard           // Unterstützung des Buttonboards mit 12 Tasten. 
  #ifdef Buttonboard          // Über das 9 Tastenfeld sind 9 weitere Shortcuts möglich.
   #ifdef FIVEBUTTONS         // Da das Buttonboard nur 3 Standarttasten unterstützt ist der 5 Tasten support nicht möglich
    #undef FIVEBUTTONS        // und wird ggf. deaktiviert.
  #endif                      // Hardwarekonfiguration auf dem Buttonboard über die DIP-Schalter beachten !
 #endif                       

// ------------------- Sprungweite für Titelsprung Vorwärts/ Rückwärts bei LongPress Vor/Zurück --- AiO und Classic -----
#define JumpLongPress         // Titelsprung bei Longpress Vorw. Rückw. Taste bei der 5 ButtonVersion
  #ifdef JumpLongPress
     #ifdef FIVEBUTTONS       // Nur im 5 Buttonmodus
  const uint8_t SetJump = 10; // Hier festlegen, um wieviele Tracks bei Longpress weiter oder zurück gesprungen wird.
     #endif                   // Empfohlen 5 bis 10 Tracks.
 #endif
 #ifndef JumpLongPress
  const uint8_t SetJump = 1;  // Wenn JumpLongPress nicht aktiviert ist, wird Sprungweite auf 1 gesetzt.
 #endif      
// -------------------- Zuletzt gespielte Karte als Shortcut speichern --- AiO und Classic -------------------------------
#define LastCard              // Die zuletzt gespielte Karte wird als Shortcut auf die Play/Pause-Taste gelegt 
                              // Shortcuts, Startsound und Weckersound werden dabei nicht berücksichtigt
                              // Die Konfiguration des Shortcuts für die Play/Pause-Taste wird im Adminmenü nicht aufgerufen.

// ---------------------- Hörbuch auf Anfang zurücksetzen --- AiO und Classic ---------------------------------------------
#define HB_Reset              // Im Abspielmodus Hörbuch wird bei laufender Wiedergabe, der Fortschritt des Hörbuches
                              // durch langen Druck der Pausetaste auf Anfang zurückgesetzt

// ---------------------- Lautstärke für das Adminmenü festlegen --- AiO und Classic --------------------------------------
#define MenueVol                // Die Menülautstärke wird auf die Startlautstärke Lautsprecher eingestellt.
const uint8_t MenueVolume = 20; // Bei Deaktivierung von MenueVol wird die Menülautstärke auf diesen Festwert eingestellt.

// ---------------------- Zählen der Ordner auf der SD-Karte --- AiO und Classic ------------------------------------------
#define CountFolders           // Die Anzahl der Ordner des Speichermediums im DfPlayer wird ermittelt
                               // und als Begrenzung bei der Ordnerauswahl im Adminmenü verwendet.
                               // Abhängig vom Chipsatz des DfPlayers ist die Funktion nicht immer verfügbar.
                               // Dann deaktivieren ! Es werden dann wieder die Funktionen ohne CountFolders verwendet.
                               // Getestet mit MH-ETLive, IL AA19 und YX5200 24SS - funktioniert.
                               // AiO Platine funktioniert auch.

// ---------------------- Windows SystemVolumeInfo ignorieren --- AiO und Classic -----------------------------------------
#ifdef CountFolders            // Der von Windows automatisch angelegte Ordner, System Volume Info -Ordner 
                               // stört die exakte Funktion von CountFolders.
 #define IgnoreWinSysInf       // Der Windows-Ordner "System Volume Information" kann auf der SD-Karte
                               // verbleiben und wird ignoriert. Dies ist bei Nutzung der Option CountFolders
                               // wichtig, um die korrekte Ordner Anzahl für die davon abhängigen Funktionen
                               // zu verwenden.
                               // Hinweis !!!!
                               // Ist CountFolders aktiviert und der Ordner Windows SystemvolumeInfo NICHT ! auf der SD-Karte
                               // vorhanden, ist beim Konfigurieren der Karten und Shortcuts der höchste belegte Ordner der 
                               // Mediadateien nicht auswählbar.
#endif
// ---------------------- Abschaltung über Hardware - Pololu-Switch,MosFet, u.s.w. -- AiO und Classic ----------------------
#define HW_PowerOff            // Abschaltung über Hardware, wie Mosfet oder Pololu-Switch
                               // Der Ausschaltimpuls wird als Mehrfachimpuls LOW - HIGH - LOW ausgegeben.
                               // Dadurch werden beide Möglichkeiten HIGH Aktiv und LOW Aktiv bedient.
                               // Hardwareerweiterung für TonUINO Classc erforderlich. Mosfet oder Pololu-Switch
                               // Auf der AiO Platine ist die erforderliche Hardware bereits vorhanden
  #ifdef HW_PowerOff           // Festlegen des Ausschalt-Signals, (HIGH oder LOW)
    #define LowActive          // LOW Pegel schaltet den TonUINO aus.
                               // Für Pololu-Swich (HIGH aktiv) #define LowActive deaktivieren.
  #endif      
// ---------------------- Abschaltung durch die Powerbank bei Unterschreiten der Mindestlast -- I < 27 mA -- nur Classic ----
#ifndef AiO                    // Nur für den TonUINO Classic
//#define LowCurrPwDown          // Die Stromaufnahme des Tonuino wird auf < 27 mA reduziert.
#endif                         // Die Abschaltung erfolgt durch die Powerbank. 
                               // Bei Unterschreitung der Mindestlast schaltet die Powerbank selbstständig automatisch aus.
                               // Die Powerbank muss das Abschalten bei Unterschreiten eines minimalen Laststromes unterstützen.
                               // Für die AiO wird LowCurrPwDown nicht benötigt.

// ---------------------- LED Animation mit NEOPixel LED Ring oder Strip --- AiO und Classic --------------------------------
 #ifndef Konsole               // Nur bei deaktivierter Konsole wird define LED_SR aktiv
  #define LED_SR               // LED Animation mit Neopixel LED-Ring oder Strip
 #endif                        // Hardwareerweiterung erforderlich: (Neopixel LED's,Strip oder Ring)

 #ifdef LED_SR                 // Bei definierter LED Animation
  const uint8_t LED_COUNT = 22 ; // Anzahl der LEDs im Ring oder Strip. Kann hier angepasst werden.
  #define LED_SR_Switch        // Möglichkeit die LED-Animation über gleichzeitigen langen Druck 
                               // der Up-Down Tasten oder über Software ein- und auszuschalten
 #endif 
// ---------------------- USB Stick als Speichermedium --- Nur TonUINO Classic ----------------------------------------------
#ifndef AiO
//#define USB-Stick             // An Stelle der SD-Karte arbeitet der DF-Player mit einem USB-Stick
                               // Hardwareerweiterung erforderlich: (USB - A Buchse am DF-Player angeschlossen)
  #endif   
// ---------------------- Lautsprecher Abschaltung über Software ---AiO auch über KH Buchse ----------------------------------
#define SpkOnOff              // Aus und Einschalten des Lautsprechers über Software 
                              // zur Unterdrückung des Einschaltgeräusches und
                              // Möglichkeit der Abschaltung beim Anschluss eines Kopfhörers (AiO über KH-Buchse )
                              // Hardwareerweiterung für TonUINO Classic erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
                              // Bei der AiO wird der Verstärker ein bzw. ausgeschaltet.

// ---------------------- Kopfhörer --- Nur TonUINO Classic --- Nutzung mit der AiO nach Hardwareänderung möglich ---
#ifndef AiO                   // Hier für TonUino Classic änderbar
   #define Jackdetekt         // Jackdetekt Classic, bei Nutzung Kopfhörer-Buchse oder Platine mit Jackdetekt.
#endif                               
#ifdef AiO                    // Abfrage für Jackdetekt der AiO. Hier nichts ändern!
  #ifdef JackdetektAiO        // Wenn für die AiO Jackdetekt aktiviert ist (Siehe oben bei Boardauswahl)
   #define Jackdetekt         // Jackdetekt aktivieren (Option hier NICHT ändern !!!)
  #endif
#endif             

#ifdef Jackdetekt             // Wenn Jackdetekt oder JackdetektAiO aktiviert sind
#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
    #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
       #ifndef SpkOnOff       // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
        #define SpkOnOff      // Hardwareerweiterung erforderlich: (TonUINO Classic, - Abschaltung des Lautsprechers über MOS-FET's)
       #endif                 // Die Startlautstärken werden getrennt für Lautsprecher und Kopfhörer über das Adminmenü voreingestellt.
    #endif                    // Die jeweils letzten Laustärken werden getrennt bis zum Abschalten temporär gespeichert.
#endif
// -------------------- Festlegen des Sensorpegels für den Kophöreranschluss --- Nur TonUINO Classic ------------------------------
#ifndef AiO                   // Nur TonUINO Classic
//#define KHSensLOW             // Der Sensorpegel für den Kopfhöreranschluss ist bei eingestecktem Kopfhörer LOW
                              // Wenn der Sensorpegel bei eingestecktem Kopfhörer HIGH ist, #define KHSensLOW deaktivieren
#endif
// ------------------- Weckerfunktion mit Weckermodul --- AiO und Classic ---------------------------------------------------------
//#define Wecker              // Über ein externes Weckeruhrwerk wird eine Weckfunktion aktiviert
                            // TonUINO wird eingeschaltet und ein vordefinierter Shortcut als Wecker abgespielt
                            // Bei gestecktem Kopfhörer wird der Weckersound trotzdem über Lautsprecher abgespielt.
                            // Bei der AiO setzt das die Hardwareänderung Kopfhörer voraus.
#ifdef Wecker               // Der Dialog zum Erstellen des Weckershortcuts wird im Adminmenü aktiviert.
 #ifndef SpkOnOff           // Wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch aktiviert
   #define SpkOnOff         // Hardwareerweiterung für TonUINO Classic erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
  #endif                    // Für die AiO wird das Einschaltsignal über 10 kOhm auf PBN gelegt.(LOW-aktiv)
#endif
// ------------------- Lese-Empfindlichkeit des RFID-Lesers --- AiO und Classic ----------------------------------------------------
// Bei Leseproblemen des RFID Lesers kann die Leseempfindlichkeit verändert werden.
#define NFCgain_avg         // Mittlere Empfindlichkeit RFID Leser - Default wert
//#define NFCgain_max       // Maximale Empfindlichkeit RFID Leser
//#define NFCgain_min       // Minimale Empfindlichkeit RFID Leser

// ------------------- Überwachung der Batteriespannung --- TonUINO Classic und AiO ------------------------------------------------
//#define BatteryCheck        // Bei AiO muss die Lötbrücke SJ1 geschlossen werden und das modifizierte BSP LGT8FX
                            // mit Unterstützung des AnalogPin A10 installiert werden.(siehe obiger Link)
                            // AiO,- auf R17 einen 220 kOhm smd Widerstand huckepack auflöten, oder R17 durch einen 65 kOhm
                            // smd Widerstand ersetzen.(Erweiterter Spannungsmessbereich bis 5 V)
                            // Kann beim Classic nur im 3 Tasten-Modus verwendet werden, da AnalogPin A4 im 5 Tastenmodus belegt ist.
                            // Wenn ein anderer Analogpin frei zur Nutzung ist, kann dieser für BatteryCheck verwendet werden.
                            // Vor den BatteryCheckPin einen 100kOhm Widerstand in Reihe schalten (Classic).
// Wichtiger Hinweis !!!!!     Bei Anschluss der AiO über die USB-Buchse wird in der Konsole nicht die richtige Akkuspannung angezeigt.
                            // Wenn diese über die Konsole korrekt angezeigt werden soll, (nicht im Ladebetrieb)
                            // muss der PC über einen FTDI-Adapter (Jumper auf 3,3V) an rx/tx am Erweiterungsport der AiO Platine angeschlossen werden.
//                           ___________________________________________________________________________________
  // Festlegung der Spannungswerte für die Batterieüberwachung. Kann hier angepasst werden.

 #ifdef BatteryCheck           // Die Akkuspannung wird überwacht
                               // Hardwareerweiterung erforderlich (Batteriespannung muss bei ausgeschaltetem Tonuino
                               // vom Eingang des Arduino getrennt sein. (Nur TonUINO Classic,MosFet oder Relais)
                               // bei Unterschreiten des BatLow - Wertes wird eine Warnung ausgegeben
                               // bei Erreichen des BatEmpty - Wertes wird der Tonuino ausgeschaltet.
                               // Vor Abschalten erfolgt ein Ausfaden der Lautstärke über 20 Sekunden.
                               // Davon unabhängig schaltet die AiO bei Unterschreiten von 2,8 V über Hardware aus.
                              
  #ifndef AiO                      // TonUINO Classic , Werte gelten für Betrieb mit LiPo und LiIon Akku
  const float BatLow = 3.2 ;       // Spannungswert für Warnung "Batterie schwach"
  const float BatEmpty = 3.0 ;     // Spannungswert für automatische Abschaltung über Software ShutDown.
   #define Bandgap 1104000L   
  #endif                      

  #ifdef AiO                       // AiO, Werte gelten für Betrieb mit LiFePO4 Akku.
  const float BatLow = 2.95 ;      // Spannungswert für Warnung
  const float BatEmpty = 2.90 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
  const float correction = 2.495 ; // Korrekturwert für Spannungsteiler (Anpassung der Anzeige an die tatsächliche Batteriespannung)
  #endif                      
 #endif
// ------------------------------------------------------------------------------------------------------------------------------------
#ifdef Buttonboard                 // Vorgabe der Geschwindigkeit der Volume Änderung bei Lautstärkeeinstellung
const uint8_t setVolChSp = 2 ;     // über longPress der Lautstärketasten. Wert zwischen 1 und 20. 
#endif                             // Je größer der Wert um so langsamer die Lautstärkeänderung
#ifndef Buttonboard                // Empfohlener Wert zwischen 5 und 10.
const uint8_t setVolChSp = 5 ;
#endif
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

// ============================== Definitionen =============================================
#ifndef AiO                       // für TonUINO Classic

//******************* Definitionen der Pins für TonUINO Classic ****************************

// ------------------ Analog-Pins -------------------------------
// --------------- 3 und 5 Button-Version -----------------------
#ifndef Buttonboard                // 3 Tasten-Version
 #define ButtonPause A0            // Taste 1 - Play / Pause
 #define ButtonUp A1               // Taste 2 - Vor / Lauter
 #define ButtonDown A2             // Taste 3 - Zurück / Leiser

 #ifdef FIVEBUTTONS                // 5 Tasten-Version
 #define ButtonFourPin A3          // Taste 4 - Lauter / Vor
 #define ButtonFivePin A4          // Taste 5 - Leiser / Zurück
 #endif
 #ifndef FIVEBUTTONS
 #ifdef BatteryCheck               // Batterieüberwachung
 #define BatteryCheckPin A4        // Kontrollpin für Batterieüberwachung (Umdeklarierbar, wenn ein anderer Analogpin bei Nichtnutzung frei wird.)
 #endif
 #endif                            
#endif

// --------------- Mit 12-Buttonboard -----------------------------
#ifdef Buttonboard                 // 12 Tasten-Version mit Buttonboard
 #define Buttonmatrix A2           // Tastenmatrix 9 Tasten
 #define ButtonPause A0            // Taste 1 - Play / Pause
 #define ButtonUp A3               // Taste 2 - Vor / Lauter
 #define ButtonDown A4             // Taste 3 - Zurück / Leiser
 
 #ifdef BatteryCheck               // Batterieüberwachung
 #define BatteryCheckPin A1        // Kontrollpin für Batterieüberwachung 
 #endif                            
#endif
// --------------------------------------------------------------
#ifdef EarPhone
#define EarPhonePin A5            // Kontrollpin Kopfhörer angeschlossen
#endif

#ifdef Wecker
#define WeckerPin A6              // Eingangspin zum Abspielen Wecker-shortcut
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl

// ----------------- Digital-Pins ---------------------------------

#define BusyPin 4                 // Auswertung des Busy Signals vom DF-Player
#define LedPin 5                  // Daten für Neopixel-LED-Ring

#ifdef SpkOnOff
#define SpkOnPin 6                // Schaltsignal Lautsprecher Ein/Aus
#endif

#ifdef HW_PowerOff
#define ShutDownPin 7             // Abschaltsignal für MosFet oder Polulo-Switch
#endif

#ifdef USB-Stick
#define UsbPowerPin 8             // Schaltsignal für Power USB-Stick
#endif

#define RstPin 9                  // MFRC 522 -RST
#define SdaPin 10                 // MFRC 522 -SDA

#endif                            // Ende Pin-Definitionen TonUINO Classic

//******************* Definitionen der Pins für AiO ********************************
#ifdef AiO
//  Boardbeschreibung des AiO Boards Pin-Belegung und Zuordnung

//  D5, A6 und A7 sind auf den extension port geschaltet.
//  D6 ist zum button breakout board geschaltet (beschriftet mit WS(D6)).
//  D9 (RST), D10 (SDA), D11 (MOSI), D12 (MISO) und D13 (SCK) sind zum nfc breakout board geschaltet.
//  Die anderen Pins sind fest verdrahtet, siehe folgend: Die Funktion ergibt sich aus dem Status der Inversion für die Tasten
//   button0Pin = A0;                      // play/pause/power on
//   button1Pin = A1;                      // prev (Zurück) oder vol- (Leiser)
//   button2Pin = A2;                      // next (Vor) oder vol+ (Lauter)
//   button3Pin = A3;                      // vol- (Leiser) oder prev (Zurück)
//   button4Pin = A4;                      // vol+ (Lauter) oder next (Vor)
//   onboardSdAccessControlPin = A5;       // Steuerpin für externen SD-Karten Zugriff (HIGH = enabled, LOW = disabled)
//   BatteryCheckPin = A10;                // Vorbereitet für Batteriespannungsüberwachung, Verbunden mit Lötbrücke SJ-1 und Spannungsteiler R15/R17 
//   mp3SerialRxPin = 2;                   // mp3 serial rx, kommt vom tx pin des mp3 chip
//   mp3SerialTxPin = 3;                   // mp3 serial tx, geht zum rx pin des mp3 chip
//   busyPin = 4;                          // checkt den Wiedergabestatus des mp3 chips (HIGH = not playing, LOW = playing)
//   powerControlPin = 7;                  // Steuerpin zur Ein und Ausschaltung des Systems (HIGH = power on, LOW = power off)
//   onboardAmpControlPin = 8;             // Steuerpin zum Ein und Ausschalten des onboard NF-Verstärkers (HIGH = Verstärker AUS, LOW = Verstärker EIN)


//---------------- Analog-Pins -------------------------------------
//--------------  3 und 5 Tastenmodus ------------------------------
#ifndef Buttonboard               // 3 Tastenkonfiguration
 #define ButtonPause A0           // Taste 1 - Play / Pause
 #define ButtonDown A1            // Taste 2 - Zurück / Leiser
 #define ButtonUp A2              // Taste 3 - Vor / Lauter

 #ifdef FIVEBUTTONS               // 5 Tastenkonfiguration
 #define ButtonFivePin A3         // Taste 5 - Lauter / Taste Vor 5 Tastenmodus
 #define ButtonFourPin A4         // Taste 4 - Leiser / Taste Zurück 5 Tastenmodus
 #endif
#endif
//-------------- Mit 12-Buttonboard --- 3 + 9 Tasten ----------------
#ifdef Buttonboard                // Buttonboard Konfiguration
 #define Buttonmatrix A2          // Tastenmatrix 9 Tasten
 #define ButtonPause A0           // Taste 1 - Play / Pause
 #define ButtonDown A3            // Taste 2 - Zurück / Leiser
 #define ButtonUp A4              // Taste 3 - Vor / Lauter
#endif

// -----------------------------------------------------------------
#define Access_SD_Pin A5          // Pin zur Freigabe des SD-Kartenzugriffs über USB
                                  // control pin of the external sd card access (HIGH = enabled, LOW = disabled)
#ifdef Wecker
 #define WeckerPin A6             // Eingangspin zum Abspielen Wecker-shortcut (Extension Board)
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl (Extension Board)

#ifdef BatteryCheck               // Batterieüberwachung
 #define BatteryCheckPin A10      // Kontrollpin für Batterieüberwachung (über Lötbrücke SJ-1 auf AiO Platine verbinden)
#endif


//---------------- Digital-Pins -------------------------------------
#define BusyPin 4                 // Busy Signal vom DF-Player

#ifdef EarPhone
 #define EarPhonePin 5            // Sensorpin, ob Kopfhörer angeschlossen (Extension Board) 
#endif                            // Auswertung nur möglich wenn die fest verdrahtete Abschaltleitung der KH-Buchse
                                  // aufgetrennt wird und das Signal für den Sensorpin genutzt wird.
#ifdef LED_SR
 #define LedPin 6                 // Daten für Neopixel-LED-Ring (ButtonBreakout Board "WS" )
#endif

#define ShutDownPin 7             // Ein/Ausschaltsignal
                                  // control pin used to power the system (HIGH = power on, LOW = power off)
#ifdef SpkOnOff
 #define SpkOnPin 8               // Verstärker Ein/Ausschalten
#endif                            // control pin to enable/disable the onboard amp (HIGH = amp off, LOW = amp on)

#define RstPin 9                  // MFRC 522 -RST
#define SdaPin 10                 // MFRC 522 -SDA

#endif

//****************** Definitionen für letzte gespielte Karte als Shortcut auf Playtaste legen ************************
#ifdef LastCard
 #define folderReg 201            // Ordner
 #define modeReg 202              // Abspielmodus
 #define specialReg 203           // Starttrack Spezial von-bis
 #define specialReg2 204          // Endtrack Spezial von-bis
#endif

//******************** Deklaration der Variablen **********************************************************************
// ------------------ Lautstärkemanagement -----------------------
uint8_t SpkVol;                                 // Lautstärke für den Lautsprecher
uint8_t EarVol;                                 // Lautstärke für den Kopfhörer
uint8_t MenuVol = MenueVolume;                  // Lautstärke für das Adminmenü auf Festwert
bool longPressVol = false;                      // VolÄnderung durch longPress
uint8_t countVolCh = 0 ;                        // Zählvariable speed VolÄnderung
bool msgMin = true ;                            // Message "minimale Lautstärke erreicht"
bool msgMax = true ;                            // Message "maximale Lautstärke erreicht"

// ------------------ Shortcuts,  Kopfhörer, Lautsprecher, Wecker ----------------------------
#ifndef Buttonboard
 #ifndef FIVEBUTTONS                            // 3 Tastenversion
 uint8_t NextLauterButton = 1;                  // Shortcut der Vor/Lautertaste
 uint8_t PrevLeiserButton = 2;                  // Shortcut der Zurück/Leisertaste
 uint8_t Welcome = 3;                           // Shortcut des Welcomesounds 
 uint8_t ShcWecker = 4;                         // Shortcut des Weckersounds
 #endif

 #ifdef FIVEBUTTONS                             // 5 Tastenversion
 uint8_t NextButton = 1;                        // Shortcut der Weitertaste
 uint8_t PrevButton = 2;                        // Shortcut der Zurücktaste
 uint8_t LauterButton = 3;                      // Shortcut der Lautertaste
 uint8_t LeiserButton = 4;                      // Shortcut der /Leisertaste
 uint8_t Welcome = 5;                           // Shortcut des Welcomesounds 
 uint8_t ShcWecker = 6;                         // Shortcut des Weckersounds
 #endif
#endif
#ifdef Buttonboard                              // 9 Tasten Matrixversion
 uint8_t NextLauterButton = 1;                  // Shortcut der Vor/Lautertaste
 uint8_t PrevLeiserButton = 2;                  // Shortcut der Zurück/Leisertaste
 uint8_t Welcome = 12;                          // Shortcut des Welcomesounds 
 uint8_t ShcWecker = 13;                        // Shortcut des Weckersounds
 bool TaGedr = false ;                          // eine Taste der Matrix gedrückt Voreinstellung Nein
 uint8_t Matrix;                                // Taste die gedrückt wurde
 uint16_t Wert;                                 // Auslesewert des Matrixpins
#endif
uint8_t Steps = 1;                              // Sprungweite der vor/zurücktasten, Voreinstellung 1
#ifdef EarPhone
 int Ear;                                       // Abfrageergebnis Pinabfrage EarPhonePin
#endif
#ifdef SpkOnOff
 bool SpkisOn = false;                          // Marker Lautsprecher Ein/Aus, Voreinstellung Aus
 bool EarFirstTime = true;                      // Marker, ob Kopfhörer das erste mal eingesteckt wird, Voreinstellung JA
#endif
#ifdef Wecker
 uint16_t ReadWecker = 0;                       // Variable für den ausgelesenen Wert des WeckerPin
 bool WeckerStart = false;                      // Startimpuls für den Wecker wurde gegeben, Voreinstellung NEIN
 bool ActWecker = false;                        // Wecker ist aktiviert worden, Voreinstellung NEIN
#endif
bool WeckerPlay = false;                        // Weckershortcut wird gespielt, Voreinstellung NEIN
bool ShortCutIsPlaying = false ;                // Shortcut wird gespielt, Voreinstellung NEIN
bool SETUP = true;                              // ist true solange setup() durchlaufen wird
bool StdBy = false;                             // StanbyTimer aktiviert, Voreinstellung NEIN
bool mp3error = false;                          // Error vom mp3 Player oder Bibliothek

// ---------------------- Adminmenü ----------------------------------------------------------------------
uint8_t progmode = 0;                           // Modus für die Programmierung der Karten und shortcuts
uint8_t Minuten = 2;                            // AdmTimeOut Vorgabe, Zeit in Minuten
unsigned long AdmTimeOut = 0;                   // Abgelaufene TimeOutzeit
unsigned long SollAdmTimeOut = 120000;          // AdmTimeOut Vorgabe Zeit ,2 Minuten in Millisekunden
bool AbbrActive = false;                        // Adminmenü abgebrochen, Voreinstellung Nein
bool AdjVol = false;                            // Adminmenü in Vol-Einstellungen, Voreinstellung Aus
bool rolling = true;                            // Adminmenü, Durchschalten der Optionen umlaufend, Voreinstelung JA
uint8_t StartTrack;                             // letzter Rückgabewert für StartTrack Voicemenü
// ---------------------- Batterieüberwachung -----------------------------------------------------------
#ifdef AiO
const float reference = 2.048;                  // Referenzspannung AiO
const float steps = 4064;                       // Auflösung ADU
#endif
#ifdef BatteryCheck
#ifndef AiO
float u_reference = 0.00 ;                      // Referenzspannung TonUINO Classic wird durch interne Messung ermittelt
#endif
float Vbatt = 3.40;                             // Batteriespannung (Wird bei der Messung auf aktuellen Wert gesetzt)
float VbattGl = 3.20;                           // Geglättete Batteriespannung aus 60 Einzelmessungen,Voreinstellung 3,2V AiO
                                                // Geglättete Batteriespannung aus 10 Einzelmessungen , Classic
const float Vwarning = BatLow;                  // Voltzahl für Warnung Batteriespannung, bei den #defines festgelegt
const float Vshutdown = BatEmpty;               // Voltzahl für Shutdown, Batterie leer, bei den #defines festgelegt

#ifndef AiO
unsigned long TestIntervall = 6000;             // Testintervall Batterie ,Classic: 6 Sekunden
#endif
#ifdef AiO
unsigned long TestIntervall = 1000;             // Testintervall Batterie  ,   AiO: 1 Sekunde
#endif

uint8_t countTi = 0;                            // Anzahl der durchlaufenen Testintervalle
uint32_t SumValue = 0;                          // Summe der Sensorwerte aller  Testintervalle 

unsigned long Now = 0;                          // millis() im Moment des Auslesens der Batteriespannung
unsigned long lastTest = 0;                     // Zeitpunkt letzte Prüfung der Batteriespannung

bool BattLeer = false;                          // Marker, leere Batterie erkannt, Voreinstellung Nein

#endif  //BatteryCheck

// ******************** Definitionen für LED Animation *** by t@on **  modifyed by @atomphil  *******************
#ifdef LED_SR
 
// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LedPin, NEO_GRB + NEO_KHZ800);

// Zählvarbiablen
uint16_t loopCount;                             // Runterzählen der Loops
uint16_t loopCountWait;                         // Definierte Anzahl wieviele Loops runtergezählt werden sollen, also wie lange gewartet wird
uint8_t animCount;                              // Wie oft die einmalige Animation ausgeführt wird bevor es zurück in die Hauptschleife (Animationsmodus 0) geht
uint8_t i;
uint8_t y;
uint8_t Zhl = 5;                                // Zählvariable LED Animation für error Mp3 Player

// Datenvariablen
uint8_t currentDetectedTrack;                   // Speichern des aktuellen Tracks für späteren Vergleich
uint8_t lastDetectedTrack;                      // Speichern des Tracks um die Animation nur ein mal zu triggern
uint8_t currentDetectedVolume;                  // Speichern der aktuellen Lautstärke für späteren Vergleich
uint8_t lastDetectedVolume;                     // Speichern der Lautstärke um die Animation nur ein mal zu triggern
uint8_t volumeScope;                            // Differenz der von euch eingestellten minimalen und maximalen Lautstärke
uint8_t volumeScopeAmount;                      // Lautstärkenwert in deinem Scope
uint8_t volumeScopeAmountMod;                   // Lautstärkewert in %
 
uint32_t  firstPixelHue = 0;
uint32_t  pixelHue;
 
uint32_t  TrckChgColor_FFW = 21845L;            // Farbe wird bei Animation nächstes Lied verwendet
uint32_t  TrckChgColor_REW = 43690L;            // Farbe wird bei Animation Lied zurück verwendet
uint8_t   TrckChgSpeed = 64;                    // Geschwindigkeit Animation Lied vor/zurück (1 bis 255)
uint8_t   TrckChgMaxBrightness = 255;           // Helligkeit Animation Lied vor/zurück (1 bis 255)
uint32_t  TrckChgProgress = 0;
 
uint8_t lsrAnimationMode;                       // Animationsmodus - 0: Daueranimation, 1-2 einmalige Animation (als Unterbrechung zu 0)
uint8_t lsrAnimationTrackMode;                  // Bei Animationsmodus Liedwechsel bestimmung der Farbe und Richtung

//----------- Vordefinierte Farben ------------------------------
uint32_t magenta = strip.Color(255, 0, 255, 64);
uint32_t lightblue = strip.Color(32, 64, 128, 64);
uint32_t red = strip.Color(255, 0, 0, 64);
uint32_t greeen = strip.Color(0, 255, 0, 64);
uint32_t blue = strip.Color(0, 0, 255, 64);
uint32_t gold = strip.Color(255,193,37, 64);

#ifdef LED_SR_Switch
bool lsrSwitch = false;                         // Ein-Ausschalten aktiviert, true wenn up und down Button long press
bool lsrEnable = true;                          // LED-Animation-Freigabe
bool lsrAudioBreak = false;                     // Wiedergabe gestoppt während Ein-Ausschalten LED-Animation .
bool lsrOffByStdby = false;                     // Ausschaltsignal LED-Animation durch Standbytimer Software only
#endif
#endif
 
// ********************** Cookies ************************************************
                                               
// Abhängig von der Hardwarekonfiguration wird die Struktur von mySettings verändert.
// Zur Anpassung der Settings an die geänderte Hardware muss der EEPROM rückgesetzt werden. 
// Durch eine von den #defines abhängige Änderung von myCookie erfolgt das automatisch.

uint32_t myCookie = 130219560;                  // Grundwert myCookie zum Erkennen einer Softwareversion mit geänderter mySettings Struktur
                                                // Eine Änderung von myCookie sorgt für einen automatischen Reset der mySettings
                                                // Änderungen der #defines, die eine Strukturänderung bewirken, verändern myCookie
                                                // durch Addition bei Hinzufügen einer neuen Funktion bzw durch Subtraktion bei Entfernen einer Funktion.
                                                // Dadurch ist garantiert, das jede mySettings ändernde Konfiguration ein anderes myCookie erzeugt.
                                                
static const uint32_t cardCookie = 322417479;   // Cookie zum Erkennen der TonUINO-RFID Karten
                                                // sorgt für das automatische Starten der Kartenkonfiguration bei neuen Karten

//*********************** Buttons *************************************************
//LONG_PRESS 1000                               // langer Druck >= 1 sekunde
static const uint16_t LONG_PRESS = 1000;
Button ButtonOne(ButtonPause);                  // Taste 1
Button ButtonTwo(ButtonUp);                     // Taste 2
Button ButtonThree(ButtonDown);                 // Taste 3
#ifdef FIVEBUTTONS
Button ButtonFour(ButtonFourPin);               // Taste 4
Button ButtonFive(ButtonFivePin);               // Taste 5
#endif
bool ignoreButtonOne = false;                   // Taste 1 übergehen, Voreinstellung Nein
bool ignoreButtonTwo = false;                   // Taste 2 übergehen, Voreinstellung Nein
bool ignoreButtonThree = false;                 // Taste 3 übergehen, Voreinstellung Nein
#ifdef FIVEBUTTONS
bool ignoreButtonFour = false;                  // Taste 4 übergehen, Voreinstellung Nein
bool ignoreButtonFive = false;                  // Taste 5 übergehen, Voreinstellung Nein
#endif

//********************* RFID Reader ************************************************
// MFRC522
MFRC522 mfrc522(SdaPin, RstPin);                // Create MFRC522
MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
MFRC522::StatusCode status;

// ******************** DF-Player **************************************************
// DFPlayer Mini
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX   // Digitalpins zur Steuerung des DF-Players
uint8_t numFolders;                                // Anzahl der Ordner im Speichermedium
uint8_t numTracksInFolder;                         // Anzahl der Tracks im Ordner
uint8_t firstTrack;                                // erster Track
uint8_t currentQueueIndex;                         // index in queue[] aktuelle Tracknr in der queue
uint8_t queueSize;                                 // Länge der queue
uint8_t queue[255];                                // max 255 tracks/folder. entries 0..254 and values 1..255 are used.
uint8_t volume;                                    // Lautstärke
// --------------------------------------------------------
struct folderSettings {                            // Struktur der Foldersettings
  uint8_t folder;                                  // Ordnernummer
  uint8_t mode;                                    // Abspielmodus
  uint8_t special;                                 // Spezialmodus Start-track
  uint8_t special2;                                // Spezialmodus End-track
};
// ---------------------------------------------------------
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
// ----------------------------------------------------------
struct adminSettings                               // admin settings stored in eeprom
{
  uint32_t cookie;                                 // gespeichertes mycookie
  byte version;                                    // Version der settings
  uint8_t maxVolume;                               // max Lautstärke Lautsprecher
  uint8_t minVolume;                               // min Lautstärke Lautsprecher
  uint8_t initVolume;                              // start Lautstärke Lautsprecher
#ifdef EarPhone  
  uint8_t maxEarVol;                               // max Lautstärke Kopfhörer
  uint8_t minEarVol;                               // min Lautstärke Kopfhörer
  uint8_t initEarVol;                              // start Lautstärke Kopfhörer
#endif  
  uint8_t eq;                                      // Equalizer Einstellung
  long standbyTimer;                               // standbytimer time
  bool invertVolumeButtons;                        // Funktion LS Tasten und Vor/Zurücktasten tauschen
#ifndef Buttonboard 
 #ifndef FIVEBUTTONS                               // - Drei-Tasten-Modus
  folderSettings shortCuts[5];                     // 5 shortcuts, (3 Tasten, Welcomesound + Wecker)
 #endif
 #ifdef FIVEBUTTONS                                // - Fünf-Tasten-Modus
  folderSettings shortCuts[7];                     // 7 shortcuts, (5 Tasten, Welcomesound + Wecker)
 #endif
#endif
#ifdef Buttonboard                                 // - Buttonboard 12 Tasten
  folderSettings shortCuts[14];                    // 14 shortcuts, (3 StandartTasten,9-TastenMatrix, Welcomesound + Wecker)
#endif  
  uint8_t adminMenuLocked;                         // Schutz des Adminmenüs
};
//-----------------------------------------------
adminSettings mySettings;                          // Hardwareconfigurationen in EEPROM
nfcTagObject myCard;                               // settings für Kartenprogrammierung
folderSettings *myFolder;
unsigned long sleepAtMillis = 0;                   // Variable für den Standbytimer
static uint16_t _lastTrackFinished;                // Zuletzt gespielter Track

static void nextTrack(uint16_t track);             // Nächster Track
//------------------------------------------------
uint8_t voiceMenu(                                 // Rückgabewert voiceMenu
  int numberOfOptions,                             // Anzahl der Optionen
  int startMessage,                                // Tracknr der StartAnsage
  int messageOffset,                               // Tracknummer ab der die Ansagen der Optionen gespielt werden
  bool preview = false,                            // Vorschau, Voreinstellung NEIN
  int previewFromFolder = 0,                       // Vorschau Ordner
  int defaultValue = 0,                            // Standart Rückgabewert
  bool exitWithLongPress = false);                 // Abbruch durch longPress, Voreinstellung NEIN
//-----------------------------------------------

void writeCard(nfcTagObject nfcTag);               // RFID Karte schreiben
void dump_byte_array(byte * buffer, byte bufferSize);  // Auslesen HEX-Daten
void adminMenu(bool fromCard = false);             // Adminmenü von Karte starten, Voreinstellung NEIN
//void playShortCut(uint8_t shortCut);               // Shortcut abspielen
bool knownCard = false;                            // Karte bekannt, Voreinstellung NEIN
bool isPlaying();                                  // Marker, Wiedergabe läuft

// implement a notification class,
// its member methods will get called
// ***************************************************************************
// used by DFPlayer Mini library during callbacks
class Mp3Notify {
  public:

// ***************** Error-meldungen des df-players **************************

    static void OnError(uint16_t returnValue)
    {
      switch (returnValue)
      {
        case DfMp3_Error_Busy: {
            Serial.print(F("1- busy"));              // Es läuft eine Wiedergabe
            break;
          }
        case DfMp3_Error_Sleeping: {
            Serial.print(F("2- sleep"));             // Df Player im Sleepmodus
            break;
          }
        case DfMp3_Error_SerialWrongStack: {
            Serial.print(F("3- mem"));               // Fehler interer Speicher
            break;
          }
        case DfMp3_Error_CheckSumNotMatch: {
            Serial.print(F("4-Hw-com"));             // Hardware Kommunikationsfehler
            break;
          }
        case DfMp3_Error_FileIndexOut: {
            Serial.print(F("5- file index Out "));   // Dateinummer außerhalb des Bereiches
            break;
          }
        case DfMp3_Error_FileMismatch: {
            Serial.print(F("6- file not found"));    // Datei nicht gefunden
            break;
          }
        case DfMp3_Error_Advertise: {
            Serial.print(F("7- advert"));            // Fehler beim Abspielen Advert
            break;
          }
        case DfMp3_Error_RxTimeout: {
            Serial.print(F("rx timeout"));           // Zeitüberschreitung RX-Signal
            break;
          }
        case DfMp3_Error_PacketSize: {
            Serial.print(F("p-size"));               // Fehler Sektorgröße
            break;
          }
        case DfMp3_Error_PacketHeader: {
            Serial.print(F("p-header"));             // Fehler Header
            break;
          }
        case DfMp3_Error_PacketChecksum: {
            Serial.print(F("p-checksum"));           // Prüfsummenfehler
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
      
    mp3error = true;
    }

    // Speichermedium der Sounddateien
    static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
    {
      if (source & DfMp3_PlaySources_Sd) Serial.print("SD Karte ");
#ifdef USB-Stick
      if (source & DfMp3_PlaySources_Usb) Serial.print("USB ");
#endif
      //if (source & DfMp3_PlaySources_Flash) Serial.print("Flash ");
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

// ************** Zufallsliste erstellen ***********************
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

// ************** Track Index **********************************
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
void Serial_println_F(const PROGMEM char* str) 
{
  Serial.println((const __FlashStringHelper*)str);
}
void Serial_print_F  (const PROGMEM char* str) 
{
  Serial.print  ((const __FlashStringHelper*)str);
}
#endif

// ********************* my Settings speichern ********************
void writeSettingsToFlash() {               // my Settings im EEPROM speichern
#ifdef Konsole
  Serial.println(F("Sp.Settings"));
#endif
  int address = sizeof(myFolder->folder) * 100;
#ifndef AiO
  EEPROM.put(address, mySettings);
#endif
#ifdef AiO
  EEPROM_put(address, mySettings);
#endif
}

// ********************** my Settings zurücksetzen ****************
void resetSettings() {                     // my Settings auf defaultwerte zurücksetzen
#ifdef Konsole
  Serial.println(F("Reset Settings"));
#endif
  mySettings.cookie = myCookie;            // aktuellen myCookie zuweisen
  mySettings.version = 2;
  mySettings.maxVolume = 25;               // max.Lautstärke Lautsprecher
  mySettings.minVolume = 2;                // min.Lautstärke Lautsprecher
  mySettings.initVolume = 15;              // Start-Lautstärke Lautsprecher
#ifdef EarPhone  
  mySettings.maxEarVol = 20;               // max.Lautstärke Kopfhörer
  mySettings.minEarVol = 2;                // min.Lautstärke Kopfhörer
  mySettings.initEarVol = 15;              // Start-Lautstärke Kopfhörer
#endif 
  mySettings.eq = 1;                       // Equalizer Normal
  mySettings.standbyTimer = 5;             // Standbytimer auf 5 min
#ifndef FIVEBUTTONS                        // 3-Tastenversion
  mySettings.invertVolumeButtons = false;  // Funktion Shortpress und Longpress der Vol- Vor/Zur-Tasten umkehren, AUS
#endif
#ifdef FIVEBUTTONS                         // 5-Tastenversion
  mySettings.invertVolumeButtons = true;   // Funktion der Vol-und Vor/Zur-Tasten tauschen, EIN
#endif
#ifndef FIVEBUTTONS                        // Shortcuts 3 Tasten-Version
  #ifndef Buttonboard
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Play-Pausetaste  (Taste 1)
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-Lautertaste  (Taste 2)
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-Leisertaste (Taste 3)
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Welcomesound
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Weckersound
  #endif
#endif
#ifdef FIVEBUTTONS                         // Shortcuts 5 Tasten-Version 
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Pausetaste (Taste 1)
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-taste  (Taste 2)
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-taste (Taste 3) 
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Vol+ taste (Taste 4)
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Vol- taste (Taste 5)
  mySettings.shortCuts[5].folder = 0;      // kein Shortcut Welcomesound
  mySettings.shortCuts[6].folder = 0;      // kein Shortcut Weckersound
#endif
#ifdef Buttonboard                         // Shortcuts Buttonboard-Version
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Play-Pausetaste  (Taste 1)
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-Lautertaste  (Taste 2)
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-Leisertaste (Taste 3)
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Taste A
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Taste B
  mySettings.shortCuts[5].folder = 0;      // kein Shortcut Taste C
  mySettings.shortCuts[6].folder = 0;      // kein Shortcut Taste D
  mySettings.shortCuts[7].folder = 0;      // kein Shortcut Taste E
  mySettings.shortCuts[8].folder = 0;      // kein Shortcut Taste F
  mySettings.shortCuts[9].folder = 0;      // kein Shortcut Taste G
  mySettings.shortCuts[10].folder = 0;     // kein Shortcut Taste H
  mySettings.shortCuts[11].folder = 0;     // kein Shortcut Taste I
  mySettings.shortCuts[12].folder = 0;     // kein Shortcut Welcomesound
  mySettings.shortCuts[13].folder = 0;     // kein Shortcut Weckersound  
#endif
  mySettings.adminMenuLocked = 0;          // 0 = Adminmenü nicht geschützt,
                                           // 1 = Schutz durch Adminkarte,

  writeSettingsToFlash();                  // Settings im EEPROM speichern

  #ifdef LED_SR                            // LED-Animation RESET

   for(int i=0; i<5; i++)                  // Bei Reset 5x Rot blinken
    {
    strip.fill(red);
    strip.show();
    delay(200);
    strip.clear();
    strip.show();
    delay(100); 
    }
  #endif
}

// ****************************************************************************
void migrateSettings(int oldVersion) 
{
  if (oldVersion == 1) 
  {
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
  Serial.println(F("load mySettings"));
#endif
  int address = sizeof(myFolder->folder) * 100;
#ifndef AiO
  EEPROM.get(address, mySettings);
#endif
#ifdef AiO
  EEPROM_get(address, mySettings);
#endif
  if (mySettings.cookie != myCookie)      // wenn durch Änderungen bei den #defines myCookie verändert wurde -> Reset der mySettings
    resetSettings();
    migrateSettings(mySettings.version);

  // ****************** mySettings im Ser Monitor anzeigen *********************

  Serial.print(F("Vers.: "));
  Serial.println(mySettings.version);
#ifndef EarPhone  
  Serial.print(F("Max Vol. : "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Min Vol. : "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Init Vol. : "));
  Serial.println(mySettings.initVolume);
#endif
#ifdef EarPhone
  Serial.print(F("Max Vol.Lsp : "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Min Vol.Lsp : "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Init Vol.Lsp: "));
  Serial.println(mySettings.initVolume);

  Serial.print(F("Max Vol.Ear : "));
  Serial.println(mySettings.maxEarVol);

  Serial.print(F("Min Vol.Ear : "));
  Serial.println(mySettings.minEarVol);

  Serial.print(F("Init Vol. Ear : "));
  Serial.println(mySettings.initEarVol);
#endif
  Serial.print(F("EQ :  "));
  Serial.println(mySettings.eq);

  Serial.print(F("StBy Timer: "));
  Serial.print(mySettings.standbyTimer);
  Serial.println(F(" min"));

  Serial.print(F("Skip Buttons: "));
  Serial.println(mySettings.invertVolumeButtons);

  Serial.print(F("Adm.Menu: "));
if(mySettings.adminMenuLocked = 0)
  Serial.println("unlocked");
else
  Serial.println("locked");
  Serial.println(" ");
  Serial.println("-- ShortCuts --");
#ifndef LastCard
  Serial.print(F("SC-0,Play-Taste:   ")); 
  Serial.println(mySettings.shortCuts[0].folder);
#endif
#ifdef LastCard
  Serial.print(F("SC-0,Letzte Karte: ")); 
  Serial.println(mySettings.shortCuts[0].folder);
#endif
#ifndef FIVEBUTTONS
  #ifndef Buttonboard
  Serial.print(F("SC-1, Weiter/Lauter-Taste: "));
  Serial.println(mySettings.shortCuts[1].folder);

  Serial.print(F("SC-2, Zurück/Leiser-Taste: "));
  Serial.println(mySettings.shortCuts[2].folder);

  Serial.print(F("SC-3, Begrüßung : "));
  Serial.println(mySettings.shortCuts[3].folder);
   #ifdef Wecker
  Serial.print(F("SC-4, Wecker :    "));
  Serial.println(mySettings.shortCuts[4].folder);
   #endif  
  #endif 
#endif
#ifdef FIVEBUTTONS
  Serial.print(F("SC-1, Weiter-Taste: "));
  Serial.println(mySettings.shortCuts[1].folder);

  Serial.print(F("SC-2, Zurück-Taste: "));
  Serial.println(mySettings.shortCuts[2].folder);

  Serial.print(F("SC-3, Lauter-Taste : "));
  Serial.println(mySettings.shortCuts[3].folder);

  Serial.print(F("SC-4, Leiser-Taste : "));
  Serial.println(mySettings.shortCuts[4].folder);

  Serial.print(F("SC-5, Begrüßung : "));
  Serial.println(mySettings.shortCuts[5].folder);
  #ifdef Wecker
  Serial.print(F("SC-6, Wecker :    "));
  Serial.println(mySettings.shortCuts[6].folder);
  #endif
#endif
#ifdef Buttonboard
  Serial.print(F("SC-3, Matr.A :  "));
  Serial.println(mySettings.shortCuts[3].folder);
  Serial.print(F("SC-4, Matr.B :  "));
  Serial.println(mySettings.shortCuts[4].folder);
  Serial.print(F("SC-5, Matr.C :  "));
  Serial.println(mySettings.shortCuts[5].folder);  
  Serial.print(F("SC-6, Matr.D :  "));
  Serial.println(mySettings.shortCuts[6].folder);
  Serial.print(F("SC-7, Matr.E :  "));
  Serial.println(mySettings.shortCuts[7].folder);
  Serial.print(F("SC-8, Matr.F :  "));
  Serial.println(mySettings.shortCuts[8].folder);
  Serial.print(F("SC-9, Matr.G :  "));
  Serial.println(mySettings.shortCuts[9].folder);
  Serial.print(F("SC-10,Matr.H :  "));
  Serial.println(mySettings.shortCuts[10].folder);
  Serial.print(F("SC-11,Matr.I :  "));
  Serial.println(mySettings.shortCuts[11].folder);
  Serial.print(F("SC-12,Begrüßung : "));
  Serial.println(mySettings.shortCuts[12].folder);
 #ifdef Wecker
  Serial.print(F("SC-13, Wecker  :  "));
  Serial.println(mySettings.shortCuts[13].folder);
 #endif
#endif
  Serial.println();

}

// **************** Tasten und RFID Sperren ********************
void LockPause()
{
#ifdef Konsole
  Serial.println(F("Pause -> LOCKED!"));   // Play/Pausetaste sperren
#endif
  return true;
}

void LockNext()
{
#ifdef Konsole
  Serial.println(F("Next -> LOCKED!"));    // Nächster Titel sperren
#endif
  return true;
}

void LockPrevious()
{
#ifdef Konsole
  Serial.println(F("Prev. -> LOCKED!"));  // Vorhergehender Titel sperren
#endif
  return true;
}

void LockVolUp()
{
#ifdef Konsole
  Serial.println(F("Vol.Up -> LOCKED!"));  // Lautertaste sperren
#endif
  return true;
}

void LockVolDown()
{
#ifdef Konsole
  Serial.println(F("Vol.Down -> LOCKED!")); // Leisertaste sperren
#endif
  return true;
}

void LockRFID()
{
#ifdef Konsole
  Serial.println(F("RFID -> LOCKED!"));     // Neue Karte abspielen sperren
#endif
  return true;
}

//********************** Modifikationskarten *****************************
//************************************************************************

class Modifier 
{
  public:
    virtual void loop() {}

    virtual bool handlePause() 
    {
      return false;
    }
    virtual bool handleNext() 
    {
      return false;
    }
    virtual bool handlePrevious() 
    {
      return false;
    }
    virtual bool handleNextButton() 
    {
      return false;
    }
    virtual bool handlePreviousButton() 
    {
      return false;
    }
    virtual bool handleVolumeUp() 
    {
      return false;
    }
    virtual bool handleVolumeDown() 
    {
      return false;
    }
    virtual bool handleRFID(nfcTagObject *newCard) 
    {
      return false;
    }
    virtual uint8_t getActive() 
    {
      return 0;
    }
    Modifier() {} 
    
};

Modifier *activeModifier = NULL;

// *** Modkarte **** Sleeptimer mit Ausfaden Lautstärke und Tastensperre ************
// Dieses Modifier wird zusätzlich genutzt beim shutdown wenn Batterie leer. Zeit 20 Sekunden.

class SleepTimer : public Modifier
{
  private:
    unsigned long sleepAtMillis = 0;
    unsigned long lastVolCheck = 0;
    uint16_t lastVolume = 0;
#ifdef LED_SR
    unsigned long Brightn = 64;                           // Startwert für Ausfaden der Helligkeit der LED-Animation
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
          Serial.print(F("Fade Vol: "));
          Serial.println(val);
#endif
#ifdef LED_SR                                             // Helligkeit der LED Animation ausfaden
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
    // Nach Auflegen der Modifikationskarte "Schlummermodus" wird bei laufender Wiedergabe
    // der Tonuino nach Ablauf der voreingestellten Zeit ausgeschaltet.
    // Vor-Zurück Tasten und neue Karte sind gesperrt.
    // Die letzten 20 Sekunden wird die Lautstärke gleichmäßig auf 0 verringert.
    // Danach schaltet der Standbytimer sofort AUS.

    SleepTimer(float minutes)                       // Variablentyp auf float geändert für Werte < 1
    {
#ifdef Konsole
      Serial.print(F("SleepTimer: "));
      Serial.print(minutes);
      Serial.println(F(" min"));
#endif
      this->sleepAtMillis = millis() + minutes * 60000;
      this->lastVolCheck = millis();
#ifdef BatteryCheck
      if (BattLeer == false)
      {
#endif
        delay(500);
        mp3.playAdvertisement(302);                 //advert-302- Schlummerfunktion aktiviert.
        delay(500);

#ifdef BatteryCheck
      }
#endif
    }

    //************ Tasten und neue Karte im Sleepmode sperren *************
    //Für Tasten die nicht gesperrt werden sollen, jeweils die 5 zugehörigen Zeilen mit // deaktivieren
    /*  // ---------------------------------------------------------------
        virtual bool handlePause()
        {
          LockPause();           // Play/Pausetaste sperren
        }
    */
    // ---------------------------------------------------------------
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
      modEnd ();                             // Deaktivieren durch erneutes Auflegen dieser
                                             // oder einer anderen Modifikationskarte
#endif
      return 1;
    }
};

//**** Modkarte ****** Stopptanz *************************************
// Nach Auflegen der Modifikationskarte "Stopptanz" wird die laufende Wiedergabe
// in unregelmäßigen Zeitabständen angehalten und nach kurzer Pause fortgesetzt.

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
          mp3.playAdvertisement(301);            //advert-301- Und Stopp!**Ticken**Nicht bewegen!**Ticken**weiter geht´s!
          delay(500);
        }
        else
        {
          if (StdBy == false)
          setstandbyTimer();
        }
        setNextStopAtMillis();                   // Zeit zum nächsten Stop setzen
      }
    }
    FreezeDance(void)
    {
#ifdef Konsole
      Serial.println(F("StopTanz "));
#endif
      if (isPlaying())                          // Bei laufender Wiedergabe
      {
        mp3.playAdvertisement(300);             //advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
      }
      else                                      // Wenn keine Wiedergabe läuft
      {
        mp3.start();                            // Wiedergabe des letzt gespielten Titels starten
        mp3.playAdvertisement(300);             // advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
      }

      setNextStopAtMillis();
    }
    uint8_t getActive()
    {
#ifdef Konsole
      modEnd ();                                // Deaktivieren durch erneutes Auflegen dieser
#endif                                          // oder einer anderen Modifikationskarte
      return 2;
    }
};

//****** Modkarte *** TonUINO Sperren *************************************
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
      LockRFID();            // Neue Karte abspielen sperren
    }
    // ---------------------------------------------------------------

    Locked(void)
    {
#ifdef Konsole
      Serial.println(F("Gesperrt!"));
#endif
      mp3.playAdvertisement(303);                     // advert-303- TonUINO ist nun gesperrt.
    }
    uint8_t getActive()
    {
#ifdef Konsole
      modEnd ();                                      // Deaktivieren durch erneutes Auflegen dieser
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
      modEnd ();                                  // Deaktivieren durch erneutes Auflegen dieser
#endif                                            // oder einer anderen Modifikationskarte
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
    /*    virtual bool handlePause()
          {
            LockPause();                            // Pausetaste gesperrt
      
          }
    */
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
      if (!isPlaying())                             // wenn laufender Track beendet
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
      mp3.playAdvertisement(305);                   // advert-305- KiTa-Modus aktiviert.
      //delay(500);

    }
    uint8_t getActive()
    {
#ifdef Konsole
      modEnd ();                                    // Deaktivieren durch erneutes Auflegen dieser
#endif                                              // oder einer anderen Modifikationskarte
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
      Serial.println(F("Next -> Track wiederholen"));
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
      Serial.println(F("Prev. -> Track wiederholen"));
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
      modEnd ();                                      // Deaktivieren durch erneutes Auflegen dieser
#endif                                                // oder einer anderen Modifikationskarte
      return 6;
    }
};
// ---------------------
void modEnd ()
{
Serial.println(F("deaktiviert"));                     // Anzeige Deaktivierung oder Wechsel der ModKarte
}                                             

// **************** aktuellen Titel spielen ********************
void playCurrentTrack()
{
//#ifdef Konsole
  Serial.print(F("Play que idx: "));
  Serial.print(currentQueueIndex);                                 // Tracknummer in der Queue
  Serial.print(F(", Track: "));
  Serial.println(queue[currentQueueIndex]);                        // Tracknummer im Ordner
//#endif
  mp3.playFolderTrack(myFolder->folder, queue[currentQueueIndex]); // Abspielen des aktuellen Titels in der Queue
}


//*********************** Track vor *** Track zurück *****************************
//********************************************************************************

// ************ Track vor (nächster Titel) *********************
static void nextTrack(uint16_t track)
{
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
  Serial.println(F(" -> nxtTrk "));
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
//#ifdef Konsole
        Serial.println(queueSize);
        Serial.print(currentQueueIndex);
        Serial.print(" --> ");
//#endif
if((currentQueueIndex + Steps) < queueSize)                 // wenn Queueindex plus Sprung unter queueSize
currentQueueIndex = (currentQueueIndex + Steps);            // Weiterspringen in der Queue
    else                                                    // wenn Queueindex plus Sprung gleich oder größer queueSize
    {
     currentQueueIndex = queueSize -1;                      // Gehe zum Ende der queue
//#ifdef Konsole
      Serial.println(currentQueueIndex);
      Serial.println(F("  Ende Queue "));   
 //#endif
    }     
     Steps = 1;                                             // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;

    case 3: //Party
    case 8: //Party-SpezialVonBis
      currentQueueIndex = currentQueueIndex + Steps;        // Weiterschalten in der Queue
      if (currentQueueIndex >= queueSize)                   // Ende der Queue erreicht oder überschritten
      {
#ifdef Konsole
        Serial.println(F("Ende Queue --> mische neu."));
#endif
        shuffleQueue();                                      // Am Ende der Queue soll neu gemischt werden
        currentQueueIndex = 0;                               // Ende der Queue -> springe zum Start
     bStop = false ;                                         // Queue wird endlos abgespielt
      }
      Steps = 1;                                             // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;

    case 5: //Hoerbuch
      if (currentQueueIndex + Steps < queueSize)              // Prüfung letzter Track in Queue?
      {
        currentQueueIndex = currentQueueIndex + Steps;
        if (currentQueueIndex + Steps >= queueSize)
        {
         currentQueueIndex = queueSize -1; 
        }
#ifndef AiO
        EEPROM.update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern
#endif
#ifdef Konsole
        Serial.println(F("Sp.-Fortschr."));
#endif
        Steps = 1;                                                  // Rücksetzen der Sprungweite auf 1 für Einzelschritt
        break;
      }
      else                                                          // Ende der Queue
      {
#ifndef AiO
        EEPROM.update(myFolder->folder, 1);                         // Fortschritt zurücksetzen (Classik)
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, 1);                         // Fortschritt zurücksetzen (AiO)
#endif
#ifdef Konsole
        Serial.println(F("Hörb->Anfang"));
#endif
        bStop = true;                                               // Stop am Ende der Queue
        Steps = 1;                                                  // Rücksetzen der Sprungweite auf 1 für Einzelschritt
        break;
      }

    default:
      return; // do nothing
  }
  // *************** queue zu Ende  ***********
  if (bStop)
  {
    if (!isPlaying())             // wenn Titel beendet ist
    {
  #ifdef Konsole
      Serial.println(F("Stop"));
  #endif
      mp3.pause();
      setstandbyTimer();
    }
  }
  else                            // wenn bStop nicht aktiv
  {
    disablestandbyTimer();
    playCurrentTrack();           // aktuellen Titel spielen
  }
  delay(500);
}

//************ Track zurück **( vorheriger Titel) ************************
static void previousTrack()
{
#ifdef Konsole
  Serial.print(F("prev.Track : "));
  Serial_println_F(getModeName(myFolder->mode));
#endif
  switch (myFolder->mode)
  {
  // ----------------------------------------------------
    /*
      case 1;
      case 6:
       Serial.println(F("Hörspielmodus -> Track von vorne spielen"));

       break;
    */
  // -----------------------------------------------------
    case 2: //Album
    case 7: //Album-SpezialVonBis
#ifdef Konsole
      Serial.print(F("Album -> vorh.Track : "));
#endif
 
      if (currentQueueIndex > (Steps -1))              // Prüfung ob QueueIndex noch über der Sprungweite liegt
        
        currentQueueIndex = currentQueueIndex - Steps; // Rücksprung um Sprungweite

      else                                             // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat
        currentQueueIndex = 0;                         // QueueIndex auf Null setzen
        Steps = 1;                                     // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;
  // -----------------------------------------------------
    case 3: // Party
    case 8: // Party-SpezialVonBis
      if (currentQueueIndex > (Steps -1))              // Prüfung ob QueueIndex noch über der Sprungweite liegt
        
        currentQueueIndex = currentQueueIndex - Steps; // Rücksprung um Sprungweite

      else                                             // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat
        currentQueueIndex = queueSize - 1;             // QueueIndex auf höchsten Wert setzen
        Steps = 1;                                     // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;
  // -----------------------------------------------------
    case 4: // Einzel
#ifdef Konsole
      Serial.println(F("Single Mod.-> Track repeat."));
#endif
      break;
  // -----------------------------------------------------
    case 5: // Hörbuch
#ifdef Konsole
      Serial.println(F("Hörb.Modus -> vorh.Track und "
                       "Fortschr.speichern"));
#endif

     if (currentQueueIndex > (Steps -1))                           // Prüfung ob QueueIndex noch über der Sprungweite liegt

       currentQueueIndex = currentQueueIndex - Steps;              // Rücksprung um Sprungweite

     else                                                          // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat

        currentQueueIndex = 0;                                     // QueueIndex auf Null setzen
    Steps = 1;                                                     // Rücksetzen der Sprungweite auf 1 für Einzelschritt
#ifndef AiO
        EEPROM.update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern (Classic)
#endif
#ifdef AiO
        EEPROM_update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern (AiO)
#endif
 //     }

      break;
  // -----------------------------------------------------
    default:
      return; // do nothing

  }
 _lastTrackFinished --;
  disablestandbyTimer();
  playCurrentTrack();
  delay(500);
}

// ************************* Spannungsüberwachung der Batterie *********************************

#ifdef BatteryCheck
#ifndef AiO                           // TonUINO Classic
// ************* Funktion zur Ermittlung der genauen Referenzspannung ****************

long readVcc()
{
  long result;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);                // eventuell Zeit verlängern auf 10 ms
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = Bandgap / result;       // 1126400L Bandgapspannung
  return result;
}
#endif  // Ende #ifndef AiO

// ************** Batteriespannung in % *** AiO **************************************************
/*
#ifdef AiO  
  uint16_t getBatteryPercent() 
  {      
  int16_t batteryPercent = map((SumValue / 60), 2250, 2700, 10, 100);
  return batteryPercent < 0 ? 0 : batteryPercent;
  }
#endif */
// *********** Spannungsmessung der Batteriespannung mit der genauen Referenzspannung *************

void VoltControl()
{
  
#ifndef AiO                                           // TonUINO Classic
  
  u_reference = readVcc() / 1000.0;                   // Referenzspannung = ausgelesene Referenzspanung /1000  in V

 // Serial.print("Referenzspannung: ");               // Anzeige der Referenzspannung
 // Serial.print( u_reference );
 // Serial.println(" V");

  uint16_t value = analogRead(BatteryCheckPin);       // Sensorwert Batteriespannung
 /* 
  Vbatt = value * u_reference / 1024 ;                // Berechnung der genauen Batteriespannung in Volt Einzelmessung
  Serial.print(F("Batt =  "));                        // Bei Aktivierung wird jede Einzelmessung im SerMonitor angezeigt
  Serial.print ( Vbatt);
  Serial.println (F( " Volt"));
 //*/ 

  SumValue = SumValue + value;                        // Aufsummierte Einzelmessungen
  countTi = countTi +1;
  if (countTi >= 10)                                  // Testzyklenzahl erreicht
  {
    countTi = 0; 

  VbattGl = SumValue * u_reference / 10240 ;          // Berechnung der geglätteten Batteriespannung in Volt
  Serial.print(F("Batt.=  "));
  Serial.print ( VbattGl);
  Serial.println (F( " V"));
  
  SumValue = 0;
  
#endif     // Ende #ifndef AiO                        

#ifdef AiO
  
  uint16_t value = analogRead(BatteryCheckPin);       // Sensorwert Batteriespannung
/*                                                    // Bei Aktivierung, Anzeige jeder Einzelmessung im SerMonitor
  Serial.print(value);                                // Je nach Spannung Wert zwischen 0 und 4064
  Serial.print(" - ");
  Serial.print(value * reference / steps);            // Wert zwischen 0V und Referenzspannung
  Serial.println(" V");

  Vbatt = (value * reference * correction / steps);   // Berechnung der genauen Batteriespannung in Volt, Einzelmessung
  Serial.print(F("B =  "));
  Serial.print(Vbatt);                                
  Serial.println(" V");                               
  Serial.print(getBatteryPercent());
  Serial.println("%");
*/
  
  SumValue = SumValue + value;                                         // Aufsummierung der Einzelmessungen
  countTi = countTi +1;

  if (countTi >= 60)                                                   // Testzyklenzahl erreicht
  {
    countTi = 0;
    VbattGl = ((SumValue / 60) * reference * correction /  steps );    //Berechnung geglätteter BattspWert
    //Serial.println(SumValue / 60);
    Serial.print(F("Batt.=  "));
    Serial.print(VbattGl);                                
    Serial.println(" V");                                 
    //Serial.print(getBatteryPercent());
    //Serial.println(" %");
    SumValue = 0;
  
  
  // } gemeinsame Schlussklammer für AiO oder Classic weiter unten

#endif          // Ende #ifdef AiO

  // Spannung für Shutdown
  if (VbattGl <= Vshutdown)                         // wenn Batteriespannung Entladeschlussspannung erreicht
  {
    BattLeer = true;
    Serial.println(F("Batt.leer -->ShutDown"));
    if (isPlaying())                                // Wenn Wiedergabe läuft
    {
      mp3.playAdvertisement(404);                   // Batterie ist leer, schalte mich aus
      activeModifier = new SleepTimer(0.5);         // Sleeptimer auf 0,5 min setzen zum langsamen Ausfaden der Lautstärke
                                                    // vor dem Shutdown.
    }
    else                                            // Wenn keine Wiedergabe läuft,sofort abschalten
    {
      mp3.playMp3FolderTrack(604);                  // Batterie ist leer, schalte mich aus
      waitForTrackToFinish();
      delay (500);
    
      ShutDown();                                   // Tonuino abschalten
    }
}
  // Spannung für Warnung                           // wenn Batteriespannung Schwellwert für Warnung erreicht
  if (VbattGl <= Vwarning)
  {
    if (BattLeer == false)
    {
      Serial.println(F("Batt.schwach "));

      if (isPlaying())
      {
        mp3.playAdvertisement(401);
      }
      else
      {
        mp3.playMp3FolderTrack(601);
        //waitForTrackToFinish();
        delay (3000);
        mp3.stop();
        if (StdBy == false)
          setstandbyTimer();
      }
    }            
  }              // Ende If <= Warning
 }               //gemeinsame Schlussklammer } Ende If countTi ,(60 AiO ),(10 Classic)
 
}
#endif          // Ende #ifdef BatteryCheck           


//**** Funktionen für den Standby Timer (z.B. über Pololu-Switch oder Mosfet) ********************
//*********** Im Schlummermodus wird der StandbyTimer auf 99  gesetzt **********************

void setstandbyTimer()                                                // Standbytimer aktivieren
{
  if (mySettings.standbyTimer != 0)                                   // wenn Wert >0 wird Standbytimer aktiviert
  {
    if (mySettings.standbyTimer == 99)                                // Wenn vom Schlummermodus auf 99 gesetzt, Tonuino ausschalten
    {
#ifdef Konsole
      Serial.println(F("TimeOut Sleep"));
#endif
      delay(1000);
      ShutDown();
    }
//#ifdef Konsole
    Serial.print(F("StdBy ON: "));
    Serial.print(mySettings.standbyTimer);
    Serial.println(F(" min"));
    Serial.println(F(""));
//#endif
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
//#ifdef Konsole
  Serial.println(F(""));
  Serial.println(F("StdBy OFF"));
//#endif
  sleepAtMillis = 0;
  StdBy = false;
}

void checkStandbyAtMillis()                                         // Standbytimer Ablauf prüfen
{
  if (sleepAtMillis != 0 && millis() > sleepAtMillis)               // wenn Standbyzeit erreicht, Ausschalten
    ShutDown();
}

// ************* Ausschalten **************************
void ShutDown()                                                     // Ausschalten
{
  #ifdef SpkOnOff
  SpkOff();                                                         // Stummschalten
  #endif
  Serial.println(F("Power OFF!"));

#ifdef USB-Stick
#ifndef AiO
  digitalWrite(UsbPowerPin, HIGH);                                  // MosFet für 5V USB-Port Aus
  delay(500);
#endif
#endif

#ifdef LED_SR                                                       // LED-Ausschaltanimation
                                                                    // Farbfolge Rot-Grün-Blau
strip.fill(red);
strip.show();
delay(1000);
strip.fill(greeen);
strip.show();
delay(1000);
strip.fill(blue);
strip.show();
delay(1000);
strip.clear();
strip.show();
#endif
#ifdef HW_PowerOff
  digitalWrite(ShutDownPin, LOW);                                   // Ausschalten!, Low Pegel zum Rücksetzen des Einschalt-Flip-Flop
  delay(500);
  digitalWrite(ShutDownPin, HIGH);                                  // Ausschalten!, High Pegel für Pololu Switch
  delay(500);
  digitalWrite(ShutDownPin, LOW);                                   // Widerholung!, Low Pegel zum Rücksetzen des Einschalt-Flip-Flop
  delay(500);
#endif

  // http://discourse.voss.earth/t/intenso-s10000-powerbank-automatische-abschaltung-software-only/805
  // powerdown to 27mA (powerbank switches off after 30-60s)

#ifdef LED_SR_Switch
  lsrOffByStdby = true;                                             // LED-Animation ausschalten
#endif
#ifdef LowCurrPwDown
#ifndef AiO
  mfrc522.PCD_AntennaOff();                                         // Rfid-Reader Antenne ausschalten
  mfrc522.PCD_SoftPowerDown();                                      // Rfid-Reader Stromsparmodus
#endif

  mp3.pause();                                                      // Wiedergabe stoppen
#ifndef AiO
  mp3.sleep();                                                      // df-Player in sleep-Mode setzen
                                                                    
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                                                              
  sleep_mode();
#endif
#endif   // Ende ifdef LowCurrPwDown
#ifndef AiO
cli();                                                              // Disable interrupts
#endif
return ;
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
  theFolder->mode = EEPROM.read(modeReg);           // Auslesen Abspielmodus aus Flash
  theFolder->special = EEPROM.read(specialReg);     // Auslesen Starttrack aus Flash für Mod-Spez VonBis
  theFolder->special2 = EEPROM.read(specialReg2);   // Auslesen Endtrack aus Flash für Mod-Spez VonBis
}

#endif

// ************************ lauter **************************************************
void lauter()                                 // Lautstärke erhöhen
{
  volume++;                                   // Lautstärkewert erhöhen 
  mp3.setVolume (volume);
 
  //#ifdef Konsole
  msgMin = true ;
  Serial.print(F("Lauter -> "));
  Serial.println(volume);
  //#endif
}
// ************************ leiser **************************************************
void leiser()                                 // Lautstärke verringern
{
  volume--;                                   // Lautstärkewert verringern
  mp3.setVolume (volume);
 
  //#ifdef Konsole
  msgMax = true ;
  Serial.print(F("Leiser -> "));
  Serial.println(volume);
  //#endif
}

// ************************************************************************************
// ************************* Tasten auslesen ******************************************
void readButtons()
{
  ButtonOne.read();
  ButtonTwo.read();
  ButtonThree.read();
#ifdef FIVEBUTTONS
  ButtonFour.read();
  ButtonFive.read();
#endif
}

// ********* lauter Taste **************
void volumeUpButton()
{
  if (activeModifier != NULL)                          // wenn Modifikation aktiv
    if (activeModifier->handleVolumeUp() == true)      // wenn Taste gesperrt
      return;                                          // kein VolUp

#ifdef SpkOnOff
  if (SpkisOn == true)                                 // wenn Lautsprecher an
  {
#endif
    //#ifdef Konsole
    if (volume >= mySettings.maxVolume )               // wenn Vol größer oder gleich maxVolume Spk
    {
      if (msgMax == true)
      {
      Serial.println("Max Volume !");
      msgMax = false ;
      }
    }
    //#endif
    if (volume < mySettings.maxVolume)                // wenn Vol kleiner maxVolume Spk
    {
      if (longPressVol == true)                       // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)lauter();  
      }
      else lauter();                                  // VolÄnderung durch Einzeldruck der Taste
    }
    
#ifdef SpkOnOff
  }
#endif
#ifdef EarPhone 
  else                                                 // wenn Lautsprecher aus
  {
    //#ifdef Konsole
    {
    if (volume >= mySettings.maxEarVol)                // wenn Vol größer oder gleich maxVolume Ear
     {
     if (msgMax == true)
      {
      Serial.println("Max Volume !");
      msgMax = false ;
      }
     }
    }
    //#endif
    if (volume < mySettings.maxEarVol)                 // wenn Vol kleiner maxVolume Ear
    {
      if (longPressVol == true)                        // VolÄnderung durch longPress
      {  
       if (countVolCh == 0) lauter(); 
      }
      else lauter();                                   // VolÄnderung durch Einzeldruck der Taste
    }
  }
#endif

  countVolCh ++ ;
  if (countVolCh >= setVolChSp) countVolCh = 0 ; 
}
// ******** leiser Taste ************
void volumeDownButton()
{
  if (activeModifier != NULL)                          // wenn Modifikation aktiv
    if (activeModifier->handleVolumeDown() == true)    // wenn Taste gesperrt
      return;                                          // kein VolDown

#ifdef SpkOnOff
  if (SpkisOn == true)                                 // wenn Lautsprecher an
  {
#endif    
    //#ifdef Konsole
     if (volume <= mySettings.minVolume)               // wenn Vol kleiner oder gleich minVolume 
     {
     if (msgMin == true) 
      {
      Serial.println("Min Volume !");
      msgMin = false ;
      }
    } 
    //#endif
    if (volume > mySettings.minVolume)                 // wenn Vol größer min Volume Spk
    {
     if (longPressVol == true)                         // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)leiser();                   // Verzögerung für nächsten Vol-Schritt abgelaufen ( Geschw. der VolÄnderung)
      }
      else leiser();                                   // VolÄnderung durch Einzeldruck der Taste
    }
#ifdef SpkOnOff
  }
#endif
#ifdef EarPhone 
  else                                                 // wenn Lautsprecher aus
  {
    //#ifdef Konsole
    if (volume <= mySettings.minEarVol)                // wenn Vol kleiner oder gleich minVolume 
    {
      if (msgMin == true)
     {
      Serial.println("Min Volume !");
      msgMin = false ;
     }
    }
    //#endif
    if (volume > mySettings.minEarVol)                 // wenn Vol größer minVolume Ear
    {
      if (longPressVol == true)                        // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)leiser();                   // Verzögerung für nächsten Vol-Schritt abgelaufen ( Geschw. der VolÄnderung)
      }
      else leiser();                                   // VolÄnderung durch Einzeldruck der Taste
    }
  }
#endif

  countVolCh ++ ;                                      // Verzögerungszähler einen Schritt weiterschalten
  if (countVolCh >= setVolChSp) countVolCh = 0 ;       // Verzögerungswert erreicht-> Zähler zurücksetzen
}

// ************ Titel Vorwärts Taste *************
void nextButton()
{
  if (activeModifier != NULL)                          // wenn Modifikation aktiv
    if (activeModifier->handleNextButton() == true)    // wenn Taste gesperrt
      return;                                          // Titel nicht weiter
 Steps = 1;
  nextTrack(_lastTrackFinished + 1);                   // beliebige Tracknummer außer _lastTrackFinished

  delay(500);
}
// ************ Titel Zurück Taste *************
void previousButton()
{
  if (activeModifier != NULL)                           // wenn Modifikation aktiv
    if (activeModifier->handlePreviousButton() == true) // wenn Taste gesperrt
      return;                                           // Titel nicht zurück

  previousTrack();                                      // Track zurück
  delay(500);
}

#ifdef FIVEBUTTONS
#ifdef JumpLongPress

// ************ Titel Vorwärts Sprung *************
void JumpForw()
{
  if (activeModifier != NULL)                          // wenn Modifikation aktiv
    if (activeModifier->handleNextButton() == true)    // wenn Taste gesperrt
      return;                                          // Titel nicht weiter
  Steps = SetJump;                                     // Sprungweite setzen
  nextTrack(_lastTrackFinished + 1);                   // beliebige Tracknummer außer _lastTrackFinished
  delay(3000);                                         // Delay zum Anspielen des angesprungenen Titels
}
// ************ Titel Rückwärts Sprung *************
void JumpBackw()
{
  if (activeModifier != NULL)                           // wenn Modifikation aktiv
    if (activeModifier->handlePreviousButton() == true) // wenn Taste gesperrt
      return;                                           // Titel nicht zurück
Steps = SetJump;                                        // Sprungweite setzen
  previousTrack();                                      // Track zurück
  delay(3000);                                          // Delay zum Anspielen des angesprungenen Titels
}
#endif
#endif
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

  bool randomOrder   = false;                 // entweder Tracks in Sortierung oder gemischt abspielen
  bool randomStart   = false;                 // entweder Start playback mit erstem Track oder einem Zufallstrack
  uint8_t fromTrack  = 1;                     // Nummer des 1.Tracks des Abspielbereiches(default 1)
  uint8_t toTrack    = numTracksInFolder;     // Nummer des letzten Tracks des Abspielbereiches (default lastTrack)
  uint8_t firstTrack = 1;                     // Nummer des Tracks, der zuerst abgespielt wird

  bool printRange    = false;

  switch (myFolder->mode)                     // Abspielmodus einstellen
  {
    case 1:                                   // Hörspielmodus: eine zufällige Datei aus dem Ordner
      randomStart = true;                     // Start mit zufälligem Track -> Ja
      break;

    case 2:                                   // Album Modus: kompletten Ordner spielen
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

    default:                                  // Kein Abspielmodus (e.g. AdminCard) -> exit method
      return;
  }

#ifdef Konsole
  if (printRange)                             // Spezial - Bereich im ser Mon ausgeben
  {
    Serial.print(F("Track "));
    Serial.print(myFolder->special);          // StartTrack
    Serial.print(F(" bis "));
    Serial.println(myFolder->special2);       // EndTrack
  }
#endif
 
  initQueue(fromTrack, toTrack);                                // queue erstellen [fromTrack, toTrack], shuffle if requested
  if (randomOrder) shuffleQueue();                              // bei aktivem Zufall, Queue mischen.

  
  if (randomStart) firstTrack = random(fromTrack, toTrack + 1); // festlegen start track
  currentQueueIndex = findQueueIndex(firstTrack);               // festlegen queue index für firstTrack
  if (currentQueueIndex == 0xff) currentQueueIndex = 0;         // bei Fehler findQueueIndex, Index auf 0 setzen

  playCurrentTrack();                                           // start playing



  // ***********************************************************************************
  // ************** Update letzte Karte im EEPROM speichern ****************************
  // ********** Gespielte Shortcuts sollen nicht als letzte Karte gespeichert werden ***

#ifdef LastCard
  if (ShortCutIsPlaying == false)                         // wenn Marker  "shortcut wird nicht gespielt"
  {
#ifndef AiO                                               // TonUINO Classic
    EEPROM.update(folderReg, myFolder->folder);           // EEPROM update letzte gespielte Karte
    EEPROM.update(modeReg, myFolder->mode);               // EEPROM update Abspielmodus
    EEPROM.update(specialReg, myFolder->special);         // EEPROM Update Starttrack
    EEPROM.update(specialReg2, myFolder->special2);       // EEPROM update Endtrack
#endif
#ifdef AiO                                                // TonUINO AiO
    EEPROM_update(folderReg, myFolder->folder);           // EEPROM update letzte gespielte Karte
    EEPROM_update(modeReg, myFolder->mode);               // EEPROM update Abspielmodus
    EEPROM_update(specialReg, myFolder->special);         // EEPROM Update Starttrack
    EEPROM_update(specialReg2, myFolder->special2);       // EEPROM update Endtrack
#endif
#ifdef Konsole
    Serial.println(F("last Card -> EEPROM !"));
#endif
  }

  ShortCutIsPlaying = false ;                             // Marker rücksetzen "Shortcut wird gespielt"
#endif
}

// ************************************************************************************
// ************ Einen gespeicherten Shortcut abspielen *************

void playShortCut(uint8_t shortCut)
{
//#ifdef Konsole
  Serial.print(F("Play Sct: "));
  Serial.println(shortCut);
//#endif
//---- Letzte gespielte Karte auf shortcut 0 legen ------
#ifdef LastCard                                         // wenn LastCard aktiviert ist
  if (shortCut == 0)                                    // Wenn Shortcut Playtaste abgerufen
  {
    setupPlayShortcut(&mySettings.shortCuts[0]);        // LastCard auf Play (shortcut 0) legen
#ifdef Konsole
    Serial.println(F("Last Card-> Sct.0!"));
#endif
  }
#endif                                                  // Ende Lastcard auf Shortcut0 legen
  
  //---- gespeicherten Shortcut abspielen ----
  if (mySettings.shortCuts[shortCut].folder != 0)       // wenn ein shortcut gespeichert ist
  {
    ShortCutIsPlaying = true ;                          // Marker setzen "shortcut wird gespielt"
    myFolder = &mySettings.shortCuts[shortCut];         // aktueller Track -> Gespeichert in shortcut
    playFolder();                                       // shortcut spielen
    
    disablestandbyTimer();
    delay(500);
  }
  else                                                  // wenn kein shortcut gespeichert ist
  {
//#ifdef Konsole
    Serial.println(F("Shortcut n.belegt!"));
//#endif
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
    Serial.println(F("TimeOut-Admin "));
#endif
    mp3.playMp3FolderTrack(803);                      // 803- "Abbruch nach Timeout,Schalte aus"
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
  Serial.println(F("= AdminMenu ="));
#endif
  if (fromCard == false)                          // wenn Adminmenü über Tasten aufgerufen
  { 
    // ************* Prüfung auf Schutz, ggF.Entsperren ************************

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
  // int subMenu              --> Rückgabewert der Nummer des subMenüs
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


  // ************** Karte neu Konfiguriern *************************
  if (subMenu == 1)                                           // 901- "Karte neu Konfigurieren"
  {
    progmode = 1;                                             // Kartenart - Neue Karte
    if (AbbrActive == true)
      return;
    resetCard();
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  // ******* Einzelkarten für einen Ordner festlegen *********************
  else if (subMenu == 2)                                      // 902- "Einzelkarten für einen Ordner festlegen"
  {
    progmode = 2;                                             // Kartenart - Einzelkarte (Ein Titel je Karte)
    if (AbbrActive == true)
      return;
    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.mode = 4;                      // Abspielmodus - Einzelmodus
#ifdef CountFolders
    tempCard.nfcFolderSettings.folder = voiceMenu(numFolders - 2, 301, 0, true); // 301- "Verwende die Vor/zurück-tasten um einen Ordner auszuwählen"
#endif                                                                           // numFolders -2 -> Anzahl der ermittelten Ordner 
                                                                                 // abzueglich mp3 und advert Ordner

#ifndef CountFolders
    tempCard.nfcFolderSettings.folder = voiceMenu(99, 301, 0, true);             // 301- "Verwende die Vor/zurück-tasten um einen Ordner auszuwählen"
#endif                                                                           // 001 - 099 setzt die Ordnernummer Kurzer Druck + oder - 1
                                                                                 //                                  Langer Druck + oder - 10
    if (AbbrActive == true)
      return;
    
    uint8_t special = voiceMenu(mp3.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 321, 0,  // 321- "Startdatei auswählen"
                                true, tempCard.nfcFolderSettings.folder);                            // setzt den Start-Track
    StartTrack = special;                                                                            // zwischenspeichern StartTrack
    if (AbbrActive == true)
      return;
    rolling = false;                                                                                 // Sprung vom letzten Track -> Track 1 gesperrt
    uint8_t special2 = voiceMenu(mp3.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 322, 0, // 322- "Enddatei auswählen"
                                 true, tempCard.nfcFolderSettings.folder, special);                  // setzt den End-Track
    
    rolling = true;                                                                                  // Sprung letzter Track -> Track 1 entsperrt
    if (AbbrActive == true)
      return;

    mp3.playMp3FolderTrack(939);                // 939 - "OK, bitte lege nun nacheinander die Karten auf die Box.
                                                //      Ich werde die jeweilige Nummer vorher ansagen, damit du nicht durcheinander kommst.
                                                //      Zum Abbrechen einfach eine der Lautstärketasten drücken!"

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
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased()) // Lauter oder Leiser-Taste wurde für Abbruch gedrückt?
        {
#ifdef Konsole
          Serial.println(F("Abbruch!"));
#endif
          AbbrActive = true;                                    // Abbruch ist aktiv
          mp3.playMp3FolderTrack(802);                          // 802- "OK, ich habe den Vorgang abgebrochen."
          waitForTrackToFinish();
          setstandbyTimer();
          return;
        }
     } while (!mfrc522.PICC_IsNewCardPresent());                // bleibe in der Schleife solange keine Karte aufgelegt

      if (mfrc522.PICC_ReadCardSerial())                        // RFID Karte wurde aufgelegt
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

  // *********** Modifikationskarten erstellen ***********************
  else if (subMenu == 3)                                        // 903- "Modifikationskarte erstellen"
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

// Hier wären noch drei weitere Modifikationen möglich (977,978,979)

    tempCard.nfcFolderSettings.mode = voiceMenu(6, 970, 970, false, false, 0, true); // 970 - 976
                                                                          //970-Bitte wähle nun deine Modifikationskarte mit den Vor/zurück-tasten aus.

                                                                          //971 -Schlummermodus
                                                                          //972 -Stopptanz - TonUINO spielt Stopptanz mit dir
                                                                          //     und hält zufällig für dich die Wiedergabe kurz an.
                                                                          //973 -TonUINO Sperren
                                                                          //974 -Krabbler-Modus - Alle Tasten vom TonUINO werden für die ganz Kleinen gesperrt.
                                                                          //     Karten funktionieren weiterhin.
                                                                          //975 -KiTa-Modus - Damit es keinen Streit mehr gibt werden neue Karten
                                                                          //     nicht sofort gespielt sondern erst nachdem das aktuelle Lied vorbei ist.
                                                                          //     Die Vor- und Zurücktasten sind gesperrt.
                                                                          //976 -Titel wiederholen - den aktuellen Titel endlos wiederholen.


    if (tempCard.nfcFolderSettings.mode != 0)                     // wenn Option ungleich 0
    {
      if (AbbrActive == true)
        return;
      if (tempCard.nfcFolderSettings.mode == 1)                   // Sleeptimer konfigurieren (Schlummermodus)
      {
        switch (voiceMenu(4, 960, 960))                           // 960- "Nach wievielen Minuten soll der TonUINO ausgeschaltet werden?
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
        AbbrAdminTimeout();                                       // Abbruch nach Timeout Adminmenü

        readButtons();
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased())   // Lauter oder Leiser-Taste gedrückt für Abbruch?
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
      while (!mfrc522.PICC_IsNewCardPresent());                // bleibe in der Schleife solange keine Karte aufgelegt

      if (mfrc522.PICC_ReadCardSerial())                       // RFID Karte wurde aufgelegt
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
// ******** Drei Tasten ********************
#ifndef Buttonboard
#ifndef FIVEBUTTONS
  else if (subMenu == 4)                                      // 904-"Shortcut configurieren ( mit Weckershortcut)
  {                                                           // 995-"Shortcut configurieren ( ohne Weckershortcut)

    progmode = 4;                                             // Shortcut
    if (AbbrActive == true)
      return;
#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(4, 710, 710);                // (711-714)    Playtaste/Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(5, 710, 710);                // (711-715)    Playtaste/Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound/WeckerSound
#endif
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(3, 710, 711);                // (712-714)     Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(4, 710, 711);                // (712-715)     Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound/WeckerSound
#endif
#endif

    if (AbbrActive == true)
      return;

#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
    setupFolder(&mySettings.shortCuts[shortcut - 1]);         // shortcuts 0 - 3 bzw. 0 - 4, Playtaste/Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound/(WeckerSound)
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
    setupFolder(&mySettings.shortCuts[shortcut]);             // shortcuts 1 - 3 bzw. 1 - 4, Up-Lauter-Taste/Down-Leiser-Taste/WelcomeSound/(WeckerSound)
#endif                                                        // shortcut 0 , Playtaste wird mit last card belegt.
  }
#endif
#endif

//****** Fünf Tasten ********************
#ifdef FIVEBUTTONS
  else if (subMenu == 4)                                      // 904-"Shortcut configurieren ( mit Weckershortcut)
  {                                                           // 995-"Shortcut configurieren ( ohne Weckershortcut)

    progmode = 4;                                             // Shortcut
    if (AbbrActive == true)
      return;
#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(6, 720, 720);                // (721-724)    Playtaste/UpTaste/DownTaste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(7, 720, 720);                // (721-725)    Playtaste/UpTaste/DownTaste/WelcomeSound/WeckerSound
#endif
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(5, 720, 721);                // (722-724)     UpTaste/DownTaste/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(6, 720, 721);                // (722-725)     UpTaste/DownTaste/WelcomeSound/WeckerSound
#endif
#endif

    if (AbbrActive == true)
      return;

#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
    setupFolder(&mySettings.shortCuts[shortcut - 1]);         // shortcuts 0 - 3 bzw. 0 - 4, Playtaste/UpTaste/DownTaste/WelcomeSound/(WeckerSound)
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
    setupFolder(&mySettings.shortCuts[shortcut]);             // shortcuts 1 - 3 bzw. 1 - 4, UpTaste/DownTaste/WelcomeSound/(WeckerSound)
#endif                                                        // shortcut 0 , Playtaste wird mit last card belegt.
  }
#endif
// ************ Buttonboard *****************
#ifdef Buttonboard
  else if (subMenu == 4)                                      // 904-"Shortcut configurieren ( mit Weckershortcut)
  {                                                           // 995-"Shortcut configurieren ( ohne Weckershortcut)

    progmode = 4;                                             // Shortcut
    if (AbbrActive == true)
      return;
#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(13, 730, 730);               // (731-743)    Playtaste/Up-LauterTaste/Down-LeiserTaste/Matrix A bis I/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(14, 730, 730);               // (731-744)    Playtaste/Up-LauterTaste/Down-LeiserTaste/Matrix A bis I/WeckerSound
#endif
#endif

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
#ifndef Wecker                                                // wenn Weckerfunktion nicht definiert
    uint8_t shortcut = voiceMenu(12, 730, 731);               // (722-724)     Up-LauterTaste/Down-LeiserTaste/Matrix A bis I/WelcomeSound
#endif
#ifdef Wecker                                                 // wenn Weckerfunktion definiert
    uint8_t shortcut = voiceMenu(13, 730, 731);               // (722-725)     Up-LauterTaste/Down-LeiserTaste/Matrix A bis I/WelcomeSound/WeckerSound
#endif
#endif

    if (AbbrActive == true)
      return;

#ifndef LastCard                                              // wenn Letzte Karte auf PlayTaste legen nicht definiert
    setupFolder(&mySettings.shortCuts[shortcut - 1]);         // shortcuts 0 - 12 bzw. 0 - 13, Playtaste/Up-LauterTaste/Down-LeiserTaste
#endif                                                        // Matrix A bis I/WelcomeSound/(WeckerSound)

#ifdef LastCard                                               // wenn Letzte Karte auf PlayTaste legen definiert
    setupFolder(&mySettings.shortCuts[shortcut]);             // shortcuts 1 - 12 bzw. 1 - 13, Up-LauterTaste/Down-LeiserTaste
#endif                                                        // Matrix A bis I/WelcomeSound/(WeckerSound)
  }                                                           // shortcut 0 , Playtaste wird mit last card belegt.
#endif                                                        



  // ********** Funktion der Lautstärketasten und Vor/Zurücktasten tauschen **************
  else if (subMenu == 5)                                            //905- "Funktion der Vor/Zurücktasten und der Lautstärketasten tauschen
  {
  if (AbbrActive == true)
      return;
  #ifdef  FIVEBUTTONS  
    int temp = voiceMenu(2, 930, 930, false);                       //930- "Möchtest du die Vor/Zurücktasten mit den  Lautstärketasten tauschen?
  #endif                                                                  // Die Funktionen der jeweiligen Tastenpaare werden untereinander getauscht.
 #ifndef  FIVEBUTTONS  
    int temp = voiceMenu(2, 929, 930, false);                       //929- "Möchtest du Shortpress und Longpress der Vor/Zurücktasten tauschen
  #endif                                                                  //Dabei werden die Funktionen von kurzem und langem Tastendruck getauscht.   

    if (temp == 1)                                                  //931- "Ja
    {                                                               // Funktionen tauschen
      if(mySettings.invertVolumeButtons == false)                   
      mySettings.invertVolumeButtons = true;                        
      else
      mySettings.invertVolumeButtons = false;
    }
    else                                                            //932- "Nein
    {                                                               //keine Änderung, Funktionen werden nicht getauscht   
    }
  }

  // ********** Lautstärke und EQ Einstellungen ändern *********************

  else if (subMenu == 6)                                            // 906- "Einstellungen für die Lautstärke und den Klangcharakter ändern
  {
    if (AbbrActive == true)
      return;
#ifdef EarPhone
    int VolMenu = voiceMenu(3, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
                                                                    // 910 - Bitte wähle mit den Vor/zurück-tasten die Einstellung aus und bestätige mit der Pausetaste
                                                                    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
                                                                    // 912 - Einstellungen für die Lautstärke des Kopfhörers ändern
                                                                    // 913 - Den Klangcharakter konfigurieren
#endif
#ifndef EarPhone
    int VolMenu = voiceMenu(2, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
    if (VolMenu == 2) VolMenu = 3;                                  // 910 - Bitte wähle mit den Vor/zurück-tasten die Einstellung aus und bestätige mit der Pausetaste
                                                                    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
                                                                    // 913 - Den Klangcharakter konfigurieren
#endif
    // ********** Lautstärkeeinstellungen Lautsprecher ***************

    if (VolMenu == 1)                                               // 911- "Einstellungen für die Lautstärke des lautsprechers  ändern
    {
      if (AbbrActive == true)
      return;
      int LspMenu = voiceMenu(3, 914, 914, false, false, 0, true);    //(mp3/ 914- 917)
                                                                    // 914 - Bitte wähle mit den Vor/zurück-tasten die zu ändernde Lautstärke aus
                                                                    //       und bestätige mit der Pausetaste
                                                                    // 915 - Maximale Lautstärke Lautsprecher
                                                                    // 916 - Minimale Lautstärke Lautsprecher
                                                                    // 917 - Lautstärke des Lautsprechers beim Start

      // ********** Max Lautstärke des Lautsprechers *******************

      if (LspMenu == 1)                                                       // 915 - Maximale Lautstärke Lautsprecher
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.maxVolume = voiceMenu(30 - mySettings.minVolume, 933,      // 933 - Bitte wähle mit den Vor/zurück-tasten die
                                         mySettings.minVolume,                //       max. Lautstärke des Lautsprechers aus
                                         false, false,
                                         mySettings.maxVolume - mySettings.minVolume)
                                         + mySettings.minVolume; 
      }

      // ********** Min Lautstärke des Lautsprechers *******************

      if (LspMenu == 2)                                                       // 916 - Minimale Lautstärke Lautsprecher
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.minVolume = voiceMenu(mySettings.maxVolume - 1, 934, 0,    // 934 - Bitte wähle mit den Vor/zurück-tasten die
                                         false, false, mySettings.minVolume); //       min. Lautstärke des Lautsprechers aus
      }

      // ********** Initial Lautstärke des Lautsprechers *******************

      if (LspMenu == 3)                                                       // 917 - Lautstärke des Lautsprechers beim Start
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.initVolume = voiceMenu(mySettings.maxVolume - mySettings.minVolume + 1, 935, // 935 - Bitte wähle mit den Vor/zurück-tasten die
                                          mySettings.minVolume - 1, false, false,               //      Lautstärke des Lautsprechers beim Start aus
                                          mySettings.initVolume - mySettings.minVolume + 1)
                                          + mySettings.minVolume - 1;
      }
    }

    // ********** Lautstärkeeinstellungen Kopfhörer ***************
#ifdef EarPhone     
    if (VolMenu == 2)                                                         // 912- "Einstellungen für die Lautstärke des Kopfhörers ändern

    {
      if (AbbrActive == true)
      return;
      int EarMenu = voiceMenu(3, 918, 918, false, false, 0, true);              //  (mp3/ 918 - 921)
                                                                              // 918 - Bitte wähle mit den Vor/zurück-tasten die zu ändernde Lautstärke aus
                                                                              //       und bestätige mit der Pausetaste
                                                                              // 919 - Maximale Lautstärke Kopfhörer
                                                                              // 920 - Minimale Lautstärke Kopfhörer
                                                                              // 921 - Lautstärke des Kopfhörers beim Start

      // ********** Maximale Lautstärke Kopfhörer **************************

      if (EarMenu == 1)                                                       // 919 - Maximale Lautstärke Kopfhörer
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.maxEarVol = voiceMenu(30 - mySettings.minEarVol, 936,        //936 - Bitte wähle mit den Vor/zurück-tasten die
                                         mySettings.minEarVol, false, false,    //      max. Lautstärke des Kopfhörers aus
                                         mySettings.maxEarVol - mySettings.minEarVol) 
                                         + mySettings.minEarVol;
      }

      // ********** Minimale Lautstärke Kopfhörer **************************

      if (EarMenu == 2)                                                           // 920 - Minimale Lautstärke Kopfhörer
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.minEarVol = voiceMenu(mySettings.maxEarVol - 1, 937,           // 937 - Bitte wähle mit den Vor/zurück-tasten die
                                         0, false, false, mySettings.minEarVol);  //       min. Lautstärke des Kopfhörers aus
      }

      // ********** Initial Lautstärke Kopfhörer **************************

      if (EarMenu == 3)                                                           // 921 - Lautstärke des Kopfhörers beim Start
      {
        if (AbbrActive == true)
        return;
        AdjVol = true;
        mySettings.initEarVol = voiceMenu(mySettings.maxEarVol - mySettings.minEarVol + 1, 938, // 938 - Bitte wähle mit den Vor/zurück-tasten die
                                          mySettings.minEarVol - 1, false, false,               //       Lautstärke des Kopfhörers beim Start aus
                                          mySettings.initEarVol - mySettings.minEarVol + 1) 
                                          + mySettings.minEarVol - 1;
      }
    }
#endif

    // *********** Equalizer konfigurieren ************
    if (VolMenu == 3)                                                        //913- "Den Klangcharakter konfigurieren

    {
      if (AbbrActive == true)
      return;
      mySettings.eq = voiceMenu(6, 922, 922, false, false, mySettings.eq);   //922- "Bitte wähle eine Einstellung für den Klangcharakter
                                                                             //      mit den Vor/zurück-tasten aus und bestätige sie mit der Pausetaste.
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
  else if (subMenu == 7)                                                    // 907- "StandbyTimer Konfigurieren
  {
    if (AbbrActive == true)
    return;
    switch (voiceMenu(5, 960, 960))                                         // 960-965
    {
      case 1: mySettings.standbyTimer = 5; break;                           // 961 - 5 Min
      case 2: mySettings.standbyTimer = 15; break;                          // 962 - 15 Min
      case 3: mySettings.standbyTimer = 30; break;                          // 963 - 30 Min
      case 4: mySettings.standbyTimer = 60; break;                          // 964 - 60 Min
      case 5: mySettings.standbyTimer = 0; break;                           // 965 - Kein Standbytimer
    }
  }


  // ********** Das Adminmenü schützen ****************
  else if (subMenu == 8)                                    // 908- "Admin Menü schützen
  {
    if (AbbrActive == true)
    return;
    int temp = voiceMenu(2, 980, 980, false);               // 980 - "Wähle bitte aus ob und wie das Adminmenü geschützt werden soll.
                                                            // 981 - kein Schutz
                                                            // 982 - Nur Adminkarte


    if (temp == 1)                                          // 981 - Kein Schutz
    {
      mySettings.adminMenuLocked = 0;
    }

    else if (temp == 2)                                     // 982 - Nur Adminkarte
    {
      mySettings.adminMenuLocked = 1;
    }
  }

  // ********** Tonuino zurücksetzen ****************
  else if (subMenu == 9)                                    // 909- "Tonuino zurücksetzen
  {
     if (AbbrActive == true)
     return;
#ifdef Konsole
    Serial.println(F("Reset -> lösche EEPROM"));
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
    if (AbbrActive == true)
      return;

#ifdef Konsole
      Serial.println(F("Sct konfiguriert"));
#endif
      mp3.playMp3FolderTrack(403);                            // 403 - "OK.Shortcut konfiguriert"
    }
    else if ( progmode != 9)                                  // aktiver Modus ist nicht Shortcut programmieren
                                                              // und nicht Adminkarte erstellen
    {
    if (AbbrActive == true)
      return;
#ifdef Konsole
      Serial.println(F("Änderungen gespeichert"));
#endif
      mp3.playMp3FolderTrack(998);                            // 998 - "OK.Änderungen gespeichert"
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
  bool Ans = false;
  uint8_t returnValue = defaultValue;
  //bool LP = true;
  // ********* Menülautstärke  festlegen *************
  if (startMessage != 0)

#ifdef MenueVol
    MenuVol = mySettings.initVolume;                      // Auslesen der Startlautstärke aus mySettings
#endif

  mp3.setVolume (MenuVol);                                // Setzen der Menülautstärke
  
#ifdef Konsole
  Serial.print(F("MenüVol:  "));
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

    if ((millis() - AdmTimeOut) >= SollAdmTimeOut)        // Abbruch nach TimeOut
    {
      if (! isPlaying())
      {

#ifdef Konsole
        Serial.println(F("TimeOut-Admin "));
#endif
        mp3.playMp3FolderTrack(803);                      // 803 - Abbruch nach Timeout,Schalte aus
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

    if (ButtonOne.pressedFor(LONG_PRESS))         // Abbruch durch longpress Play/Pause-Taste
    {
#ifdef Konsole
      Serial.println(F("man. Abbruch"));
#endif
      AbbrActive = true;                          // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                // 802 - "OK, ich habe den Vorgang abgebrochen."
      waitForTrackToFinish();
      ignoreButtonOne = true;                     // PauseTaste übergehen
      setstandbyTimer();
      //return defaultValue;
      return;
    }
    if (ButtonOne.wasReleased())                   // Pause-Taste ist gedrückt worden?
    {
      if (returnValue != 0)                        // Liegt ein Rückgabewert des aktiven Voicemenüs vor?
      {
        AdmTimeOut = millis();                     // Neustart TimeOut Timer
#ifdef Konsole
        Serial.print(F("Auswahl "));
        Serial.print(returnValue);
        Serial.println(F(" ok"));
#endif
        return returnValue;                        // Bestätigen des Ordners oder Tracks
      }                                            // bzw Sprung ins neue Voicemenü (Option)
      delay(1000);
    }
    // ************ 10-er Schritt** vorwärts **************
    
    if (ButtonTwo.pressedFor(LONG_PRESS))                               // longpress Taste 2 (Konfigurationsabhängig Weiter oder Lauter)
    {
      if (!ButtonTwo.pressedFor(3000))                                  // wenn Taste länger als 3s gedrückt wird, 
     {                                                                  // soll trotzdem nur einmal Longpress ausgewertet werden
           
      AdmTimeOut = millis();                                            // Neustart TimeOut Timer
      
      if (rolling == true)                                              // wenn rolling erlaubt
          {
          if (returnValue == numberOfOptions)  returnValue = 0;         // Wenn höchste Option erreicht,Rücksprung zum Anfang der Optionen
          if (returnValue == 0)  returnValue = 1;                       // Optionen von 1 beginnen
           else
          if (returnValue == 1)  returnValue = 10;                      // Erster Sprung von 1 auf 10
          else
          returnValue = min(returnValue +10 , numberOfOptions);         // Weitersprünge 10 Schritte hoch bis max Anzahl der Optionen
          }
      else                                                              // wenn rolling nicht erlaubt
        returnValue = min(returnValue +10 , numberOfOptions);           // 10 Schritte hoch bis max Anzahl der Optionen

      ignoreButtonTwo = true;                                           // Taste 2 übergehen
      Ans = true;                                                       // Ansage freigegeben    
      }
    }
    // ************ Einzelschritt weiter ****************************
    else if (ButtonTwo.wasReleased())                                   // Taste 2 wurde kurz gedrückt
    {
      AdmTimeOut = millis();                                            // Neustart TimeOut Timer
      if (!ignoreButtonTwo)                                             // Wenn Taste 2 ausgewertet wird
      {
          if (rolling == true)                                          // wenn rolling erlaubt 
          if (returnValue == numberOfOptions)returnValue = 0;           // Rücksprung zum Anfang der Optionen
          
     
        returnValue = min(returnValue + 1, numberOfOptions);            // 1 Schritt weiter
         Ans = true;

      }
      else                                                              // Wenn Taste 2 nicht ausgewertet wird
      {
        ignoreButtonTwo = false;                                        // LauterTaste auswerten
      }
    }
    // ************* 10-er Schritt* zurück ***************

    if (ButtonThree.pressedFor(LONG_PRESS))                     // Longpress Taste 3 (Zurück oder Leisertaste, Konfigurationsabhängig)
    {
     if (!ButtonThree.pressedFor(3000))                         // wenn Taste länger als 3s gedrückt wird, 
     {                                                          // soll trotzdem nur einmal Longpress ausgewertet werden

      AdmTimeOut = millis();                                    // Neustart TimeOut Timer
      if (rolling == true)                                      // wenn rolling erlaubt 
        {
        if (returnValue == 1)                                   // Wenn von erster Option zurückgesprungen wird
        returnValue = (numberOfOptions + 1);                    // Rücksprung an das Ende der Optionen
        }
      returnValue = max(returnValue - 10, 1);                   // 10 Schritte zurück innerhalb der möglichen Optionen

      if (rolling == false)                                     // wenn rolling gesperrt   
        {
        if(returnValue < StartTrack)                            // wenn Rückgabewert für EndTrack kleiner als StartTrack
        returnValue = StartTrack;                               // Rückgabewert auf zuletzt gespeicherten StartTrack setzen
        }                                                       // Verhindert, dass bei der Erstellung der Spezialmodi oder Einzelkarten
                                                                // der EndTrack vor dem StartTrack liegen kann.
      
      ignoreButtonThree = true;                                 // Taste 3 übergehen
      Ans = true;
      }
    }  
    // **************** Einzelschritt zurück *****************
    else if (ButtonThree.wasReleased())
    {
      AdmTimeOut = millis();                                        // Neustart TimeOut Timer
      if (!ignoreButtonThree)                                       // wenn Taste 3 ausgewertet wird
       {
      if (rolling == true)                                          // wenn rolling erlaubt
        {
        if (returnValue == 1)                                       // Rücksprung zum Ende der Optionen
          returnValue = (numberOfOptions + 1);
        }
        returnValue = max(returnValue - 1, 1);                      // 1 Schritt zurück

       if (rolling == false)                                        // wenn rolling gesperrt   
        {
        if(returnValue < StartTrack)                                // wenn Rückgabewert für EndTrack kleiner als StartTrack
        returnValue = StartTrack;                                   // Rückgabewert auf letzt gespeicherten StartTrack setzen
        }                                                           // Verhindert, dass bei der Erstellung der Spezialmodi oder Einzelkarten
      Ans = true;                                                   // der EndTrack vor dem StartTrack liegen kann.

     }
    else                                                            // wenn Taste 3 nicht ausgewertet wird
    {
     ignoreButtonThree = false;                                     // LeiserTaste auswerten
    }
  }

//================ Ansagen der Optionen und Prewiew ============================
 if(Ans == true)
{
  
 #ifdef Konsole
        Serial.print("Auswahl: ");
        if (AdjVol == false) Serial.println(returnValue);           // Nr der Option
        else Serial.println(messageOffset + returnValue);           // Volume
#endif
        mp3.pause();

// ---------- Messages tauschen --------------------
#ifndef Buttonboard                                                 // 3 und 5 Tastenversion
#ifndef Wecker
        if (messageOffset + returnValue == 904)                     //  Shortcuts mit Weckershortcut
          mp3.playMp3FolderTrack(700);                              // 700 Den Shortcut für eine Taste oder den Startsound programmieren
        else
#endif
#endif

#ifdef Buttonboard                                                  // Big Buttonboard und Wecker
#ifndef Wecker                                                      // Big Buttonboard ohne Wecker
        if (messageOffset + returnValue == 904)                     // Shortcuts mit Weckershortcut
          mp3.playMp3FolderTrack(702);                              // 702 Shortcut mit Matrix ohne Weckershortcut
         else
#endif

#ifdef Wecker
        if (messageOffset + returnValue == 904)                     // Shortcuts mit Weckershortcut
          mp3.playMp3FolderTrack(703);                              // 703 Shortcut mit Matrix und Weckersound
          else
#endif 
#endif

#ifndef EarPhone
      if (messageOffset + returnValue == 912)                      //  Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);                               // 913-Einstellungen für den Klang
      else
#endif

         mp3.playMp3FolderTrack(messageOffset + returnValue);      // Ansage Rückgabewert OrdnerNr, TrackNr, oder Lautstärke


 // ********* Vorschau *************       
       if (preview)
        {
          waitForTrackToFinish();
          if (previewFromFolder == 0)
          mp3.playFolderTrack(returnValue, 1);                   // Vorschau 1. Track des gewählten Ordners
         
       else
          mp3.playFolderTrack(previewFromFolder, returnValue);   // Vorschau des gewählten Tracks

          delay(1000);
        } 
      Ans = false;
      
 
 }
// =========================================================  
  
    
  } while (true);
}

// *********************** Karte neu konfigurieren ***************
void resetCard()
{
  mp3.playMp3FolderTrack(800);                                // 800- "Bitte lege nun die Karte auf!
  delay(1000);
  AdmTimeOutStart();                                          // Start der Timeoutzeit

  do
  {

    AbbrAdminTimeout();                                       // Abbruch nach Timeout Adminmenü

    ButtonOne.read();
    ButtonTwo.read();
    ButtonThree.read();

    if (ButtonTwo.wasReleased() || ButtonThree.wasReleased()) // Vor oder Zurücktaste für Abbruch
    {
#ifdef Konsole
      Serial.print(F("Abbruch!"));
#endif
      AbbrActive = true;                                      // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                            // 802- "OK, ich habe den Vorgang abgebrochen.
      waitForTrackToFinish();
      setstandbyTimer();
      return;
    }
  }

  while (!mfrc522.PICC_IsNewCardPresent());                   // bleibe in der Schleife bis Karte aufgelegt

  if (!mfrc522.PICC_ReadCardSerial())
    return;

#ifdef Konsole
  Serial.print(F("Karte wird neu konf.!"));
#endif
  setupCard();
}

bool setupFolder(folderSettings * theFolder)
{
  // Ordner abfragen
#ifdef CountFolders                                                         // wenn CountFolders aktiv
  theFolder->folder = voiceMenu(numFolders - 2, 301, 0, true, 0, 0, true);  // 301 - Wähle den Ordner aus ( 1 bis numFolders-2)
#endif
#ifndef CountFolders                                                        // wenn CountFolders nicht aktiv
  theFolder->folder = voiceMenu(99, 301, 0, true, 0, 0, true);              // 301 - Wähle den Ordner aus ( 1 - 99)
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
  if (theFolder->mode == 6 || theFolder->mode == 7 || theFolder->mode == 8)              // Spezial Von Bis : Hörsp, Album, Party 
  {
    theFolder->special = voiceMenu(mp3.getFolderTrackCount(theFolder->folder), 321, 0,
                                   true, theFolder->folder);                             // StartTrack
    StartTrack = theFolder->special;                                                     // StartTrack zwischenspeichern um zu Verhindern
                                                                                         // dass Endtrack vor Starttrack liegen kann.
    rolling = false;                                                                     // vom letzten Track -> Track 1 gesperrt
    theFolder->special2 = voiceMenu(mp3.getFolderTrackCount(theFolder->folder), 322, 0,
                                    true, theFolder->folder, theFolder->special);        // EndTrack
    rolling = true;                                                                      // vom letzten Track -> Track 1 entsperrt
  }

  // Admin Funktionen
  if (theFolder->mode == 9)
  {
    progmode = 9;                                                                        // Adminkarte erstellen

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
      // Jingle ist hier deaktiviert, weil der df-player keine zwei advert files hintereinander abspielen kann.
      // Ansonsten würde die Ansage der Modifikation beim aktivieren unterdrückt.
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
    byte pACK[] = {0, 0};                                      //16 bit PassWord ACK returned by the NFCtag

    // Authenticate using key A
#ifdef Konsole
    Serial.println(F("Authenticating UL..."));
#endif
    status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK)                           // Status Fehler
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

  if (status != MFRC522::STATUS_OK)                     // Status Fehler
  {
#ifdef Konsole
    Serial.print(F("MIFARE_Write failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
#endif
    mp3.playMp3FolderTrack(401);                        //401 - "Oh weh! Das hat leider nicht geklappt!
    waitForTrackToFinish();
  }

  else                                                  // Status OK.
  {

    if (progmode == 1)
    {
#ifdef Konsole
      Serial.println(F("Konfiguration OK."));
#endif
      mp3.playMp3FolderTrack(400);                      //400 - "OK. Ich habe die Karte oder den Shortcut konfiguriert.
    }

    if (progmode == 2)
    {
#ifdef Konsole
      Serial.println(F("Einzelkarte fertig"));
#endif
      mp3.playMp3FolderTrack(402);                      // 402 - "OK. Karte fertig"
    }

    if (progmode == 3)
    {
#ifdef Konsole
      Serial.println(F("Modifikationskarte fertig"));
#endif
      mp3.playMp3FolderTrack(404);                     // 404 - "OK. Modifikationskarte fertig"
    }

    if (progmode == 9)
    {
#ifdef Konsole
      Serial.println(F("Adminkarte fertig"));
#endif
      mp3.playMp3FolderTrack(409);                     // 409 - " Adminkarte erstellt"
    }
  }
  waitForTrackToFinish();

  //Serial.println();
  delay(500);
}

// *************************** Wecker *************************************************

#ifdef Wecker
void weckerstart()
{
 ReadWecker = analogRead(WeckerPin);        // Weil Analogpin 6 und 7 nicht als Digitalpins verwendet werden können
                                            // muss ein Umweg über analogRead() gegangen werden.
#ifndef AiO
  if (ReadWecker >= 512)                    // wenn Analogwert WeckerPin > 2,5V (TonUINO Classik)
#endif
#ifdef AiO
  if (ReadWecker >= 1500)                   // wenn Analogwert WeckerPin > 1,6V (AiO )
#endif
  {
    WeckerStart = true;
    Serial.println("Startimpuls Wecker erkannt"); 
  }
}

void wecker()
{
  
  if (ActWecker == false)                       // Wenn Wecker noch nicht aktiviert wurde
  {
    ReadWecker = analogRead(WeckerPin);         // Weil Analogpin 6 und 7 nicht als Digitalpins verwendet werden können
  }                                             // muss ein Umweg über analogRead() gegangen werden.
#ifndef AiO
  if ((ReadWecker >= 512)||WeckerStart == true) // wenn Analogwert WeckerPin > 2,5V (TonUINO Classik)
#endif
#ifdef AiO
  if ((ReadWecker >= 1500)||WeckerStart == true)// wenn Analogwert WeckerPin > 1,6V (AiO )
#endif
  {
//#ifdef Konsole
    Serial.println(F("Wecker aktiviert! "));
//#endif

    SpkOn();                                    // Lautsprecher auch bei angeschlossenem Kopfhörer anschalten

    ActWecker = true;                           // Marker setzen: Wecker wurde aktiviert (Erneutes Abspielen
                                                //                des Weckers erst nach Ausschalten des Tonuino möglich)

    playShortCut(ShcWecker);                    // Wecker abspielen
    delay(200);
    setstandbyTimer();
    if (isPlaying())                            // Solange Wecker spielt
    {
      WeckerPlay = true;                        // Marker setzen - Weckershortcut wird gespielt
    }
  }
  else                                          // Wecker wurde nicht aktiviert
  {

    if (SETUP == true)                          // wenn Programmablauf im Setup
    {
      playShortCut(Welcome);                    // Welcomesound spielen
      setstandbyTimer();
    }
  }
}
#endif


// ************************* Kopfhörer *************************************************

// --------------- Lautsprecher abschalten wenn Kopfhörer angeschlossen -------------------------
// --------------- Bei aktivem Weckersound soll der Lautsprecher nicht ausgeschaltet werden -----
#ifdef EarPhone
void Earphone ()
{
#ifdef Wecker
  if (WeckerPlay == true)                       // Marker Weckershortcut wird gespielt gesetzt?
  {
    if (!isPlaying())                           // Wiedergabe beendet?
    {
      WeckerPlay = false;                       // Marker Weckershortcut wird gespielt-zurücksetzen
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
          SpkOn();                              // Lautsprecher Einschalten
      }
  }
#ifdef Wecker
}
#endif
#endif


// ************************** Lautsprecher über Software an und ausschalten ***************
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
  digitalWrite(SpkOnPin, LOW);                                  // Lautsprecher über Mosfets Ausschalten (Classic )
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, HIGH);                                 // Verstärker Ausschalten AiO
#endif
  SpkisOn = false;                                              // Marker setzen-Lautsprecher AUS
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

  if ( (ButtonTwo.pressedFor(LONG_PRESS)
        || ButtonThree.pressedFor(LONG_PRESS) )
       && ButtonTwo.isPressed()
       && ButtonThree.isPressed())
  {
    lsrSwitch = true;                     // Marker auf Tasten gedrückt setzen
#ifdef Konsole
    Serial.print(F("LED-Animation: "));
#endif
    ignoreButtonTwo = true;               // Taste-2 übergehen
    ignoreButtonThree = true;             // Taste-3 übergehen
  }

  // ***************** Einschalten Animation *************

  if (lsrSwitch == true
      && lsrEnable == false
      && (ButtonTwo.isReleased())
      && (ButtonThree.isReleased()))
  {
    lsrSwitch = false ;                  // Marker Tasten gedrückt rücksetzen
    lsrEnable = true ;                   // Animation aktivieren
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
       && (ButtonTwo.isReleased())
       && (ButtonThree.isReleased()))
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

 //*************LED-Animaion by @tON ****  modifyed by @atomphil ***********************
    ///////////////// Prüfung der einmaligen Animationen /////////////////
 
    // ----------   Liedänderung erkennen und Animation aktivieren   ---------- //
    currentDetectedTrack = currentQueueIndex;
    if (currentDetectedTrack != lastDetectedTrack)
    {
      strip.clear();                                              // über schwarz oder über die vorherige Animation
      if (currentQueueIndex > lastDetectedTrack) //nächstes Lied
      {
        lsrAnimationTrackMode = 1;
      }
      if (currentQueueIndex < lastDetectedTrack) // Lied zurück
      {
        lsrAnimationTrackMode = 2;
      }
      lsrAnimationMode = 1;
      loopCountWait = 0;   
      y = 0;
    }
 
    // ----------    Lautstärkenanpassung erkennen und Animation aktivieren    ---------- //
    currentDetectedVolume = volume;
    if (currentDetectedVolume != lastDetectedVolume)
    {
      lsrAnimationMode = 2;
      animCount = strip.numPixels();
      loopCountWait = 0;
    }
 
    ///////////////// Dauerhafte Loop Animationen /////////////////
 
    // ----------   Loop Animation: Default Mode   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == false && knownCard == false)
    {
        for(int i=(strip.numPixels()/2)-1; i>=0; i--) {
          pixelHue = firstPixelHue - (i * 65536L / (strip.numPixels()));
          strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
          strip.setPixelColor(strip.numPixels()-i-1, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();                 // Update strip with new contents
        
        firstPixelHue += 128;         // Geschwindigkeit der Animation, je kleiner um so langsamer
    }
 
    // ----------   Loop Animation: Musik spielt   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == true && knownCard == true)
    {
        for(int i=0; i<strip.numPixels(); i++) {
          pixelHue = firstPixelHue + (i * 65536L / (strip.numPixels()*1));
          strip.setPixelColor(strip.numPixels()-1-i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();                // Update strip with new contents
        
        firstPixelHue += 384;       // Geschwindigkeit der Animation, je kleiner um so langsamer
     }
 
    // ----------   Loop Animation: Musik pausiert   ---------- //
    if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() == false && knownCard == true)
    {
        for(int i=0; i<strip.numPixels(); i++) {
          pixelHue = firstPixelHue + (i * 65536L / (strip.numPixels()*8));
          strip.setPixelColor(strip.numPixels()-1-i, strip.ColorHSV(pixelHue, 192, 8));       
        }
        //strip.setBrightness(64);
        strip.show();                 // Update strip with new contents
        
        firstPixelHue += 64;          // Geschwindigkeit der Animation, je kleiner um so langsamer
    }
      
    ///////////////// Einmalige Animationen bei einem Ereignis /////////////////
 
    // ----------   Einmalige Animation: Liedänderung    ---------- //
    if (lsrAnimationMode == 1 && loopCount == 0)
    {
      animCount = strip.numPixels();
      int Balken = TrckChgProgress;
      int i = 0;
      
      while (Balken > TrckChgMaxBrightness)
        {
           if (lsrAnimationTrackMode == 1){
                strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(TrckChgColor_FFW, 255, TrckChgMaxBrightness)); 
           }else{
                strip.setPixelColor(i, strip.ColorHSV(TrckChgColor_REW, 255, TrckChgMaxBrightness));             
           }
           Balken -= TrckChgMaxBrightness;
           i++;
           if (animCount != 0)
              {
                animCount--;
              }
        }
      
      if ( animCount != 0 && Balken > 0 )
        {
           if (lsrAnimationTrackMode == 1){
                strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(TrckChgColor_FFW, 255, Balken)); 
           }else{
                strip.setPixelColor(i, strip.ColorHSV(TrckChgColor_REW, 255, Balken));             
           }
        }
  
      strip.show();
      
      TrckChgProgress += TrckChgSpeed;
      
      if (animCount == 0)
      {
        lsrAnimationMode = 0;
        TrckChgProgress = 0;
        loopCount = 40;
      }
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
         animCount = 50; 
      }
      
      volumeScope = (mySettings.maxVolume - mySettings.minVolume);
      volumeScopeAmount = (volume - mySettings.minVolume) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs
      volumeScopeAmountMod = (volume - mySettings.minVolume) * (LED_COUNT - 1) % volumeScope;
 
#ifdef EarPhone
     if (SpkisOn == false)
      { 
      volumeScope = (mySettings.maxEarVol - mySettings.minEarVol);
      volumeScopeAmount = (volume - mySettings.minEarVol) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige Kopfhörer angepasst an die Anzahl der LEDs
      volumeScopeAmountMod = (volume - mySettings.minEarVol) * (LED_COUNT - 1) % volumeScope; 
      }
#endif
 
      uint8_t VolMaxBrightness = 255;
      
      uint16_t VolColor = 23000L - (((volume - mySettings.minVolume) * 23000L) / volumeScope);
      for (i = 0; i < strip.numPixels(); i++)
        {
          if (i<=volumeScopeAmount){
                strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, VolMaxBrightness)); 
            }
          else if (i==volumeScopeAmount+1){
                strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, ((volumeScopeAmountMod * VolMaxBrightness) / volumeScope))); 
            }
          else{
                strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, 0)); 
            }
        }
 
      strip.show();
      
 
      if (animCount == 0)
      {
        lsrAnimationMode = 0;
        TrckChgProgress = 0;        
      }
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
 
  if (lsrAudioBreak == true)     // wenn Wiedergabe von LED On/Off gestoppt
  {
    mp3.start();                 // Wiedergabe fortsetzen
    disablestandbyTimer();
    lsrAudioBreak = false;       // Marker Wiedergabe läuft wieder
  }
}
#endif                           // Ende Abfrage Aktivierung LED Animation (#ifdef LED_SR)
 
// *************************** Ende LED Animation ******************************************

// *************************** Fehlerbehandlung des Df-Players *****************************
  void mp3Error()
  {
  if (mp3error == true)                         // bei Vorliegen eines Fehlercodes vom Df-Player
    {
     if (StdBy == false) setstandbyTimer();     // Standbytimer starten
      #ifdef LED_SR                             // Blinksignal 5 x Magenta
      strip.fill(magenta);
      strip.show();
      delay(1000);
      strip.clear();
      strip.show();
      delay(1000);
      Zhl = Zhl-1;
      if(Zhl == 0)
      {
        mp3error = false;                       // Rücksetzen Marker mp3error
        Zhl = 5;
        if (!isPlaying()) nextTrack(_lastTrackFinished + 1); // Ist wiedergabe gestoppt -> Wechsel zum nächsten Track
      }
     #endif 
    }
  }


#ifdef Buttonboard
void ReadMatrix()
{

if(TaGedr == false)
  {
  analogRead(Buttonmatrix);
  delay(50);
  Wert = analogRead(Buttonmatrix);
#ifdef AiO
  Matrix = map(Wert, 0, 4064, 1, 10);
#endif
#ifndef AiO
  Matrix = map(Wert, 0, 1023, 1, 10);
#endif
  
  switch (Matrix)
     {
 //------------------------------------------
        case 1:
        
            Serial.println(F(" A"));              // Matrixtaste 1 (A)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(3);
            delay(500);
            TaGedr = false ;
            break;
 //------------------------------------------        
        case 2: 
       
            Serial.println(F(" B"));              // Matrixtaste 2 (B)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(4);
            delay(500);
            TaGedr = false ;
            break;
 //------------------------------------------       
        case 3:
        
            Serial.println(F(" C"));              // Matrixtaste 3 (C)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(5);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------        
        case 4: 
        
            Serial.println(F(" D"));              // Matrixtaste 4 (D)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(6);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------       
        case 5:
        
            Serial.println(F(" E"));              // Matrixtaste 5 (E)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(7);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------        
        case 6: 
        
            Serial.println(F(" F"));              // Matrixtaste 6 (F)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(8);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------        
        case 7:
       
            Serial.println(F(" G"));              // Matrixtaste 7 (G)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(9);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------       
        case 8: 
        
            Serial.println(F(" H"));              // Matrixtaste 8 (H)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(10);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------        
        case 9: 
       
            Serial.println(F(" I"));              // Matrixtaste 9 (I)
            //Serial.println(Wert);
            TaGedr = true ;
            playShortCut(11);
            delay(500);
            TaGedr = false ; 
            break;
 //------------------------------------------       
        default:
       
            //Serial.print(F("keine Taste"));          // Keine Taste gedrückt
            TaGedr = false ;
            break;
 //------------------------------------------       
     }
  }
}
#endif

// =========================================================================================
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
  Serial.println(F("** TONUINO **"));
#endif
#ifdef AiO
  Serial.println(F("** TONUINO - AiO **"));
#endif
  Serial.println(F("** VERSION THOMAS LEHNERT ** 2021-12-18 **"));
  Serial.println();
#ifndef AiO
  Serial.println(F("Based on TonUINO V.2.1"));
#endif
#ifdef AiO
  Serial.println(F("Based on TonUINO V.2.2"));
#endif
  Serial.println(F("created by Thorsten Voß and licensed under GNU/GPL."));
  Serial.println(F("https://tonuino.de.\n"));
  // ------------------------------------------------------------------------------------
#ifndef Buttonboard
 #ifndef FIVEBUTTONS
  Serial.println(F("*** 3 Tasten ***"));  // 3-Tastenversion
 #endif
 #ifdef FIVEBUTTONS
  Serial.println(F("*** 5 Tasten ***"));  // 5-Tastenversion
 #endif
#endif
#ifdef Buttonboard
  Serial.println(F("*** 12 Tasten ***")); // Buttonboard-Version (12 Tasten)
#endif 
  Serial.println(" ");
  // ------------------------------------------------------------------------------------
  pinMode(BusyPin, INPUT);                // Eingang Busy-Signal vom DF-Player
  pinMode(ButtonPause, INPUT_PULLUP);     // Eingang Pausetaste
  pinMode(ButtonUp, INPUT_PULLUP);        // Eingang Uptaste
  pinMode(ButtonDown, INPUT_PULLUP);      // Eingang Downtaste
#ifdef FIVEBUTTONS
  pinMode(ButtonFourPin, INPUT_PULLUP);   // Eingang Taste 4
  pinMode(ButtonFivePin, INPUT_PULLUP);   // Eingang Taste 5
#endif
#ifdef Buttonboard
  pinMode(Buttonmatrix, INPUT);           // Eingang Tastenmatrix 9-Tasten (A-I)
  //------------------------------------------------------------------------------------
  #ifdef AiO
   #ifndef BatteryCheck
   analogReference(INTERNAL2V048);        // Festlegung der Referenz
   analogReadResolution(12);              // Auflösung Auslesen
   #endif
  #endif

#endif 
  // ------------------------------------------------------------------------------------
#ifdef BatteryCheck
  pinMode(BatteryCheckPin, INPUT);      // Eingang Batteriespannungskontrolle
 #ifdef AiO
  analogReference(INTERNAL2V048);       // Festlegung der Referenz
  analogReadResolution(12);             // Auflösung Auslesen
 #endif
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
  digitalWrite(ShutDownPin, HIGH);      // Voreinstellung - On (LOW-Active)
  #endif
  #ifndef LowActive
  digitalWrite(ShutDownPin, LOW);       // Voreinstellung - On (HIGH-Active)
  #endif
#endif
#endif
#ifdef AiO
  pinMode(ShutDownPin, OUTPUT);
  digitalWrite(ShutDownPin, HIGH);      // Spannung AiO einschalten

  pinMode(Access_SD_Pin, OUTPUT);
  digitalWrite(Access_SD_Pin, LOW);     // SD karten Zugang über USB gesperrt
#endif
#ifdef USB-Stick
#ifndef AiO
  pinMode(UsbPowerPin, OUTPUT);         // Ausgang USB Powersignal
  digitalWrite(UsbPowerPin, LOW);       // Voreinstellung - UsbPower On
#endif
#endif
  // ----------------------------------------------------------------------------------------
#ifdef SpkOnOff
  pinMode(SpkOnPin, OUTPUT);            // Ausgang Lautsprecher-Einschaltsignal
#ifndef AiO
  digitalWrite(SpkOnPin, LOW);          // Voreinstellung TonUINO Classic - Speaker Off
#endif
#ifdef AiO
  digitalWrite(SpkOnPin, HIGH);         // Voreinstellung AiO - Speaker Off (Amp Off)
#endif
#endif
  // ----------------------------------------------------------------------------------------
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
  // ----------------------------------------------------------------------------------------
  // *************** Settings aus EEPROM laden **und Prüfung auf geänderte Struktur durch #defines ***********
  //     Bei Änderungen in den #defines die eine Änderung der Speicherstruktur im EEPROM bewirken, wird durch 
  //     Änderung des Wertes von myCokie ein automatischer Reset von mySettings erzwungen, 
  //     um die Speicherstruktur an die neue Konfiguration anzupassen.
   
  #ifdef EarPhone
myCookie = myCookie +1;                // setzt myCookie um 1 hoch (Settings um KH-Einstellungen erweitert)
#endif                                          
#ifdef FIVEBUTTONS
myCookie = myCookie +2;                // setzt myCookie um 2 hoch (2 Zusätzliche Shortcuts in den Settings)
#endif       
#ifdef Buttonboard
myCookie = myCookie +4;                // setzt myCookie um 4 hoch (9 Zusätzliche Shortcuts in den Settings)
#endif         
  loadSettingsFromFlash();
  // ----------------------------------------------------------------------------------------   
  // ********** Kontrolle ob über Wecker eingeschaltet wurde **********
 #ifdef Wecker
  weckerstart();
 #endif
  // ------------------------------------------------------------------------------------
  //*************** LED Animation initialisieren ************
#ifdef LED_SR
  strip.begin();
  strip.clear();
  strip.setBrightness(64);
  strip.show();
  strip.fill(lightblue);
  strip.show();
 
  loopCount = 0;
  animCount = 1;
  lastDetectedTrack = 0;
#endif

  // ---------------------------------------------------------------------------------------
  //*************** DFPlayer Mini initialisieren *******************************************
  mp3.begin();
#ifdef USB-Stick
  delay(5000);    // Fünf Sekunden warten bis der DFPlayer Mini initialisiert ist für Nutzung des USB-Stick
#endif

#ifndef USB-Stick
  delay(3000);   // Drei Sekunden warten bis der DFPlayer Mini initialisiert ist ohne Nutzung des USB-Stick
#endif
 // ----------------------------------------------------------------------------------
 //************* Ordner des Speichermediums zählen *****************
#ifdef CountFolders
  numFolders = (mp3.getTotalFolderCount( ));  // Ordner zählen
#ifdef IgnoreWinSysInf
  numFolders = numFolders - 1;                // Der Windows Ordner SystemVolumeInformation wird von der Ordnerzahl abgezogen
#endif
  Serial.print("Ordner auf SD: ");
  Serial.println (numFolders);
  Serial.println ();
#endif

  // ------------------------------------------------------------------------------------
  //************* NFC Leser initialisieren **********************************************
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

  // ----------------------------------------------------------------------------------------
  //************ Lautstärke des Lautsprechers auf Startlautstärke setzen ********************

  volume = mySettings.initVolume;                     // Startlautstärke
  mp3.setVolume(volume);
  delay(50);
  mp3.setEq(mySettings.eq - 1);
  
  // -----------------------------------------------------------------------------------------
  // ******************* Lautsprecher einschalten ***Hardwareerweiterung erforderlich ********
#ifdef SpkOnOff

  SpkVol = mySettings.initVolume;                     // Variable setzen, Startlautstärke Lautsprecher
 #ifdef EarPhone
  EarVol = mySettings.initEarVol;                     // Variable setzen, Startlautstärke für Kopfhörer
 #endif

  SpkOn();                                            // Lautsprecher einschalten (Abhängig von gestecktem Kophörer)

  if (SpkisOn == true) mp3.setVolume(SpkVol);         //Startlautstärke Lautsprecher einstellen
 #ifdef EarPhone
  else mp3.setVolume(EarVol);                         //Startlautstärke für Kopfhörer einstellen
 
 #endif
#endif

  // -----------------------------------------------------------------------------------------
  //  *************** Manueller Reset beim Einschalten ****************************************

  // RESET --- ALLE DREI KNÖPFE BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden auf DEFAULT gesetzt
   readButtons();                             // Tasten auslesen
     if (ButtonOne.isPressed()
      && ButtonTwo.isPressed()
      && ButtonThree.isPressed())
  {
    Serial.println(F("Reset -> lösche EEPROM"));
#ifndef AiO
    for (int i = 0; i < EEPROM.length(); i++)
    {
      EEPROM.update(i, 0);                          // EEPROM löschen (Klassik)
    }
#endif
#ifdef AiO
    for (int i = 0; i < 1024; i++)
    {
      EEPROM_update(i, 0);                          // EEPROM löschen (AiO)
    }
#endif

    resetSettings();                                // mySettings Standartwerte setzen und im EEPROM speichern.

    mp3.playMp3FolderTrack(999);                    //999 Reset wurde durchgeführt!
    waitForTrackToFinish();
    delay(5000);
  }

  // ---------------------------------------------------------------------------------------
  // ****************** Standby Timer aktivieren *******************************************
  setstandbyTimer();

  // ---------------------------------------------------------------------------------------
  // *********************** Kopfhörer *****************************************************
#ifdef Wecker
  WeckerPlay = false;           // Weckershortcut wird nicht abgespielt
#endif

#ifdef EarPhone
  EarFirstTime = true ;        // Marker Kopfhörer nach Einschalten erstmals eingesteckt
  Earphone ();                 // Prüfen ob KH gesteckt
#endif

  // --------------------------------------------------------------------------------------
  // *************  Wecker ** Hardwareerweiterung erforderlich ****************************
#ifdef Wecker
 wecker();                    // Prüfen ob durch Wecker eingeschaltet wurde
#endif                        // ggf. Start Weckershortcut, falls konfiguriert
delay(1000);
  // ------------------------------------------------------------------------------------
  // *********** Start Shortcut "at Startup" - e.g. Welcome Sound ************************
#ifndef Wecker
   playShortCut(Welcome);    // Start Shortcut Welcomesound, falls konfiguriert
#endif

  // ------------------------------------------------------------------------------------
  // *************** Freigabe oder Unterdrückung Konsolenausgabe **************************
#ifndef Konsole
  Serial.println ("Weitere Konsolenausgaben minimiert");
#endif

  // ------------------------------------------------------------------------------------
  SETUP = false;                          // Marker zurücksetzen, Setup ist beendet
}

// ****************** Ende Setup ************************************************
// ******************************************************************************

// ===============================================================================
// *******************************************************************************
//                            MAIN-LOOP
// *******************************************************************************
void loop()
{
  do
  {
    // ********************* Big Buttonboard ***************************************************
#ifdef Buttonboard                            // bei aktivem 12 Buttonboard
ReadMatrix();                                 // Kontrolle ob eine Taste der Matrix gedrückt wurde.
#endif

    // ********************* Intervallmäßiges Prüfen der Batteriespannung ***********************
#ifdef BatteryCheck

    Now = millis();                           // auslesen aktueller Zeitpunkt
    if (Now - lastTest >= TestIntervall)
    {
      lastTest = Now;                         // Speichern letzter Testzeitpunkt
      VoltControl();                          // Batterieprüfung
    }
#endif

    // ************************ Wecker **** Hardwareerweiterung erforderlich **********************
#ifdef Wecker
    if (ActWecker == false)   // wenn Wecker in aktiver Session noch nicht aktiviert worden ist
      wecker();
#endif

    // ******************** Lautsprecher abschalten wenn Kopfhörer angeschlossen *******************
    // **** wenn der Wecker aktiv wird soll der Lautsprecher nicht abgeschaltet werden *************

#ifdef EarPhone
    Earphone ();
#endif

    // *********************** LED Animation ** Hardwareerweiterung erforderlich ******************
#ifdef LED_SR
   
    // --------- LED-Signalisation MP3-Error --------------
    mp3Error();                                // Bei einem mp3 Error 5 x Blinksignal Magenta
     
    LED_Animation();                           // Standart-LED-Animation
#endif

    // ************************Prüfen StandbyTimer und aktive Modifikation *************************
    checkStandbyAtMillis();                    // Prüfen Standbytimer
    mp3.loop();

    if (activeModifier != NULL)                // Prüfen auf aktive Modifikationskarte
      activeModifier->loop();                  // Modifikation aktivieren

    // ********************** Auswerten der Tasten *************************************************
    // Buttons werden nun über JS_Button behandelt, dadurch kann jede Taste
    // doppelt belegt werden

    readButtons();                             // Tasten auslesen

    // ***************** Adminmenu über longPress 3 Tasten aktivieren **************************

    if ((ButtonOne.pressedFor(LONG_PRESS)
         || ButtonTwo.pressedFor(LONG_PRESS)
         || ButtonThree.pressedFor(LONG_PRESS))
        && ButtonOne.isPressed()
        && ButtonTwo.isPressed()
        && ButtonThree.isPressed())
    {
      mp3.pause();                             // Wiedergabe stoppen
      do
      {
        readButtons();                         // Tasten auslesen
      }

      while (ButtonOne.isPressed()
             || ButtonTwo.isPressed()
             || ButtonThree.isPressed());

      readButtons();                           // Tasten auslesen
      adminMenu();                             // Adminmenü starten
      break;
    }

    // ******************* Taste 1 (Play/Pause Taste) ****************************************************
    // ------------- ShortPress --------------------------------
    if (ButtonOne.wasReleased())                                // wenn Play/Pausetaste gedrückt wurde
    {
       mp3error = false;                                        // Rücksetzen Marker mp3error
    
      if (activeModifier != NULL)                               // wenn Modifikation aktiv
        if (activeModifier->handlePause() == true)              // wenn akt.Modifikation pause Taste sperrt
          return;                                               // Abbrechen
      if (ignoreButtonOne == false)                             // Wenn Taste ausgewertet wird
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
      ignoreButtonOne = false;                                  // Pausetaste auswerten
    }
// ---------------- LongPress -------------------------------------
    else if (ButtonOne.pressedFor(LONG_PRESS)
             && ignoreButtonOne == false)                       // Langer Druck Pausetaste für Ansage des aktuellen Tracks
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
          Serial.println(F("Hörb.-> Anfang"));
#endif
          mp3.playFolderTrack(myFolder->folder, currentQueueIndex);  // aktuellen Track spielen
        }
#endif
      //************** Ende, Rücksetzen - Hörbuch auf Anfang ***********************
        else                                                    // alle anderen Abspielmodi außer Hörbuch
        {
          mp3.playAdvertisement(advertTrack);                   // Tracknummer ansagen
        }
      }
      else                                                      // wenn keine Wiedergabe läuft
      {
        playShortCut(0);                                        // Shortcut Pausetaste spielen
      }
      ignoreButtonOne = true;                                   // PauseTaste übergehen
    }
    // *********** Ende Taste 1 (Play/Pausetaste) *************************************************

    // *************** Taste 2  (Vor/Vol +) *******************************************************
    // ---------------- LongPress -------------------------------------
#ifdef LED_SR_Switch
    if (ButtonTwo.pressedFor(LONG_PRESS) && lsrSwitch == false)
#endif
#ifndef LED_SR_Switch
    if (ButtonTwo.pressedFor(LONG_PRESS))       // Wenn Taste2 lange gedrückt
#endif    
  {
   
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (!mySettings.invertVolumeButtons)    // wenn Funktion der Vol-Tasten nicht getauscht
         {
          longPressVol = true;                  // VolÄnderung durch longPress 3 und 5 Tastenmodus
          volumeUpButton();                     // Lauter Taste
         }
         else                                   // wenn Funktion der Vol-Tasten getauscht
         {                                       
           #ifndef FIVEBUTTONS                  // 3 Tastenmodus und Buttonboard
           nextButton();                        // weiter Taste longpress im 3 Tastenmodus
           #endif
           #ifdef FIVEBUTTONS                   // 5 Tastenmodus
           JumpForw();                          // Titelsprung longpress im 5 Tastenmodus
           #endif
         }
      }
    else                                        // wenn keine Wiedergabe läuft
     {                                          // Aufrufen der Shortcuts
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Vol-Tasten getauscht
        {
        #ifndef FIVEBUTTONS                     // 3 Tastenmodus
         playShortCut(NextLauterButton);        // Shortcut spielen Vor/Lauter-Taste
        #endif
        #ifdef FIVEBUTTONS
         playShortCut(NextButton);              // Shortcut spielen Weiter-Taste
        #endif
        }
        else                                   // wenn Funktion der Vol-Tasten nicht getauscht
        {
        #ifndef FIVEBUTTONS                    // 3 Tastenmodus und Buttonboard
        playShortCut(NextLauterButton);        // Shortcut spielen Vor/Lauter-Taste
        #endif
        #ifdef FIVEBUTTONS                     // 5 Tastenmodus
        playShortCut(LauterButton);            // Shortcut spielen Lauter-Taste
        #endif
        }
       }
     
      ignoreButtonTwo = true;                   // Taste2 nach loslassen übergehen

    }                                           // Ende longPress
    // ---------------- ShortPress -------------------------------------    
    else if (ButtonTwo.wasReleased())           // wenn kein longpress und Taste nur kurz gedrückt wurde (shortpress)
    {
      if (!ignoreButtonTwo)                     // Wenn Taste gelesen werden soll
       {
        if (!mySettings.invertVolumeButtons)    // wenn Funktion der Vol Tasten nicht getauscht
        {
 #ifndef FIVEBUTTONS                            // 3 Tastenmodus und Buttonboard
          nextButton();                         // weiter Taste im 3 Tastenmodus durch kurzen Tastendruck
 #endif
 #ifdef FIVEBUTTONS                             // 5 Tastenmodus
         volumeUpButton();                      // Lauter Taste
         longPressVol = false;                  // schrittweise VolÄnderung durch kurzen Tastendruck
 #endif       
        }
        else                                    // wenn Funktion der Vol Tasten getauscht
        {
 #ifndef FIVEBUTTONS       
         volumeUpButton();                      // Lauter Taste im 3 Tasenmodus
         longPressVol = false;                  // schrittweise VolÄnderung durch kurzen Tastendruck
  #endif
  #ifdef FIVEBUTTONS       
         nextButton();                          // weiter Taste im 5 Tastenmodus durch kurzen Tastendruck
 
 #endif
        }
       }
      ignoreButtonTwo = false;                  // Taste2 wieder auswerten
    
    }                                           // ende shortpress
    // *********** Ende Taste 2  (Vor/Vol +)  ********************************************

    // *************** Taste3 (Zurück/Vol -)  *********************************************
    // ---------------- LongPress -------------------------------------
#ifdef LED_SR_Switch
    if (ButtonThree.pressedFor(LONG_PRESS) && lsrSwitch == false)
#endif
#ifndef LED_SR_Switch
    if (ButtonThree.pressedFor(LONG_PRESS))
#endif    
   {
     if (isPlaying())                                   // Bei laufender Wiedergabe
     {
        if (!mySettings.invertVolumeButtons)            // wenn Funktion der Vol-Tasten nicht getauscht
        {
          longPressVol = true;                          // VolÄnderung durch longPress 3 und 5 Tastenmodus
          volumeDownButton();                           // Leisertaste
        }
        else                                            // wenn Funktion der Vol-Tasten getauscht
        {
        #ifndef FIVEBUTTONS
         previousButton();                              // Track zurück 3 Tastenmodus durch longpress
        #endif
        #ifdef FIVEBUTTONS
         JumpBackw();                                   // Sprung rückwärts 5 Tastenmodus durch longpress
        #endif
        }
     }
     else                                               // wenn keine Wiedergabe läuft
       {
        if (mySettings.invertVolumeButtons)             // wenn Funktion der Vol-Tasten getauscht
        {
        #ifndef FIVEBUTTONS
        playShortCut(PrevLeiserButton);                 // Shortcut spielen Zurück/Leiser-Taste
        #endif
        #ifdef FIVEBUTTONS
        playShortCut(PrevButton);                       // Shortcut spielen Zurück-Taste
        #endif
       }
        else                                            // wenn Funktion der Vol-Tasten nicht getauscht
       {
        #ifndef FIVEBUTTONS                             // 3 Tasten und Matrix
        playShortCut(PrevLeiserButton);                 // Shortcut spielen Zurück/Leiser-Taste
        #endif
        #ifdef FIVEBUTTONS                              // 5 Tasten
        playShortCut(LeiserButton);                     // Shortcut spielen Leiser-Taste
        #endif
       }
      }
      ignoreButtonThree = true;                         // Taste3 übergehen

   }                                                    // Ende longpress
    // ---------------- ShortPress -------------------------------------        
    else if (ButtonThree.wasReleased())                 // Wenn Taste3 betätigt wurde (shortpress)
    {
      mp3error = false;                                 // Rücksetzen Marker mp3error
      if (!ignoreButtonThree)                           // Wenn Taste3 ausgewertet werden soll
      {
        if (!mySettings.invertVolumeButtons)            // Wenn Funktion der Vol Tasten nicht getauscht
        {
  #ifndef FIVEBUTTONS       
          previousButton();                             // Zurück Taste kurzer Tastendruck 3 Tastenmodus
 #endif
 #ifdef FIVEBUTTONS       
         volumeDownButton();                            // Leiser Taste 5 Tastenmodus
         longPressVol = false;                          // schrittweise VolÄnderung durch kurzen Tastendruck
 #endif       
        }
        else                                            // wenn Funktion der Vol Tasten getauscht
        {
#ifndef FIVEBUTTONS
          volumeDownButton();                           // Leiser Taste 3 Tastenmodus
          longPressVol = false;                         // schrittweise VolÄnderung durch kurzen Tastendruck
#endif
#ifdef FIVEBUTTONS
         previousButton();                              // Zurück Taste kurzer Tastendruck 5 Tastenmodus
#endif
        }
      }
      ignoreButtonThree = false;                        // Taste3 wieder auswerten
    }                                                   // Ende shortpress
    // *********** Ende Taste 3 (Zurück/Vol -) ********************************************

    // ********** 5 Tasten-Modus ***********************************************

#ifdef FIVEBUTTONS                              // 5 Tasten-Modus

    // ************ Taste 4 (Vol+/Vor)**************************************
    // ---------------- LongPress -------------------------------------
    if (ButtonFour.pressedFor(LONG_PRESS))
   
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Vol-Tasten getauscht
        {
          longPressVol = true;                  // VolÄnderung durch longPress
          volumeUpButton();                     // Lauter Taste
        }
       else                                     // wenn Funktion der Vol-Tasten nicht getauscht
        {                                       
           JumpForw();                          // Titelsprung Vorwärts bei longpress im 5 Tastenmodus
        }
      }
      else                                      // wenn keine Wiedergabe
      {
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Vol-Tasten getauscht 
        {
        #ifdef FIVEBUTTONS                      // 5 Tasten
        playShortCut(LauterButton);             // Shortcut spielen Lauter-Taste
        #endif
        }
        else                                    // wenn Funktion der Vol-Tasten nicht getauscht 
        {
        #ifdef FIVEBUTTONS                      // 5 Tasten
        playShortCut(NextButton);               // Shortcut spielen Weiter-Taste
        #endif  
        }
      }
      ignoreButtonFour = true;                  // Taste4 übergehen

    }                                           // Ende longPress
    // ---------------- ShortPress -------------------------------------            
    else if (ButtonFour.wasReleased())          // wenn Taste4  betätigt wurde (shortpress)
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      if (!ignoreButtonFour)                    // Wenn Taste ausgewertet werden soll
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Vol Tasten  getauscht
        {
          volumeUpButton();                     // Lauter-Taste
          longPressVol = false;                 // schrittweise VolÄnderung durch kurzen Tastendruck
        }
        else                                    // wenn Funktion der Vol Tasten nicht getauscht
        {
          nextButton();                         // Next - Taste
        }
      }
      
      ignoreButtonFour = false;                 // Taste4 wieder auswerten
    }                                           // Ende shortpress

    // ************ Taste 5 (Vol-/Zurück)************************************
    // ---------------- LongPress -------------------------------------    
   if (ButtonFive.pressedFor(LONG_PRESS))
   
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Vol-Tasten getauscht
        {
          longPressVol = true;                  // VolÄnderung durch longPress
          volumeDownButton();                   // Leiser Taste
        }
        else                                    // wenn Funktion der Vol-Tasten nicht getauscht
        {                                       
          JumpBackw();                          // Sprung rückwärts 5 Tastenmodus durch longpress
        }
      }
      else                                      // wenn keine Wiedergabe
      {
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Vol-Tasten getauscht 
        {
        #ifdef FIVEBUTTONS                      // 5 Tasten
        playShortCut(LeiserButton);             // Shortcut spielen Leiser-Taste
        #endif
        }
        else                                    // wenn Funktion der Vol-Tasten nicht getauscht 
        {
        #ifdef FIVEBUTTONS                      // 5 Tasten
        playShortCut(PrevButton);               // Shortcut spielen Zurück-Taste
        #endif  
        }
      }
      ignoreButtonFive = true;                  // Leiser Taste übergehen
    // ---------------- ShortPress -------------------------------------    
    }                                           // Ende longPress   
    else if (ButtonFive.wasReleased())          // Taste wurde betätigt (shortpress)
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      if (!ignoreButtonFive)                    // Wenn Taste ausgewertet werden soll
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Vol Tasten  getauscht
        {
          volumeDownButton();                   // Leiser-Taste
          longPressVol = false;                 // schrittweise VolÄnderung durch kurzen Tastendruck
        }
        else                                    // wenn Funktion der Vol Tasten nicht getauscht
        {
          previousButton();                     // Zurück - Taste
        }
      }
      
      ignoreButtonFive = false;                 // Taste wieder auswerten   
    }                                           // Ende shortpress
#endif

  }
  // ******************* Ende der Buttons ***********************************

  // ************** RFID-Reader - check ob Karte aufgelegt ******************

  while (!mfrc522.PICC_IsNewCardPresent());           // bleibe in der Schleife, Solange keine neue Karte aufgelegt

  // *************** RFID Karte wurde aufgelegt ************************

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
// ************ Main LOOP ENDE *************************************************
// *****************************************************************************

// =============================================================================
// ***************** Hilfsroutinen *********************************************

////////////////////// Dump Byte Array /////////////////////////////////////////

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

// ====================================================================================================================

/*

      Meine Änderungen ( Teilweise über " #define " wähl- oder abwählbar)
    ====================================================================================================
    - Auswahlmöglichkeit für die Nutzung der Software auf dem AiO Board, oder dem Tonuino aus Einzelkomponenten (TonUINO Classic)   - (AiO und TonUINO Classic)
    - Integration der Hilfsroutine für den EEPROM der AiO Platine und Codeanpassung                                                 - (nur für AiO)

    - Das Buttonboard 12 Tasten wurde integriert. Durch #define Buttonboard aktivierbar.                                           - (AiO, Classic in Arbeit)
      Die 9 Tasten werden über das Adminmenü mit Shortcuts belegt.
    - Bei Ausgabe eines Fehlers des Df-Players wird ein Magenta Blinksignal der LED-Animation                                      - (AiO und TonUINO Classic)
      aktiviert, unabhängig ob die LED-Anim eingeschaltet oder ausgeschaltet ist. Quittierung
      über Druck der Play/Pause-Taste. Kann der Df-Player den nächst folgenden Track der Queue abspielen,
      wird dieser abgespielt und der Fehler zurückgesetzt. 
      Ist keine weitere Wiedergabe möglich wird der Standbytimer aktiviert zum Ausschalten.
    - LED Animation umgestaltet nach @atomphil. Weichere und fließendere Animation.                                                - (AiO und TonUINO Classic)
    - 5 Tastenfunktion Shortpress und Longpress für alle Tasten. Shortcuts für alle Tasten.                                        - (AiO und TonUINO Classic) 
        Vol-Tasten - Shortpress schrittweise Vol-Änderung, Longpress continuirliche Vol-änderung.   
        Vor-Zurück Tasten - Shortpress -> 1 Titel vor oder zurück,Longpress -> Sprung mehrerer Titel vor oder zurück.
        Die Anzahl der zu überspringenden Titel ist in den defines voreinstellbar. 
        Titel der einzelnen Sprünge werden kurz angespielt.
    - Manuelle Abbrüche im Adminmenü überarbeitet, zum sauberen Ausstieg aus allen Untermenüs.                                      - (AiO und TonUINO Classic)
    - Änderung der Geschwindigkeit der Lautstärkeeinstellung über longPress der Laustärketasten                                     - (AiO und TonUINO Classic)
      Die Veränderung der Geschw erfolgt nicht mehr über ein delay, sondern über einen Counter.
      Dadurch kann die Geschw bei den Defines am Scetchanfang festgelegt werden. 
      Der Durchlauf der Mainloop wird durch die delays nicht mehr gebremst.
    - Management der Batteriemessung abgeschlossen.                                                                                 - (AiO und TonUINO Classic)
      Glättung der Messwerte durch Mittelwertbildung über 60 Messungen in einer Minute, AiO                                         - (AiO)
      Glättung der Messwerte durch Mittelwertbildung über 10 Messungen in einer Minute, Classic                                     - (TonUINO Classic)
    - Abschaltung über MOSFET oder Pololu-Switch, ShutDownPin - Anpassbar über defines ,Low oder High aktiv                         - (AiO und TonUINO Classic)
    - Der Powerdown Impuls wird als Impulsfolge HIGH-LOW-HIGH ausgeführt zur Abschaltung über MosFet oder Pololu-Switch             - (nur TonUINO-Classic)
    - Unterstützung USB-Stick als Speichermedium                                                                                    - (nur TonUINO-Classic)
    - USB-Powerschaltung über MOSFET - UsbPowerPin - High aktiv                                                                     - (nur TonUINO-Classic)
    - Animation mit LED-RGB-Ring, Ein- und Ausschaltbar über langen Druck Up + Down                                                 - (AiO und TonUINO Classic)
    - StandBy Timer auf 5 min voreingestellt und aktiviert als Grundeinstellung.                                                    - (AiO und TonUINO Classic)
    - Sleepmodus, Ausfaden der Lautstärke über die letzten 20 Sekunden. Standbytimer schaltet danach sofort aus.                    - (AiO und TonUINO Classic)
    - Sleepmodus, Neue Karte und Tasten ausser Play-Pause und Lauter/Leiser bis zum Ausschalten gesperrt                            - (AiO und TonUINO Classic)
    - Abschaltung der LED-Animation über Standbytimer zur Abschaltung Powerbank Software-only                                       - (nur TonUINO Classic)
    - Verzögerte Zuschaltung des Lautsprechers beim Einschalten, (Classic über MOSFET) (Unterdrückung Einschaltgeräusch)            - (AiO und TonUINO Classic)
    - Lautsprecher wird bei angeschlossenem Kopfhörer über Software abgeschaltet. Für AiO nur durch Änderung der Platine möglich!   - (nur TonUINO Classic)
      Die originale Abschaltung bei der AiO erfolgt über die Kopfhörerbuchse (Amp wird direkt abgeschaltet)
    - Die Pegel des Kopfhörer Sensors können über #define KHSensLOW umgestellt werden. LOW oder HIGH aktiv.                         - (nur TonUINO Classic)
    - Lautstärkeänderung bei Einstellung über long press button, Geschwindigkeit in den defines festlegbar.                         - (AiO und TonUINO Classic)
    - Menülautstärke kann unabhängig von zuletzt eingestellter Lautstärke auf Startlautstärke oder Festwert gesetzt werden          - (AiO und TonUINO Classic)
    - Reihenfolge der Funktionen im Adminmenü geändert, Ordner mp3 auf der SD Karte muss angepasst werden !!!                       - (AiO und TonUINO Classic)
    - Die Auswahloptionen im Adminmenü werden jetzt umlaufend durchgeschaltet.                                                      - (AiO und TonUINO Classic)
      D.h. ist die höchste Option erreicht, wird anschließend zu Option 1 weitergeschaltet. 
      In Rückwärtsrichtung von 1 zu höchster Option.
    - Bei der Ordnerauswahl werden nur noch die vorhandenen Ordner berücksichtigt. ( Funktioniert nicht mit allen DfMini Playern)   - (AiO und TonUINO Classic)
    - Rechenaufgabe und PIN Eingabe aus Schutzfunktion Adminmenü entfernt                                                           - (AiO und TonUINO Classic)
    - Feedback beim Beenden des Admin-Menues                                                                                        - (AiO und TonUINO Classic)
    - Feedback beim Schreiben von Karten und Konfigurieren der Shortcuts                                                            - (AiO und TonUINO Classic)
    - Feedback auch beim Konfigurieren "Neue Karte" ohne Benutzung des Adminmenüs                                                   - (AiO und TonUINO Classic)
    - Jingle beim Entfernen der Modifikationskarten, Funktion beim Auflegen wird angesagt                                           - (AiO und TonUINO Classic)
    - Hörbuchmodus, Fortschritt wird bei langem Druck der Pausetaste auf Track 1 zurückgesetzt                                      - (AiO und TonUINO Classic)
    - Letzte gespielte Karte wird gespeichert und als Shortcut auf die Play-Taste gelegt                                            - (AiO und TonUINO Classic)
      Im Adminmenü wird die Konfiguration des Shortcuts für die PlayTaste ausgeblendet, da diese mit lastcard belegt wird.
    - TonUINO als Wecker. Ein Uhrenmodul schaltet den TonUINO ein und gibt ein Signal auf Analogpin A6                              - (AiO und TonUINO Classic)
      das das Abspielen eines Shortcuts als Wecksound startet. Konfiguration des Weckershortcuts im Adminmenü integriert.
    - Wecker wird auch bei angeschlossenem Kopfhörer (Lautsprecher Aus), über den Lautsprecher abgespielt.                          - (nur TonUINO Classic)
      Für die AiO ist diese Funktion nur nach einer Änderung an der Platine (Trennung einer Verbindung) nutzbar.                      (AiO nach Hardwareänderung)
    - Empfindlichkeit des RFID Lesers kann in der Initialisierung ( "mfrc522.PCD_Init()")geändert werden. Hier auf mittel gesetzt.  - (AiO und TonUINO Classic)
    - Alle Abspielmodi arbeiten jetzt mit einer Queue (Playlist)- "Always queue".                                                   - (AiO und TonUINO Classic)
    - Die Queue in den Modi Party beginnen jetzt bei jedem Start mit einem anderen zufälligen Track.                                - (AiO und TonUINO Classic)
    - Die Queue in den Modi Party werden vor Neustart am Ende neu gemischt.                                                         - (AiO und TonUINO Classic)
    - Die Fehlercodes des DF-Players werden im seriellen Monitor im Klartext angezeigt.                                             - (AiO und TonUINO Classic)
    - Die Batterie bzw. Akkuspannung kann überwacht werden. Bei Erreichen einer ersten Schwelle wird alle 60 sekunden               - (AiO und TonUINO Classic)
      eine Warnung ausgegeben. Bei Erreichen der Entladeschlusspannung wird eine Warnung ausgegeben
      und der Tonuino mit Ausfaden der Lautstärke über 20 Sekunden ausgeschaltet.
    - Die Messung der Batteriespannung wird durch Nutzung der internen Referenzspannung genauer.                                    - (AiO und TonUINO Classic)
    - Weitestgehende Kürzung der Ausgaben über den Ser-Monitor zur Einsparung von Programmspeicher                                  - (AiO und TonUINO Classic)
    - Debug Modus: (Konsole) Die Ausgaben auf den Seriellen Monitor können zur Einsparung von Speicherplatz                         - (AiO und TonUINO Classic)
      über die defines ausgeschaltet werden. Es werden nur die Meldungen beim Start angezeigt.
      Bei aktivierter LED-Animation wird diese im Debug-Modus deaktiviert, um Speicherplatz für die Ausgaben
      in der Konsole frei zu machen. (Ersparnis ca 20% Programmspeicher)

    ************** Bug Fixes **********************************************************
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
     - Bei der Abfrage ob die Funktion der LS-Tsten umgedreht werden soll, erfolgt der Wechsel immer wenn JA gewählt wird.
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
