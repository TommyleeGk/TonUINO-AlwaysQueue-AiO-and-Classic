
/****** Alternative Software *************
 ______        _____ ___ ___  _______
|_   _|___ ___|  |  |   |   | |     |
  | | | . |   |  |  |- -| | | |  |  |
  |_| |___|_|_|_____|___|_|___|_____|
  Based on TonUINO Version 2.1 and Version 2.2 AiO / AiO+
  created by Thorsten Voß and licensed under GNU/GPL.
  Information and contribution at https://tonuino.de.

 ********* Always Queue - alle Hardwareversionen ************************

 modified ,extended and supported by Thomas Lehnert

 https://github.com/TommyleeGk/TonUINO-AlwaysQueue-AiO-and-Classic
      

 Bearbeitungsstand:   2024-07-25
 ===============================

    In der Registerkarte "config-Alle.h" und der der Hardwareversion entsprechenden Registerkarte "config-xxx.h" 
    wird über die #defines ausgewählt, welche Hardwarekonfiguration und welche Funktionen verwendet werden.
    Auswahlmöglichkeiten sind: 
    AiOPLUS, AiO bis Version 1.2, Klassik mit Arduino EVERY, oder Klassik mit Arduino Nano oder UNO.
    In den Versionen Klassik und Every kann die Traegerplatine aktiviert werden. Nicht mit der Klassikplatine von LKP verwechseln.
    In den Registerkarten für die verschiedenen Hardwareversionen sind Hinweise aufgeführt, welche Einstellungen 
    im Boardmanager unter Werkzeuge vorgenommen werden müssen.

   !!!!!! EINSTELLUNGEN ZUR KONFIGURATION NUR IN DEN REGISTERKARTEN config-XXX.h VORNEHMEN !!!!!!!!!!!!!!!!!!!!
   Einstellungen in der config-Alle.h sind für alle Hardwareversionen gültig.
   Einstellungen in den config-AiO.... usw. sind nur für die jeweilige Hardwareversion gültig.
   
   ===========================================================================================================
    !!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!!!! WICHTIG !!!!!!!!! WICHTIG !!!!!!!!!!!
    !!                                                                                                     !!
    !!   Diese Version  erfordert geänderte und erweiterte Dateien im advert und mp3 Ordner.               !!
    !!   Für die korrekte Funktion müssen die dieser Version beigefügten mp3 und advert Ordner verwendet   !!
    !!   werden.                                                                                           !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ============================================================================================================


   Eine Übersicht aller vorgenommenen Änderungen und Erweiterungen befindet sich in der history.h.
   ============================================================================================================
*/
//============================================================================================================

// ******** Auswahl der Tonuino-Variante ** TonUINO Klassik, Klassik mit Arduino EVERY, AiO oder AiOPLUS ********
// Durch die richtige Boardauswahl im Menü Werkzeuge, 
// werden für alle Boardtypen die Definitionen der Hardwareversion automatisch gesetzt. 
// Die Vorgaben für die Boardauswahl sind in den Hardwareabhängigen config-XXX.h noch einmal beschrieben.

//================= ACHTUNG !!! ======== Die #define's für den Boardtyp werden automatisch gesetzt ============
//================= Hier keine Änderungen vornehmen !!!! ======================================================

// ----------------------TonUINO Klassik mit Arduino NANO 328P --automatische Auswahl -----------------------------
#if defined (ARDUINO_AVR_NANO)
 #define Klassik         // Automatisches setzen der Definition bei dieser Boardauswahl.
#endif                   // Software für die Klassik-Version mit Arduino-Nano oder Uno

// ----------------------TonUINO Klassik mit Arduino Every --automatische Auswahl --------------------------------
#if defined(ARDUINO_AVR_NANO_EVERY)
 #define EVERY           // Automatisches setzen der Definition bei dieser Boardauswahl
#endif                   // Software für die Klassik-Version mit Arduino-Nano-Every

// ----------------------- AiO-PLUS -- automatische Auswahl -----------------------------------------------------
#if defined(MEGACOREX)    // Automatisches setzen der Definition bei dieser Boardauswahl
  #define AiOPLUS         // Software für das AiO PLUS Board
#endif
// ---------------------- All in One Board bis V 1.2 --automatische Auswahl -------------------------------------
#if defined(__LGT8F__)   // Automatisches setzen der Definition bei dieser Boardauswahl
  #define AiO            // Software für das AiO Board bis Version 1.2
#endif                     


// =================================================================================================================

// ******************** Auswahl der Optionen und Zusatzfunktionen **************************************************

// Die Optionen und Zusatzfunktionen werden durch Setzen oder Entfernen der Kommentarzeichen "//" 
// in den Hardware abhängigen Registerkarten config-xxx.h aktiviert oder gesperrt.
// Einstellungen in config-Alle.h gelten für alle Hardwareversionen.

// ==================================================================================================================

// *************** Einbinden der Konfigurationen **************************************************
#include "config-Alle.h"
#include "config-AiO-plus.h"
#include "config-AiO.h"
#include "config-Every.h"
#include "config-Klassik.h"


// *************** Einbinden der Bibliotheken *****************************************************
#include <DFMiniMp3.h>             // Version 1.2.3 oder höher
#include <EEPROM.h>
#include <JC_Button.h>
#include <MFRC522.h>
#include <SPI.h>
#ifndef Hardwareserial
#include <SoftwareSerial.h>
#endif
#ifdef Klassik
#include <avr/sleep.h>
#endif
#ifdef LED_SR
#include <Adafruit_NeoPixel.h>
#endif

// ============================== Deklarationen =============================================
// ********************** Cookies ******************************************************************
                                               
// Abhängig von der Hardwarekonfiguration wird die Struktur von mySettings verändert.
// Zur Anpassung der Settings an die geänderte Hardware muss der EEPROM rückgesetzt werden. 
// Durch eine von den #defines abhängige Änderung von myCookie erfolgt das automatisch.

uint32_t myCookie = 130219560;                  // Grundwert myCookie zum Erkennen einer Softwareversion mit geänderter mySettings Struktur
//                                              // Eine Änderung von myCookie sorgt für einen automatischen Reset der mySettings
//                                              // Änderungen der #defines, die eine Strukturänderung bewirken, verändern myCookie
//                                              // durch Addition bei Hinzufügen einer neuen Funktion bzw durch Subtraktion bei Entfernen einer Funktion.
//                                              // Dadurch ist garantiert, das jede mySettings ändernde Konfiguration ein anderes myCookie erzeugt.
                                                
static const uint32_t cardCookie = 322417479;   // Cookie zum Erkennen der TonUINO-RFID Karten
//                                              // sorgt für das automatische Starten der Kartenkonfiguration bei neuen Karten

//******************** Deklaration der Variablen **********************************************************************
// ------------------ Lautstärkemanagement -----------------------
uint8_t SpkVol;                                 // Lautstärke für den Lautsprecher
uint8_t EarVol;                                 // Lautstärke für den Kopfhörer
uint8_t MenuVol = MenueVolume;                  // Lautstärke für das Adminmenü auf Festwert
bool longPressVol = false;                      // VolÄnderung durch longPress
uint8_t countVolCh = 0 ;                        // Zählvariable speed VolÄnderung
bool msgMin = true ;                            // Message "minimale Lautstärke erreicht"
bool msgMax = true ;                            // Message "maximale Lautstärke erreicht"

// ------------------ Shortcuts,  Kopfhörer, Lautsprecher, Bluetooth, Wecker ---------------------
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
#ifdef Bluetooth
bool BT = false;                                // Bluetooth eingeschaltet, Voreinstellung NEIN
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
bool ResetHB = false;                           // Hörbuch auf Anfang zurückgesetzt, Voreinstellung NEIN
bool KontrPlay = false;
bool EoQ = false;
bool nxTr = false;
// ---------------------- Adminmenü ----------------------------------------------------------------------
uint8_t progmode = 0;                           // Modus für die Programmierung der Karten und Shortcuts
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
#ifdef EVERY
const float reference = 2.500;                  // Referenzspannung EVERY
const float steps = 1024;                       // Auflösung ADU
#endif
#ifdef AiOPLUS
const float reference = 2.500;                  // Referenzspannung AiOPLUS
const float steps = 1024;                       // Auflösung ADU
#endif
#ifdef BatteryCheck
#ifndef AiO
float u_reference = 0.00 ;                      // Referenzspannung TonUINO Klassik wird durch interne Messung ermittelt
#endif
float Vbatt = 3.40;                             // Batteriespannung (Wird bei der Messung auf aktuellen Wert gesetzt)
float VbattGl = 3.20;                           // Geglättete Batteriespannung aus 60 Einzelmessungen,Voreinstellung 3,2V AiO
//                                              // Geglättete Batteriespannung aus 10 Einzelmessungen , Klassik
const float Vwarning = BatLow;                  // Spannungswert in Volt für Warnung Batteriespannung, bei den #defines festgelegt
const float Vshutdown = BatEmpty;               // Spannungswert in Volt für Shutdown, Batterie leer, bei den #defines festgelegt

#ifdef Klassik
 unsigned long TestIntervall = 6000;            // Testintervall Batterie ,Klassik: 6 Sekunden
#endif
#ifndef Klassik
 unsigned long TestIntervall = 1000;            // Testintervall Batterie  ,AiO, AiOPLUS, EVERY: 1 Sekunde
#endif


uint8_t countTi = 0;                            // Anzahl der durchlaufenen Testintervalle
uint32_t SumValue = 0;                          // Summe der Sensorwerte aller  Testintervalle 

unsigned long Now = 0;                          // millis() im Moment des Auslesens der Batteriespannung
unsigned long lastTest = 0;                     // Zeitpunkt letzte Prüfung der Batteriespannung

bool BattLeer = false;                          // Marker, leere Batterie erkannt, Voreinstellung Nein

#endif  //BatteryCheck

bool sp = true;

// ******************** Variablen für LED Animation *** by t@on **  modifyed by @atomphil  *******************
#ifdef LED_SR
 
// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LedPin, NEO_GRB + NEO_KHZ800);

// Zählvarbiablen
uint16_t loopCount;                             // Runterzählen der Loops
uint16_t loopCountWait;                         // Definierte Anzahl wieviele Loops runtergezählt werden sollen, also wie lange gewartet wird
uint8_t animCount;                              // Wie oft die einmalige Animation ausgeführt wird bevor es zurück in die Hauptschleife (Animationsmodus 0) geht
uint8_t i;
uint8_t Zhl = 5;                                // Zählvariable LED Animation für error Mp3 Player

// Datenvariablen
uint8_t currentDetectedTrack;                   // Speichern des aktuellen Tracks für späteren Vergleich
uint8_t lastDetectedTrack;                      // Speichern des Tracks um die Animation nur ein mal zu triggern
//uint8_t Trackwechsel = 0;                       // Wird bei nexttrack auf 1 und bei prevtrack auf 2 gesetzt
uint8_t currentDetectedVolume;                  // Speichern der aktuellen Lautstärke für späteren Vergleich
uint8_t lastDetectedVolume;                     // Speichern der Lautstärke um die Animation nur ein mal zu triggern
uint8_t volumeScope;                            // Differenz der in mySettings voreingestellten minimalen und maximalen Lautstärke
uint8_t volumeScopeAmount;                      // Lautstärkenwert in deinem Scope
uint8_t volumeScopeAmountMod;                   // Lautstärkewert in %
 
uint32_t  firstPixelHue = 0;
uint32_t  pixelHue;
 
uint32_t  TrckChgColor_FFW = 21845L;            // Farbe wird bei Animation nächstes Lied verwendet
uint32_t  TrckChgColor_REW = 43690L;            // Farbe wird bei Animation Lied zurück verwendet
uint8_t   TrckChgSpeed = 32; //64;                  // Geschwindigkeit Animation Lied vor/zurück (1 bis 255)
uint8_t   TrckChgMaxBrightness = 128;//255;           // Helligkeit Animation Lied vor/zurück (1 bis 255)
uint32_t  TrckChgProgress = 0;
 
uint8_t lsrAnimationMode;                       // Animationsmodus - 0: Daueranimation, 1-2 einmalige Animation (als Unterbrechung zu 0)
uint8_t lsrAnimationTrackMode;                  // Bei Animationsmodus Liedwechsel, Bestimmung der Farbe und Richtung

#ifdef CandleLight
#define DELAYVAL 500                            // Time (in milliseconds) to pause between pixels
long lastTimeCandle;
int intervalCandle;
bool Candle = false;                            // wird bei aktivieren des Modify Schlummermodus auf true gesetzt
#endif
//----------- Vordefinierte Farben ------------------------------
uint32_t magenta = strip.Color(255, 0, 255, 64);    // Alle LED's leuchten in der selben Farbe
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

//****************** Definitionen für letzte gespielte Karte als Shortcut auf Playtaste legen ************************
#ifdef LastCard
 #define folderReg 201            // Ordner
 #define modeReg 202              // Abspielmodus
 #define specialReg 203           // Starttrack Spezial von-bis
 #define specialReg2 204          // Endtrack Spezial von-bis
#endif

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
MFRC522 mfrc522(CS_Pin, RstPin);                // Create MFRC522
MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
MFRC522::StatusCode status;

// ******************** DF-Player **************************************************
// DFPlayer Mini

#ifndef Hardwareserial
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX   // Digitalpins zur Steuerung des DF-Players
#endif
uint8_t Ordner = 01;                               // Ermittelte Anzahl Ordner wenn CountFolder nicht unterstützt wird
uint8_t numFolders;                                // Anzahl der Ordner im Speichermedium
uint8_t numTracksInFolder;                         // Anzahl der Tracks im Ordner 
uint8_t firstTrack;                                // erster Track
uint8_t currentQueueIndex;                         // index in queue[] aktuelle Tracknr in der queue
uint8_t queueSize;                                 // Länge der queue
uint8_t queue[255];                                // max 255 tracks/folder. entries 0..254 and values 1..255 are used.
uint8_t volume;                                    // Lautstärke
// --------------------------------------------------------
struct folderSettings 
{                                                  // Struktur der Foldersettings
  uint8_t folder;                                  // Ordnernummer
  uint8_t mode;                                    // Abspielmodus
  uint8_t special;                                 // Spezialmodus Start-track
  uint8_t special2;                                // Spezialmodus End-track
};
// ---------------------------------------------------------
// this object stores nfc tag data
struct nfcTagObject 
{                                                  // Struktur der RFID-Karte
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
  int startMessage,                                // Tracknr der StartAnsage im mp3 Ordner
  int messageOffset,                               // Tracknummer im mp3 Ordner ab der die Ansagen der Optionen gespielt werden
  bool preview = false,                            // Vorschau, Voreinstellung NEIN
  int previewFromFolder = 0,                       // Vorschau Ordner
  int defaultValue = 0,                            // Standart Rückgabewert
  bool exitWithLongPress = false);                 // Abbruch durch longPress, Voreinstellung NEIN
//-----------------------------------------------

void writeCard(nfcTagObject nfcTag);                   // RFID Karte schreiben
void dump_byte_array(byte * buffer, byte bufferSize);  // Auslesen HEX-Daten
void adminMenu(bool fromCard = false);               // Adminmenü von Karte starten, Voreinstellung NEIN
void playShortCut(uint8_t shortCut);                   // Shortcut abspielen
bool knownCard = false;                                // Karte bekannt, Voreinstellung NEIN
bool isPlaying();                                      // Marker, Wiedergabe läuft


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mp3Notify; 
#ifdef Hardwareserial

#ifdef EVERY
typedef DFMiniMp3<HardwareSerial, Mp3Notify, Mp3ChipIncongruousNoAck, 4000> DfMp3;  // Serial 1 für Klassik oder Traegerplatine mit EVERY
DfMp3 mp3(Serial1);
#endif

#ifdef AiOPLUS
typedef DFMiniMp3<HardwareSerial, Mp3Notify, Mp3ChipIncongruousNoAck, 4000> DfMp3;  // Serial 3 für AiOPLUS
DfMp3 mp3(Serial3);
#endif
#endif

#ifndef Hardwareserial
typedef DFMiniMp3<SoftwareSerial, Mp3Notify, Mp3ChipIncongruousNoAck, 4000> DfMp3; // Softwareserial Klassik, Taegerplatine mit Nano, oder AiO
DfMp3 mp3(mySoftwareSerial);
#endif



// implement a notification class,
// its member methods will get called
// ***************************************************************************
class Mp3Notify
{

  public:

  // ***************** Error-meldungen des df-players **************************

   static void OnError(DfMp3& mp3, uint16_t errorCode) 
  {
    
    switch (errorCode)
    {
     case DfMp3_Error_Busy: 
     {
       Serial.print(F("1-bsy"));              // Es läuft eine Wiedergabe
       break;
     }
     case DfMp3_Error_Sleeping: 
     {
       Serial.print(F("2-slp"));             // Df Player im Sleepmodus
       break;
     }
     case DfMp3_Error_SerialWrongStack: 
     {
       Serial.print(F("3-mem"));               // Fehler interer Speicher
       break;
     }
     case DfMp3_Error_CheckSumNotMatch: 
     {
       Serial.print(F("4-Com"));             // Hardware Kommunikationsfehler
       break;
     }
     case DfMp3_Error_FileIndexOut: 
     {
       Serial.print(F("5-idx Out "));     // Dateinummer außerhalb des Bereiches
       break;
     }
     case DfMp3_Error_FileMismatch: 
     {
       Serial.print(F("6-miss-file"));      // Datei nicht gefunden
       break;
     }
     case DfMp3_Error_Advertise: 
     {
       Serial.print(F("7-adv"));               // Fehler beim Abspielen Advert
       #ifdef DfPlayer_spez
       AdvPlaying = false;
       #endif
       break;
     }
     case DfMp3_Error_RxTimeout: 
     {
       Serial.print(F("rx T-out"));           // Zeitüberschreitung RX-Signal
       break;
     }
     case DfMp3_Error_PacketSize: 
     {
       Serial.print(F("p-size"));             // Fehler Sektorgröße
       break;
     }
     case DfMp3_Error_PacketHeader: 
     {
       Serial.print(F("p-head"));             // Fehler Header
       break;
     }
     case DfMp3_Error_PacketChecksum: 
     {
       Serial.print(F("p-chksum"));           // Prüfsummenfehler
       break;
     }
     case DfMp3_Error_General: 
     {
       Serial.print(F("gen."));               // allgemeiner Fehler
       break;
     }
     default: 
     {
       Serial.print(F("unkn."));              // unbekannter Fehler
       break;
     }
    }
   Serial.println(F(" err"));
      
   mp3error = true;                           // Marker setzen bei mp3-Error
  }

 // Speichermedium der Sounddateien
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
   if (source & DfMp3_PlaySources_Sd) Serial.print(F("SD-K"));
   #ifdef UsbStick
   if (source & DfMp3_PlaySources_Usb) Serial.print(F("USB"));
   #endif
   //if (source & DfMp3_PlaySources_Flash) Serial.print("Flash ");       // Wird nicht benötigt
 
   Serial.println(action);
  }


 // Meldung vom Df Player - Track beendet ,                                  Meldung erfolgt
 
 static void OnPlayFinished(DfMp3& mp3, DfMp3_PlaySources source, uint16_t track) 
  {                                                                       //  am Ende von Files aus dem mp3-Ordner
   #ifdef DfPlayer_spez                                                   // von Adverts ein Track beendet ausgeben. z.B.DFROBOT DF 290
     if(!AdvPlaying)                                                      // Wenn kein Advert abgespielt wurde
      {
   #endif
   
   PrintlnSourceAction(source, "-EoTr -> nxtTr");                         //  wird am Ende von advert-Tracks nicht gesendet
   nextTrack(track);                                                      // Wenn der Track regulär beendet wird , nextTrack.
   delay(300);
   #ifdef DfPlayer_spez
      }                                                                     
     AdvPlaying = false;                                                  // Marker zurücksetzen dass Advert gespielt wurde
   #endif  
  }                                                                       // außer bei advert-Tracks


 
  // Speichermedium online
  
  static void OnPlaySourceOnline( DfMp3& mp3, DfMp3_PlaySources source) // Abspielmedium Online
  
  {
   PrintlnSourceAction(source, "onl.");
  }

  // Speichermedium bereit
  
  static void OnPlaySourceInserted(DfMp3& mp3, DfMp3_PlaySources source) // Abspielmedium Bereit
  {
   PrintlnSourceAction(source, "ready");
  }

 // Speichermedium entfernt
  
  static void OnPlaySourceRemoved(DfMp3& mp3, DfMp3_PlaySources source) // Abspielmedium nicht erkannt (entfernt)
  {
   PrintlnSourceAction(source, "abs.");
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ************** Initialisierung der queue ******************
void initQueue(uint8_t from, uint8_t to)                    // Von und Bis eingeschlossen
{
 firstTrack = from;                                         // erster Track -> von
 queueSize = to - from + 1;                                 // Länge der queue berechnen
 for (uint8_t x = 0; x < queueSize; x++)
  queue[x] = x + from;
}

// ************** Zufallsliste erstellen ***********************
void shuffleQueue()                                         // Queue für die Zufallswiedergabe erstellen
{
 for (uint8_t i = 0; i < queueSize; i++)
 {
   uint8_t j = random(i, queueSize);                        // elems [i .. queueSize] remain, pick one
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
   if (queue[i] == track) return i;                         // return index with queue[index]==track
  }
  return 0xff;                                              // return 0xff if queue does not contain track
}

// ********** Namen der Abspielmodi *******************************
const PROGMEM char* getModeName(uint8_t mode)
{
  switch (mode)
  {
    case 1:   return PSTR("Hörsp.");
    case 2:   return PSTR("Alb.");
    case 3:   return PSTR("Pty");
    case 4:   return PSTR("Einz.");
    case 5:   return PSTR("Hörb.");
    case 6:   return PSTR("V-B: Hörsp.");
    case 7:   return PSTR("V-B: Alb.");
    case 8:   return PSTR("V-B: Pty.");
    case 9:   return PSTR("Adm.");
    default:  return PSTR("?");
  }
}

// *****************************************************************
// helper to print string from PROGMEM pointer

//#ifdef Konsole
void Serial_println_F(const PROGMEM char* str) 
{
  Serial.println((const __FlashStringHelper*)str);
}
void Serial_print_F  (const PROGMEM char* str) 
{
  Serial.print  ((const __FlashStringHelper*)str);
}
//#endif

///////////////////////// My-Settings ///////////////////////////////////////

// ********************* my Settings speichern ********************
void writeSettingsToFlash()                // my Settings im EEPROM speichern
{
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
void resetSettings()                       // my Settings auf defaultwerte zurücksetzen
{                    
 #ifdef Konsole
  Serial.println(F("Res. Settings"));
 #endif
  mySettings.cookie = myCookie;            // aktuellen myCookie zuweisen
  mySettings.version = 2;
 // ------------------ Volume Settings -------------------------------------------------------
  mySettings.maxVolume = 25;               // max.Lautstärke Lautsprecher
  mySettings.minVolume = 2;                // min.Lautstärke Lautsprecher
  mySettings.initVolume = 15;              // Start-Lautstärke Lautsprecher
 #ifdef EarPhone  
  mySettings.maxEarVol = 20;               // max.Lautstärke Kopfhörer
  mySettings.minEarVol = 2;                // min.Lautstärke Kopfhörer
  mySettings.initEarVol = 15;              // Start-Lautstärke Kopfhörer
 #endif 
  mySettings.eq = 1;                       // Equalizer Normal
 // ------------------ Standby Timer --------------------------------------------------------
  mySettings.standbyTimer = 5;             // Standbytimer auf 5 min
 // ------------------ Funktion der Tasten tauschen --------------------------------------------------------
 #ifndef FIVEBUTTONS                        // 3-Tastenversion
  mySettings.invertVolumeButtons = false;   // Funktion Shortpress und Longpress der Lautstärke und Vor/Zur-Tasten umkehren, AUS
 #endif                                     // Vor/Zurück -> ShortPress, Lauter/Leiser -> LongPress
 #ifdef FIVEBUTTONS                         // 5-Tastenversion
  mySettings.invertVolumeButtons = true;    // Funktion der Vol-und Vor/Zur-Tasten tauschen, EIN
 #endif                                     // Vor/Zurück ->Tasten 2 und 3, Lauter/Leiser -> Tasten 4 und 5
 // ----------------- Shortcuts ---------------------------------------------------------
 #ifndef FIVEBUTTONS                        // Shortcuts 3 Tasten-Version
  #ifndef Buttonboard
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Play-Pausetaste  (Taste 1)
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-Lautertaste  (Taste 2)
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-Leisertaste (Taste 3)
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Welcomesound
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Weckersound
  #endif
 #endif
 // -------------------------------------------------------------------------
 #ifdef FIVEBUTTONS                        // Shortcuts 5 Tasten-Version 
  mySettings.shortCuts[0].folder = 0;      // kein Shortcut Pausetaste (Taste 1)
  mySettings.shortCuts[1].folder = 0;      // kein Shortcut Vor-taste  (Taste 2)
  mySettings.shortCuts[2].folder = 0;      // kein Shortcut Rück-taste (Taste 3) 
  mySettings.shortCuts[3].folder = 0;      // kein Shortcut Vol+ taste (Taste 4)
  mySettings.shortCuts[4].folder = 0;      // kein Shortcut Vol- taste (Taste 5)
  mySettings.shortCuts[5].folder = 0;      // kein Shortcut Welcomesound
  mySettings.shortCuts[6].folder = 0;      // kein Shortcut Weckersound
 #endif
 // -------------------------------------------------------------------------
 #ifdef Buttonboard                        // Shortcuts Buttonboard-Version
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
 // -------------- Schutz des Adminmenues -------------------------------------------------------------------
  mySettings.adminMenuLocked = 0;          // 0 = Adminmenü nicht geschützt,
 //                                        // 1 = Schutz durch Adminkarte,
 // ---------------------------------------------------------------------------------
  writeSettingsToFlash();                  // Settings im EEPROM speichern

  #ifdef LED_SR                            // LED-Animation bei RESET von mySettings

  for(uint8_t i=0; i<5; i++)               // Bei Reset 5x Rot blinken
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
void migrateSettings(byte oldVersion) 
{
  if (oldVersion == 1) 
  {
   #ifdef Konsole
    Serial.println(F("Rst.Settings"));
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
  if (mySettings.cookie != myCookie) resetSettings();     // wenn durch Änderungen bei den #defines myCookie verändert wurde -> Reset der mySettings
    
  migrateSettings(mySettings.version);

  // ****************** mySettings im Ser Monitor anzeigen *********************

  Serial.print(F("Vers.: "));
  Serial.println(mySettings.version);
 #ifndef EarPhone  
  Serial.print(F("Max Vol. : "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Min Vol. : "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Ini Vol.: "));
  Serial.println(mySettings.initVolume);
 #endif
 #ifdef EarPhone
  Serial.print(F("Max Vol.Lsp : "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Min Vol.Lsp : "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Ini Vol.Lsp: "));
  Serial.println(mySettings.initVolume);

  Serial.print(F("Max Vol.Ear : "));
  Serial.println(mySettings.maxEarVol);

  Serial.print(F("Min Vol.Ear : "));
  Serial.println(mySettings.minEarVol);

  Serial.print(F("Ini Vol.Ear: "));
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
 if(mySettings.adminMenuLocked == 0) 
  Serial.println(F("unlocked"));
 else
  Serial.println(F("locked"));
  Serial.println();
  Serial.println(F("- ShCuts -"));
 #ifndef LastCard
  Serial.print(F("SC-0,  Play-T.: ")); 
  Serial.println(mySettings.shortCuts[0].folder);
 #endif
 #ifdef LastCard
  Serial.println(F("SC-0,Pl.-T.: Letzte Karte")); 
 #endif
 #ifndef FIVEBUTTONS
  #ifndef Buttonboard
  Serial.print(F("SC-1, Nxt/Vol+ : "));
  Serial.println(mySettings.shortCuts[1].folder);

  Serial.print(F("SC-2, Zur/Vol- : "));
  Serial.println(mySettings.shortCuts[2].folder);

  Serial.print(F("SC-3, Startsnd : "));
  Serial.println(mySettings.shortCuts[3].folder);
  #ifdef Wecker
  Serial.print(F("SC-4, Wecker :    "));
  Serial.println(mySettings.shortCuts[4].folder);
 #endif  
 #endif 
 #endif
 #ifdef FIVEBUTTONS
  Serial.print(F("SC-1, Nxt-T.: "));
  Serial.println(mySettings.shortCuts[1].folder);

  Serial.print(F("SC-2, Zur-T.: "));
  Serial.println(mySettings.shortCuts[2].folder);

  Serial.print(F("SC-3, Vol+ T.: "));
  Serial.println(mySettings.shortCuts[3].folder);

  Serial.print(F("SC-4, Vol- T.: "));
  Serial.println(mySettings.shortCuts[4].folder);

  Serial.print(F("SC-5,  Startsnd  : "));
  Serial.println(mySettings.shortCuts[5].folder);
  #ifdef Wecker
  Serial.print(F("SC-6,  Wecker     : "));
  Serial.println(mySettings.shortCuts[6].folder);
  #endif
 #endif
 #ifdef Buttonboard
  Serial.print(F("SC-3, - A :  "));
  Serial.println(mySettings.shortCuts[3].folder);
  Serial.print(F("SC-4, - B :  "));
  Serial.println(mySettings.shortCuts[4].folder);
  Serial.print(F("SC-5, - C :  "));
  Serial.println(mySettings.shortCuts[5].folder);  
  Serial.print(F("SC-6, - D :  "));
  Serial.println(mySettings.shortCuts[6].folder);
  Serial.print(F("SC-7, - E :  "));
  Serial.println(mySettings.shortCuts[7].folder);
  Serial.print(F("SC-8, - F :  "));
  Serial.println(mySettings.shortCuts[8].folder);
  Serial.print(F("SC-9, - G :  "));
  Serial.println(mySettings.shortCuts[9].folder);
  Serial.print(F("SC-10,- H :  "));
  Serial.println(mySettings.shortCuts[10].folder);
  Serial.print(F("SC-11,- I :  "));
  Serial.println(mySettings.shortCuts[11].folder);
  Serial.print(F("SC-12,Startsnd : "));
  Serial.println(mySettings.shortCuts[12].folder);
 #ifdef Wecker
  Serial.print(F("SC-13,  Wecker  : "));
  Serial.println(mySettings.shortCuts[13].folder);
 #endif
 #endif
  Serial.println();
}

////////////////////// Ordner zählen, wenn CountFolders vom DF-Player nicht unterstützt ////////////////////

// ********************** Ordner zählen, wenn CountFolders nicht unterstützt wird ******************
void OrdnerZaehlen()
{
  Serial.println("Zähle Ordner");
  for (uint8_t i = 0; i < 99; i++)
  {
    numTracksInFolder = mp3.getFolderTrackCount(Ordner);
    if (numTracksInFolder > 0) 
    {
   
     Serial.print(Ordner);
     Serial.print(", ");
     if(Ordner == 20 || Ordner == 40) Serial.println();
     if(Ordner == 60 || Ordner == 80) Serial.println();

     //mp3.playMp3FolderTrack(262);                              // 262- "piep"
     Ordner = Ordner + 1;
    }
   else  return;
 
  }
}

// *************Bluetooth Einschalten und Ausschalten ****************************

#ifdef Bluetooth
void bluetooth()
{
  Serial.println(F("BT-Karte "));
  if(!BT)
 {
   digitalWrite(BtOnPin,HIGH);
   BT = true;
   delay(2000);
   if(isPlaying ())
   {
     mp3.playAdvertisement(610);
      #ifdef DfPlayer_spez
       AdvPlaying = false;
      #endif
    } 
    else mp3.playMp3FolderTrack(610);

    Serial.println(F("BT -> ON "));
  }
  else
  {
   Serial.println(F("BT -> OFF"));
   digitalWrite(BtOnPin,LOW);
   BT = false;
   if(isPlaying())
    {
      mp3.playAdvertisement(611);
      #ifdef DfPlayer_spez
      AdvPlaying = false;
      #endif
    }
    else  mp3.playMp3FolderTrack(611);
  }
}
#endif

///////////////////////// Lautsprecher an oder aus //////////////////////////////////////

// ************************** Lautsprecher über Software an und ausschalten ***************
#ifdef SpkOnOff

// **************************Speaker On *******************

void SpkOn()
{
 #ifdef EarPhone
  if (SpkisOn == false) EarVol = volume ;                     // KH-Lautstärke speichern

 #ifdef Konsole
  Serial.print(F("Ear-Vol.speichern: "));
  Serial.println(EarVol);
 #endif
  volume = SpkVol ;                                           // Rücksetzen der Lautstärke auf letzten Lautsprecherwert
  mp3.setVolume(volume);
 
 digitalWrite(SpkOnPin, On);                                  // Lautsprecher oder Verstärker Einschalten
 
 #ifdef Konsole
  Serial.println(F("KH getr.! Lsp EIN!"));
  Serial.print(F("Spk-Vol: "));
  Serial.println(volume);
 #endif
 #endif
 #ifndef EarPhone
 digitalWrite(SpkOnPin, On);                                  // Lautsprecher oder Verstärker einschalten
 
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
    Serial.print(F("Spk-Vol speichern: "));
    Serial.println(SpkVol);
   #endif

    if (EarFirstTime == true)
    {
      EarVol = mySettings.initEarVol;                           // Wenn Kh das erste mal eingesteckt,Startlautstärke für Kopfhörer einstellen
      EarFirstTime = false;                                     // Rücksetzen Marker, Kopfhörer das erste mal gesteckt
    }

    volume = EarVol;

    mp3.setVolume(volume);                                      // KH-Lautstärke setzen
    digitalWrite(SpkOnPin, Off);                                // Lautsprecher oder Verstärker ausschalten
    
   #ifdef Konsole
    Serial.println(F("K.hörer! Lsp AUS!"));
    Serial.print(F("Ear-Volume: "));
    Serial.println(volume);
   #endif
    SpkisOn = false;                                            // Marker setzen-Lautsprecher AUS
  }
 #endif
 #ifndef EarPhone
 digitalWrite(SpkOnPin, Off);                                   // Lautsprecher oder Verstärker ausschalten
  SpkisOn = false;                                              // Marker setzen-Lautsprecher AUS
 #endif
}
#endif

/////////////////////////// Kopfhörer (Jackdetekt) ///////////////////////////////////////////////////////////

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
     if (SpkisOn == true) SpkOff();           // Lautsprecher Ausschalten
    }

    //-------------- Lautsprecher einschalten wenn Kopfhörer getrennt ---------

   else
   {
     if (SpkisOn == false) SpkOn();            // Lautsprecher Einschalten
   }
 }
  #ifdef Wecker
}
#endif
#endif

//////////////////////////////////////// StandbyTimer ////////////////////////////////////////

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
    Serial.print(F("StdB ON: "));
    Serial.print(mySettings.standbyTimer);
    Serial.println(F(" min"));
    Serial.println();
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
// -------------------------------
void disablestandbyTimer()                                            // Standbytimer deaktivieren
{
 
 //#ifdef Konsole
  Serial.println();
  Serial.println(F("StdB OFF"));
 //#endif
  sleepAtMillis = 0;
  StdBy = false;
}
// -------------------------------
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
  Serial.println(F("Pwr OFF"));

  mp3.pause();                                                      // Wiedergabe stoppen falls diese noch läuft

 #ifdef UsbStick
 #ifndef AiOPLUS
 #ifndef AiO
  digitalWrite(UsbPowerPin, HIGH);                                  // MosFet für 5V USB-Port Aus
  delay(500);
 #endif
 #endif
 #endif

 #ifdef LED_SR                                                       // LED-Ausschaltanimation
  //                                                                 // Farbfolge Rot-Grün-Blau
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

 #ifndef AiOPLUS                                                     // Ausschalten der Klassik Versionen mit Hardwareerweiterung
 #ifndef AiO                                                         // MosFet oder Pololu Powerswitch
 #ifdef HW_PowerOff
  
  digitalWrite(ShutDownPin, LOW);                                   // Ausschalten!, Low Pegel zum Rücksetzen des Einschalt-Flip-Flop
  delay(1000);
  digitalWrite(ShutDownPin, HIGH);                                  // Ausschalten!, High Pegel für Pololu Powerswitch
  delay(1000);
  digitalWrite(ShutDownPin, LOW);                                   // Widerholung!, Low Pegel zum Rücksetzen des Einschalt-Flip-Flop
  
 #endif                                                              // bei Notwendigkeit
 #endif
 #endif

 #ifdef AiOPLUS
  digitalWrite(ShutDownPin, LOW);                                   // Ausschalten!, Low Pegel
 #endif

 #ifdef AiO
 digitalWrite(ShutDownPin, LOW);                                     // Ausschalten!, Low Pegel
 #endif
 delay(5000);
 
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

//////////////////////////////////// LED-Animation //////////////////////////////////////

// ******************** LED-Animation ****************************
#ifdef LED_SR

 void LED_Animation()
 {
   if (isPlaying()) bool lsrAudioBreak = false;           // Marker, ob Wiedergabe gestoppt bei Ein-Ausschalten LED Animation
   

   #ifdef LED_SR_Switch                      // Einstieg Abfrage Tasten zur Aktivierung / Deaktivierung LED Animationen

     if (isPlaying()) lsrAudioBreak = false; // wenn Track gespielt wird, Marker setzen Wiedergabe läuft
    

     // *********** Led Animation Ein oder Ausschalten ******************
     //************ Tasten 2 und 3 langer Druck ** je nach Konfiguration Vor/Zurück oder Lauter/Leiser *************

     if ( (ButtonTwo.pressedFor(LONG_PRESS)
     || ButtonThree.pressedFor(LONG_PRESS) )
     && ButtonTwo.isPressed()
     && ButtonThree.isPressed())
     {
       lsrSwitch = true;                     // Marker auf Tasten gedrückt setzen
       #ifdef Konsole
       Serial.print(F("LED-Anim.: "));
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
       #ifdef Konsole
       if (lsrOffByStdby && lsrEnable)     // verhindert das Vielfache Ausgeben bei abschaltung über sleep.
       Serial.println(F("deaktiviert"));
       #endif
       lsrSwitch = false ;                 // Marker Tasten gedrückt rücksetzen
       lsrEnable = false ;                 // Animation deaktivieren
    
       if (isPlaying())                    // Widergabe muss gestoppt werden, sonst hängt sich der Mp3-Player auf
       {
         mp3.pause();                      // Wiedergabe stoppen  --> Fortsetzen der Wiedergabe nach 1.Durchlauf der Animationsschleife
         setstandbyTimer();
         lsrAudioBreak = true;             // Marker Wiedergabe gestoppt setzen
         strip.clear();                    // Strip löschen
         strip.show();
       }
     }

     if (lsrEnable == true)                 // Wenn wahr, Animationen durchführen
     {
   #endif                                   // Ende Abfrage Tasten zur Aktivierung LED Animationen #ifdef LED_SR_Switch

   //*************LED-Animaion by @tON ****  modifyed by @atomphil ***********************
   ///////////////// Prüfung der einmaligen Animationen /////////////////
   #ifdef CandleLight 
    if (!Candle)                                 // wenn Modifikation Schlummermodus aktiv ist dieser Wert gesetzt
    {
   #endif
   mp3.loop();
     // ----------   Liedänderung erkennen und Animation aktivieren   ---------- //
     
      
     currentDetectedTrack = queue[currentQueueIndex];
     if (currentDetectedTrack != lastDetectedTrack)

     { 
       // mp3.loop();
        strip.clear();                                     // über schwarz oder über die vorherige Animation
        if (currentDetectedTrack > lastDetectedTrack) lsrAnimationTrackMode = 1;  //nächstes Lied
        if (currentDetectedTrack < lastDetectedTrack) lsrAnimationTrackMode = 2;  // Lied zurück
        
        lsrAnimationMode = 1;
        loopCountWait = 0;   
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
      if (lsrAnimationMode == 0 && loopCount == 0 && !isPlaying()  && !knownCard)
      {
        for(int i=(strip.numPixels()/2)-1; i>=0; i--) 
        {
        // mp3.loop();
          pixelHue = firstPixelHue - (i * 65536L / (strip.numPixels()));
          strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
          strip.setPixelColor(strip.numPixels()-i-1, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();                 // Update strip with new contents
        
        firstPixelHue += 128;         // Geschwindigkeit der Animation, je kleiner um so langsamer
      }
 
     // ----------   Loop Animation: Musik spielt   ---------- //
      if (lsrAnimationMode == 0 && loopCount == 0 && isPlaying() && knownCard )
      {
        //mp3.loop();  
        for(uint16_t i=0; i<strip.numPixels(); i++) 
        {
          pixelHue = firstPixelHue + (i * 65536L / (strip.numPixels()*1));
          strip.setPixelColor(strip.numPixels()-1-i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();                // Update strip with new contents
       
        firstPixelHue += 384;       // Geschwindigkeit der Animation, je kleiner um so langsamer
      }
 
     // ----------   Loop Animation: Musik pausiert   ---------- //
      if (lsrAnimationMode == 0 && loopCount == 0 && !isPlaying() && knownCard == true)
      {
        //mp3.loop();
        for(uint16_t i=0; i<strip.numPixels(); i++) 
        {
          pixelHue = firstPixelHue + (i * 65536L / (strip.numPixels()*8));
          strip.setPixelColor(strip.numPixels()-1-i, strip.ColorHSV(pixelHue, 255, 64));       
        }
     
        strip.show();                 // Update strip with new contents
        
        firstPixelHue += 128;          // Geschwindigkeit der Animation, je kleiner um so langsamer
      }
      
     ///////////////// Einmalige Animationen bei einem Ereignis /////////////////
     
     // ----------   Einmalige Animation: Liedänderung    ---------- //
      if (lsrAnimationMode == 1 && loopCount == 0)
      {
        animCount = strip.numPixels();
        int Balken = TrckChgProgress;
        int i = 0;
     
        while (Balken > TrckChgMaxBrightness)        //Schleife solange Balken>TrckChgMaxBrightness
        {
          if (lsrAnimationTrackMode == 1)            // Wenn Track vorwärts Balken vorwärts aufbauen, Grün
          strip.setPixelColor(i, strip.ColorHSV(TrckChgColor_FFW, 255, TrckChgMaxBrightness)); 
           
          else if (lsrAnimationTrackMode == 2)       //Wenn Track zurück Balken rückwärts aufbauen, Blau
          strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(TrckChgColor_REW, 255, TrckChgMaxBrightness));             
           
          Balken -= TrckChgMaxBrightness;            // Neuer Wert für Balken = Balken - TrackChg....
          i++;
          if (animCount != 0) animCount--;

        }
        
        if ( animCount != 0 && Balken > 0 )
        {
          if (lsrAnimationTrackMode == 1)
          strip.setPixelColor(i, strip.ColorHSV(TrckChgColor_FFW, 255, Balken)); 
           
          else if (lsrAnimationTrackMode == 2)
          strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(TrckChgColor_REW, 255, Balken));             

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
        if (animCount != 0) animCount--;
        
        if (currentDetectedVolume != lastDetectedVolume) animCount = 50; 
            
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
          if (i<=volumeScopeAmount)
          strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, VolMaxBrightness)); 
           
          else if (i==volumeScopeAmount+1)
          strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, ((volumeScopeAmountMod * VolMaxBrightness) / volumeScope))); 
       
          else
          strip.setPixelColor(strip.numPixels()-i-1, strip.ColorHSV(VolColor, 255, 0)); 
       
        }
 
        strip.show();

        if (animCount == 0)
        {
          lsrAnimationMode = 0;
          TrckChgProgress = 0;        
        }
      }
 
     // ----------   Countdown Zähler über den loop als Ersatz zur delay Funktion   ----------
      if (loopCount != 0 ) loopCount--; 
    
 
     // ----------   Dadurch wird die Änderung der Lautstärke bzw. Track nur ein mal registiert   ----------
      lastDetectedVolume = currentDetectedVolume;
      lastDetectedTrack = currentDetectedTrack;
 
      #ifdef LED_SR_Switch
      }
      
      if (lsrAudioBreak == true)     // wenn Wiedergabe von LED On/Off gestoppt
      {
        mp3.start();                 // Wiedergabe fortsetzen
        disablestandbyTimer();
        lsrAudioBreak = false;       // Marker Wiedergabe läuft wieder
      }
     #endif
    }        // Ende von if(!Candle)
   #ifdef CandleLight
     if (Candle)
     { 
       strip.clear();
       SimulateFire(true, 0);               
     }
   #endif                            
 }
#endif      // Ende Abfrage Aktivierung LED Animation (#ifdef LED_SR)
// *************************** Ende LED Animation ******************************************

///////////////////////////////////////////////////////////////////////////////////////////////////
// *************************** Fehlerbehandlung des Df-Players *****************************
void mp3Error()
{
  mp3.loop();
  if (mp3error == true)                        // bei Vorliegen eines Fehlercodes vom Df-Player
  {
    
    if (StdBy == false) setstandbyTimer();     // Standbytimer starten
    #ifdef LED_SR                              // Blinksignal 3 x Magenta
    strip.fill(magenta);
    strip.show();
    delay(1000);
    strip.clear();
    strip.show();
    delay(1000);
    Zhl = Zhl-1;
    if(Zhl == 0)                                // 3x blinken
    {
      Zhl = 3;
      //nextTrack(_lastTrackFinished + 1); 
      if (!isPlaying()) nextTrack(_lastTrackFinished + 1); // Ist wiedergabe gestoppt -> Wechsel zum nächsten Track
      mp3error = false;                       // Rücksetzen Marker mp3error
    }
    #endif 
  }
}



///////////////////////////- Sperren in den Modifys - ///////////////////////////////////////////////////////////////////////////////////

// **************** Tasten und RFID Sperren: Anzeige in der Konsole ********************
void LockPause()
{
 #ifdef Konsole
  Serial.println(F("Pause -> Gesp!"));    // Play/Pausetaste sperren
 #endif
}
// -------------------------------------
void LockNext()
{
 #ifdef Konsole
  Serial.println(F("Nxt -> Gesp!"));      // Nächster Titel sperren
 #endif
}
// -------------------------------------
void LockPrevious()
{
 #ifdef Konsole
  Serial.println(F("Prev. -> Gesp!"));    // Vorhergehender Titel sperren
 #endif
}
// -------------------------------------
void LockVolUp()
{
 #ifdef Konsole
  Serial.println(F("Vol.+ -> Gesp!"));   // Lautertaste sperren
 #endif
}
// -------------------------------------
void LockVolDown()
{
 #ifdef Konsole
  Serial.println(F("Vol.- -> Gesp!")); // Leisertaste sperren
 #endif
}
// -------------------------------------
#ifdef Buttonboard
void LockMatrix()
{
 #ifdef Konsole
 if(sp)
 {
   Serial.println(F("But.brd -> Gesp!"));// Buttonboard sperren
   sp = false;
 }
 #endif
}
#endif
// ------------------------------------
void LockRFID()
{
 #ifdef Konsole
  Serial.println(F("RFID -> Gesp!"));   // Neue Karte abspielen sperren
 #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    #ifdef Buttonboard
    virtual bool handleMatrix() 
    {
      return false;
    }
    #endif
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
    unsigned long Brightn = 128;                           // Startwert für Ausfaden der Helligkeit der LED-Animation
   #endif

  public:

    void loop()
    {
      if (this->sleepAtMillis > 0 && millis() > this->sleepAtMillis)
      {
       #ifdef Konsole
        Serial.println(F("-> SLEEP!"));
       #endif
        mp3.pause();

        mySettings.standbyTimer = 99;                     // Setzt die Variable für den Standbytimer auf 99,
        //                                                // damit nach Ablauf des Sleeptimers
        //                                                // der Standbytimer sofort ausschaltet.
        setstandbyTimer();
        activeModifier = NULL;
        delete this;

      }
      else                                                // Prüfen ob die letzten 20 Sekunden laufen
      {                                                   // Lautstärke ausfaden
        if (isPlaying() && this->sleepAtMillis > 0 && millis() > this->sleepAtMillis - 20000
            && millis() > this->lastVolCheck + 1000)
        {
          if (this->lastVolume <= 0) this->lastVolume = volume;
          
          this->lastVolCheck = millis();
          uint16_t val = this->lastVolume 
          - map(this->lastVolCheck, this->sleepAtMillis - 20000, this->sleepAtMillis, 0, this->lastVolume);
          mp3.setVolume(val); 
         #ifdef Konsole
          Serial.print(F("Fade Vol: "));
          Serial.println(val);
         #endif
         #ifdef LED_SR                                      // Helligkeit der LED Animation ausfaden
          Brightn = (val*6) ;
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

    SleepTimer(float minutes)                        // Variablentyp auf float geändert für Werte < 1
    {
     #ifdef Konsole
      Serial.print(F("Sleep: "));
      Serial.print(minutes);
      Serial.println(F(" min"));
      #ifdef CandleLight
      Serial.println(F(" Candlelight"));
      #endif
     #endif
      this->sleepAtMillis = millis() + minutes * 60000;
      this->lastVolCheck = millis();
     #ifdef BatteryCheck
      if (BattLeer == false)                        // Wenn Batterie nicht leer -> Ansage der Schlummerfunktion
      {
       #endif
        delay(500);
        mp3.playAdvertisement(302);                 //advert-302- Schlummerfunktion aktiviert.
        delay(500);
        #ifdef LED_SR
         #ifdef CandleLight
         Candle = true;
         #endif
        #endif
        #ifdef DfPlayer_spez
          AdvPlaying = false;
        #endif
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
     return true;
    }
    */
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();             // Next Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();         // Zurück Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    /*virtual bool handleVolumeUp()
    {
      LockVolUp();         // Lautertaste sperren
      return true;
    }
   // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();      // Leisertaste sperren
      return true;
    }
   // ---------------------------------------------------------------
    */
   #ifdef Buttonboard
    virtual bool handleVolumeDown()
    {
      LockMatrix();      // Buttonboard sperren
      return true;
    }
   #endif
   // ---------------------------------------------------------------
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();           // Neue Karte abspielen sperren
      return true;
    }
    // ---------------------------------------------------------------
    uint8_t getActive()
    {
     #ifdef LED_SR
     #ifdef CandleLight
      Candle = false;
     #endif
     #endif
     #ifdef Konsole
      modEnd ();                             // Deaktivieren durch erneutes Auflegen dieser
     //                                      // oder einer anderen Modifikationskarte
     
     #endif
      return 1;
    }
} ;

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
      Serial.print(F("StpT->NxtStp : "));
      Serial.print(seconds);
      Serial.println(F(" sek"));
     #endif
      this->nextStopAtMillis = millis() + seconds * 1000;
    }

  public:
    void loop()
    {
      if (this->nextStopAtMillis != 0 && millis() > this->nextStopAtMillis)
      {
       #ifdef Konsole
        Serial.println(F("-> STOP!"));
       #endif
        if (isPlaying())
        {
          mp3.playAdvertisement(301);             //advert-301- Und Stopp!**Ticken**Nicht bewegen!**Ticken**weiter geht´s!
          delay(500);
          #ifdef DfPlayer_spez
           AdvPlaying = false;
          #endif
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
      mp3.loop();
      #ifdef Konsole
      Serial.println(F("StopTanz "));
      #endif
      if (isPlaying())                          // Bei laufender Wiedergabe
      {
        mp3.playAdvertisement(300);             //advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
       #ifdef DfPlayer_spez
        AdvPlaying = false;
       #endif
      }
      else                                      // Wenn keine Wiedergabe läuft
      {
        mp3.start();                            // Wiedergabe des letzt gespielten Titels starten
        mp3.playAdvertisement(300);             // advert-300- Wir spielen jetzt den Stopptanz. Wenn die Musik stoppt, bleibe stehen!
       #ifdef DfPlayer_spez
        AdvPlaying = false;
       #endif
      }

      setNextStopAtMillis();
    }
    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                // Deaktivieren durch erneutes Auflegen dieser
     #endif                                     // oder einer anderen Modifikationskarte
      return 2;
    }
} ;

//****** Modkarte *** TonUINO Sperren *************************************
// Nach Auflegen der Modifikationskarte "TonUINO Sperren"
// sind alle Tasten und neue Karte lesen gesperrt.

class Locked: public Modifier
{
  public:
    // ---------------------------------------------------------------
    virtual bool handlePause()
    {
      LockPause();            // Play/Pausetaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();              // Next Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();         // Zurück Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeUp()
    {
      LockVolUp();           // Lautertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();         // Leisertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    #ifdef Buttonboard
    virtual bool handleMatrix()
    {
      LockMatrix();          // Buttonboard sperren
      return true;
    }
    #endif
    
    // ---------------------------------------------------------------
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();            // Neue Karte abspielen sperren
      return true;
    }
    // ---------------------------------------------------------------

    Locked(void)
    {
     #ifdef Konsole
      Serial.println(F("Gesperrt!"));
     #endif
      mp3.playAdvertisement(303);                     // advert-303- TonUINO ist nun gesperrt.
     #ifdef DfPlayer_spez
      AdvPlaying = false;
     #endif
    }
    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                      // Deaktivieren durch erneutes Auflegen dieser
     #endif                                           // oder einer anderen Modifikationskarte
      return 3;
    }
} ;

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
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();            // Next Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();        // Zurück Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeUp()
    {
      LockVolUp();           // Lautertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();         // Leisertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    #ifdef Buttonboard
    virtual bool handleMatrix()
    {
      LockMatrix();      // Buttonboard sperren
      return true;
    }
    #endif
   // ---------------------------------------------------------------
    
    /*/ ---------------------------------------------------------------
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();            // Neue Karte abspielen sperren
      return true;
    }
    */
    // ---------------------------------------------------------------
    ToddlerMode(void)
    {
     #ifdef Konsole
      Serial.println(F("Toddler"));
     #endif
      if (isPlaying())                            // Wenn Wiedergabe läuft
      {
        mp3.playAdvertisement(304);               // advert-304- Tasten sind nun gesperrt.
        #ifdef DfPlayer_spez
         AdvPlaying = false;
        #endif
      }
      else                                        // wenn keine Wiedergabe läuft
      {
        mp3.start();                              // Start der Wiedergabe des letzt gespielten Titels
        mp3.playAdvertisement(304);               // advert-304- Tasten sind nun gesperrt.
        #ifdef DfPlayer_spez
          AdvPlaying = false;
        #endif
      }
    }

    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                  // Deaktivieren durch erneutes Auflegen dieser
     #endif                                            // oder einer anderen Modifikationskarte
      return 4;
    }
} ;

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
      Serial.println(F("NXT"));
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
   // --------------------------------------------------------------------
    /* virtual bool handlePause()
   {
     LockPause();                            // Pausetaste gesperrt
     return true;      
    }
    */
   // --------------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();                                   // VorTaste gesperrt
      return true;
    }
   // --------------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();                               // ZurückTaste gesperrt
      return true;
    }
   // --------------------------------------------------------------------
    #ifdef Buttonboard
    virtual bool handleMatrix()
    {
      LockMatrix();      // Buttonboard sperren
      return true;
    }
    #endif
   // ---------------------------------------------------------------
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
   // --------------------------------------------------------------------
    KindergardenMode()
    {
     #ifdef Konsole
      Serial.println(F("Kita"));
     #endif
      //delay(500);
      mp3.playAdvertisement(305);                   // advert-305- KiTa-Modus aktiviert.
      #ifdef DfPlayer_spez
       AdvPlaying = false;
      #endif
      //delay(500);

    }
    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                    // Deaktivieren durch erneutes Auflegen dieser
     #endif                                              // oder einer anderen Modifikationskarte
      return 5;
    }
} ;


//**** Modkarte ******** Titel endlos wiederholen *************************************
// Nach Auflegen der Modifikationskarte "Titel endlos wiederholen"
// wird der aktuelle Track endlos wiederholt.

class RepeatSingleModifier: public Modifier
// --------------------------------------------------------------------
{
  public:
    virtual bool handleNext()
    {
     #ifdef Konsole
      Serial.println(F("Nxt -> Trck wiederh"));
     #endif
      delay(50);
      if (isPlaying()) return true;

      playCurrentTrack();

      _lastTrackFinished = 0;
      return true;
    }
   // --------------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
     #ifdef Konsole
      Serial.println(F("Prev. -> Trck wiederh"));
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
      Serial.println(F("RepeatSingle"));
     #endif
      //delay(500);
      mp3.playAdvertisement(306);                     // advert-306 - Titel in Endlosschleife
      #ifdef DfPlayer_spez
       AdvPlaying = false;
      #endif
      //delay(500);
    }
    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                      // Deaktivieren durch erneutes Auflegen dieser
     #endif                                           // oder einer anderen Modifikationskarte
      return 6;
    }
} ;

#ifdef USB_Zugriff_SD_Karte
//**** Modkarte ******** SD-Zugriff über USB *************************************
// Diese Modifikation ist nur auf der AiO/AiO+ nutzbar.
// Nach Auflegen der Modifikationskarte "Freigabe SD-Karte über USB"
// wird der Zugriff auf die SD-Karte über den USB-Port freigeschaltet.
// Es sind alle Tasten und das abspielen von Karten  gesperrt.

class SD_Card_USB: public Modifier
// -------------------------------------------------------------------
{
  public:
    // ---------------------------------------------------------------
    virtual bool handlePause()
    {
      LockPause();           // Play/Pausetaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleNextButton()
    {
      LockNext();            // Next Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handlePreviousButton()
    {
      LockPrevious();        // Zurück Taste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeUp()
    {
      LockVolUp();           // Lautertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    virtual bool handleVolumeDown()
    {
      LockVolDown();         // Leisertaste sperren
      return true;
    }
    // ---------------------------------------------------------------
    #ifdef Buttonboard
    virtual bool handleMatrix()
    {
      LockMatrix();      // Buttonboard sperren
      return true;
    }
    #endif
    // ---------------------------------------------------------------
    virtual bool handleRFID(nfcTagObject *newCard)
    {
      LockRFID();            // Neue Karte abspielen sperren
      return true;
    }
   
    // ---------------------------------------------------------------
    SD_Card_USB(void)
    {
     #ifdef Konsole
      Serial.println(F("SD-Karte <--> USB"));
      Serial.println(F("Tonuino gesperrt!"));
     #endif
      if (isPlaying())                            // Wenn Wiedergabe läuft
      {
       mp3.playAdvertisement(307);                // advert-307- SD-Kartenzugriff über USB freigegeben.
       #ifdef DfPlayer_spez
         AdvPlaying = false;
       #endif
       delay(100);
      }
      else
      {
       mp3.start();                               // Start der Wiedergabe des letzt gespielten Titels
       delay(100);
       mp3.playAdvertisement(307);                // advert-307- SD-Kartenzugriff über USB freigegeben.
       #ifdef DfPlayer_spez
        AdvPlaying = false;
       #endif
      }
      mySettings.standbyTimer = 30;               // Standbytimer auf 30 min setzen
      setstandbyTimer();
      delay(5000);                                // Zeit für Message
      mp3.stop();                                 // Wiedrgabe stoppen
      delay(100);
      digitalWrite(Access_SD_Pin, HIGH);          // SD karten Zugang über USB freigeben
    }

    uint8_t getActive()
    {
     #ifdef Konsole
      modEnd ();                                  // Deaktivieren durch erneutes Auflegen dieser
     #endif                                       // oder einer anderen Modifikationskarte
     digitalWrite(Access_SD_Pin, LOW);            // SD karten Zugang über USB wieder sperren
     mySettings.standbyTimer = 5;                 // Standbytimer wieder auf 5 min
     setstandbyTimer();
     return 7;
    }
} ;
#endif //USB_Zugriff_SD_Karte


// ---------------------
void modEnd ()
{
 Serial.println(F("EndMod"));                 // Anzeige Deaktivierung oder Wechsel der ModKarte
 sp = true;
 /*#ifdef LED_SR
 #ifdef CandleLight
 Candle = false;
 #endif
 #endif*/
}                                             
// ENDE Modifikationskarten ////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Batteriecheck ///////////////////////////////////////////////////////////

// ************************* Spannungsüberwachung der Batterie *********************************
//                                TonUINO Klassik mit NANO
#ifdef BatteryCheck
#ifdef Klassik
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
#endif


// *********** Spannungsmessung der Batteriespannung mit der genauen Referenzspannung *************

void CheckVoltage()                                   // Spannungsmessung
{
 #ifndef AiOPLUS  
 #ifndef AiO                                          // TonUINO Klassik
 #ifndef EVERY  
  u_reference = readVcc() / 1000.0;                   // Referenzspannung = ausgelesene Referenzspanung /1000  in V

  uint16_t value = analogRead(BatteryCheckPin)*correction; // Sensorwert Batteriespannung mal Korrekturwert Klassic
 
  SumValue = SumValue + value;                        // Aufsummierte Einzelmessungen
  countTi = countTi +1;
  if (countTi >= 10)                                  // Testzyklenzahl erreicht
  {
    countTi = 0; 

   VbattGl = SumValue * u_reference / 10240 ;          // Berechnung der geglätteten Batteriespannung in Volt
   Serial.print(F("Bat.=  "));
   Serial.print ( VbattGl);
   Serial.println (F( " V"));
  
   SumValue = 0;
  
   #endif     // Ende #ifndef AiO                        
   #endif     // Ende #ifndef EVERY
    // ---------------------------------------------
   #ifdef AiO                          // AiO
  
   uint16_t value = analogRead(BatteryCheckPin);                        // Sensorwert Batteriespannung
     
   SumValue = SumValue + value;                                         // Aufsummierung der Einzelmessungen
   countTi = countTi +1;

   if (countTi >= 60)                                                   // Testzyklenzahl erreicht
   {
     countTi = 0;
     VbattGl = ((SumValue / 60) * reference * correction /  steps );    //Berechnung geglätteter BattspWert
     Serial.print(F("Bat.=  "));
     Serial.print(VbattGl);                                
     Serial.println(F(" V"));                                 
     
     SumValue = 0;
  
  
     // } gemeinsame Schlussklammer für AiO, AiOPLUS, EVERY oder Klassik weiter unten

     #endif          // Ende #ifdef AiO
     #endif          // Ende #ifndef AiOPLUS
     // ------------------------------------
     #ifdef EVERY                // Klassik mit Nano-Every
  
     uint16_t value = analogRead(BatteryCheckPin);                        // Sensorwert Batteriespannung
  
     SumValue = SumValue + value;                                         // Aufsummierung der Einzelmessungen
     countTi = countTi +1;

     if (countTi >= 60)                                                   // Testzyklenzahl erreicht
     {
       countTi = 0;
       VbattGl = ((SumValue / 60) * reference * correction /  steps );    //Berechnung geglätteter BattspWert
       Serial.print(F("Bat.=  "));
       Serial.print(VbattGl);                                
       Serial.println(F(" V"));                                 
       SumValue = 0;
  
  
       // } gemeinsame Schlussklammer für AiO, AiOPLUS , EVERY oder Klassik weiter unten

       #endif          // Ende #ifdef EVERY

       // ------------------------------------
       #ifdef AiOPLUS            // AiO Plus
  
       uint16_t value = analogRead(BatteryCheckPin);                         // Sensorwert Batteriespannung
  
       SumValue = SumValue + value;                                         // Aufsummierung der Einzelmessungen
       countTi = countTi +1;

       if (countTi >= 60)                                                   // Testzyklenzahl erreicht
       {
         countTi = 0;
         VbattGl = ((SumValue / 60) * reference * correction /  steps );    //Berechnung geglätteter BattspWert
         Serial.print(F("Bat.=  "));
         Serial.print(VbattGl);                                
         Serial.println(F(" V"));
         Serial1.print(F("Bat.=  "));                   // Ausgabe der Batteriesspannung über Serial1
         Serial1.print(VbattGl);                         // FTDI Adapter an RX1/TX1 und GND anschließen       
         Serial1.println(F(" V"));                          // Jumper auf 3,3V setzen             
         SumValue = 0;                                   // Zur Kontrolle der Batteriemessung AiOPLUS 
         //                                              // nur mit Akku und nicht über USB-Port betreiben
  
         // } gemeinsame Schlussklammer für AiO ,AiOPLUS, EVERY oder Klassik weiter unten

         #endif          // Ende #ifdef AiOPLUS

         // ------------------------------------
         // Spannung für Shutdown
         if (VbattGl <= Vshutdown)                         // wenn Batteriespannung Entladeschlussspannung erreicht
         {
           BattLeer = true;
           Serial.println(F("Bat.leer -> Off"));
           if (isPlaying())                                // Wenn Wiedergabe läuft
           {
             mp3.playAdvertisement(404);                   // Batterie ist leer, schalte mich aus
             #ifdef DfPlayer_spez
              AdvPlaying = false;
             #endif
             activeModifier = new SleepTimer(0.5);         // Sleeptimer auf 0,5 min setzen zum langsamen Ausfaden der Lautstärke
             //                                            // vor dem Shutdown.
            }
           else                                            // Wenn keine Wiedergabe läuft,sofort abschalten
           {
             mp3.playMp3FolderTrack(604);                  // Batterie ist leer, schalte aus
             waitForTrackToFinish();
             delay (500);
    
             ShutDown();                                   // Tonuino abschalten
            }
          }
          // --------------------------------------
          // Spannung für Warnung                           // wenn Batteriespannung Schwellwert für Warnung erreicht
         if (VbattGl <= Vwarning)
         {
           if (BattLeer == false)
           {
             Serial.println(F("Bat.schw "));

             if (isPlaying())
             {
               mp3.playAdvertisement(401);                         // Ansage Batterie fast leer, Aufforderung zum Laden
               #ifdef DfPlayer_spez
                AdvPlaying = false;
               #endif
              }
             else
             {
               mp3.playMp3FolderTrack(601);
               //waitForTrackToFinish();
               delay (3000);
               mp3.stop();
                if (StdBy == false) setstandbyTimer();
              }
            }            
          }              // Ende If <= Warning
        }                //gemeinsame Schlussklammer } Ende If countTi ,(60 AiO ),(10 Klassik)
}
#endif                  // Ende #ifdef BatteryCheck           


//////////////////////////////  Wecker ////////////////////////////////////

// *************************** Wecker *************************************************

#ifdef Wecker
void weckerstart()
{
 ReadWecker = analogRead(WeckerPin);        // Weil Analogpin 6 und 7 nicht als Digitalpins verwendet werden können
 //                                         // muss ein Umweg über analogRead() gegangen werden.
 #ifndef AiO
  if (ReadWecker >= 512)                    // wenn Analogwert WeckerPin > 2,5V (TonUINO Classik)
 #endif
 #ifdef AiO
  if (ReadWecker >= 1500)                   // wenn Analogwert WeckerPin > 1,6V (AiO )
 #endif
  {
    WeckerStart = true;
    Serial.println("Init Wecker"); 
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
   #ifdef Konsole
    Serial.println(F("Wecker akt.! "));
   #endif

    SpkOn();                                    // Lautsprecher auch bei angeschlossenem Kopfhörer anschalten

    ActWecker = true;                           // Marker setzen: Wecker wurde aktiviert (Erneutes Abspielen
    //                                             des Weckers erst nach Ausschalten des Tonuino möglich)

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


///////////////// - Funktionen für die Wiedergabe - //////////////////////////////////////////////////////////////////////////////////////////

// ***************** Ordner abspielen ******************
void playFolder()
{
 
   disablestandbyTimer();
  randomSeed(millis() + random(1000));
  EoQ = false;
  knownCard = true;
  _lastTrackFinished = 0;
  numTracksInFolder = mp3.getFolderTrackCount(myFolder->folder);      // Anzahl der Tracks im Ordner
  firstTrack = 1;
 //#ifdef Konsole
  Serial.print(F("Play Folder: "));
  Serial.println(myFolder->folder);                                   // Ordner Nr
  Serial_println_F(getModeName(myFolder->mode));                      // Anzeige Abspielmodus
  Serial.print(numTracksInFolder);                                    // Anzahl der Tracks
  Serial.println(F(" Tracks "));
  
 //#endif

  // **************** Abspielmodi ***********************************************

  bool randomOrder   = false;                 // entweder Tracks in Sortierung oder gemischt abspielen
  bool randomStart   = false;                 // entweder Start playback mit erstem Track oder einem Zufallstrack
  uint8_t fromTrack  = 1;                     // Nummer des 1.Tracks des Abspielbereiches(default 1)
  uint8_t toTrack    = numTracksInFolder;     // Nummer des letzten Tracks des Abspielbereiches (default lastTrack)
  uint8_t firstTrack = 1;                     // Nummer des Tracks, der zuerst abgespielt wird
 #ifdef Konsole
  bool printRange    = false;
 #endif
  switch (myFolder->mode)                     // Abspielmodus einstellen
  {
    case 1:                                   // Hörspielmodus: eine zufällige Datei aus dem Ordner
      randomStart = true;                     // Start mit zufälligem Track -> Ja
    break;

    case 2:                                   // Album Modus: kompletten Ordner spielen
    
    break;

    case 3:                                   // Party Modus: Ordner in zufälliger Reihenfolge
      randomOrder = true;                     // Zufällige Reihenfolge -> Ja
      randomStart = true;                     // Start mit zufälligem Track -> Ja
    break;

    case 4:                                   // Einzel Modus: eine Datei aus dem Ordner abspielen
      firstTrack = myFolder->special;         // Tracknr aus myFolder->special
    break;

    case 5:                                   // Hörbuch Modus: kompletten Ordner spielen und Fortschritt merken
      firstTrack = EEPROM.read(myFolder->folder);   // Starttrack aus EEprom Fortschritt auslesen
    break;

    case 6:                                   // Spezialmodus Von-Bis: Hörspiel: eine zufällige Datei aus dem Ordner
     #ifdef Konsole
      printRange  = true;
     #endif
      fromTrack   = myFolder->special;        // Start track
      toTrack     = myFolder->special2;       // End track
      randomStart = true;                     // zufälliger Track -> Ja
    break;

    case 7:                                   // Spezialmodus Von-Bis: Album: alle Dateien zwischen Start und Ende spielen
     #ifdef Konsole
      printRange = true;
     #endif
      firstTrack = myFolder->special;         // erster track
      fromTrack  = myFolder->special;         // Start track
      toTrack    = myFolder->special2;        // End track
      randomOrder = false;                    // Zufällige Reihenfolge -> Nein
      randomStart = false;                    // Start mit zufälligem Track -> Nein 
    break;

    case 8:                                   // Spezialmodus Von-Bis: Party Ordner in zufälliger Reihenfolge
     #ifdef Konsole
      printRange  = true;
     #endif
      fromTrack   = myFolder->special;        // Start track
      toTrack     = myFolder->special2;       // End track
      randomOrder = true;                     // Zufällige Reihenfolge -> Ja
      randomStart = true;                     // Start mit zufälligem Track -> Ja
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
   #ifndef AiO                                               // TonUINO Klassik
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
  Serial.print(F("Pl. Sct: "));
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

    Serial.println(F("Sct. n.bel.!"));

    ShortCutIsPlaying = false ;                         // Marker setzen "Kein shortcut gespielt"
  }
}

// **************** aktuellen Titel spielen ********************

void playCurrentTrack()                                            // Titel vom Anfang spielen
{
  mp3.loop();
  mp3.playFolderTrack(myFolder->folder,queue[currentQueueIndex]); // Abspielen des aktuellen Titels in der Queue 
   
 //#ifdef Konsole
  Serial.print(currentQueueIndex);
  Serial.print(F(" von "));
  Serial.println(queueSize);
  Serial.print(F("Pl. Q-idx "));
  Serial.print(currentQueueIndex);                                 // Tracknummer in der Queue
  Serial.print(F(", Trk "));
  Serial.println(queue[currentQueueIndex]);                        // Tracknummer im Ordner
 //#endif

  disablestandbyTimer(); 
  Serial.println(); 
}


//*********************** Track vor *** Track zurück *****************************
//********************************************************************************

// ************ Track vor (nächster Titel) *********************
static void nextTrack(uint16_t track)
{
  //mp3.loop();
  Serial.println(F("nxTr aufgerufen "));
  if (activeModifier != NULL)
  if (activeModifier->handleNext() == true)  return;     // Wenn NextTrack gesperrt -> Abbruch
  // -------------------------
        
  if (track == _lastTrackFinished) 
  {
   Serial.println(F("Trk = lastTrk "));
   return;
  }

  if (track == _lastTrackFinished +2)
  { 
   Serial.println(F("dbl nxtTr "));
   track = track-1;
  }
 
  // ---------------------------
  _lastTrackFinished = track;

  if (knownCard == false)                                 // Wenn Karte nicht bekannt -> Abbruch
  {
    // Wenn eine neue Karte angelernt wird soll das Ende eines Tracks nicht
    // verarbeitet werden
   Serial.println(F("knCard = false "));
    return;
  }
  #ifdef Konsole
  Serial.println();
  Serial_print_F(getModeName(myFolder->mode));
  Serial.println(F(" -> nxtTrk "));
  #endif
  bool bStop = false;
  bool Single = false;
  
  switch (myFolder->mode)
  {
   // --------------------------------------
    case 1: //Hoerspiel
    case 6: //Hoerspiel-SpezialVonBis
    case 4: //EinzelTitel
      Single = true;                                         // Single Track Modus
      bStop = true;                                          // Stop am Ende des Titels
      
      
      break;
   // --------------------------------------
    case 2: //Album
    case 7: //Album-SpezialVonBis
      Single = 0;
     //#ifdef Konsole
      Serial.print(F("idx "));
      Serial.print(currentQueueIndex);
      Serial.print(F(" -> "));
     //#endif
     if((currentQueueIndex + Steps) < queueSize)              // wenn Queueindex plus Sprung unter queueSize
     {
       EoQ = false;                                           // Queue noch nicht am Ende
       currentQueueIndex = (currentQueueIndex + Steps);       // Weiterspringen in der Queue
     }
     else                                                     // wenn Queueindex plus Sprung gleich oder größer queueSize
     {
       EoQ = true;
       currentQueueIndex = (queueSize -1);                    // Gehe zum Ende der queue
       bStop = true ;                                         // Stop am Ende der Queue
       //#ifdef Konsole
       Serial.println(currentQueueIndex);
       Serial.println(F(" - EoQ"));   
       //#endif
     }     
     
     Steps = 1;                                             // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;
   // --------------------------------------
    case 3: //Party
    case 8: //Party-SpezialVonBis
      Single = 0;
     //#ifdef Konsole
     Serial.print(F("idx "));
     Serial.print(currentQueueIndex);
     Serial.print(F(" -> "));
     //#endif
      currentQueueIndex = currentQueueIndex + Steps;        // Weiterschalten in der Queue
      if (currentQueueIndex >= queueSize)                   // Ende der Queue erreicht oder überschritten
      {
        //#ifdef Konsole
        Serial.println(F("Ende, mische neu."));
       //#endif
       
       EoQ = true;
       shuffleQueue();                                      // Am Ende der Queue soll neu gemischt werden
       currentQueueIndex = 1;                               // Ende der Queue -> springe zum Start
      
       bStop = 0 ;                                          // Queue wird endlos abgespielt
       
      }
      else
      {
        EoQ = false;
      }
      Steps = 1;                                            // Rücksetzen der Sprungweite auf 1 für Einzelschritt
      break;
   // --------------------------------------
    case 5: //Hoerbuch
     Single = 0;
     //#ifdef Konsole
     Serial.print(F("idx "));
     Serial.print(currentQueueIndex);
     Serial.print(F(" -> "));
     //#endif
     if (ResetHB == false)                                    // Wenn nxtTrk und update EEProm HB nicht gesperrt
     { 
       if (currentQueueIndex + Steps < queueSize)             // Wenn Sprung unter Queue Ende bleibt
       {
         currentQueueIndex = currentQueueIndex + Steps;       // Weitersprung in Queue
          if (currentQueueIndex + Steps >= queueSize)          // Wenn Sprung Queue Ende erreicht oder Überschreitet
          {
           EoQ = true;
           currentQueueIndex = (queueSize - 1);               // index auf Ende der Queue setzen
          }
         #ifndef AiO
         EEPROM.update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
         #endif
         #ifdef AiO
         EEPROM_update(myFolder->folder, queue[currentQueueIndex]);  // Fortschritt im EEPROM abspeichern
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
         EEPROM.update(myFolder->folder, 1);                        // Fortschritt am Ende HB autom.zurücksetzen (Classik)
         #endif
         #ifdef AiO
         EEPROM_update(myFolder->folder, 1);                         // Fortschritt am Ende HB autom.zurücksetzen (AiO)
         #endif
         #ifdef Konsole
         Serial.println(F("Hörb->Anf."));
         #endif
         bStop = true;                                               // Stop am Ende der Queue
         Steps = 1;                                                  // Rücksetzen der Sprungweite auf 1 für Einzelschritt
         break;
        }
     // --------------------------------------
     default:
     return; // do nothing
    }
    ResetHB = false;                                                // Rücksetzen Marker Hörbuch reset, Aufheben der Sperre
  } 
  // ---------------------------------------
  
  if (!Single)
  {
   delay(250);
   playCurrentTrack();                   // wenn kein Singletrack Modus aktuellen Titel spielen
  }
  // *************** queue zu Ende  ***********
  if (bStop)                                         // wenn Stop am Ende der Queue gesetzt
  {
    delay(200);
    if (!isPlaying())                                // wenn Titel beendet ist
    {
      EoQ = true;
      bStop = false;
      Serial.println(F("EoQ->Stp"));
      mp3.pause();
      delay(500);
      if(!Single) currentQueueIndex = (queueSize - 1); // PlayTaste spielt nach EoQ letzten Titel der queue
      setstandbyTimer();
    }
  }
}

//************ Track zurück **( vorheriger Titel) ************************
static void previousTrack()
{
 #ifdef Konsole
  Serial.print(F("prev.Trck : "));
  Serial_println_F(getModeName(myFolder->mode));
 #endif
 
  switch (myFolder->mode)
  {
   // ----------------------------------------------------
    
    case 1: // Hörspielmodus
    case 6: // Hörspielmodus-SpezialVonBis
      //Serial.println(F("Hörspielmodus -> Track von vorne spielen"));
    break;
    
   // -----------------------------------------------------
    case 2: //Album
    case 7: //Album-SpezialVonBis
     #ifdef Konsole
      Serial.print(F("Album -> Trck zur.: "));
     #endif
     //#ifdef Konsole
      Serial.print(currentQueueIndex);
      Serial.print(F(" -> "));
     //#endif 
     if (currentQueueIndex > (Steps -1))              // Prüfung ob QueueIndex noch über der Sprungweite liegt
     currentQueueIndex = currentQueueIndex - Steps;  // Rücksprung um Sprungweite

     else                                             // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat
     currentQueueIndex = 0;                          // QueueIndex auf Null setzen
     
     Steps = 1;                                      // Rücksetzen der Sprungweite auf 1 für Einzelschritt
    break;
   // -----------------------------------------------------
    case 3: // Party
    case 8: // Party-SpezialVonBis
     //#ifdef Konsole
     Serial.print(currentQueueIndex);
     Serial.print(F(" -> "));
     //#endif 
     if (currentQueueIndex > (Steps -1))             // Prüfung ob QueueIndex noch über der Sprungweite liegt
     currentQueueIndex = currentQueueIndex - Steps;  // Rücksprung um Sprungweite

     else                                             // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat
     currentQueueIndex = queueSize - 1;             // QueueIndex auf höchsten Wert setzen
     
     Steps = 1;                                     // Rücksetzen der Sprungweite auf 1 für Einzelschritt
    break;
   // -----------------------------------------------------
    case 4: // Einzel
      #ifdef Konsole
      Serial.println(F("Single Mod.-> Trck repeat."));
      #endif
    break;
   // -----------------------------------------------------
    case 5: // Hörbuch
      #ifdef Konsole
      Serial.println(F("Hörb. -> Fortschr.sp."));
      #endif
     //#ifdef Konsole
      Serial.print(currentQueueIndex);
      Serial.print(F(" -> "));
     //#endif 
     if (currentQueueIndex > (Steps -1))                         // Prüfung ob QueueIndex noch über der Sprungweite liegt
     currentQueueIndex = currentQueueIndex - Steps;              // Rücksprung um Sprungweite

     else                                                        // Wenn QueueIndex 0 oder Wert unter Sprungweite erreicht hat

     currentQueueIndex = 0;                                     // QueueIndex auf Null setzen
     Steps = 1;                                                     // Rücksetzen der Sprungweite auf 1 für Einzelschritt
     #ifndef AiO
     EEPROM.update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern (Klassik)
     #endif
     #ifdef AiO
     EEPROM_update(myFolder->folder, queue[currentQueueIndex]); // Fortschritt im EEPROM abspeichern (AiO)
     #endif
 
    break;
   // -----------------------------------------------------
    default:
    return; // do nothing

  }
 _lastTrackFinished --;
  playCurrentTrack();
  delay(500);
}

//******************************************************************************************************************************

//****************** Is Playing ************************
bool isPlaying()
{
  return !digitalRead(BusyPin);
}

//************* Track zu Ende spielen **************************
void waitForTrackToFinish()
{
 unsigned long currentTime = millis();
 #define TIMEOUT 1000

 #ifdef Konsole
 Serial.println (" Wait for TtF");
 #endif

  do                                                          // Schleife bis Ende Track und 1000 ms danach
  {
    mp3.loop();                                               // Meldung vom df-Player über serial?
  }
  while (!isPlaying() && millis() < currentTime + TIMEOUT);   // Schleife verlassen nach Ende Track plus 1 sek

  delay(1000);                                                // 1 sek Pause

  do                                                          // Schleife bis Track spielt
  {
    mp3.loop();                                               // Meldung vom df-Player über serial?
  }
  while (isPlaying());                                        // Schleife verlassen wenn Wiedergabe beendet oder pausiert
  delay(1000);                                                // delay beseitigt Timeouterrors der df-Player Bibliothek.
    
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
  
  mp3.setVolume (volume);                     // an df-Player übergeben
  
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
  
  mp3.setVolume (volume);                     // an df-player übergeben
  
  //#ifdef Konsole
  msgMax = true ;
  Serial.print(F("Leiser -> "));
  Serial.println(volume);
  //#endif
}

// ************************************************************************************

/////////////////////////////  Funktionen über die Tasten aufrufen ///////////////////////////////////////////////////

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
  if (activeModifier != NULL)                                 // wenn Modifikation aktiv
  if (activeModifier->handleVolumeUp() == true) return;     // wenn Taste gesperrt kein VolUp
      
  #ifdef SpkOnOff
  if (SpkisOn == true)                                 // wenn Lautsprecher an
  {
   #endif
    //#ifdef Konsole
    if (volume >= mySettings.maxVolume )               // wenn Vol größer oder gleich maxVolume Spk
    {
      if (msgMax == true)                              // wenn max Volume erreicht
      {
       Serial.println("Max Vol !");                  // Anzeige Konsole 
       msgMax = false ;                                 // Rücksetzen max Volume erreicht
      }
    }
    //#endif
    if (volume < mySettings.maxVolume)                // wenn Vol kleiner maxVolume Spk
    {
      if (longPressVol == true)                       // VolÄnderung durch longPress
      {  
       if (countVolCh == 0)lauter();                  // Nächster Schritt longPress Volume
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
   
    if (volume >= mySettings.maxEarVol)                // wenn Vol größer oder gleich maxVolume Ear
    {
      if (msgMax == true)
      {
        Serial.println("Max Vol !");
        msgMax = false ;
      }
    }
   
    //#endif
    if (volume < mySettings.maxEarVol)                 // wenn Vol kleiner maxVolume Ear
    {
      if (longPressVol == true)                        // VolÄnderung durch longPress
      {  
       if (countVolCh == 0) lauter();                  // Nächster Schritt longPress Lauter
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
  if (activeModifier != NULL)                                // wenn Modifikation aktiv
  if (activeModifier->handleVolumeDown() == true) return;    // wenn Taste gesperrt kein VolDown

  #ifdef SpkOnOff
  if (SpkisOn == true)                                 // wenn Lautsprecher an
  {
   #endif    
    //#ifdef Konsole
    if (volume <= mySettings.minVolume)               // wenn Vol kleiner oder gleich minVolume 
    {
     if (msgMin == true) 
      {
       Serial.println("Min Vol !");
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
   if (volume <= mySettings.minEarVol)                // wenn Vol kleiner oder gleich minVolume 
    {
      if (msgMin == true)
     {
       Serial.println("Min Vol !");
       msgMin = false ;
     }
    }
    
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
  if (activeModifier != NULL)                               // wenn Modifikation aktiv
  if (activeModifier->handleNextButton() == true) return;   // wenn Taste gesperrt Titel nicht weiter
  Steps = 1;                                                // Schrittweite auf 1 Track setzen
  nextTrack(_lastTrackFinished + 1);                        // beliebige Tracknummer außer _lastTrackFinished

  delay(500);
}

// ************ Titel Zurück Taste *************
void previousButton()
{
  if (activeModifier != NULL)                                 // wenn Modifikation aktiv
  if (activeModifier->handlePreviousButton() == true) return; // wenn Taste gesperrt Titel nicht zurück
  previousTrack();                                            // Track zurück
  delay(500);
}

#ifdef FIVEBUTTONS
#ifdef JumpLongPress

// ************ Titel Vorwärts Sprung *************
void JumpForw()
{
  if (activeModifier != NULL)                              // wenn Modifikation aktiv
  if (activeModifier->handleNextButton() == true)  return; // wenn Taste gesperrt Titel nicht weiter
  Steps = SetJump;                                         // Sprungweite setzen
  nextTrack(_lastTrackFinished + 1);                       // beliebige Tracknummer außer _lastTrackFinished
  delay(3000);                                             // Delay zum Anspielen des angesprungenen Titels
}
// ************ Titel Rückwärts Sprung *************
void JumpBackw()
{
  if (activeModifier != NULL)                              // wenn Modifikation aktiv
  if (activeModifier->handlePreviousButton() == true) return;// wenn Taste gesperrt Titel nicht zurück
  Steps = SetJump;                                        // Sprungweite setzen
  previousTrack();                                        // Track zurück
  delay(3000);                                            // Delay zum Anspielen des angesprungenen Titels
}
#endif
#endif

////////////////////////////////  ADMIN - MENUE  //////////////////////////////////////////////////////////////////////

// ************** TimeOutfunktion für das Adminmenü **********************
// **************** Start TimeOut Adminmenü ******************************
void AdmTimeOutStart()
{
  AdmTimeOut = millis();                             // Start der Timeoutzeit
 #ifdef Konsole
  Serial.print(F("AdmTimeOut: "));
  Serial.print(Minuten);
  Serial.println(F(" min"));
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

    // Admin menu gesperrt - Es kann immer mit der admin card gestartet werden
    if (mySettings.adminMenuLocked == 1)            // Nur mit Adminkarte
    {
     #ifdef Konsole
      Serial.println(F("Gesp.!- Nur Adminkarte"));
     #endif
      mp3.start();
      delay(500);
      mp3.playAdvertisement(500);                  // 500- Das Adminmenü ist geschützt. Zum Starten musst du die Adminkarte auflegen.
      #ifdef DfPlayer_spez
       AdvPlaying = false;
      #endif
      delay(3000);
      return;
    }
    else
    {
      knownCard = false;
    }
  }
  knownCard = false;

  //*********************Admin-Menü-Funktionen auswählen*****************

  // Aufbau des Voicemenüs
  // uint8_t subMenu          --> Rückgabewert der Nummer des subMenüs
  // = voiceMenu(
  // 9,    (numberOfOptions)  --> Anzahl der subMenüs 9
  // 900,  (startMessage)     --> Tracknummer der Ansage im mp3Ordner 0900
  // 900,  (messageOffset)    --> nachfolgende Ansagen nach dieser Tracknummer 0901-0909
  // false,(preview)          --> Keine Vorschau
  // false,(previewFromFolder)--> Keine Vorschau
  // 0,   ,(defaultValue)     --> von diesem wert ab zählen  1 - 9
  // true) (exitWithLongPress)--> Abbruch mit langem Tastendruck möglich

  uint8_t subMenu = voiceMenu(9, 900, 900, false, false, 0, true); // 900- Submenu 0, "Willkommen im Adminmenü,Wähle eine Funktion ...(mp3/ 901 - 909)
  //                                                               // 901- Submenu 1, "Eine Karte neu konfigurieren"
  //                                                               // 902- Submenu 2, "Einzelkarten für einen Ordner festlegen"
  //                                                               // 903- Submenu 3, "Modifikationskarte erstellen"
  //                                                               // 904- Submenu 4, "Shortcut configurieren"
  //                                                               // 905- Submenu 5, "Funktion der Vor/Zurücktasten und der Lautstärketasten tauschen"
  //                                                               // 906- Submenu 6, "Einstellungen für die Lautstärke und den Klangcharakter ändern"
  //                                                               // 907- Submenu 7, "StandbyTimer Konfigurieren"
  //                                                               // 908- Submenu 8, "Admin Menü schützen"
  //                                                               // 909- Submenu 9, "Tonuino zurücksetzen"

  if (AbbrActive == true)  subMenu = 0;
  if (subMenu == 0)
  {
    progmode = 0;
    return;
  }
  if (subMenu >= 4) progmode = 0;
  if (subMenu != 6)  AdjVol = false;

  // ************** Karte neu konfiguriern *************************
  if (subMenu == 1)                                           // 901- "Karte neu Konfigurieren"
  {
    progmode = 1;                                             // Kartenart - Neue Karte
    if (AbbrActive == true) return;

    resetCard();
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  // ******* Einzelkarten für einen Ordner festlegen *********************
  else if (subMenu == 2)                                      // 902- "Einzelkarten für einen Ordner festlegen"
  {
    progmode = 2;                                             // Kartenart - Einzelkarte (Ein Titel je Karte)
    if (AbbrActive == true) return;

    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.mode = 4;                      // Abspielmodus - Einzelmodus
   #ifdef CountFolders
    tempCard.nfcFolderSettings.folder = voiceMenu(numFolders - 2, 301, 0, true); // 301- "Verwende die Vor/zurück-tasten um einen Ordner auszuwählen"
   #endif                                                                        // numFolders -2 -> Anzahl der ermittelten Ordner 
   //                                                                            // abzueglich mp3 und advert Ordner

   #ifndef CountFolders
     #ifndef ZaehleOrdner
     tempCard.nfcFolderSettings.folder = voiceMenu(99, 301, 0, true);             // 301- "Verwende die Vor/zurück-tasten um einen Ordner auszuwählen"
     #endif                                                                        // 001 - 099 setzt die Ordnernummer Kurzer Druck + oder - 1
     #ifdef ZaehleOrdner                                                          //                                  Langer Druck + oder - 10
     tempCard.nfcFolderSettings.folder = voiceMenu(numFolders - 2, 301, 0, true);
     #endif
   #endif
   if (AbbrActive == true) return;

    numTracksInFolder = mp3.getFolderTrackCount(tempCard.nfcFolderSettings.folder); // Tracks im Ordner zählen
    #ifdef Konsole
    Serial.print(F("Dat. im Ordner: "));
    Serial.print(tempCard.nfcFolderSettings.folder);
    Serial.print(F(" -> "));
    Serial.println(numTracksInFolder);
    #endif  

    uint8_t special = voiceMenu(numTracksInFolder, 321, 0,true,tempCard.nfcFolderSettings.folder);
    //                                                                  // 321- "Startdatei auswählen"
    //                                                                  // setzt den Start-Track

    StartTrack = special;                                               // zwischenspeichern StartTrack
    if (AbbrActive == true) return;
    rolling = false;                                                    // Sprung vom letzten Track -> Track 1 gesperrt

    uint8_t special2 = voiceMenu(numTracksInFolder, 322, 0,true,tempCard.nfcFolderSettings.folder, special);
    //                                                                 // 322- "Enddatei auswählen"
    //                                                                 // setzt den End-Track

    rolling = true;                                                    // Sprung letzter Track -> Track 1 entsperrt
    if (AbbrActive == true) return;

    mp3.pause();
    delay(500);
    mp3.playMp3FolderTrack(939);                // 939 - "OK, bitte lege nun nacheinander die Karten auf die Box.
    //                                          //      Ich werde die jeweilige Nummer vorher ansagen, damit du nicht durcheinander kommst.
    //                                          //      Zum Abbrechen einfach eine der Lautstärketasten drücken!"

    delay(500);
    for (uint8_t x = special; x <= special2; x++)              // Schleife bis alle Einzelkarten geschrieben sind, oder Abbruch
    {
      waitForTrackToFinish();
      mp3.playMp3FolderTrack(x);
      waitForTrackToFinish();
      tempCard.nfcFolderSettings.special = x;
     #ifdef Konsole
      Serial.print(F("Karte "));
      Serial.print(x);
      Serial.println(F(" auflegen"));
      #endif
      AdmTimeOutStart();                                        // Start der Timeoutzeit

      // ****** Einzelkarte schreiben ********
      do                                                        // Schleife bis Karte aufgelegt, oder Abbruch
      {
        AbbrAdminTimeout();                                     // Abbruch nach Timeout Adminmenü

        readButtons();
        #ifndef FIVEBUTTONS
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased()) // Lauter oder Leiser-Taste wurde für Abbruch gedrückt?
        #endif
        #ifdef FIVEBUTTONS
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased()
        || ButtonFour.wasReleased()||ButtonFive.wasReleased()) // Lauter/Leiser-Taste oder Vor/Zurück Taste wurde für Abbruch gedrückt?
        #endif
        {
         #ifdef Konsole
          Serial.println(F("Abbr."));
         #endif
          AbbrActive = true;                                    // Abbruch ist aktiv
          mp3.playMp3FolderTrack(802);                          // 802- "OK, ich habe den Vorgang abgebrochen."
          waitForTrackToFinish();
          setstandbyTimer();
          return;
        }
     }
     while (!mfrc522.PICC_IsNewCardPresent());                  // bleibe in der Schleife solange keine Karte aufgelegt

      if (mfrc522.PICC_ReadCardSerial())                        // RFID Karte wurde aufgelegt
      {
        delay(500);
       #ifdef Konsole
        Serial.println(F("schreibe Karte"));
       #endif
        writeCard(tempCard);                                    // Karte wird geschrieben
        delay(100);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
      }
    }         // Ende der Schleife bis alle Einzelkarten geschrieben sind
  }

  // *********** Modifikationskarten erstellen ***********************
  else if (subMenu == 3)                                        // 903- "Modifikationskarte erstellen"
  {
    progmode = 3;                                               // Kartenart - Modifikationskarte
    if (AbbrActive == true) return;

    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.folder = 0;
    tempCard.nfcFolderSettings.special = 0;
    tempCard.nfcFolderSettings.special2 = 0;

    #ifndef USB_Zugriff_SD_Karte
    #ifndef Bluetooth
    tempCard.nfcFolderSettings.mode = voiceMenu(6, 970, 970, false, false, 0, true); // 970 - 976
    #endif
    #endif
    #ifdef USB_Zugriff_SD_Karte
    tempCard.nfcFolderSettings.mode = voiceMenu(7, 970, 970, false, false, 0, true); // 970 - 977
    #endif
    #ifdef Bluetooth
    tempCard.nfcFolderSettings.mode = voiceMenu(7, 970, 970, false, false, 0, true); // 970 - 977
    #endif
    //970-tempCard.nfcFolderSettings.mode 0, Bitte wähle nun deine Modifikationskarte mit den Vor/zurück-tasten aus.
    //971- tempCard.nfcFolderSettings.mode 1, Schlummermodus
    //972- tempCard.nfcFolderSettings.mode 2, Stopptanz - TonUINO spielt Stopptanz mit dir
    //     und hält zufällig für dich die Wiedergabe kurz an.
    //973- tempCard.nfcFolderSettings.mode 3, TonUINO Sperren
    //974- tempCard.nfcFolderSettings.mode 4, Krabbler-Modus - Alle Tasten vom TonUINO werden für die ganz Kleinen gesperrt.
    //     Karten funktionieren weiterhin.
    //975- tempCard.nfcFolderSettings.mode 5, KiTa-Modus - Damit es keinen Streit mehr gibt werden neue Karten
    //     nicht sofort gespielt sondern erst nachdem das aktuelle Lied vorbei ist.
    //     Die Vor- und Zurücktasten sind gesperrt.
    //976- tempCard.nfcFolderSettings.mode 6, Titel wiederholen - den aktuellen Titel endlos wiederholen.
    //977- tempCard.nfcFolderSettings.mode 7, USB_Zugriff_SD_Karte - Über den USB Port kann auf die SD-Karte zugegriffen werden.
                         

    // Hier wären noch drei weitere Modifikationen möglich (977,978,979)


    if (tempCard.nfcFolderSettings.mode != 0)                     // wenn Option ungleich 0
    {
      if (AbbrActive == true) return;

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

      AdmTimeOutStart();                                          // Start der Timeoutzeit Adminmenü

     // ********** Modifikationskarte schreiben ***********
      do                                                          // Schleife bis Karte aufgelegt, oder Abbruch
      {
        AbbrAdminTimeout();                                       // Abbruch nach Timeout Adminmenü

        readButtons();
        #ifndef FIVEBUTTONS
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased()) // Lauter oder Leiser-Taste wurde für Abbruch gedrückt?
        #endif
        #ifdef FIVEBUTTONS
        if (ButtonTwo.wasReleased()||ButtonThree.wasReleased()
        || ButtonFour.wasReleased()||ButtonFive.wasReleased()) // Lauter/Leiser-Taste oder Vor/Zurück Taste wurde für Abbruch gedrückt?
        #endif
        {
         #ifdef Konsole
          Serial.println(F("Abbr."));
         #endif
          AbbrActive = true;                                    // Abbruch ist aktiv
          mp3.playMp3FolderTrack(802);                          //802- "OK, ich habe den Vorgang abgebrochen.
          waitForTrackToFinish();
          setstandbyTimer();
          return;
        }
      }
      while (!mfrc522.PICC_IsNewCardPresent());                 // bleibe in der Schleife solange keine Karte aufgelegt

      if (mfrc522.PICC_ReadCardSerial())                        // RFID Karte wurde aufgelegt
      {
       #ifdef Konsole
        Serial.println(F("schreibe Karte"));
       #endif
        writeCard(tempCard);                                    // Karte wird geschrieben
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
    if (AbbrActive == true) return;

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

    if (AbbrActive == true) return;

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
    if (AbbrActive == true) return;

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

    if (AbbrActive == true) return;

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
    if (AbbrActive == true) return;

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

    if (AbbrActive == true) return;

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
   if (AbbrActive == true) return;

   #ifdef  FIVEBUTTONS  
    uint8_t temp = voiceMenu(2, 930, 930, false);                       //930- "Möchtest du die Vor/Zurücktasten mit den  Lautstärketasten tauschen?
   #endif                                                                  // Die Funktionen der jeweiligen Tastenpaare werden untereinander getauscht.
   #ifndef  FIVEBUTTONS  
    uint8_t temp = voiceMenu(2, 929, 930, false);                       //929- "Möchtest du Shortpress und Longpress der Vor/Zurücktasten tauschen
   #endif                                                                  //Dabei werden die Funktionen von kurzem und langem Tastendruck getauscht.   

    if (temp == 1)                                                  //931- "Ja
    {                                                               // Funktionen tauschen
      if(mySettings.invertVolumeButtons == false)                   
      mySettings.invertVolumeButtons = true;                        
      else
      mySettings.invertVolumeButtons = false;
    }
    else                                                            //932- "Nein
    { }                                                            //keine Änderung, Funktionen werden nicht getauscht   
  }

 // ********** Lautstärke und EQ Einstellungen ändern *********************

 else if (subMenu == 6)                                            // 906- "Einstellungen für die Lautstärke und den Klangcharakter ändern
  {
    if (AbbrActive == true) return;

   #ifdef EarPhone
    uint8_t VolMenu = voiceMenu(3, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
    // 910 - Bitte wähle mit den Vor/zurück-tasten die Einstellung aus und bestätige mit der Pausetaste
    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
    // 912 - Einstellungen für die Lautstärke des Kopfhörers ändern
    // 913 - Den Klangcharakter konfigurieren
   #endif
   #ifndef EarPhone
    uint8_t
    VolMenu = voiceMenu(2, 910, 910, false, false, 0, true);      // (mp3/ 910 - 913)
    if (VolMenu == 2) VolMenu = 3;                               
    // 910 - Bitte wähle mit den Vor/zurück-tasten die Einstellung aus und bestätige mit der Pausetaste
    // 911 - Einstellungen für die Lautstärke des Lautsprechers  ändern
    // 913 - Den Klangcharakter konfigurieren
   #endif
    // ********** Lautstärkeeinstellungen Lautsprecher ***************

    if (VolMenu == 1)                                               // 911- "Einstellungen für die Lautstärke des lautsprechers  ändern
    {
      if (AbbrActive == true) return;

      int LspMenu = voiceMenu(3, 914, 914, false, false, 0, true);    //(mp3/ 914- 917)
      // 914 - Bitte wähle mit den Vor/zurück-tasten die zu ändernde Lautstärke aus
      //       und bestätige mit der Pausetaste
      // 915 - Maximale Lautstärke Lautsprecher
      // 916 - Minimale Lautstärke Lautsprecher
      // 917 - Lautstärke des Lautsprechers beim Start

      // ********** Max Lautstärke des Lautsprechers *******************

      if (LspMenu == 1)                                                       // 915 - Maximale Lautstärke Lautsprecher
      {
        if (AbbrActive == true) return;

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
        if (AbbrActive == true) return;
        AdjVol = true;
        mySettings.minVolume = voiceMenu(mySettings.maxVolume - 1, 934, 0,    // 934 - Bitte wähle mit den Vor/zurück-tasten die
                                         false, false, mySettings.minVolume); //       min. Lautstärke des Lautsprechers aus
      }

      // ********** Initial Lautstärke des Lautsprechers *******************

      if (LspMenu == 3)                                                       // 917 - Lautstärke des Lautsprechers beim Start
      {
        if (AbbrActive == true) return;
        AdjVol = true;
        mySettings.initVolume = voiceMenu(mySettings.maxVolume - mySettings.minVolume + 1, 935, // 935 - Bitte wähle mit den Vor/zurück-tasten die
                                          mySettings.minVolume - 1, false, false,               //      Lautstärke des Lautsprechers beim Start aus
                                          mySettings.initVolume - mySettings.minVolume + 1)
                                         + mySettings.minVolume - 1;
      }
    }

    // ********** Lautstärkeeinstellungen Kopfhörer ***************
#ifdef EarPhone     
    if (VolMenu == 2)                                               // 912- "Einstellungen für die Lautstärke des Kopfhörers ändern

    {
      if (AbbrActive == true) return;

      uint8_t EarMenu = voiceMenu(3, 918, 918, false, false, 0, true);              //  (mp3/ 918 - 921)
     // 918 - Bitte wähle mit den Vor/zurück-tasten die zu ändernde Lautstärke aus
     //       und bestätige mit der Pausetaste
     // 919 - Maximale Lautstärke Kopfhörer
     // 920 - Minimale Lautstärke Kopfhörer
     // 921 - Lautstärke des Kopfhörers beim Start

      // ********** Maximale Lautstärke Kopfhörer **************************

      if (EarMenu == 1)                                               // 919 - Maximale Lautstärke Kopfhörer
      {
        if (AbbrActive == true) return;

        AdjVol = true;
        mySettings.maxEarVol = voiceMenu(30 - mySettings.minEarVol, 936,        //936 - Bitte wähle mit den Vor/zurück-tasten die
                                         mySettings.minEarVol, false, false,    //      max. Lautstärke des Kopfhörers aus
                                         mySettings.maxEarVol - mySettings.minEarVol) 
                                         + mySettings.minEarVol;
      }

      // ********** Minimale Lautstärke Kopfhörer **************************

      if (EarMenu == 2)                                                           // 920 - Minimale Lautstärke Kopfhörer
      {
        if (AbbrActive == true) return;

        AdjVol = true;
        mySettings.minEarVol = voiceMenu(mySettings.maxEarVol - 1, 937,           // 937 - Bitte wähle mit den Vor/zurück-tasten die
                                         0, false, false, mySettings.minEarVol);  //       min. Lautstärke des Kopfhörers aus
      }

      // ********** Initial Lautstärke Kopfhörer **************************

      if (EarMenu == 3)                                                           // 921 - Lautstärke des Kopfhörers beim Start
      {
        if (AbbrActive == true) return;

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
      if (AbbrActive == true) return;

      mySettings.eq = voiceMenu(6, 922, 922, false, false, mySettings.eq);  
     //922- "Bitte wähle eine Einstellung für den Klangcharakter
     //      mit den Vor/zurück-tasten aus und bestätige sie mit der Pausetaste.
     //923- "Normal
     //924- "Pop
     //925- "Rock
     //926- "Jazz
     //927- "Klassik
     //928- "Bass
      mp3.setEq((DfMp3_Eq)(mySettings.eq - 1));
    }
  }

  // ******** Den Standbytimer konfigurieren **********************
  else if (subMenu == 7)                                                    // 907- "StandbyTimer Konfigurieren
  {
    if (AbbrActive == true) return;

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
    if (AbbrActive == true) return;

    uint8_t temp = voiceMenu(2, 980, 980, false);           // 980 - Wähle bitte aus ob und wie das Adminmenü geschützt werden soll.
                                                            // 981 - Kein Schutz
                                                            // 982 - Aufruf nur mit Adminkarte


    if (temp == 1)                                          // 981 - Kein Schutz
    {
      mySettings.adminMenuLocked = 0;
    }

    else if (temp == 2)                                     // 982 - Aufruf nur mit Adminkarte
    {
      mySettings.adminMenuLocked = 1;
    }
  }

  // ********** Tonuino zurücksetzen ****************
  else if (subMenu == 9)                                    // 909- "Tonuino zurücksetzen
  {
   if (AbbrActive == true) return;

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
   if (AbbrActive == true) return;

    writeSettingsToFlash();


    //********Feedback beim Verlassen des Adminmenus **
    if (progmode == 4)                                        // aktiver Modus Shortcut programmieren
    {
     if (AbbrActive == true) return;

     #ifdef Konsole
      Serial.println(F("Sct konf."));
     #endif
      mp3.playMp3FolderTrack(403);                            // 403 - "OK.Shortcut konfiguriert"
    }
    else if ( progmode != 9)                                  // aktiver Modus ist nicht Shortcut programmieren
    //                                                        // und nicht Adminkarte erstellen
    {
     if (AbbrActive == true) return;

     #ifdef Konsole
      Serial.println(F("gespeichert"));
     #endif
      mp3.playMp3FolderTrack(998);                            // 998 - "OK.Änderungen gespeichert"
    }
    waitForTrackToFinish();

  }
  // ************ Ende Ablauf Adminmenü ***************************************
  progmode = 0;
  setstandbyTimer();
}

// ************ Sprachmenüs Adminmenü  ********************************************


uint8_t voiceMenu(int numberOfOptions,
                  int startMessage,
                  int messageOffset,
                  bool preview,
                  int previewFromFolder,
                  int defaultValue,
                  bool exitWithLongPress)

{
  bool Ans = false;
  uint8_t returnValue = defaultValue;
  
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

  // ************** TimeOutfunktion für das Adminmenü  starten ************************

  AdmTimeOutStart();                                      // Start der Timeoutzeit

  do
  {
    if (isPlaying())
    AdmTimeOut = millis();                                // Timeoutzeit erst starten wenn Preview beendet

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
        return 0;

      }
    }

    if (Serial.available() > 0)
    {
      int optionSerial = Serial.parseInt();
      if (optionSerial != 0 && optionSerial <= numberOfOptions)
      return optionSerial;
    }


    readButtons();
    //mp3.loop();

    if (ButtonOne.pressedFor(LONG_PRESS))         // Abbruch durch longpress Play/Pause-Taste
    {
     #ifdef Konsole
      Serial.println(F("man. Abbr"));
     #endif
      AbbrActive = true;                          // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                // 802 - "OK, ich habe den Vorgang abgebrochen."
      waitForTrackToFinish();
      ignoreButtonOne = true;                     // PauseTaste übergehen
      setstandbyTimer();
      return defaultValue;
      //return;
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
    #ifndef FIVEBUTTONS
    if (ButtonTwo.pressedFor(LONG_PRESS))                               // longpress Taste 2 (Konfigurationsabhängig Weiter oder Lauter)
    #endif
    #ifdef FIVEBUTTONS
    if (ButtonTwo.pressedFor(LONG_PRESS)||ButtonFour.pressedFor(LONG_PRESS)) // longpress Taste 2 oder 4 (Weiter oder Lauter)
    #endif
    {
      #ifndef FIVEBUTTONS
      if (!ButtonTwo.pressedFor(3000))                                  // wenn Taste länger als 3s gedrückt wird, 
      #endif                                                            // soll trotzdem nur einmal Longpress ausgewertet werden
      #ifdef FIVEBUTTONS
      if (!ButtonTwo.pressedFor(3000)||!ButtonFour.pressedFor(3000))    // wenn Taste länger als 3s gedrückt wird, 
      #endif                                                            // soll trotzdem nur einmal Longpress ausgewertet werden
     {                                                                  
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
       #ifdef FIVEBUTTONS
       ignoreButtonFour = true;
       #endif
       Ans = true;                                                       // Ansage freigegeben    
      }
    }
    // ************ Einzelschritt weiter ****************************
    #ifndef FIVEBUTTONS
    else if (ButtonTwo.wasReleased())                                   // Taste 2 wurde kurz gedrückt
    #endif
    #ifdef FIVEBUTTONS
    else if (ButtonTwo.wasReleased()||ButtonFour.wasReleased())         // Taste 2 oder 4 wurde kurz gedrückt
    #endif
    {
      AdmTimeOut = millis();                                            // Neustart TimeOut Timer
      #ifndef FIVEBUTTONS
      if (!ignoreButtonTwo)                                             // Wenn Taste 2 ausgewertet wird
      #endif
      #ifdef FIVEBUTTONS
      if (!ignoreButtonTwo ||!ignoreButtonFour )                        // Wenn Taste 2 oder 4 ausgewertet wird
      #endif
      {
        if (rolling == true)                                          // wenn rolling erlaubt 
        if (returnValue == numberOfOptions)returnValue = 0;           // Rücksprung zum Anfang der Optionen
          
     
        returnValue = min(returnValue + 1, numberOfOptions);            // 1 Schritt weiter
        Ans = true;

      }
      else                                                              // Wenn Taste 2 oder 4 nicht ausgewertet wird
      {
        ignoreButtonTwo = false;                                        // Taste 2 auswerten
        #ifdef FIVEBUTTONS
        ignoreButtonFour = false;                                       // Taste 4 auswerten
        #endif
      }
    }
    // ************* 10-er Schritt* zurück ***************
    #ifndef FIVEBUTTONS
    if (ButtonThree.pressedFor(LONG_PRESS))                     // Longpress Taste 3 (Zurück oder Leisertaste, Konfigurationsabhängig)
    #endif
    #ifdef FIVEBUTTONS
    if (ButtonThree.pressedFor(LONG_PRESS)||ButtonFive.pressedFor(LONG_PRESS)) // Longpress Taste 3 oder 5(Zurück oder Leisertaste,)
    #endif
    {
     #ifndef FIVEBUTTONS
     if (!ButtonThree.pressedFor(3000))                         // wenn Taste länger als 3s gedrückt wird,
     #endif 
     #ifdef FIVEBUTTONS
     if (!ButtonThree.pressedFor(3000)||!ButtonFive.pressedFor(3000))// wenn Taste länger als 3s gedrückt wird,
     #endif 
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
        //                                                      // der EndTrack vor dem StartTrack liegen kann.
      
      
       ignoreButtonThree = true;                                 // Taste 3 übergehen
       #ifdef FIVEBUTTONS
       ignoreButtonFive = true;                                  // Taste 5 übergehen
       #endif
       Ans = true;
      }
    }  
    // **************** Einzelschritt zurück *****************
    #ifndef FIVEBUTTONS
    else if (ButtonThree.wasReleased())
    #endif
    #ifdef FIVEBUTTONS
    else if (ButtonThree.wasReleased()||ButtonFive.wasReleased())
    #endif
    {
      AdmTimeOut = millis();                                        // Neustart TimeOut Timer
      if (!ignoreButtonThree)                                       // wenn Taste 3 ausgewertet wird
      {
       if (rolling == true)                                         // wenn rolling erlaubt
        {
          if (returnValue == 1)                                     // Rücksprung zum Ende der Optionen
          returnValue = (numberOfOptions + 1);
        }
        returnValue = max(returnValue - 1, 1);                      // 1 Schritt zurück

       if (rolling == false)                                        // wenn rolling gesperrt   
        {
         if(returnValue < StartTrack)                                // wenn Rückgabewert für EndTrack kleiner als StartTrack
         returnValue = StartTrack;                                   // Rückgabewert auf letzt gespeicherten StartTrack setzen
        }                                                            // Verhindert, dass bei der Erstellung der Spezialmodi oder Einzelkarten
       Ans = true;                                                   // der EndTrack vor dem StartTrack liegen kann.
      }
     else                                                            // wenn Taste 3 nicht ausgewertet wird
     {
       ignoreButtonThree = false;                                     // Taste 3 auswerten
       #ifdef FIVEBUTTONS
       ignoreButtonFive = false;                                      // Taste 5 auswerten
       #endif
     }
   }

   //================ Ansagen der Optionen und Prewiew ============================
   if(Ans == true)
   {
     #ifdef Konsole
      Serial.print(F("Auswahl: "));
      if (AdjVol == false) Serial.println(returnValue);           // Nr der Option
      else Serial.println(messageOffset + returnValue);           // Volume
     #endif
     mp3.pause();
     delay(100);

      // ---------- Messages tauschen --------------------
      #ifndef Buttonboard                                       // 3 und 5 Tastenversion
      #ifndef Wecker
      if (messageOffset + returnValue == 904)                   //  Shortcuts mit Weckershortcut
      mp3.playMp3FolderTrack(700);                              // 700 Den Shortcut für eine Taste oder den Startsound programmieren
      else
      #endif
      #endif

      #ifdef Buttonboard                                         // Big Buttonboard und Wecker
      #ifndef Wecker                                             // Big Buttonboard ohne Wecker
      if (messageOffset + returnValue == 904)                    // Shortcuts mit Weckershortcut
      mp3.playMp3FolderTrack(702);                               // 702 Shortcut mit Matrix ohne Weckershortcut
      else
      #endif

     #ifdef Wecker
     if (messageOffset + returnValue == 904)                    // Shortcuts mit Weckershortcut
       mp3.playMp3FolderTrack(703);                               // 703 Shortcut mit Matrix und Weckersound
     else
     #endif 
     #endif

     #ifndef EarPhone
      if (messageOffset + returnValue == 912)                      // Kopfhörereinstellungen
        mp3.playMp3FolderTrack(913);                               // 913-Einstellungen für den Klang
      else
     #endif

     #ifdef Bluetooth
      if (messageOffset + returnValue == 977)                      // Bluetoothkarte
        mp3.playMp3FolderTrack(978);                               // 978- Bluetoothkarte erstellen
      else
     #endif

      mp3.playMp3FolderTrack(messageOffset + returnValue);      // Ansage Rückgabewert OrdnerNr, TrackNr, oder Lautstärke
      //delay(1500);  
      waitForTrackToFinish();                                   // Warten bis Ende der Ansage Ordner, oder Titelnummer  

      // ********* Vorschau *************       
     if (preview)
     {
        //waitForTrackToFinish();                                // Warten bis Ende der Ansage Ordner, oder Titelnummer
        if (previewFromFolder == 0)
        {
          mp3.playFolderTrack(returnValue, 1);                   // Vorschau 1. Track des gewählten Ordners
        }
       else
        {
          mp3.playFolderTrack(previewFromFolder, returnValue);   // Vorschau des gewählten Tracks
        }
       delay(1000);
      } 
      Ans = false;
      
 
    }
  } 
 while (true);
}
// =========================================================  
// *********************** Karte neu konfigurieren ***************
void resetCard()
{
  mp3.playMp3FolderTrack(800);                                // 800- "Bitte lege nun die Karte auf!
  delay(1000);
  AdmTimeOutStart();                                          // Start der Timeoutzeit

  do                                                          // Schleife bis Karte aufgelegt wird,oder Abbruch erfolgt
  {

    AbbrAdminTimeout();                                       // Abbruch nach Timeout Adminmenü

    ButtonOne.read();
    ButtonTwo.read();
    ButtonThree.read();
    #ifdef FIVEBUTTONS
    ButtonFour.read();
    ButtonFive.read();
    #endif

    #ifndef FIVEBUTTONS
    if (ButtonTwo.wasReleased() || ButtonThree.wasReleased()) // Vor oder Zurücktaste für Abbruch Karten schreiben
    #endif
    #ifdef FIVEBUTTONS
    if (ButtonTwo.wasReleased() || ButtonThree.wasReleased()
    || ButtonFour.wasReleased() || ButtonFive.wasReleased() ) // Vor/Zurücktaste oder Vol Taste für Abbruch Karten schreiben
    #endif
    {
     #ifdef Konsole
      Serial.print(F("Abbr.!"));
     #endif
      AbbrActive = true;                                      // Abbruch ist aktiv
      mp3.playMp3FolderTrack(802);                            // 802- "OK, ich habe den Vorgang abgebrochen.
      waitForTrackToFinish();
      setstandbyTimer();
      return;
    }
  }

  while (!mfrc522.PICC_IsNewCardPresent());                   // bleibe in der Schleife bis Karte aufgelegt
  delay(100);

  if (!mfrc522.PICC_ReadCardSerial())                        // Karte wurde aufgelegt, Wenn Karte nicht lesbar - Abbruch
  {
   #ifdef Konsole
   Serial.print(F("Karte n.lesbar !"));
   #endif
   mp3.playMp3FolderTrack(801);                                // Diese Karte ist unbekannt oder nicht lesbar
   return;
  }
  else
  {
   #ifdef Konsole
   Serial.print(F("Karte wird neu konf.!"));
   #endif
   setupCard();                                                 // Karte konfigurieren
  }
}
// -------------------------------------------
bool setupFolder(folderSettings * theFolder)
{
  // Ordner abfragen
 #ifdef CountFolders                                             // wenn CountFolders aktiv
  theFolder->folder = 
  voiceMenu(numFolders - 2, 301, 0, true, 0, 0, true);          // 301 - Wähle den Ordner aus ( 1 bis numFolders-2)
 #endif
 #ifndef CountFolders                                            // wenn CountFolders nicht aktiv
  theFolder->folder = voiceMenu(99, 301, 0, true, 0, 0, true);  // 301 - Wähle den Ordner aus ( 1 - 99)
 #endif
  if (theFolder->folder == 0) return false;

  // Wiedergabemodus abfragen
  if (AbbrActive == true) return 0;

  numTracksInFolder = mp3.getFolderTrackCount(theFolder->folder);
 #ifdef Konsole
  Serial.print(F("Dat. im Ordner: "));
  Serial.print(theFolder->folder);
  Serial.print(F(" -> "));
  Serial.println(numTracksInFolder);
 #endif  
  theFolder->mode = voiceMenu(9, 310, 310, false, 0, 0, true);        // 310 - Wähle den Wiedergabemodus ( Alle Abspielmodi)
  //                                                                  // 311 - Hörspielmodus
  //                                                                  // 312 - Albummodus
  //                                                                  // 313 - Partymodus
  //                                                                  // 314 - Einzelmodus
  //                                                                  // 315 - Hörbuchmodus
  //                                                                  // 316 - Hörspiel-Spezial Von Bis
  //                                                                  // 317 - Album - Spezial Von Bis
  //                                                                  // 318 - Party - Spezial Von Bis
  //                                                                  // 319 - Adminkarte erstellen
  if (theFolder->mode == 0) return false;
  if (progmode == 0)
  if (theFolder->mode <= 8) progmode = 2;


  // Einzelmodus -> Datei abfragen
  if (theFolder->mode == 4)
  theFolder->special = voiceMenu(numTracksInFolder, 320, 0,true, theFolder->folder);  // 320 - Trackauswahl
                                   

  // Spezialmodus Von-Bis
  if (theFolder->mode == 6 || theFolder->mode == 7 || theFolder->mode == 8)            // Spezial Von Bis : Hörsp, Album, Party 
  {
    
    theFolder->special = voiceMenu(numTracksInFolder, 321, 0,true, theFolder->folder);   // StartTrack

    StartTrack = theFolder->special;                                                     // StartTrack zwischenspeichern um zu Verhindern
    //                                                                                   // dass Endtrack vor Starttrack liegen kann.
    rolling = false;                                                                     // vom letzten Track -> Track 1 gesperrt

    theFolder->special2 = voiceMenu(numTracksInFolder, 322, 0,true, theFolder->folder, theFolder->special);  // EndTrack

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
    { }
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
   Serial.println(F(" Klassik key A..."));
   #endif
   status = mfrc522.PCD_Authenticate( MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }
  else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
   byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the tempCard

    // Authenticate using key A
   #ifdef Konsole
   Serial.println(F(" MIFARE UL..."));
   #endif
   status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK)
  {
   #ifdef Konsole
    Serial.print(F("PCD_Authent. failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
   #endif
   return false;
  }

  // Show the whole sector as it currently is
  // Serial.println(F("Current data in sector:"));
  // mfrc522.PICC_DumpMifareKlassikSectorToSerial(&(mfrc522.uid), &key, sector);
  // Serial.println();

  // Read data from the block
  if ((piccType == MFRC522::PICC_TYPE_MIFARE_MINI ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_1K ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_4K ) )
  {
   #ifdef Konsole
    Serial.print(F("Read data block "));
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
      Serial.print(F("MIFARE_Read_2 fail: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
     #endif
      return false;
    }
    memcpy(buffer + 4, buffer2, 4);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(10, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
     #ifdef Konsole
      Serial.print(F("MIFARE_Read_3 fail: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
     #endif
      return false;
    }
    memcpy(buffer + 8, buffer2, 4);

    status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(11, buffer2, &size2);
    if (status != MFRC522::STATUS_OK)
    {
     #ifdef Konsole
      Serial.print(F("MIFARE_Read_4 fail: "));
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
          if (activeModifier !=7) 
           {activeModifier = NULL;
             #ifdef Konsole
             Serial.println(F("mod. removed"));
             #endif
           }
          if (isPlaying())
          {
            mp3.playAdvertisement(261);   // Jingle Modifikation AUS
            #ifdef DfPlayer_spez
             AdvPlaying = false;
            #endif
          }
          else
          {
            mp3.start();
            delay(100);
            mp3.playAdvertisement(261);  // Jingle Modifikation AUS
            #ifdef DfPlayer_spez
              AdvPlaying = false;
            #endif
            delay(100);
            mp3.pause();
          }
          delay(100);
          return false;
        }
      }
      // ******** Modifikation einschalten *********
      

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
       #ifdef USB_Zugriff_SD_Karte
        case 7: activeModifier = new SD_Card_USB (); break;
       #endif
       #ifdef Bluetooth
        case 7: bluetooth(); break;
       #endif
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
  byte buffer[16] = {0x13, 0x37, 0xb3, 0x47,                    // 0x1337 0xb347 magic cookie to identify our nfc tags
                     0x02,                                      // version 1
                     nfcTag.nfcFolderSettings.folder,           // the folder picked by the user
                     nfcTag.nfcFolderSettings.mode,             // the playback mode picked by the user
                     nfcTag.nfcFolderSettings.special,          // track or function for admin cards
                     nfcTag.nfcFolderSettings.special2,         // endtrack for track from-to
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
    Serial.println(F("Authent. again, key A..."));
   #endif
    status = mfrc522.PCD_Authenticate(
    MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }
  else if (mifareType == MFRC522::PICC_TYPE_MIFARE_UL )
  {
    byte pACK[] = {0, 0};                                      //16 bit PassWord ACK returned by the NFCtag

    // Authenticate using key A
   #ifdef Konsole
    Serial.println(F("Authentic. UL..."));
   #endif
    status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK)                           // wenn Status Fehler
  {
    #ifdef Konsole
    Serial.print(F("PCD_Authent. fail: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
   #endif
    mp3.playMp3FolderTrack(401);                              //401- "Oh weh! Das hat leider nicht geklappt!
    waitForTrackToFinish();
    return;
  }

  // Write data to the block
 #ifdef Konsole
  Serial.print(F("Writing data "));
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

  if (status != MFRC522::STATUS_OK)                     // wenn Status Fehler
  {
   #ifdef Konsole
    Serial.print(F("MIFARE_Write fail: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
   #endif
    mp3.playMp3FolderTrack(401);                        //401 - "Oh weh! Das hat leider nicht geklappt!
    waitForTrackToFinish();
  }

  else                                                  // Status OK.
  {
   // ****** Abschlussmeldung Karte oder Shortcut konfigurieren *****

    if (progmode == 1)                                  // wenn Karte neu konfigurieren
    {
     #ifdef Konsole
      Serial.println(F("Konf. OK."));
     #endif
      mp3.playMp3FolderTrack(400);                      //400 - "OK. Ich habe die Karte oder den Shortcut konfiguriert.
    }

    if (progmode == 2)                                  // wenn Einzelkarten konfigurieren
    {
     #ifdef Konsole
      Serial.println(F("Einzelkarte OK."));
     #endif
      mp3.playMp3FolderTrack(402);                      // 402 - "OK. Karte fertig"
    }

    if (progmode == 3)                                  // wenn Modifikationskarte erstellen
    {
     #ifdef Konsole
      Serial.println(F("Modifikationskarte OK."));
     #endif
      mp3.playMp3FolderTrack(404);                     // 404 - "OK. Modifikationskarte fertig"
    }

    if (progmode == 9)                                 // wenn Adminkarte erstellen
    {
     #ifdef Konsole
      Serial.println(F("Adminkarte OK."));
     #endif
      mp3.playMp3FolderTrack(409);                     // 409 - " Adminkarte erstellt"
    }
  }
  waitForTrackToFinish();
  delay(500);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// *********************** Buttonboard *******************************
#ifdef Buttonboard
void ReadMatrix()
{
  if (activeModifier != NULL)                               // wenn Modifikation aktiv
  if (activeModifier->handleMatrix() == true) return;       // wenn akt.Modifikation das Buttonboard sperrt -> Abbrechen
  
  if(TaGedr == false)
  {
   analogRead(Buttonmatrix);
   delay(50);
   Wert = analogRead(Buttonmatrix);
   Matrix = map(Wert, 0, mapMax, 1, 10);
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
       
        //Serial.print(F("keine Taste"));      // Keine Taste gedrückt
        //Serial.println(Wert);
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
 #ifdef AiOPLUS
  Serial1.begin(9600);                   // serielle Schnittstelle-1 für FTDI-Adapter zur Batteriespannungskontrolle initialisieren
  Serial1.println("Serial 1 initialisiert");
  Serial1.println("Anzeige Batteriespannung im Minutentakt");
  Serial1.println("AiO-PLUS nur über Akku betreiben");
  Serial1.println("Zur korrekten Anzeige, USB-Port nicht anschließen !");
 #endif  
  // ------------------------------------------------------------------------------------
  // Urheber Infos, Dieser Hinweis darf nicht entfernt werden
  Serial.println();

  Serial.print(F("** TONUINO "));

 #ifdef Klassik
  Serial.print(F("- Klassik "));
 #ifdef Traegerplatine
  Serial.print(F("-TLE-Traegerplatine"));
 #endif
 #endif
 #ifdef EVERY
  Serial.print(F("- EVERY "));
 #ifdef Traegerplatine
  Serial.print(F("-TLE-Traegerplatine"));
 #endif 
 #endif
 #ifdef AiO
  Serial.print(F("- AiO "));
 #endif
 #ifdef AiOPLUS
  Serial.print(F("- AiO-PLUS "));
 #endif
  Serial.println(F("**"));
  Serial.println();
  Serial.println(F("** V. THOMAS LEHNERT ** 2024-03-29 **"));
  Serial.println();
 
  Serial.println(F("Based on TonUINO"));
 
  Serial.println(F("created by Thorsten Voß and licensed under GNU/GPL."));
  Serial.println(F("https://tonuino.de.\n"));
  // ------------------------------------------------------------------------------------
 #ifndef Buttonboard
 #ifndef FIVEBUTTONS
  Serial.println(F("** 3 Tasten **"));  // 3-Tastenversion
 #endif
 #ifdef FIVEBUTTONS
  Serial.println(F("** 5 Tasten **"));  // 5-Tastenversion
 #endif
 #endif
 #ifdef Buttonboard
  Serial.println(F("** 12 Tasten **")); // Buttonboard-Version (12 Tasten)
 #endif 
  Serial.println();
 #ifdef Hardwareserial
  Serial.println(F("HW-Serial")); 
 #endif 
  Serial.println();
  // ------------------------------------------------------------------------------------
 #ifdef AiO
  analogReference(INTERNAL2V048);        // Festlegung der Referenz AiO
 #ifdef highResolution
  analogReadResolution(12);              // Auflösung Auslesen AiO
 #endif
 #endif
  // ------------------------------------------------------------------------------------
 #ifdef EVERY
  analogReference(INTERNAL2V5);          // Festlegung der Referenz EVERY
 #endif
  // ------------------------------------------------------------------------------------
 #ifdef AiOPLUS
  analogReference(INTERNAL2V5);          // Festlegung der Referenz AiOPLUS
 #endif
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
 #endif 
  // ------------------------------------------------------------------------------------
 #ifdef BatteryCheck
  pinMode(BatteryCheckPin, INPUT);        // Eingang Batteriespannungskontrolle
#ifdef Konsole
  Serial.print (F("Batt.Check:  "));
 #ifdef LiFePo
  Serial.println (F("LiFePO4 !"));
 #endif
 # ifdef LiPo
  Serial.println (F("LiPO !"));
 #endif
  Serial.println (); 
 #endif
 #endif
  // ------------------------------------------------------------------------------------
 #ifdef EarPhone
 #ifdef AiO
  pinMode (EarPhonePin, INPUT);         // Eingang,Sensor ob Kopfhörer angeschlossen?
 #endif
 #ifdef AiOPLUS
  pinMode (EarPhonePin, INPUT);         // Eingang,Sensor ob Kopfhörer angeschlossen?
 #endif
 #ifndef AiO
 #ifndef AiOPLUS
  pinMode (EarPhonePin, INPUT_PULLUP);  // Eingang,Sensor ob Kopfhörer angeschlossen? interner PullUp aktiviert
 #endif
 #endif
 #endif
  // ------------------------------------------------------------------------------------
 #ifdef EVERY
 #ifdef Bluetooth
 pinMode(BtPairingPin,OUTPUT);
 pinMode(BtOnPin,OUTPUT);
 digitalWrite(BtPairingPin,LOW);
 digitalWrite(BtOnPin,LOW);
 #endif
 #endif
  // -------------------------------------------------------------------------------------
 #ifndef AiOPLUS
 # ifndef AiO                           // Tonuino Klassik Versionen oder EVERY
 #ifdef HW_PowerOff
  pinMode(ShutDownPin, OUTPUT);         // Ausgang Selbsthaltung , Ein/Ausschaltsignal 
  #ifdef LowActive
  digitalWrite(ShutDownPin, HIGH);      // Voreinstellung - On (LOW-Active)
  Serial.println ("ShtDn - L-act.");
  Serial.println ( ); 
  #endif
  #ifndef LowActive
  digitalWrite(ShutDownPin, LOW);       // Voreinstellung - On (HIGH-Active)
  Serial.println ("ShtDn - H-act."); 
  Serial.println ( );
  #endif
 #endif
 #endif
 #endif
 #ifdef AiOPLUS
  pinMode(ShutDownPin, OUTPUT);         // Ausgang Selbsthaltung , Ein/Ausschaltsignal AiOPLUS
  digitalWrite(ShutDownPin, HIGH);      // Selbsthaltung AiOPLUS, Ein/Ausschaltsignal (LOW schaltet aus)
  pinMode(Access_SD_Pin, OUTPUT);       // Steuerpin für SD-Zugriff über USB
  digitalWrite(Access_SD_Pin, LOW);     // SD karten Zugang über USB gesperrt
 #endif
 #ifdef AiO
  pinMode(ShutDownPin, OUTPUT);         // Ausgang Selbsthaltung , Ein/Ausschaltsignal AiO
  digitalWrite(ShutDownPin, HIGH);      // Selbsthaltung AiO, Ein/Ausschaltsignal (LOW schaltet aus)
  pinMode(Access_SD_Pin, OUTPUT);       // Steuerpin für SD-Zugriff über USB
  digitalWrite(Access_SD_Pin, LOW);     // SD karten Zugang über USB gesperrt
 #endif
 
  // ----------------------------------------------------------------------------------------
 #ifdef SpkOnOff
  pinMode(SpkOnPin, OUTPUT);            // Ausgang Lautsprecher-Einschaltsignal
  digitalWrite(SpkOnPin, Off);          // Lautsprecher oder Verstärker ausschalten
  #endif
  // ----------------------------------------------------------------------------------------
  // ********* Wert für randomSeed() erzeugen durch das mehrfache Sammeln *****
  // ******** von rauschenden LSBs eines offenen Analogeingangs **************
  uint32_t ADC_LSB;
  uint32_t ADCSeed;
  for (uint8_t i = 0; i < 128; i++)
  {
    ADC_LSB = analogRead(RandomPin) & 0x1;
    ADCSeed ^= ADC_LSB << (i % 32);
    delay(1);
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
 #ifdef Wecker
 myCookie = myCookie +8;                // setzt myCookie um 8 hoch (1 Zusätzliche Shortcut in den Settings)
 #endif       
 loadSettingsFromFlash();
  // ----------------------------------------------------------------------------------------   
  // ********** Kontrolle ob über Wecker eingeschaltet wurde **********
 #ifdef Wecker
  weckerstart();
 #endif
  // ------------------------------------------------------------------------------------
  // *************** LED Animation initialisieren ************
 #ifdef LED_SR
  strip.begin();
  strip.clear();
  strip.setBrightness(64);
  strip.show();
  strip.fill(lightblue);
  strip.show();
 
  loopCount = 0;
  animCount = 1;
  
  #ifdef CandleLight
   intervalCandle = 150;
  #endif

 #endif

  // ---------------------------------------------------------------------------------------
  //*************** DFPlayer Mini initialisieren *******************************************
  mp3.begin();
  
 
 #ifndef Hardwareserial
   delay(5000);    // Drei Sekunden warten bis der DFPlayer Mini initialisiert ist ohne Nutzung des USB-Stick
 #endif 

 #ifdef Hardwareserial
  delay(2000);    // Zwei Sekunden warten bis der DFPlayer Mini initialisiert ist ,Nano Every mit HardwareSerial
 #endif 
 // ----------------------------------------------------------------------------------
 //************* Ordner des Speichermediums zählen *****************
 #ifdef CountFolders
   numFolders = (mp3.getTotalFolderCount( ));  // Ordner zählen
   #ifdef IgnoreWinSysInf
    numFolders = numFolders - 1;                // Der Windows Ordner SystemVolumeInformation wird von der Ordnerzahl abgezogen
   #endif
   if(numFolders == 0 || numFolders > 99) numFolders = 99; 
   Serial.print(F("Ordner auf SD: "));
   Serial.println (numFolders);

   #ifdef EVERY
   #ifndef Hardwareserial
   if (mp3error == true)
   Serial.println(F("mp3-Err ignor."));
   #endif
   #endif
  Serial.println ();
 #endif
 #ifndef CountFolders
  #ifdef ZaehleOrdner
   OrdnerZaehlen();
   numFolders = Ordner-1;
   Serial.print(F("Ordner zählen auf SD: "));
   Serial.println (numFolders);
  #endif
 #endif
 #ifdef USB_Zugriff_SD_Karte
  Serial.println(F("mod. 'SDK <--> USB'")); 
  Serial.println ();
 #endif
 
  //************* NFC Leser initialisieren *******************************************
  SPI.begin();                                        // Init SPI bus
  mfrc522.PCD_Init();                                 // Init MFRC522


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

  mfrc522.PCD_DumpVersionToSerial();                  // Show details of PCD - MFRC522 Card Reader
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  // ----------------------------------------------------------------------------------------
  //************ Lautstärke des Lautsprechers auf Startlautstärke setzen ********************

  volume = mySettings.initVolume;                     // Startlautstärke
  mp3.setVolume(volume);                              // Setzen
  delay(200);
  mp3.setEq((DfMp3_Eq)(mySettings.eq - 1));           // Klangcharakter setzen
  delay(200);
  // -----------------------------------------------------------------------------------------
  // ******************* Lautsprecher einschalten ***Hardwareerweiterung beim Klassik erforderlich ********
 #ifdef SpkOnOff

  SpkVol = mySettings.initVolume;                     // Variable setzen, Startlautstärke Lautsprecher
 #ifdef EarPhone
  EarVol = mySettings.initEarVol;                     // Variable setzen, Startlautstärke für Kopfhörer
 #endif

  SpkOn();                                            // Lautsprecher einschalten (Abhängig von gestecktem Kophörer)

  if (SpkisOn == true)
   { mp3.setVolume(SpkVol);                           //Startlautstärke Lautsprecher einstellen
   delay(200);
   }
 #ifdef EarPhone
  else mp3.setVolume(EarVol);                         //Startlautstärke für Kopfhörer einstellen
  delay(200);
 
 #endif
 #endif

  // -----------------------------------------------------------------------------------------
  //  *************** Manueller Reset beim Einschalten ****************************************

  // RESET --- TASTEN 1, 2 und 3 BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden auf DEFAULT gesetzt
  readButtons();                             // Tasten auslesen
  if (ButtonOne.isPressed()
  && ButtonTwo.isPressed()
  && ButtonThree.isPressed())
  {
   Serial.println(F("Reset"));
   #ifndef AiO
    for (int i = 0; i < EEPROM.length(); i++)
    {
     EEPROM.update(i, 0);                          // EEPROM löschen (Klassik, EVERY und AiOPLUS)
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

 //mp3.playMp3FolderTrack(262);                     // 262- "piep"
 //delay(2000);
  // --------------------------------------------------------------------------------------
  // *************  Wecker ** Hardwareerweiterung erforderlich ****************************
 #ifdef Wecker
 wecker();                     // Prüfen ob durch Wecker eingeschaltet wurde
 #endif                        // ggf. Start Weckershortcut, falls konfiguriert
 delay(1000);
  // ------------------------------------------------------------------------------------
 
  // *********** Start Shortcut "at Startup" - e.g. Welcome Sound ************************
 #ifndef Wecker
  playShortCut(Welcome);       // Start Shortcut Welcomesound, falls konfiguriert
 #endif

 // ----------------------------------------------------------------------------------
 //************* Wiederholung Ordner des Speichermediums zählen nur für Every mit SoftwareSerial ***
 #ifdef EVERY
 #ifndef Hardwareserial
 #ifdef CountFolders
  numFolders = (mp3.getTotalFolderCount( ));  // Ordner zählen
 #ifdef IgnoreWinSysInf
  numFolders = numFolders - 1;                // Der Windows Ordner SystemVolumeInformation wird von der Ordnerzahl abgezogen
 #endif
  Serial.print(F("Ordner auf SD: "));
  Serial.println (numFolders);
  Serial.println ();
 #endif
 #endif
 #endif
  // ------------------------------------------------------------------------------------

  // *************** Freigabe oder Unterdrückung Konsolenausgabe **************************
 #ifndef Konsole
  Serial.println (F("Kons.reduz."));
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
   mp3.loop();                   // Kommunikation mit DF-Player mindestns 1x pro Schleifendurchlauf
   
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
      CheckVoltage();                          // Batterieprüfung
    }
   #endif

    // ************************ Wecker **** Hardwareerweiterung erforderlich **********************
   #ifdef Wecker
    if (ActWecker == false)  wecker();     // wenn Wecker in aktiver Session noch nicht aktiviert worden ist
     
   #endif

    // ******************** Lautsprecher abschalten wenn Kopfhörer angeschlossen *******************
    // **** wenn der Wecker aktiv wird soll der Lautsprecher nicht abgeschaltet werden *************
   #ifdef EarPhone
    Earphone ();
   #endif

    // *********************** LED Animation ** Hardwareerweiterung erforderlich ******************
   #ifdef LED_SR
   
    // --------- LED-Signalisation MP3-Error --------------
    mp3Error();                                // Bei einem mp3 Error 3 x Blinksignal Magenta
    // --------- LED Animation ----------------------------
    LED_Animation();                           // Standart-LED-Animation
   #endif

    // ************************Prüfen StandbyTimer und aktive Modifikation *************************
    checkStandbyAtMillis();                    // Prüfen Standbytimer
    //mp3.loop();                              // Abfrage Meldungen vom Df-Plsyer

    if (activeModifier != NULL)                // Prüfen auf aktive Modifikationskarte
    activeModifier->loop();                    // Modifikation aktivieren

    // ********************* Check Status StandbyTimer und isPlaying *********************
    if (!isPlaying()&&!StdBy)                   // Wenn keine Widergabe läuft und kein StandbyTimer gesetzt ist
    { 
      KontrPlay = true;                         // Vorbereitung für 2. Kontrolle
      delay(2000);                              // delay 2 sekunden
      
    }
    if (!isPlaying()&&!StdBy&&KontrPlay)        // Nach 2 sekunden erneute Prüfung ob keine Wiedergabe
    { 
      KontrPlay = false;
      setstandbyTimer();                        // Ist der StandbyTimer nicht gestartet -> Start StandbyTimer
    }

    // ********************** Auswerten der Tasten *************************************************
    // Buttons werden nun über JS_Button behandelt, dadurch kann jede Taste
    // doppelt belegt werden
    
    readButtons();                                      // Tasten auslesen

    // ***************** Adminmenu über longPress 3 Tasten aktivieren **************************

    #ifndef FIVEBUTTONS
     if ((ButtonOne.pressedFor(LONG_PRESS)              // 3 Tastendruck Longpress zum Starten Adminmenü im 3 Tastenmodus
      || ButtonTwo.pressedFor(LONG_PRESS)
      || ButtonThree.pressedFor(LONG_PRESS))
      && ButtonOne.isPressed()
      && ButtonTwo.isPressed()
      && ButtonThree.isPressed())
    #endif    
    #ifdef FIVEBUTTONS
     if ((ButtonOne.pressedFor(LONG_PRESS)               // 3 Tastendruck Longpress zum Starten Adminmenü im Fünftatsenmodus
      || ButtonTwo.pressedFor(LONG_PRESS)
      || ButtonThree.pressedFor(LONG_PRESS)
      || ButtonFour.pressedFor(LONG_PRESS)
      || ButtonFive.pressedFor(LONG_PRESS))
      && ButtonOne.isPressed()
      && (ButtonTwo.isPressed()||ButtonFour.isPressed())
      && (ButtonThree.isPressed()||ButtonFive.isPressed()))
    #endif    
    {
      mp3.pause();                                      // Wiedergabe stoppen
      do
      {
        readButtons();                                  // Tasten auslesen
      }

      while 
      (ButtonOne.isPressed()
       || ButtonTwo.isPressed()
       || ButtonThree.isPressed()
       #ifdef FIVEBUTTONS
       || ButtonFour.isPressed()
       || ButtonFive.isPressed()
       #endif
      );

      readButtons();                                    // Tasten auslesen
      adminMenu();                                      // Adminmenü starten
      break;
    }

    // ******************* Taste 1 (Play/Pause Taste) ****************************************************
    // ------------- ShortPress --------------------------------
    if (ButtonOne.wasReleased())                                // wenn Play/Pausetaste gedrückt worden ist
    {
      mp3error = false;                                         // ggf.Rücksetzen Marker mp3error
    
     if (activeModifier != NULL)                               // wenn Modifikation aktiv
      if (activeModifier->handlePause() == true) return;       // wenn akt.Modifikation pause Taste sperrt -> Abbrechen
          
     if (!ignoreButtonOne)                                     // Wenn Taste ausgewertet wird
      if (isPlaying())                                         // wenn Wiedergabe läuft
      {
       setstandbyTimer();
       mp3.pause();                                            // Pause der Wiedergabe
       
      }
      else if (knownCard)                                      // wenn keine Wiedergabe läuft und Karte bekannt
      {
       Serial.print(currentQueueIndex);
       
            
       if(!EoQ) 
       {
        Serial.println(F(" Continue Play"));
        mp3.start();
       }
       else
       {
        Serial.println(F(" Play new"));
        mp3.playFolderTrack(myFolder->folder, queue[currentQueueIndex]);
       }
       
       disablestandbyTimer();
      }
      
      ignoreButtonOne = false;                                 // Pausetaste auswerten
    }
   // ---------------- LongPress -------------------------------------
   // Langer Druck Pausetaste für Ansage des aktuellen Tracks oder Hörbuch auf Anfang zurücksetzen
    else if (ButtonOne.pressedFor(LONG_PRESS) && ignoreButtonOne == false)                       
    {                                                          
     if (activeModifier != NULL)                               // wenn Modifikationskarte aktiv
      if (activeModifier->handlePause() == true)  return;      // wenn Pausetaste gesperrt -> Abbruch
         
      if (isPlaying())                                         // wenn Wiedergabe läuft
      {
        // *********** Ansage der Tracknummer ******************************
        uint8_t advertTrack = queue[currentQueueIndex];         // Auslesen der Tracknummer für Ansage Tracknr

       // ---- Spezialmodus Von-Bis für Album gibt die Dateinummer relativ zur Startposition wieder ----
        if (myFolder->mode == 7)                                // Spezialmodus Album 
        {
          advertTrack = advertTrack - myFolder->special + 1;    // Ansage auf relative Track Nr
         #ifdef Konsole
          Serial.print(F("Track in Queue: "));                  // Anzeige der rel. Track Nr.
          Serial.println(advertTrack);
         #endif
        }

        //************ Rücksetzen - Hörbuch auf Anfang **********************
        // Im Hörbuchmodus wird durch langen Druck Pause Taste der Fortschritt auf Anfang gesetzt
       #ifdef HB_Reset
        if (myFolder->mode == 5)                                // Hörbuchmodus
        {
         ResetHB = true;                                        // Verhindert ein Nexttrack und doppeltes EEProm Update
         currentQueueIndex =0;                                  // Index auf 0 für Track1 setzen
          mp3.stop();                                           // Wiedergabe stoppen
           
         #ifdef Konsole
          Serial.println(F("Hörb.-> Anfang"));
          Serial.println(F("Track: 1"));
         #endif
         
          mp3.playMp3FolderTrack(340);                             // mp3 340 - Das Hörbuch wird auf den Anfang zurückgesetzt, Kapitel 1.

         // WaitForTrackToFinish funktioniert hier nicht richtig, deshalb 6 sek. warten bis die Ansage fertig ist.           
          delay(6000);                              
                                                                   
          mp3.playFolderTrack(myFolder->folder,1);                 // AnfangsTrack spielen

                                            
         #ifndef AiO
          EEPROM.update(myFolder->folder, currentQueueIndex);      // Track 1 im EEProm speichern
         #endif
         #ifdef AiO
          EEPROM_update(myFolder->folder, currentQueueIndex);      // Track 1 im EEProm speichern
         #endif
       }
         
       #endif  //HB_Reset
       //************** Ende, Rücksetzen - Hörbuch auf Anfang ***********************
       else                                                     // wenn Abspielmodus nicht Hörbuch ist
        {
          mp3.playAdvertisement(advertTrack);                   // Tracknummer ansagen
          waitForTrackToFinish();
          #ifdef DfPlayer_spez
           AdvPlaying = false;
          #endif  
        }
        //************ Neues Pairing über Longpress Playtaste ********************
        #ifdef PT-Pairing                                          
          if(BT)                                                // Wenn BT eingeschaltet
          {
           delay(1000);
           mp3.playAdvertisement(612); 
           waitForTrackToFinish();
           Serial.println("Pairing");
           digitalWrite(BtPairingPin,HIGH);                     // Pairing starten
           delay(500);
           digitalWrite(BtPairingPin,LOW);
          }
        #endif
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
    if (ButtonTwo.pressedFor(LONG_PRESS))       // Wenn Taste 2 lange gedrückt
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
          #ifdef JumpLongPress
         JumpForw();                           // Titelsprung longpress im 5 Tastenmodus
         #endif
         #endif
        }
      }
      else                                      // wenn keine Wiedergabe läuft
      {                                         // Aufrufen der Shortcuts
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Vol-Tasten getauscht
        {
         #ifndef FIVEBUTTONS                    // 3 Tastenmodus
         playShortCut(NextLauterButton);        // Shortcut spielen Vor/Lauter-Taste
         #endif
         #ifdef FIVEBUTTONS                     // 5 Tastenmodus
         playShortCut(NextButton);              // Shortcut spielen Weiter-Taste
         #endif
        }
        else                                    // wenn Funktion der Vol-Tasten nicht getauscht
        {
         #ifndef FIVEBUTTONS                    // 3 Tastenmodus und Buttonboard
         playShortCut(NextLauterButton);        // Shortcut spielen Vor/Lauter-Taste
         #endif
         #ifdef FIVEBUTTONS                      // 5 Tastenmodus
         playShortCut(LauterButton);            // Shortcut spielen Lauter-Taste
         #endif
        }
      }
     
      ignoreButtonTwo = true;                   // Taste2  übergehen

    }                                           // Ende longPress
    // ---------------- ShortPress -------------------------------------    
    else if (ButtonTwo.wasReleased())           // wenn kein longpress und Taste 2 nur kurz gedrückt wurde (shortpress)
    {
      if (!ignoreButtonTwo)                     // Wenn Taste 2 gelesen werden soll
      {
       if (!mySettings.invertVolumeButtons)     // wenn Funktion der Vol Tasten nicht getauscht
       {
         #ifndef FIVEBUTTONS                    // 3 Tastenmodus und Buttonboard
          nextButton();                         // weiter Taste im 3 Tastenmodus durch kurzen Tastendruck
         #endif
         #ifdef FIVEBUTTONS                     // 5 Tastenmodus
         volumeUpButton();                      // Lauter Taste
         longPressVol = false;                  // schrittweise VolÄnderung durch kurzen Tastendruck
         #endif       
        }
        else                                    // wenn Funktion der Vol Tasten getauscht
        {
         #ifndef FIVEBUTTONS                    // 3 Tastenmodus
         volumeUpButton();                      // Lauter Taste im 3 Tasenmodus
         longPressVol = false;                  // schrittweise VolÄnderung durch kurzen Tastendruck
         #endif
         #ifdef FIVEBUTTONS                     // 5 Tastenmodus
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
         #ifndef FIVEBUTTONS                            // 3 Tastenmodus
         previousButton();                              // Track zurück 3 Tastenmodus durch longpress
         #endif
         #ifdef FIVEBUTTONS                             // 5 Tastenmodus
         #ifdef JumpLongPress
         JumpBackw();                                   // Sprung rückwärts 5 Tastenmodus durch longpress
         #endif
         #endif
        }
      }
     else                                               // wenn keine Wiedergabe läuft
      {
       if (mySettings.invertVolumeButtons)              // wenn Funktion der Vol-Tasten getauscht
       {
         #ifndef FIVEBUTTONS                            // 3 Tatsenmodus
         playShortCut(PrevLeiserButton);                // Shortcut spielen Zurück/Leiser-Taste
         #endif
         #ifdef FIVEBUTTONS                             // 5 Tastenmodus
         playShortCut(PrevButton);                      // Shortcut spielen Zurück-Taste
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
      ignoreButtonThree = true;                          // Taste3 übergehen
   }                                                     // Ende longpress
   
    // ---------------- ShortPress -------------------------------------        
    else if (ButtonThree.wasReleased())                 // Wenn Taste3 betätigt wurde (shortpress)
    {
      mp3error = false;                                 // Rücksetzen Marker mp3error
      if (!ignoreButtonThree)                           // Wenn Taste3 ausgewertet werden soll
      {
       if (!mySettings.invertVolumeButtons)             // Wenn Funktion der Vol Tasten nicht getauscht
        {
         #ifndef FIVEBUTTONS                            // 3 Tastenmodus
          previousButton();                             // Zurück Taste kurzer Tastendruck 3 Tastenmodus
         #endif
         #ifdef FIVEBUTTONS       
         volumeDownButton();                            // Leiser Taste 5 Tastenmodus
         longPressVol = false;                          // schrittweise VolÄnderung durch kurzen Tastendruck
         #endif       
        }
        else                                            // wenn Funktion der Vol Tasten getauscht
        {
         #ifndef FIVEBUTTONS                            // 3 Tastenmodus
          volumeDownButton();                           // Leiser Taste 3 Tastenmodus
          longPressVol = false;                         // schrittweise VolÄnderung durch kurzen Tastendruck
         #endif
         #ifdef FIVEBUTTONS                             // 5 Tastenmodus
         previousButton();                              // Zurück Taste kurzer Tastendruck 5 Tastenmodus
         #endif
        }
      }
      ignoreButtonThree = false;                        // Taste3 wieder auswerten
    }                                                   // Ende shortpress
    // *********** Ende Taste 3 (Zurück/Vol -) ********************************************

    // ********** 5 Tasten-Modus ***********************************************

   #ifdef FIVEBUTTONS                                   // 5 Tasten-Modus

    // ************ Taste 4 (Vol+/Vor)**************************************
    // ---------------- LongPress -------------------------------------
    if (ButtonFour.pressedFor(LONG_PRESS))
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Tasten 4 und 2 getauscht
        {
          longPressVol = true;                  // VolÄnderung durch longPress
          volumeUpButton();                     // Lauter Taste
        }
        #ifdef JumpLongPress
       else                                     // wenn Funktion der Vol-Tasten nicht getauscht
        {                                       
          JumpForw();                           // Titelsprung Vorwärts bei longpress im 5 Tastenmodus
        }
        #endif
      }
      else                                      // wenn keine Wiedergabe
      {
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Tasten getauscht 
        {
         #ifdef FIVEBUTTONS                      // 5 Tasten
         playShortCut(LauterButton);             // Shortcut spielen Lauter-Taste
         #endif
        }
        else                                    // wenn Funktion der Tasten nicht getauscht 
        {
         #ifdef FIVEBUTTONS                      // 5 Tasten
         playShortCut(NextButton);               // Shortcut spielen Weiter-Taste
         #endif  
        }
      }
      ignoreButtonFour = true;                  // Taste 4 übergehen

    }                                           // Ende longPress
    // ---------------- ShortPress -------------------------------------            
    else if (ButtonFour.wasReleased())          // wenn Taste 4  betätigt wurde (shortpress)
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      if (!ignoreButtonFour)                    // Wenn Taste 4 gelesen werden soll
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Tasten  getauscht
        {
          volumeUpButton();                     // Lauter-Taste
          longPressVol = false;                 // schrittweise VolÄnderung durch kurzen Tastendruck
        }
        else                                    // wenn Funktion der Tasten nicht getauscht
        {
          nextButton();                         // Next - Taste
        }
      }
      
      ignoreButtonFour = false;                 // Taste 4 wieder auswerten
    }                                           // Ende shortpress

    // ************ Taste 5 (Vol-/Zurück)************************************
    // ---------------- LongPress -------------------------------------    
   if (ButtonFive.pressedFor(LONG_PRESS))
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Tasten 3 und 5 getauscht
        {
          longPressVol = true;                  // VolÄnderung durch longPress
          volumeDownButton();                   // Leiser Taste
        }
        #ifdef JumpLongPress
        else                                    // wenn Funktion der Tasten nicht getauscht
        {                                       
          JumpBackw();                          // Sprung rückwärts 5 Tastenmodus durch longpress
        }
        #endif
      }
      else                                      // wenn keine Wiedergabe
      {
       if (mySettings.invertVolumeButtons)      // wenn Funktion der Tasten getauscht 
        {
         #ifdef FIVEBUTTONS                      // 5 Tasten
         playShortCut(LeiserButton);             // Shortcut spielen Leiser-Taste
         #endif
        }
        else                                    // wenn Funktion der Tasten nicht getauscht 
        {
         #ifdef FIVEBUTTONS                      // 5 Tasten
         playShortCut(PrevButton);               // Shortcut spielen Zurück-Taste
         #endif  
        }
      }
      ignoreButtonFive = true;                  // Taste 5 übergehen
      // ---------------- ShortPress -------------------------------------    
    }                                           // Ende longPress   
    else if (ButtonFive.wasReleased())          // Taste 5 wurde betätigt (shortpress)
    {
      if (isPlaying())                          // wenn Wiedergabe läuft
      if (!ignoreButtonFive)                    // Wenn Taste 5 gelesen werden soll
      {
        if (mySettings.invertVolumeButtons)     // wenn Funktion der Tasten  getauscht
        {
          volumeDownButton();                   // Leiser-Taste
          longPressVol = false;                 // schrittweise VolÄnderung durch kurzen Tastendruck
        }
        else                                    // wenn Funktion der Tasten nicht getauscht
        {
          previousButton();                     // Zurück - Taste
        }
      }
      
      ignoreButtonFive = false;                 // Taste 5 wieder auswerten   
    }                                           // Ende shortpress Taste 5
   #endif

  }
  // ******************* Ende der Buttons ***********************************
  // ************** RFID-Reader - check ob Karte aufgelegt ******************
  while (!mfrc522.PICC_IsNewCardPresent());           // bleibe in der Schleife, Solange keine neue Karte aufgelegt
  // ***** ENDE der do/while Schleife ***************************************
  
  // *************** RFID Karte wurde aufgelegt ************************

  if (!mfrc522.PICC_ReadCardSerial())  return;        // wenn Karte nicht lesbar -> Abbruch, Rückkehr in Schleife
   

  // ************** Karte ist konfiguriert *****************************
  if (readCard(&myCard) == true)                      // wenn Karte lesbar
  {
    // make random a little bit more "random"
    randomSeed(millis() + random(1000));

    if (myCard.cookie == cardCookie                   // überprüfen ob Karte bekannt,
      && myCard.nfcFolderSettings.folder != 0         // ein Ordner konfiguriert,
      && myCard.nfcFolderSettings.mode != 0)          // und ein Abspielmodus festgelegt ist
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
