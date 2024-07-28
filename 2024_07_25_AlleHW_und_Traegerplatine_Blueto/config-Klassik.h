#ifdef Klassik

//      Die auf dieser Registerkarte aktivierten #defines sind nur für die Klassik-Version gültig.


//   ======================= TonUINO - Klassik == Boardeinstellungen ================================================
//   - Für die Nutzung in der Version Klassik mit Einzelkomponenten, 
//     Nano 328P oder Nano 328P(Old Bootlader) je nach Version auswählen.
//  =================================================================================================================

// ********************* Anpassung bei Verwendung der TLE-Trägerplatine ****************************************
//  Achtung nicht verwechseln mit der Klassik-Platine von LeiterkartenPiraten
//  Die Anpassungen betreffen nur die TLE-Trägerplatine.
//  
#define Traegerplatine



// ********************* Anpassung an DFPlayer von DF-ROBOT mit LISP3 Chip *****************************************
// #define DfPlayer_spez

// Nutzung eines DF-Players, der bei Adverts ein EndOfTrack Event ausgibt 
// Einige DF-Player geben beim Abspielen von Advert-Tracks ein EndOfTrack Event aus.
// Das führt dazu, dass nach dem Abspielen von Adverts, anschließend Tracks übersprungen werden.
// Bei Verwendung eines solchen Players z.B. DFROBOT mit LISP 3 Chip das #define durch Entfernen 
// der Kommentarzeichen aktivieren.


//------------------------------------------------------
// Variable zur Kennzeichnung ob Advert abgespielt wird
#ifdef DfPlayer_spez
bool AdvPlaying = false; // Advert wird abgespielt, Voreinstellung Nein
#endif
//-----------------------------------------------------


// ******************** Auswahl der Optionen und Zusatzfunktionen für Tonuino Klassik *******************************

// uncomment or comment the " #define .... "  to enable or disable the additional function

// --------------------- Debug Modus --- Klassik mit Arduino NANO oder UNO -----------------------------------
//#define Konsole
// Zum Einsparen von Programmspeicher wird die vollständige Ausgabe auf den Seriellen Monitor nur bei Freigabe ausgeführt.
// ---------------------------------------------------------------
// Hardwareabhängige Zusatzdefinitionen (Hier nichts ändern)
#ifdef Konsole                // Bei aktiver LED-Animation, wird diese deaktiviert, um den Programmspeicher
  #ifdef LED_SR               // für die Konsolenausgabe frei zu machen.
  #undef LED_SR
  #endif
  #ifdef CandleLight
  #undef CandleLight
  #endif
  #ifdef LED_SR_Switch
  #undef LED_SR_Switch
  #endif
#endif
// ---------------------- Abschaltung über Hardware - Pololu-Switch, MosFet, u.s.w. -- Klassik -----------------------
#define HW_PowerOff            // Abschaltung über Hardware, wie Mosfet oder Pololu-Switch
//#define PololuSwitch          // Abschaltung über PololuSwitch 
// -----------------------------------------
// Hardwareabhängige defines nicht verändern  
  #ifdef HW_PowerOff          // Festlegen des Ausschalt-Signals, (HIGH oder LOW)
   #ifndef PololuSwitch       // ohne PololuSwitch
    #define LowActive         // LOW Pegel schaltet den TonUINO aus.
   #endif
   
  #endif                             
                          
// ---------------------- Abschaltung durch die Powerbank bei Unterschreiten der Mindestlast -- I < 27 mA -- nur Klassik ----
//#define LowCurrPwDown  

// Die Stromaufnahme des Tonuino wird auf < 27 mA reduziert.
// Die Abschaltung erfolgt durch die Powerbank. 
// Bei Unterschreitung der Mindestlast schaltet die Powerbank selbstständig automatisch aus.
// Die Powerbank muss das Abschalten bei Unterschreiten eines minimalen Laststromes unterstützen.
                               

// ----------------------- Jackdetekt - Abschaltung des Lautsprechers bei gestecktem Kopfhörer ----------------------------

#define Jackdetekt 
// Für Jackdetekt muss ein Sensorsignal von der Kopfhörerbuchse bereitgestellt werden.
// Jackdetekt Klassik mit Nutzung Kopfhörer-Buchse oder Platine mit Jackdetekt.
// Das ermöglicht zusätzlich die Lautstärken für Lautsprecher und Kopfhörer getrennt einzustellen. 
// Die jeweiligen Lautstärkeeinstellungen bleiben bis zum Ausschalten des TonUINO gespeichert.
// Im Adminmenü können die Lautstärke Voreinstellungen für LSP und KH getrennt festgelegt werden. 

// -------------------- Festlegen des Sensorpegels für den Kophöreranschluss ---------------------------------------------
#ifdef Jackdetekt               // Wenn Jackdetekt aktiviert ist

//#define KHSensLOW 

// Der Sensorpegel für den Kopfhöreranschluss ist bei eingestecktem Kopfhörer LOW
// Wenn der Sensorpegel bei eingestecktem Kopfhörer HIGH ist, #define KHSensLOW deaktivieren

// Hardwareabhängige Zusatzdefinitionen(Hier nichts ändern)-------------------------
#define EarPhone              // Abschaltung des Lautsprechers über Software, wenn Kopfhörer angeschlossen sind
  #ifdef EarPhone           // Hardwareerweiterung erforderlich: (Kopfhöerbuchse mit Schaltkontakten, oder Kopfhöreranschlussplatine)
    #ifndef SpkOnOff        // wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch mit aktiviert
      #define SpkOnOff      // Hardwareerweiterung erforderlich: (TonUINO Klassik, - Abschaltung des Lautsprechers über MOS-FET's)
    #endif                  
  #endif                    
#endif
#ifdef Traegerplatine
 #ifdef KHSensLOW
  #undef KHSensLOW
 #endif
#endif
// ------------------- Überwachung der Batteriespannung -----------------------------------------------------------
#define BatteryCheck 
// Kann mit der LKP Klassikplatine nur im 3 Tasten-Modus verwendet werden, da AnalogPin A4 im 5 Tastenmodus belegt ist.
// Wenn ein anderer Analogpin frei zur Nutzung ist, kann dieser für BatteryCheck verwendet werden.
// Vor den BatteryCheckPin einen 100kOhm Widerstand in Reihe schalten (Klassik).

// Bei der Traegerplatine wird Analogpin A5 für die Batterieüberwachung benutzt. Dadurch ist auch im 5 Tastenmodus
// die Batteriespannungsüberwachung möglich.
//___________________________________________________________________________________
// Festlegung der Spannungswerte für die Batterieüberwachung. Kann hier angepasst werden.

#ifdef BatteryCheck               // Wenn die Batteriespannungskontrolle aktiviert ist:
  // Hardwareerweiterung erforderlich
  // (Batteriespannung muss bei ausgeschaltetem Tonuino vom Eingang des Arduino getrennt sein. (Nur TonUINO Klassik,MosFet oder Relais)
  // Bei Unterschreiten des BatLow - Wertes wird eine Warnung ausgegeben
  // Bei Erreichen des BatEmpty - Wertes wird der Tonuino ausgeschaltet.
  // Vor Abschalten erfolgt ein Ausfaden der Lautstärke über 20 Sekunden.


 // --------------------------------------- Akkutyp festlegen --------------------------------------------------------
                                                                     
 #define LiFePo                    // Lithium-Eisen-Phosphat-Akku ( LiFePO4)
 
 //#define LiPo                     // Lithium-Ion oder Lithium-Polymer Akku (Li oder LiPo)

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
 // -------------------------------- TonUINO Klassik --------------------------------------------------- 
 //                           TonUINO Klassik , Batteriespannung über 100kOhm an BattCheckPin anlegen
  #define Bandgap 1104000L   
 
  // Wird bei Verwendung der Traegerplatine eine Batteriespannung größer als 9V verwendet muss der Spannungsteiler
  // R13/R14 (R12/R13vab V2.1) und der Korrekturwert angepasst werden. z.B. R13 = 220 kOhm R14 = 100 kOhm. Korrekturfaktor 3,3.
  // Warn und Abschaltspannung an die verwendete Batterie anpassen.
 
 #ifdef Traegerplatine		     // bei der Traegerplatine wird die Batteriespannung über einen konfigurierbaren Spannungsteiler zugeführt.
   #ifndef andererAkku
    const float correction = 2.2 ;   // Korrekturwert für Spannungsteiler Traegerplatine (Anpassung der Anzeige an die tatsächliche Batteriespannung) 
   #endif
   #ifdef andererAkku
    const float correction = 3.3 ;   // Korrekturwert für Spannungsteiler Traegerplatine (Anpassung der Anzeige an die tatsächliche Batteriespannung) 
   #endif
 #endif
 #ifndef Traegerplatine
   const float correction = 1 ;      // Korrekturwert ohne Spannungsteiler (Anpassung der Anzeige an die tatsächliche Batteriespannung) 
 #endif

#endif  // Ende #ifdef Batterycheck

// ------------ Max Matrixwert des Buttonboards ------------------------------------------------------------------------------
#ifdef Buttonboard
 uint16_t mapMax = 1024;
#endif

// ------------ Logischer Wert für Lautsprecher On oder Off -(Wert nicht verändern) ---------------------------------------------------
uint8_t On = 1;    // HIGH-Pegel
uint8_t Off = 0;   // LOW-Pegel
 
// ************************************************************************************************

//******************* Definitionen der Pins für TonUINO Klassik ****************************

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

// ----------------Weckermodul ----------------------------------------

#ifdef Wecker
#define WeckerPin A6              // Eingangspin zum Abspielen Wecker-shortcut
#endif

#define RandomPin A7              // Floating Pin zur Gewinnung einer Zufallszahl

// ----------------- Digital-Pins ---------------------------------

// Pin D2 und D3 mit Softwareserial zur Steuerung des DF-Players belegt.

#define BusyPin 4                 // Auswertung des Busy Signals vom DF-Player
#define LedPin 5                  // Daten für Neopixel-LED-Ring

#ifdef SpkOnOff
#define SpkOnPin 6                // Schaltsignal Lautsprecher Ein/Aus
#endif

#ifdef HW_PowerOff
#define ShutDownPin 7             // Abschaltsignal für MosFet oder Polulo-Switch
#endif

#ifdef EarPhone
#define EarPhonePin 8             // Kontrollpin ob Kopfhörer angeschlossen ist
#endif

#define RstPin 9                  // MFRC 522 -RST
#define CS_Pin 10                 // MFRC 522 -SDA (CS)


#endif
