/*
This code is Written by Saad Jameel with the help of RandomNerdTutorial
  Contact:
    email: saadjmail1998@gmial.com
    ph: +92 333 3059002 (WhatsApp Only)
*/

/*
  SS/SDA --> D5 (Selected in code)
  SCK -----> D18(Pre Defined pin on esp32)
  MOSI ----> D23(Pre Defined pin on esp32)
  MISO ----> D19(Pre Defined pin on esp32)
  RST -----> D27 (Selected in Code)
*/
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid
//Constants
#define SS_PIN 5
#define RST_PIN 26
//Parameters
const int ipaddress[4] = {103, 97, 67, 25};
//Variables
byte nuidPICC[4] = {0, 0, 0, 0};
String userid;
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);
void setup() {
  //Init Serial USB
  Serial.begin(115200);
  Serial.println(F("Initialize System"));
  //init rfid D8,D5,D6,D7
  SPI.begin();
  rfid.PCD_Init();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();
}
void loop() {
  //readRFID();
    ////Read RFID card
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  // Look for new 1 cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // Verify if the NUID has been readed
  if (  !rfid.PICC_ReadCardSerial())
    return;
  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  //Serial.print(F("RFID In dec: "));
  userid = printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  Serial.println(userid);
  
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}
//void readRFID(void ) { /* function readRFID */


//}
/**
   Helper routine to dump a byte array as hex values to Serial.
*/
/*
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
/**
   Helper routine to dump a byte array as dec values to Serial.
*/
String printDec(byte *buffer, byte bufferSize) {
  String id;
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], DEC);
    id += String(buffer[i], DEC);
  }
  return id;
}
