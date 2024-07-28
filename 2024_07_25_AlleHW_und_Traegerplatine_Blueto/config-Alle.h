// ******************** Auswahl der Optionen und Zusatzfunktionen für Alle HW-Versionen ***************************************
// ======================================================================================================================
// In diesem Register gesetzte #defines sind für alle Hardwareversionen gültig. 
// Hardwarespezifische #defines müssen in der zur Hardware gehörigen config-XXX.h gesetzt werden.
// ======================================================================================================================

// Abhängig vom gewählten Board können nicht immer alle Funktionen aktiviert werden. 
// Das betrifft die AiO und die Klassik version mit Arduino Nano, weil der Speicherplatz
// nicht für alle Features ausreicht. In diesem Fall auf eines der Features verzichten.
// z.B. den CandleLight effekt in der LED-Animation, oder die Weckerfunktion, oder die Batterieüberwachung.
// Bei der AiO Plus und der Klassik Version mit Every ist genügend Speicher für alle Features vorhanden.
   
// uncomment or comment the " #define .... "  to enable or disable the additional function

// -------------------- 3 Tasten Support -----------------------------------------------------------------------------
//                               Für den Betrieb mit drei Tasten #define FIVEBUTTONS und //#define Buttonboard
//                               in Kommentar setzen
                              
// -------------------- 5 Tasten Support -----------------------------------------------------------------------------
#define FIVEBUTTONS           // 5 Tasten support
//                                 Wird das 12-Buttonboard aktiviert, wird der 5 Tastenmodus automatisch deaktiviert.
                              
// -------------------- Support des 12 Buttonboards mit 3 Standarttasten und 9 Zusatztasten für Shortcuts ------------
//#define Buttonboard           // Unterstützung des Buttonboards mit 12 Tasten. 
  #ifdef Buttonboard          // Über das 9 Tastenfeld sind 9 weitere Shortcuts möglich.
   #ifdef FIVEBUTTONS         // Da das Buttonboard nur 3 Standarttasten unterstützt ist der 5 Tasten support nicht möglich
    #undef FIVEBUTTONS        // und wird ggf. deaktiviert.
  #endif                      // Hardwarekonfiguration auf dem Buttonboard über die DIP-Schalter beachten !
 #endif                       
// ------------------------------------------------------------------------------------------------------------------------
#ifdef Buttonboard              // Vorgabe der Geschwindigkeit der Volume Änderung bei Lautstärkeeinstellung
const uint8_t setVolChSp = 2 ;  // über longPress der Lautstärketasten. Wert zwischen 1 und 20. 
#endif                          // Je größer der Wert um so langsamer die Lautstärkeänderung
//                                 Für Buttonboard empfohlener Wert zwischen 1 und 4.
#ifndef Buttonboard             // Für 3 und 5 Tasten empfohlener Wert zwischen 5 und 10.
const uint8_t setVolChSp = 5 ;
#endif
// ------------------- Sprungweite für Titelsprung Vorwärts/ Rückwärts bei LongPress Vor/Zurück --- nur bei Fivebuttons ---
#define JumpLongPress         // Titelsprung bei Longpress Vorw. Rückw. Taste bei der 5 ButtonVersion
  #ifndef FIVEBUTTONS         // Wenn kein 5 Tastenmodus wird JumpLongPress wieder deaktiviert
    #undef JumpLongPress
  #endif
  #ifdef JumpLongPress        // Wenn JumpLongPress aktiviert ist
   #ifdef FIVEBUTTONS         // Nur im 5 Buttonmodus
   const uint8_t SetJump = 10;// Hier festlegen, um wieviele Tracks bei Longpress weiter oder zurück gesprungen wird.
   #endif                     // Empfohlen 5 bis 10 Tracks.
  #endif
  #ifndef JumpLongPress       // Wenn JumpLongPress nicht aktiviert ist
   const uint8_t SetJump = 1; // Wenn JumpLongPress nicht aktiviert ist, wird Sprungweite auf 1 gesetzt.
  #endif 
 
// -------------------- Zuletzt gespielte Karte als Shortcut speichern -------------------------------------------------
#define LastCard              // Die zuletzt gespielte Karte wird als Shortcut auf die Play/Pause-Taste gelegt 
//                               Shortcuts, Startsound und Weckersound werden dabei nicht berücksichtigt
//                               Die Konfiguration des Shortcuts für die Play/Pause-Taste wird im Adminmenü nicht aufgerufen.

// ---------------------- Hörbuch auf Anfang zurücksetzen ---------------------------------------------------------------
#define HB_Reset              // Im Abspielmodus Hörbuch wird bei laufender Wiedergabe, der Fortschritt des Hörbuches
//                               durch langen Druck der Pausetaste auf Anfang zurückgesetzt

// ---------------------- Lautstärke für das Adminmenü festlegen ---------------------------------------------------------
#define MenueVol                // Die Menülautstärke wird auf die Startlautstärke Lautsprecher eingestellt.
const uint8_t MenueVolume = 20; // Bei Deaktivierung von MenueVol wird die Menülautstärke auf diesen Festwert eingestellt.

// ---------------------- Zählen der Ordner auf der SD-Karte -------------------------------------------------------------
#define CountFolders           // Die Anzahl der Ordner des Speichermediums im DfPlayer wird ermittelt
//                                und als Begrenzung bei der Ordnerauswahl im Adminmenü verwendet.
//                                Abhängig vom Chipsatz des DfPlayers ist die Funktion nicht immer verfügbar.
//                                Dann deaktivieren ! Es werden dann wieder die Funktionen ohne CountFolders verwendet.
//                                Getestet mit LKP-Player, MH-ETLive K24 24SS,DF-Robot LISP3, IL AA19 und YX5200 24SS - funktioniert.
//                                AiO Platine funktioniert auch.
//                                Player mit JL AB23A797393.1-7 funktioniert nicht. Hier CountFolders deaktivieren!

#ifndef CountFolders
 //#define ZaehleOrdner          // Für DF-Player, die kein CountFolders unterstützen können die Ordner einzeln gezählt
//                                werden. Das Initialisieren des Tonuino dauert dann einige Sekunden länger.                             
#endif
// ---------------------- Windows SystemVolumeInfo ignorieren ----------------------------------------------------------------
#ifdef CountFolders            // Der von Windows automatisch angelegte Ordner, System Volume Info -Ordner 
//                                stört die exakte Funktion von CountFolders.
 //#define IgnoreWinSysInf       // Der Windows-Ordner "System Volume Information" kann auf der SD-Karte
//                                verbleiben und wird ignoriert. Dies ist bei Nutzung der Option CountFolders
//                                wichtig, um die korrekte Ordner Anzahl für die davon abhängigen Funktionen
//                                zu verwenden.
//                                Hinweis !!!!
//                                Ist CountFolders aktiviert und der Ordner Windows SystemvolumeInfo NICHT ! auf der SD-Karte
//                                vorhanden, ist beim Konfigurieren der Karten und Shortcuts der höchste belegte Ordner der 
//                                Mediadateien nicht auswählbar.
#endif

     
// ---------------------- LED Animation mit NEOPixel LED Ring oder Strip ----------------------------------------------------
#define LED_SR                 // LED Animation,Hardwareerweiterung erforderlich: (Neopixel LED's,Strip oder Ring)

  #ifdef LED_SR                  // Bei definierter LED Animation 
  //#if defined(EVERY) or defined(AiOPLUS) 
  #define CandleLight          // CandleLight Simulation bei aktiver Modifikation Schlummermodus
  //#endif

 
  const uint8_t LED_COUNT = 12 ; // Anzahl der LEDs im Ring oder Strip. Kann hier angepasst werden.
  #endif

 // Hardwareabhängige Zusatzdefinitionen ( Hier nichts ändern)
 #if not defined(AiOPLUS) and not defined(EVERY)  // Bei TonUINO Klassik mit NANO, oder AiO, 
  #ifdef Konsole               // wird bei aktivierter Konsole die LED-Animation inaktiv
  #undef LED_SR                // um den erforderlichen Speicher für die Konsole zur Verfügung zu stellen
  #endif                        
 #endif                        
  
 #ifdef LED_SR                 // Bei definierter LED Animation
   #define LED_SR_Switch       // Möglichkeit die LED-Animation über gleichzeitigen langen Druck 
   //                             der Up-Down Tasten oder über Software ein- und auszuschalten
 #endif 

// ---------------------- Lautsprecher Abschaltung über Software --------------------------------------------------------------
#define SpkOnOff              // Aus und Einschalten des Lautsprechers über Software 
//                               zur Unterdrückung des Einschaltgeräusches und
//                               Möglichkeit der Abschaltung beim Anschluss eines Kopfhörers (AiO über KH-Buchse )
                              
// ------------------- Lese-Empfindlichkeit des RFID-Lesers --------------------------------------------------------------------
// Bei Leseproblemen des RFID Lesers kann die Leseempfindlichkeit verändert werden.
#define NFCgain_avg         // Mittlere Empfindlichkeit RFID Leser - Default wert
//#define NFCgain_max       // Maximale Empfindlichkeit RFID Leser
//#define NFCgain_min       // Minimale Empfindlichkeit RFID Leser

// ------------------- Weckerfunktion mit Weckermodul --- Alle Versionen ---------------------------------------------------------
#define Wecker              // Über ein externes Weckeruhrwerk wird eine Weckfunktion aktiviert
//                             TonUINO wird eingeschaltet und ein vordefinierter Shortcut als Wecker abgespielt
//                              Bei gestecktem Kopfhörer wird der Weckersound trotzdem über Lautsprecher abgespielt.
//                              Bei der AiO bis V1.2 setzt das die Hardwareänderung Kopfhörer voraus.
#ifdef Wecker               // Der Dialog zum Erstellen des Weckershortcuts wird im Adminmenü aktiviert.
  #ifndef SpkOnOff          // Wenn SpkOnOff nicht aktiviert ist, wird diese Funktion automatisch aktiviert
   #define SpkOnOff         // Hardwareerweiterung für TonUINO Klassik erforderlich: (Abschaltung des Lautsprechers über MOS-FET's)
  #endif                    // Für die AiO wird das Einschaltsignal über 10 kOhm auf PBN gelegt.(LOW-aktiv)
#endif


