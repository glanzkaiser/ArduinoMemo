
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "Sodaq_DS3231.h"
File myFile;
DateTime now;
int newHour = 0;
int oldHour = 0;

 int R0 = 6692;
 int R2 = 1000;
 int sensorPin = A0;  
 int MQ7sensorValue = 0;
 int sensorValue = 0; 
 const int redLED = 7;
 const int yellowLED = 9;
 const int greenLED = 8;
 LiquidCrystal_I2C lcd(0x27, 20,4);
 float PPM_CO2;
 float RS;

 void save_temperature() {
    myFile = SD.open("temp.txt", FILE_WRITE);
    now = rtc.now();
    myFile.print(now.hour());
    myFile.print(":");
    myFile.print(now.minute());
    rtc.convertTemperature(); //convert current temperature into registers
    myFile.print(",");
    myFile.print(rtc.getTemperature()); //read registers and save temperature on deg C
    myFile.println(" C");
    myFile.print(",");
    myFile.print(MQ7sensorValue);
    myFile.print(PPM_CO2);
    
  
    myFile.close();
  }

 void setup() {  

  pinMode(LED_BUILTIN, OUTPUT); 
  lcd.init(); 
  lcd.clear(); 
  lcd.backlight(); 
  Wire.begin();
  rtc.begin();
  // initialize the serial port  
  Serial.begin(9600);  
  Serial.println("MQ-7 and MQ-135 Sensor");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  now = rtc.now();
  oldHour = now.hour();
  
 }  

 int i = 1;
 void loop() {  
  while (i > 0) {
  int sensorValue135 = analogRead(A2);  
  float volts = sensorValue135 * 5;
  volts = volts / 1023;
  RS = R2 * (1-volts);
  RS = RS/volts; 
  
  PPM_CO2 = 470.627063 - 330.033*(RS/R0);
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
 // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   

  MQ7sensorValue = analogRead(sensorPin);  
  Serial.print("CO = "),Serial.print(MQ7sensorValue);
  Serial.println(" ppm");
  Serial.print("CO2 = "),Serial.print(PPM_CO2);
  Serial.println(" ppm");
  Serial.print("Measurement #: "),Serial.println(i);
  
  //Save temperature data to Memory card
  now = rtc.now();
  newHour = now.hour();

  save_temperature();

  
  if (MQ7sensorValue <= 200)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,HIGH);
    
    lcd.setCursor(1,0);
    lcd.print("GlanzFreya' MQ7 & MQ135");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("CO2 : "),lcd.print(PPM_CO2),lcd.print(" ppm");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
  }
  else if ((MQ7sensorValue > 200) || (MQ7sensorValue <= 800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,HIGH);
    
    lcd.setCursor(1,0);
    lcd.print("GlanzFreya' MQ7 & MQ135");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("CO2 : "),lcd.print(PPM_CO2),lcd.print(" ppm");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
    
  }
  else if ((MQ7sensorValue > 800) || (MQ7sensorValue <= 1800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,LOW);
    lcd.setCursor(1,0);
    lcd.print("GlanzFreya' MQ7 & MQ135");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("CO2 : "),lcd.print(PPM_CO2),lcd.print(" ppm");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
    
  }
  else if (MQ7sensorValue > 1800) 
  {
    digitalWrite(redLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,LOW);
    lcd.setCursor(1,0);
    lcd.print("GlanzFreya' MQ7 & MQ135");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("CO2 : "),lcd.print(PPM_CO2),lcd.print(" ppm");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
  }
  i++;
  }
 }  
