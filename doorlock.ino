/*
 * DOOR LOCK 
 * LCD KECIL
 * BUZZER
 * ANGGOTA KELOMPOK KELAS X PPLG2
 *    TEGUH DERMAWAN
 *    RENDI
 *    RAFI ADI CHANDRA
 *Library cari di tools "MANAGE LIBRARIES"KETIK>LIQUIDCRYSTAL_12C.H
 *                                              MRFC522
 *                                 
  */

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
#define lock 8
#define buzz 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd (0x27, 16, 2);
int out = 0;
bool trig = false;
String card1 = "2A CB 6B 81";
String card2 = "59 46 FC 6E";
String card3 = "xxxxxx"; //e-ktp
String card4 = "xxxxxx";

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(lock,OUTPUT);
  pinMode(buzz,OUTPUT);
  digitalWrite(lock,1);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("GoLite Store");
}

void loop() {
  String content= "";
  if ( mfrc522.PICC_IsNewCardPresent()) {
    if ( mfrc522.PICC_ReadCardSerial()) {
        trig = true;
         //Show UID on serial monitor
          Serial.println();
          Serial.print(" UID tag :");
          
          byte letter;
          for (byte i = 0; i < mfrc522.uid.size; i++) {
             Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
             Serial.print(mfrc522.uid.uidByte[i], HEX);
             content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
             content.concat(String(mfrc522.uid.uidByte[i], HEX));
          }
      }
      //delay percobaan
      delay(1000);
  }
  
  content.toUpperCase();
  //Serial.println(content);
  if (content.substring(1) == card1 || content.substring(1) == card2 || content.substring(1) == card3 || content.substring(1) == card4){
    //your code here
    Serial.println("Welcome Boss");
    trig = false;
    digitalWrite(lock,0);
    delay(3000);
    digitalWrite(lock,1); 
  }else {
     if (trig){
      lcd.setCursor(0,1);
      lcd.print(content);
      lcd.print("     ");
      Serial.println(" Access Denied ");
      beep();
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("  RFID Tester   ");
      trig = false;
    }
  }
  
  // Serial.println("end loop");
  delay(50);
}

void beep(){
  for (int i = 0; i<2; i++){
    digitalWrite(buzz,1);
    delay(75);
    digitalWrite(buzz,0);
    delay(75);
  }
}
