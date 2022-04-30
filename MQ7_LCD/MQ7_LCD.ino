
#include <LiquidCrystal_I2C.h>
 int sensorPin = A0;  
 int MQ7sensorValue = 0;
 const int redLED = 7;
 const int yellowLED = 9;
 const int greenLED = 8;
 LiquidCrystal_I2C lcd(0x27, 20,4);
 
 void setup() {  

  pinMode(LED_BUILTIN, OUTPUT); 
  lcd.init(); 
  lcd.clear(); 
  lcd.backlight(); 
  // initialize the serial port  
  Serial.begin(9600);  
  Serial.println("MQ-7 Carbon Monoxide Sensor");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
 }  

 int i = 1;
 void loop() {  
  while (i > 0) {
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
  Serial.print("Measurement #: "),Serial.println(i);
  
  if (MQ7sensorValue <= 200)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,HIGH);
    
    lcd.setCursor(1,0);
    lcd.print("MQ7 with GlanzFreya");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("Low CO level");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
  }
  else if ((MQ7sensorValue > 200) || (MQ7sensorValue <= 800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,HIGH);
    
    lcd.setCursor(1,0);
    lcd.print("MQ7 with GlanzFreya");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("Normal CO level");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
    
  }
  else if ((MQ7sensorValue > 800) || (MQ7sensorValue <= 1800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,LOW);
    lcd.setCursor(1,0);
    lcd.print("MQ7 with GlanzFreya");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("High CO level");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
    
  }
  else if (MQ7sensorValue > 1800) 
  {
    digitalWrite(redLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,LOW);
    lcd.setCursor(1,0);
    lcd.print("MQ7 with GlanzFreya");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(MQ7sensorValue),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("It's dangerous here");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
  }
  i++;
  }
 }  
