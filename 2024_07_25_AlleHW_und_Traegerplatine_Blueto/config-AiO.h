#ifdef AiO

//      Die auf dieser Registerkarte aktivierten #defines sind nur für die AiO gültig.


// ========================== AiO == Boardeinstellungen ======================================================================
//    - Für die AiO Platine müssen folgende Einstellungen vorgenommen werden.
//      Die LGT8Fx Bibliotheken müssen in der IDE installiert sein !
//      Siehe folgender Link: https://www.leiterkartenpiraten.de/2020/11/21/die-arduino-ide-einrichten/
//      Für die Batteriemessung die modifizierten LGT8FX Bibliotheken mit Unterstützung des Analogpin 10 installieren.
//      Links: https://github.com/jayzakk/lgt8fx/blob/1b0f5c53d1cd24ae76d14d37f0f526694a612431/lgt8f/variants/lgt8fx8p/pins_arduino.h
//             https://github.com/jayzakk/lgt8fx/commit/1b0f5c53d1cd24ae76d14d37f0f526694a612431
//      Ab Version 2.0.2 ist die Modifikation schon im Boardpackage enthalten.

//      Boardtyp :      LGT8F328 unter Logic green Arduino AVR Compatible Boards auswählen
//      Arduino as ISP: Default (64)
//      Clock:          16 MHz
//      Clock Source:   External (assumes 32MHz crystal)
//      Variant:        328P-LQFP (e.g. MiniEVB nano-style and WAVGAT)
//      Korrekten COM Port
//      Um den korrekten COM Port auswählen zu können, muss die AiO angeschlossen sein. 
//      Der COM Port kann sich unterscheiden (siehe Gerätemanager).
// ==============================================================================================================================

// ******************** Auswahl der Optionen und Zusatzfunktionen für die AiO ****************************************

// uncomment or comment the " #define .... "  to enable or disable the additional function

// --------------------- Debug Modus --- AiO ------------------------------------------------------------------------
//#define Konsole 
// Zum Einsparen von Programmspeicher wird die vollständige Ausgabe auf den Seriellen Monitor nur bei Freigabe ausgeführt.

// Hardwareabhängige Zusatzdefinitionen für den Debug Modus (Hier nichts ändern)
#ifdef Konsole                // Bei aktiver LED-Animation, wird diese deaktiviert, um den Programmspeicher
  #ifdef LED_SR               // für die Konsolenausgabe frei zu machen.
  #undef LED_SR
  #ifdef CandleLight
  #undef CandleLight
  #ifdef LED_SR_Switch
  #undef LED_SR_Switch
  #endif
  #endif
  #endif
#endif

// ---------------------- Modifikationskarte - Freigabe des Zugriffs auf die SD-Karte über USB -----------------------------
//#define USB_Zugriff_SD_Karte 
// Der Zugriff auf die SD-Karte über die USB-Schnittstelle wird mit einer Modifikationskarte freigegeben.
// Tasten und Karten sind in diesem Modifier gesperrt.
// Der StandbyTimer wird auf 30 min gesetzt.
// Nach Deaktivierung des Modifier wird der StandbyTimer wieder auf 5 min zurückgesetzt.
                                                              
// -----------Jackdetekt- Kopfhörer ------ Nutzung mit der AiO bis V1.2 nur nach Hardwareänderung möglich ---
#define Jackdetekt 

// Jackdetekt Kopfhörer - AiO ---- nur mit Hardwareänderung --------------------------------
// Bei gestecktem Kopfhörer wird das Jackdetekt-Signal ausgewertet und der Verstärker nur über die Software stummgeschaltet.
// Die direkte Stummschaltung des Verstärkers über die Kopfhörerbuchse ist nicht mehr aktiv.
// (Über Jumper kann die Originalfunktion wieder aktiviert werden)
// Nur aktivieren wenn Hardwareänderung für Jackdetekt auf der AiO Platine durchgeführt wurde. Ohne HW-Änderung in Kommentar setzen !!!
// Zusätzlicht kann die Lautstärke für Lautsprecher und Kopfhörer getrennt eingestellt werden.
// Die jeweiligen Lautstärkeeinstellungen bleiben bis zum Ausschalten des TonUINO gespeichert.
// Im Adminmenü können die Lautstärke Voreinstellungen für LSP und KH getrennt festgelegt werden. 


// Hardwareabhängige Zusatzdefinitionen für Jackdetekt (Hier nichts ändern)
#ifdef Jackdetekt             // Wenn Jackdetekt oder JackdetektAiO aktiviert sind
#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
    #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
      #ifndef SpkOnOff        // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
        #define SpkOnOff      
      #endif                  
    #endif                    
#endif


// ------------------- Überwachung der Batteriespannung --------------------------------------------------------------------
#define BatteryCheck 
// Bei AiO bis V1.2 muss die Lötbrücke SJ1 geschlossen werden und das modifizierte BSP LGT8FX mit Unterstützung des AnalogPin A10 installiert werden.
// (siehe obiger Link)
// Hardwareänderung AiO,- auf R17 einen 220 kOhm smd Widerstand huckepack auflöten, 
// oder R17 durch einen 65 kOhm smd Widerstand ersetzen.(Erweiterter Spannungsmessbereich bis 5 V)

#define geaend_Sp_Teiler  
// Wenn der Spannungsteiler für die Batteriemessung wie oben beschrieben geändert wurde, 
// das #define durch entfernen der Kommentarzeichen aktivieren

//#define highResolution  
// Zur Verwendung von 10-Bit Auflösung das #define in Kommentar setzen. Genauigkeit der Batteriemessung ist etwas geringer.
// Wichtiger Hinweis !!!!! 
// Bei Anschluss der AiOPUS oder AiO über die USB-Buchse wird in der Konsole nicht die richtige Akkuspannung angezeigt.
// Wenn diese über die Konsole korrekt angezeigt werden soll (nicht im Ladebetrieb),
// muss der PC über einen FTDI-Adapter (Jumper auf 3,3V) an rx/tx und Ground am Erweiterungsport der AiO Platine angeschlossen werden.
//   ___________________________________________________________________________________
// Festlegung der Spannungswerte für die Batterieüberwachung. Kann hier angepasst werden.

 #ifdef BatteryCheck               // Wenn die Batteriespannungsüberwachung aktiviert ist:
 //                                   Bei Unterschreiten des BatLow - Wertes wird eine Warnung ausgegeben.
 //                                   Bei Erreichen des BatEmpty - Wertes wird der Tonuino ausgeschaltet.
 //                                   Vor Abschalten erfolgt ein Ausfaden der Lautstärke über 20 Sekunden.
 //                                   Davon unabhängig schaltet die AiO und AiOPLUS bei Unterschreiten von 2,8 V über Hardware aus.

 // Anpassung der Anzeige an die tatsächliche Batteriespannung durch Korrekturwert. Hier nichts ändern !
 #ifdef geaend_Sp_Teiler
  #ifdef highResolution
  const float correction = 2.495 ; // Korrekturwert für Spannungsteiler mit Änderung des Spannungsteilers (R17) bei 12 Bit Auflösung
  #endif
  #ifndef highResolution
  const float correction = 2.501 ; // Korrekturwert für Spannungsteiler mit Änderung des Spannungsteilers (R17) bei 10 Bit Auflösung
  #endif
 #endif
 #ifndef geaend_Sp_Teiler
  #ifdef highResolution
  const float correction = 2.052 ; // Korrekturwert für Spannungsteiler ohne Änderung des Spannungsteilers bei 12 Bit Auflösung
  #endif
  #ifndef highResolution
  const float correction = 2.058 ; // Korrekturwert für Spannungsteiler ohne Änderung des Spannungsteilers bei 10 Bit Auflösung
  #endif
 #endif

 // --------------------------------------- Akkutyp festlegen --------------------------------------------------------
 // Die AiO und AiOPLUS Platinen sind standardmäßig für den Betrieb mit LiFePO4 ausgelegt,
 // können aber über Lötbrücken auf LiPo Betrieb geändert werden.
                                  
 #define LiFePo                    // Lithium-Eisen-Phosphat-Akku ( LiFePO4) Standard für AiO und AiOPLUS
 
 //#define LiPo                     // Lithium-Ion oder Lithium-Polymer Akku (Li oder LiPo)

 #ifdef LiFePo
   const float BatLow = 2.95 ;      // Spannungswert für Warnung "Batterie schwach"
   const float BatEmpty = 2.90 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif

 #ifdef LiPo
   const float BatLow = 3.2 ;      // Spannungswert für Warnung "Batterie schwach"
   const float BatEmpty = 3.0 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif
 



#endif  // Ende #ifdef Batterycheck

// ------------ Max Matrixwert des Buttonboards -Wert nicht verändern ------------------------------------------------------------------
#ifdef Buttonboard
 uint16_t mapMax = 4064;
#endif

// ------------ Logischer Wert für Lautsprecher on oder off -(Wert nicht verändern) ---------------------------------------------------
 uint8_t On = 0;    // LOW-Pegel
 uint8_t Off = 1;   // HIGH-Pegel
//**********************************************************************************

//******************* Definitionen der Pins für AiO ********************************
//  Boardbeschreibung des AiO Boards Pin-Belegung und Zuordnung

//  D5, A6 und A7 sind auf den extension port geschaltet.
//  D6 ist zum button breakout board geschaltet (beschriftet mit WS(D6)).
//  D9 (RST), D10 (CS/SDA), D11 (MOSI), D12 (MISO) und D13 (SCK) sind zum nfc breakout board geschaltet.
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
//                                   control pin of the external sd card access (HIGH = enabled, LOW = disabled)
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
//                                   aufgetrennt wird und das Signal für den Sensorpin genutzt wird.
#ifdef LED_SR
 #define LedPin 6                 // Daten für Neopixel-LED-Ring (ButtonBreakout Board "WS" )
#endif

#define ShutDownPin 7             // Ein/Ausschaltsignal
//                                   control pin used to power the system (HIGH = power on, LOW = power off)
#ifdef SpkOnOff
 #define SpkOnPin 8               // Verstärker Ein/Ausschalten
#endif                            // control pin to enable/disable the onboard amp (HIGH = amp off, LOW = amp on)

#define RstPin 9                  // MFRC 522 -RST
#define CS_Pin 10                 // MFRC 522 -SDA (CS)

#endif
