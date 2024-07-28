#ifdef EVERY

//      Die auf dieser Registerkarte aktivierten #defines sind nur für die Klassikversion mit nano EVery  gültig.


//   ==================== TonUINO - Klassik mit Nano EVERY == Boardeinstellungen ===========================================
//    Nutzung in der Version Klassik mit Einzelkomponenten, und mit Nano EVERY.
//  - Für die Nutzung des Nano EVERY müssen in der Boardverwaltung die Arduino megaAVRboards installiert und ausgewählt werden.
//  - als Board den Arduino Nano Every auswählen
//  - Registeremulaton None(ATMEGA 4809) auswählen.
//  - Für die Nutzung von HardwareSerial mit dem DF-Player die TX/RX Pins zum DF-Player umlegen auf D0 und D1
//    Bei der Traegerplatine werden die Pins mit dem Schiebeschater in Position EVERY umgeschaltet.
//    In den Defines das Hardwareserial durch entfernen der Kommentarzeichen aktivieren.
//  - Softwareserial ist aber auch noch nutzbar. Dazu die ursprüngliche Pinbelegung lassen und Hardwareserial nicht aktivieren.
//  ===========================================================================================================================

// ********************* Anpassung bei Verwendung der TLE-Trägerplatine ****************************************
//  Achtung nicht verwechseln mit der Klassik-Platine von LeiterkartenPiraten
//  Die Anpassungen betreffen nur die TLE-Trägerplatine.
//  
 #define Traegerplatine



// ********************* Anpassung an DFPlayer von DF-ROBOT mit LISP3 Chip *****************************************
// #define DfPlayer_spez 

// Nutzung eines DF-Players, der auch bei Adverts ein EndOfTrack Event ausgibt 
// Einige DF-Player geben beim Abspielen von Advert-Tracks ein EndOfTrack Event aus.
// Das führt dazu, dass nach dem Abspielen von Adverts, anschließend Tracks übersprungen werden.
// Bei Verwendung eines solchen Players z.B. DFROBOT mit LISP 3 Chip das #define durch Entfernen 
// der Kommentarzeichen aktivieren.


//------------------------------------------------------
// Variable zur Kennzeichnung ob Advert abgespielt wird. Hier nichts ändern !
#ifdef DfPlayer_spez
bool AdvPlaying = false; // Advert wird abgespielt, Voreinstellung Nein
#endif
//-----------------------------------------------------
#ifndef CountFolders
 #define ZaehleOrdner          // Für DF-Player, die kein CountFolders unterstützen können die Ordner einzeln gezählt
//                                werden.                             
#endif                         // Das Initialisieren des Tonuino dauert dann ca. 1 bis 2 Sekunden je Ordner länger.

// ******************** Auswahl der Optionen und Zusatzfunktionen  für Klassik mit Arduino Every ******************************

// uncomment or comment the " #define .... "  to enable or disable the additional function

// ---------------------- Debug Modus ----------------------------------------------------------------------------------
#define Konsole               // Zum Einsparen von Programmspeicher wird die vollständige Ausgabe
//                               auf den Seriellen Monitor nur bei Freigabe ausgeführt.
//                               Bei aktiver LED-Animation, wird diese deaktiviert, um den Programmspeicher
//                               für die Konsolenausgabe frei zu machen.

// ---------------------- Abschaltung über Hardware - Pololu-Switch, MosFet, u.s.w. -- Klassik mit EVERY ----------------
#define HW_PowerOff              // Abschaltung über Hardware, wie Mosfet oder Pololu-Switch
//#define PololuSwitch           // Abschaltung über PololuSwitch HIGH schaltet aus
// -----------------------------------------
// Hardwareabhängige defines nicht verändern  
  #ifdef HW_PowerOff            // Festlegen des Ausschalt-Signals, (HIGH oder LOW)
   
   #ifndef PololuSwitch       // ohne PololuSwitch
    #define LowActive         // LOW Pegel schaltet den TonUINO aus.
   #endif
  
  #endif                       


// ---------------------- Kopfhörer --- TonUINO Klassik mit Every-------------------------------------------
#define Jackdetekt         // Jackdetekt mit Nutzung Kopfhörer-Buchse oder Platine mit Jackdetekt.
//                               Das ermöglicht zusätzlich die Lautstärken für Lautsprecher und Kopfhörer
//                               getrennt einzustellen. Die jeweiligen Lautstärkeeinstellungen bleiben 
//                               bis zum Ausschalten des TonUINO gespeichert.
//                               Im Adminmenü können die Lautstärke Voreinstellungen für LSP und KH getrennt
//                               festgelegt und dauerhaft abgespeichert werden. 


#ifdef Jackdetekt              // Wenn Jackdetekt aktiviert ist

// -------------------- Festlegen des Sensorpegels für den Kophöreranschluss ---------------------------------
//#define KHSensLOW             // Der Sensorpegel für den Kopfhöreranschluss ist bei eingestecktem Kopfhörer LOW
//                               Wenn der Sensorpegel bei eingestecktem Kopfhörer HIGH ist, #define KHSensLOW deaktivieren

#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
    #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
      #ifndef SpkOnOff        // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
        #define SpkOnOff      // Hardwareerweiterung erforderlich: (TonUINO Klassik, - Abschaltung des Lautsprechers über MOS-FET's)
      #endif                  
    #endif                    
#endif
#ifdef Traegerplatine         // Die Traegerplatine benötigt ein HIGH Signal für Jackdetekt
 #ifdef KHSensLOW             // eine eventuelle LOW Definition wird deaktiviert
  #undef KHSensLOW
 #endif
#endif
// ------------------- Überwachung der Batteriespannung ---------------------------------------------------------------------------
#define BatteryCheck     // Kann auf der LKP Klassikplatine nur im 3 Tasten-Modus verwendet werden, da AnalogPin A4 im 5 Tastenmodus belegt ist.
   #ifdef FIVEBUTTONS     // Wenn ein anderer Analogpin frei zur Nutzung ist, kann dieser für BatteryCheck verwendet werden.
    #ifndef Traegerplatine// Vor den BatteryCheckPin einen 100kOhm Widerstand in Reihe schalten (Klassik).
    #undef BatteryCheck   // Bei der Traegerplatine wird Analogpin 5 Für die Batterieüberwachung benutzt.
    #endif                
  #endif                 
  
   // Wird bei Verwendung der Traegerplatine eine Batteriespannung größer als 5V verwendet muss der Spannungsteiler für die
   // Batteriekontrolle und der Korrekturwert angepasst werden. 
   // Ab Version 2.2 sind die Spannungsteiler über Lötjumper an die verschiedenen Batteriespannungen konfigurierbar.
   // Warn und Abschaltspannung an die verwendete Batterie anpassen.
   // ___________________________________________________________________________________

  // Festlegung der Spannungswerte für die Batterieüberwachung. Kann hier angepasst werden.

 #ifdef BatteryCheck               // Die Akkuspannung wird überwacht
  //                                  Hardwareerweiterung erforderlich (Batteriespannung muss bei ausgeschaltetem Tonuino
  //                                  vom Eingang des Arduino getrennt sein. (Nur TonUINO Klassik,MosFet oder Relais)
  //                                  Bei Unterschreiten des BatLow - Wertes wird eine Warnung ausgegeben
  //                                  Bei Erreichen des BatEmpty - Wertes wird der Tonuino ausgeschaltet.
  //                                  Vor Abschalten erfolgt ein Ausfaden der Lautstärke über 20 Sekunden.


                                   
  // --------------------------------------- Akkutyp festlegen --------------------------------------------------------
                                   
 // #define LiFePo                    // Lithium-Eisen-Phosphat-Akku ( LiFePO4) 
 
 #define LiPo                     // Lithium-Ion oder Lithium-Polymer Akku (Li oder LiPo)

 //#define andererAkku              // Anderer Akku bei Nutzung der Traegerplatine Max 10 - 12V

 #ifdef LiFePo
  const float BatLow = 2.95 ;      // Spannungswert für Warnung
  const float BatEmpty = 2.90 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif

 #ifdef LiPo
   const float BatLow = 3.2 ;      // Spannungswert für Warnung "Batterie schwach"
   const float BatEmpty = 3.0 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif

 #ifdef andererAkku                // Spannungswerte an verwendeten Akku hier anpassen
   const float BatLow = 9.9 ;      // Spannungswert für Warnung "Batterie schwach"
   const float BatEmpty = 7.0 ;    // Spannungswert für automatische Abschaltung über Software ShutDown.
 #endif

 // -------------------------------- TonUINO Klassik mit Nano Every -------------------------------------- 
 //                                  Batteriespannung über 100kOhm/100kOhm Spannungsteiler an BattCheckPin anlegen
 #ifndef andererAkku
  const float correction = 2.2 ;   // Korrekturwert für Spannungsteiler (Anpassung der Anzeige an die tatsächliche Batteriespannung)
 #endif
 #ifdef andererAkku                // Korrekturwert an den anderen Akku hier anpassen
  const float correction = 5 ;     // Korrekturwert für Spannungsteiler bei anderem Akku (Anpassung der Anzeige an die tatsächliche Batteriespannung)
 #endif
  
#endif  // Ende #ifdef Batterycheck
// ------------------------------------------------------------------------------------------------------------------------------------
#define Hardwareserial         // Empfohlen !!! Nutzung von HardwareSerial (serial1) anstatt SoftSerial. 
//                                Pins müssen umgelegt werden.    D0 RX, D1 TX  
  #ifdef Traegerplatine        // Bei der Traegerplatine wird zur Pinumschaltung der Schiebeschalter in Position EVERY gestellt.
    #ifndef Hardwareserial
     #define Hardwareserial
    #endif
  #endif

// ---------------------- Bluetooth mit Modifikationskarte einschalten und pairen ------------
#ifdef Hardwareserial     // Bluetoothsteuerung über ModKarte nur bei Hardwareserial DF-Player möglich
 #define Bluetooth
#endif
// ---------------------- Pairing mit Longpress Pausetaste starten ----------------------
#ifdef Bluetooth          // Wenn Bluetooth define aktiv
 #define PT-Pairing          // Bei laufender Wiedergabe erfolgt durch Longpress derPlay/Pausetaste ein Pairing .
#endif                    // Die Funktion Tracknummer ansagen bei Longpress bleibt erhalten.
//                           Das Pairing wird zusätzlich ausgeführt

// ------------ Max Matrixwert des Buttonboards ------------------------------------------------------------------------------
#ifdef Buttonboard
 uint16_t mapMax = 790;
#endif

// ------------ Logischer Wert für Lautsprecher on oder off -(Wert nicht verändern) ---------------------------------------------------
uint8_t On = 1;        // HIGH-Pegel
uint8_t Off = 0;       // LOW-Pegel
 

// ***************************************************************************************************

//******************* Definitionen der Pins für TonUINO Klassik mit EVERY ****************************

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
#endif

// --------------- Mit 12-Buttonboard -----------------------------
#ifdef Buttonboard                 // 12 Tasten-Version mit Buttonboard
 #define ButtonPause A0            // Taste 1 - Play / Pause
 #define ButtonUp A1               // Taste 2 - Vor / Lauter
 #define ButtonDown A2             // Taste 3 - Zurück / Leiser
 #define Buttonmatrix A3           // Tastenmatrix 9 Tasten
#endif
// ---------------- Batterycheck -----------------------------------
#ifdef BatteryCheck               // Batterieüberwachung
 #define BatteryCheckPin A5      // Kontrollpin für Batterieüberwachung
#endif                            

// ---------------- Weckermodul ----------------------------------------
#ifdef Wecker
#define WeckerPin A6              // Eingangspin zum Abspielen Wecker-shortcut
#endif

// ---------------- RandomPin -----------------------------------------

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl

// ----------------- Digital-Pins -------------------------------------

#ifdef Bluetooth
#define BtOnPin 2                 // Schaltsignal für BT-ON
#define BtPairingPin 3            // Tastsignal für BT-Pairing
#endif

#define BusyPin 4                 // Auswertung des Busy Signals vom DF-Player
#define LedPin 5                  // Daten für Neopixel-LED-Ring

#ifdef SpkOnOff
#define SpkOnPin 6                // Schaltsignal Lautsprecher Ein/Aus
#endif

#ifdef HW_PowerOff
#define ShutDownPin 7             // Abschaltsignal für MosFet oder Polulo-Switch
#endif

#ifdef EarPhone
#define EarPhonePin 8            // Kontrollpin ob Kopfhörer angeschlossen ist (Jackdetekt)
#endif

#define RstPin 9                  // MFRC 522 -RST
#define CS_Pin 10                 // MFRC 522 -SDA (CS)


#endif

