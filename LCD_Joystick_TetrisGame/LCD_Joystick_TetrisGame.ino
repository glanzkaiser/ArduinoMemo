#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include "Tetris.h"
#define SS_PIN 10


void setup() {
  // put your setup code here, to run once:
  lcd.init();                
  lcd.clear();
  lcd.backlight();
  
  lcd.print("   Score: 0");
  lcd.setCursor(17, 4);
  lcd.print("Zaqhiel Tetris");
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial) {
    ;
  }
  Serial.println("Loading ...");
  Dp_Init();
  Te_Init();
  Serial.println(random(9, 15) * (10 + pow(3,1) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,2) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,3) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,4) * 10));
}



byte xC = 0;
byte yC = 0;
long frameCount = 0;

void loop() {
  // put your main code here, to run repeatedly:
  frameCount++;
  Te_Draw();
  Te_Update(frameCount);
  delay(1);
}
