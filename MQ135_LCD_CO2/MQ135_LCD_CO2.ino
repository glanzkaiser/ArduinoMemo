#include <LiquidCrystal_I2C.h>
#include "MQ135.h"
#define ANALOGPIN A2    //  Define Analog PIN on Arduino Board
#define RZERO 4668.29    //  Define RZERO Calibration Value
const int redLED = 7;
const int greenLED = 8;
MQ135 gasSensor = MQ135(ANALOGPIN);
LiquidCrystal_I2C lcd(0x27, 20,4);
void setup()
{ 
  lcd.init(); 
  lcd.clear(); 
  lcd.backlight();
  Serial.begin(9600);
  float rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 Calibration Value : ");
  Serial.println(rzero);
}

void loop() {
  float ppm = gasSensor.getPPM();
  delay(1000);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  lcd.setCursor(0,0);
  lcd.print("   GlanzFreya   ");
  lcd.setCursor(0,1);
  lcd.print("CO2 : ");
  lcd.print(ppm);
  lcd.print("ppm");
  if (ppm > 1000)
  {
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
    
    lcd.setCursor(0,0);
    lcd.print("   GlanzFreya   ");
    lcd.setCursor(0,1);
    lcd.print("CO2 : ");
    lcd.print(ppm);
    lcd.print("ppm");
    lcd.setCursor(0,4);
    lcd.print("CO2 is too high");
  }
  else
  {
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,HIGH);
    
    lcd.setCursor(0,0);
    lcd.print("   GlanzFreya   ");
    lcd.setCursor(0,1);
    
    lcd.print("CO2 : ");
    lcd.print(ppm);
    lcd.print("ppm");
    lcd.setCursor(0,3);
    lcd.print("CO2 level is good");
  }
}
