/*
*LCD>>>> (GND LCD>BREADBOARD NEGATIF)(SDA LCD>A4 ARDUINO)
          (VCC LCD>BREADBOARD POSITIF)(SCL LCD>A5 ADRUINO)
*POMPA DAN RELAY5V (KABEL WARNA MERAH POMPA > N0 RELAY5V)
                    (KABEL WARNA HITAM POMPA > BREADBOARD NEGATIF) 
                    (KABEL DARI COM RELAY5V > BREADBOARD POSITIF)
*RELAY5V (GND>BREADBOARD NEGATIF)(VCC>BREADBOARD POSITIF)
          (IN>lubang breadboard ke 10 D)
*SENSOR  (GND>BREADBOARD NEGATIF)(VCC>BREADBOARD POSITIF)
          (A0>A0 ARDUINO)
*ARDUINO (GND>BREADBOARD NEGATIF)(5V>BREADBOARD POSITIF)
          (PIN 2 ARDUINO POMPA DISEBELAH (KABEL IN RELAY 5V(DIBREADBOARD))
 */
 
//PENYIRAH TANAMAN OTOMATIS lcd
// the setup routine runs once when you press reseti
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int pompa=2; //pin pompa ada di pin 2

void setup() {
 lcd.init();
 lcd.backlight ();
 lcd.begin(16, 2);
 Serial.begin(9600);
 pinMode (pompa,OUTPUT);

}

void loop () {
//read the input on analog pin 0;
delay (2000);
lcd.clear();
int sv = analogRead(A0);
Serial.println(sv);
if((sv>400)&&(sv<1023)) {
digitalWrite (pompa, LOW);
lcd.setCursor(0,0) ;
lcd.print("TANAMAN HAUS");
}
if((sv>100)&&(sv<400)) {
digitalWrite (pompa, HIGH);
lcd.setCursor(0,1);
lcd.print("TANAMAN KENYANG");
}
//delay(100)  // delay in between reads for stability

}
