#ifdef AiOPLUS

//      Die auf dieser Registerkarte aktivierten #defines sind nur für die AiO-plus gültig.


// ========================== AiOPLUS == Boardeinstellungen ==================================================
//    - Für die AiOPLUS Platine müssen folgende Einstellungen vorgenommen werden.
//      Die MegaCoreX Bibliotheken müssen in der IDE installiert sein !
//      Siehe folgender Link: https://mcudude.github.io/MegaCoreX/package_MCUdude_MegaCoreX_index.json
//    - Boardtyp :  ATmega4809
//    - Clock :     internal 16MHz
//    - BOD :       disabled,   Bei Platinen mit neuem Bootlader BOD:2,6V
//    - EEPROM :    retained 
//    - Pinout :    48 standard
//    - Reset Pin : reset
//    - Bootlader : Optiboot UART0 defaultpins
//    - Comport :   setzen (Abhängig vom Computer)
// =============================================================================================================

// ******************** Auswahl der Optionen und Zusatzfunktionen nur gültig für die AiO-Plus ***************************

// uncomment or comment the " #define .... "  to enable or disable the additional function

// ----------------------- Debug Modus ----------------------------------------------------------------------------------
#define Konsole   
// Zum Einsparen von Programmspeicher wird die vollständige Ausgabe auf den Seriellen Monitor nur bei Freigabe ausgeführt.
                              
// ---------------------- Modifikationskarte - Freigabe des Zugriffs auf die SD-Karte über USB ---------------------------
//#define USB_Zugriff_SD_Karte   
// Der Zugriff auf die SD-Karte über die USB-Schnittstelle wird mit einer Modifikationskarte freigegeben.
// Tasten und Karten sind in diesem Modifier gesperrt.
// Der StandbyTimer wird auf 30 min gesetzt.
// Nach Deaktivierung des Modifier wird der StandbyTimer wieder auf 5 min zurückgesetzt.
                               
// ---------------------- Jackdetekt Kopfhörer --------------------------------------------------------------------------
#define Jackdetekt
// Bei gestecktem Kopfhörer wird das Jackdetekt-Signal ausgewertet und der Verstärker über die Software stummgeschaltet.
// Das ermöglicht zusätzlich die Lautstärken für Lautsprecher und Kopfhörer getrennt einzustellen. 
// Die jeweiligen Lautstärkeeinstellungen bleiben bis zum Ausschalten des TonUINO gespeichert.
// Im Adminmenü können die Lautstärke Voreinstellungen für LSP und KH getrennt festgelegt werden. 

// Für Jackdetekt notwendige defines (Hier nichts ändern)
#ifdef Jackdetekt             // Wenn Jackdetekt oder JackdetektAiO aktiviert sind
#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
    #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
      #ifndef SpkOnOff        // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
        #define SpkOnOff      
      #endif                  
    #endif                    
#endif


// ------------------- Überwachung der Batteriespannung ---------------------------------------------------------------------------
#define BatteryCheck      
// Wichtiger Hinweis !!!!!
// Bei Anschluss der AiOPUS oder AiO über die USB-Buchse wird in der Konsole nicht die richtige Akkuspannung angezeigt.
// Wenn diese über die Konsole korrekt angezeigt werden soll (nicht im Ladebetrieb),
// muss der PC über einen FTDI-Adapter (Jumper auf 3,3V) an rx/tx und Ground am Erweiterungsport der AiO Platine angeschlossen werden.
// ___________________________________________________________________________________
// Festlegung der Spannungswerte für die Batterieüberwachung. Kann hier angepasst werden.

 #ifdef BatteryCheck               // Wenn die Überwachung der Batteriespannung aktiviert ist:
  //                                  Bei Unterschreiten des BatLow - Wertes wird eine Warnung ausgegeben
  //                                  Bei Erreichen des BatEmpty - Wertes wird der Tonuino ausgeschaltet.
  //                                  Vor Abschalten erfolgt ein Ausfaden der Lautstärke über 20 Sekunden.
  //                                  Davon unabhängig schaltet die AiO und AiOPLUS bei Unterschreiten von 2,8 V über Hardware aus.

 // --------------------------------------- Akkutyp festlegen --------------------------------------------------------
  // Die AiO und AiOPLUS Platinen sind standardmäßig für den Betrieb mit LiFePO4 ausgelegt,
  // können aber über Lötbrücken auf LiPo Betrieb geändert werden.
                                  
 #define LiFePo                    // Lithium-Eisen-Phosphat-Akku ( LiFePO4) Standard für AiO und AiOPLUS
 
 //#define LiPo                     // Lithium-Ion oder Lithium-Polymer Akku (Li oder LiPo)

 #ifdef LiFePo
  const float BatLow = 2.95 ;      // Spannungswert für Warnung
  const float BatEmpty = 2.90 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif

 #ifdef LiPo
   const float BatLow = 3.2 ;      // Spannungswert für Warnung "Batterie schwach"
   const float BatEmpty = 3.0 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif
 
  const float correction = 2.02 ;  // Korrekturwert für Spannungsteiler (Anpassung der Anzeige an die tatsächliche Batteriespannung)
    
#endif  // Ende #ifdef Batterycheck

// ------------- Hardwareserial --Hier nichts ändern! --------------------------------------------------------------------------------------------------------------------- 
#define Hardwareserial
// AiOPLUS verwendet Hardwareserial über (UART3) serial3  zum DF-Player
  

// ------------ Max Matrixwert des Buttonboards -(Wert nicht verändern) ---------------------------------------------------
#ifdef Buttonboard
 uint16_t mapMax = 790;
#endif

// ------------ Logischer Wert für Lautsprecher on oder off -(Wert nicht verändern) ---------------------------------------------------

uint8_t On = 0;     // LOW-Pegel
uint8_t Off = 1;    // HIGH-Pegel
 
// *************************************************************************************

//******************* Definitionen der Pins für AiOPLUS ********************************
//  Boardbeschreibung des AiO-PLUS Boards Pin-Belegung und Zuordnung für diesen Fork


//  D4 - MOSI, D5 - MISO, D6 - SCK, D7 -SS(SDA), und D11 - RST,  sind zum nfc breakout board geschaltet.
//  LED-controlPin = 18;                    ist zum button breakout board geschaltet (beschriftet mit WS)zur Steuerung der LED-Animation.
//  Die anderen Pins sind fest verdrahtet, siehe folgend: 
//   mp3SerialTxPin = 8;                    mp3 serial3 tx, geht zum rx pin des mp3 chip
//   mp3SerialRxPin = 9;                    mp3 serial3 rx, kommt vom tx pin des mp3 chip
//   busyPin = 13;                          checkt den Wiedergabestatus des mp3 chips (HIGH = not playing, LOW = playing)
//   onboardAmpControlPin = 19;             Steuerpin zum Ein und Ausschalten des onboard NF-Verstärkers (HIGH = Verstärker AUS, LOW = Verstärker EIN)
//   onboardSdAccessControlPin = 20;        Steuerpin für externen SD-Karten Zugriff (HIGH = enabled, LOW = disabled)
//   JackdetektPin = 21;                    Pin für Jackdetekt Kopfhörer, HIGH - KH gesteckt, LOW - Kopfhörer nicht gesteckt
//   powerControlPin = 27;                  Steuerpin zur Ein und Ausschaltung des Systems (HIGH = power on, LOW = power off)

//   Die Funktion der buttonPins ergibt sich aus dem Status der Inversion für die Tasten
//   button0Pin = A0;                      // play/pause/power on
//   button1Pin = A1;                      // prev (Zurück) oder vol- (Leiser)
//   button2Pin = A2;                      // next (Vor) oder vol+ (Lauter)
//   button3Pin = A3;                      // vol- (Leiser) oder prev (Zurück)
//   button4Pin = A4;                      // vol+ (Lauter) oder next (Vor)
//   BatteryCheckPin = A6;                 // Batteriespannungsüberwachung, Verbunden mit Spannungsteiler 100kOhm/100kOhm auf Vbatt/2 .
//   RandomPin = A7;                       // A7 wird nicht beschaltet und dient durch Auffangen von zufälligen Werten aus dem Umgebungsstörspektrum
//                                            der Erzeugung von Zufallswerten für die Randomfunktion

//  Die noch freien Pins stehen laut Boardbeschreibung für andere Funktionen frei zur Verfügung


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
#ifdef BatteryCheck               // Batterieüberwachung
 #define BatteryCheckPin A6       // Kontrollpin für Batterieüberwachung 
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl

#ifdef Wecker
 #define WeckerPin A11            // Eingangspin zum Abspielen Wecker-shortcut (Extension Board)
#endif

//---------------- Digital-Pins -------------------------------------
#define CS_Pin 7                  // MFRC 522 -SDA (CS, SS)
#define RstPin 11                 // MFRC 522 -RST

#define BusyPin 13                // Busy Signal vom DF-Player

#ifdef LED_SR
 #define LedPin 18                // Daten für Neopixel-LED-Ring (ButtonBreakout Board "WS" )
#endif

#ifdef SpkOnOff
 #define SpkOnPin 19              // Verstärker Ein/Ausschalten
#endif                            // control pin to enable/disable the onboard amp (HIGH = amp off, LOW = amp on)

#define Access_SD_Pin 20          // Pin zur Freigabe des SD-Kartenzugriffs über USB
//                                   control pin of the external sd card access (HIGH = enabled, LOW = disabled)
#ifdef EarPhone
 #define EarPhonePin 21           // Sensorpin, ob Kopfhörer angeschlossen (Jackdetect) 
#endif                            


#define ShutDownPin 27            // Ein/Ausschaltsignal
//                                   control pin used to power the system (HIGH = power on, LOW = power off)

//     Ende PIN Deklaration AiOPLUS


#endif
