#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ANALOG_IN_PIN A0
 
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
float R1 = 30000.0;
float R2 = 7500.0;
 
float ref_voltage = 5.0;
 
int adc_value = 0;

LiquidCrystal_I2C lcd(0x27,20,4); 
void setup()
{
  Serial.begin(9600);
  Serial.println("GlanzFreya LCD-Volt");
  lcd.init();   
  lcd.clear(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("GlanzFreya LCD-Volt");
  lcd.setCursor(1,1);
  lcd.print("Battery voltage:");
}


void loop()
{
  adc_value = analogRead(ANALOG_IN_PIN);
 
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
 
  in_voltage = adc_voltage / (R2 / (R1 + R2)) ;
 
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 5);
  
 
  lcd.setCursor(1,2);
  lcd.print(in_voltage, 5);
  lcd.print(" V");
  delay(3000);
}
