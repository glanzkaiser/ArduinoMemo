#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 
byte Heart[8] = {
0b00000,
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000
};
byte Southwest[8] =
{
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00001,
0b00010
};

byte Northeast[8] =
{
0b11100,
0b01100,
0b10100,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

void setup() {
   lcd.init();
   lcd.backlight();
   lcd.createChar(0, Heart);
   lcd.createChar(1, Southwest);
   lcd.createChar(2, Northeast);
   lcd.clear();
   lcd.print("Glanz");
}

void loop() {
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(2, 1);
  lcd.write(0);
  lcd.setCursor(3, 1);
  lcd.write(2);
  lcd.setCursor(0, 2);
  lcd.print("Freya");
}
