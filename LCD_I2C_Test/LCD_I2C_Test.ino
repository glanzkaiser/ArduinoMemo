#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 
void setup()
{
  lcd.init();   
  lcd.clear(); 
  lcd.backlight();
  //Set cursor to character 1 on line 0
  lcd.setCursor(1,0);
  lcd.print("Mon amour Freya,");
  
  lcd.setCursor(1,1);
  lcd.print("je t'aime");
  
  lcd.setCursor(1,2);
  lcd.print("Tu es toujours");
  
  lcd.setCursor(1,3);
  lcd.print("la plus belle");
}


void loop()
{
  
}
