
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface

 int R0 = 6692;
 int R2 = 1000;
 int sensorPin = A0;  
 int MQ7sensorValue = 0;
 int sensorValue = 0; 
 const int redLED = 12;
 const int yellowLED = 11;
 const int greenLED = 10;
 LiquidCrystal_I2C lcd(0x27, 20,4);
 float PPM_CO2;
 float PPM_CO;
 float RS;

//For repeating melody: Always
int melodyalways[] = {
  NOTE_B4, NOTE_D5, NOTE_D5,
  NOTE_B4, NOTE_D5,
  NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_C5, NOTE_B4, NOTE_G4,
  NOTE_G4, NOTE_E4, NOTE_G4,
  NOTE_C5, NOTE_C5, NOTE_B4,
  NOTE_G4, NOTE_E4,
  NOTE_E4, NOTE_D4,
  NOTE_E4, NOTE_F4,
};

int notealwaysDurations[] = {
  3, 4, 3,
  4, 2,
  2,
  2, 3, 4,
  4, 4, 5,
  4, 4, 4,
  4, 4, 2,
  4, 1,
  4, 4, 
  1, 2
};

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

  pinMode(LED_BUILTIN, OUTPUT); 
  lcd.init(); 
  lcd.clear(); 
  lcd.backlight(); 
  lcd.createChar(0, Heart);
  lcd.createChar(1, Southwest);
  lcd.createChar(2, Northeast);
  lcd.clear();
  lcd.print("Glanz");
  // initialize the serial port  
  Serial.begin(9600);  
  Serial.println("BMP280, MQ-7 and MQ-135 Sensor with LCD");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  
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
  PPM_CO = 155.1505 - 129.2524*(RS/R0);
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
 // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   
  
  MQ7sensorValue = analogRead(sensorPin);  
  Serial.print("CO = "),Serial.print(PPM_CO);
  Serial.print(" / "),Serial.print(MQ7sensorValue);
  Serial.println(" ppm");
  Serial.print("CO2 = "),Serial.print(PPM_CO2);
  Serial.println(" ppm");
  Serial.print("Measurement #: "),Serial.println(i);
  Serial.println();
  
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" C");
  
  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure()/100); //displaying the Pressure in hPa, you can change the unit
  Serial.println(" hPa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(975.7)); //The "975.7" is the pressure(hPa) at sea level in day in your region
  Serial.println(" m");                    //If you don't know it, modify it until you get your current altitude

  Serial.println();
  
  if (MQ7sensorValue <= 200)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,HIGH);

    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
    
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(0);
    lcd.setCursor(3, 1);
    lcd.write(2);
    lcd.setCursor(0, 2);
    lcd.print("Freya");
  
    lcd.setCursor(0,3);
    lcd.print("CO/CO2:"),lcd.print(MQ7sensorValue),lcd.print("/"),lcd.print(PPM_CO2);
    lcd.setCursor(6,0);
    lcd.print("#: "),lcd.print(i),lcd.print(" "),lcd.print(bmp.readAltitude(975.7)),lcd.print(" m");
    //The "975.7" is the pressure(hPa) at sea level in day in your region
    lcd.setCursor(6,1), lcd.print(bmp.readTemperature()),lcd.print(" C");
    lcd.setCursor(6,2), lcd.print(bmp.readPressure()/100),lcd.print(" hPa");
  }
  else if ((MQ7sensorValue > 200) || (MQ7sensorValue <= 800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,HIGH);

    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
    
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(0);
    lcd.setCursor(3, 1);
    lcd.write(2);
    lcd.setCursor(0, 2);
    lcd.print("Freya");
  
    lcd.setCursor(0,3);
    lcd.print("CO/CO2:"),lcd.print(MQ7sensorValue),lcd.print("/"),lcd.print(PPM_CO2);
    lcd.setCursor(6,0);
    lcd.print("#: "),lcd.print(i),lcd.print(" "),lcd.print(bmp.readAltitude(975.7)),lcd.print(" m");
    //The "975.7" is the pressure(hPa) at sea level in day in your region
    lcd.setCursor(6,1), lcd.print(bmp.readTemperature()),lcd.print(" C");
    lcd.setCursor(6,2), lcd.print(bmp.readPressure()/100),lcd.print(" hPa");
  }
  else if ((MQ7sensorValue > 800) || (MQ7sensorValue <= 1800))
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,LOW);

    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(0);
    lcd.setCursor(3, 1);
    lcd.write(2);
    lcd.setCursor(0, 2);
    lcd.print("Freya");
  
    lcd.setCursor(0,3);
    lcd.print("CO/CO2:"),lcd.print(MQ7sensorValue),lcd.print("/"),lcd.print(PPM_CO2);
    lcd.setCursor(6,0);
    lcd.print("#: "),lcd.print(i),lcd.print(" "),lcd.print(bmp.readAltitude(975.7)),lcd.print(" m");
    //The "975.7" is the pressure(hPa) at sea level in day in your region
    lcd.setCursor(6,1), lcd.print(bmp.readTemperature()),lcd.print(" C");
    lcd.setCursor(6,2), lcd.print(bmp.readPressure()/100),lcd.print(" hPa");
  }
  else if (MQ7sensorValue > 1800) 
  {
    digitalWrite(redLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,LOW);

    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
    
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(0);
    lcd.setCursor(3, 1);
    lcd.write(2);
    lcd.setCursor(0, 2);
    lcd.print("Freya");
  
    lcd.setCursor(0,3);
    lcd.print("CO/CO2:"),lcd.print(MQ7sensorValue),lcd.print("/"),lcd.print(PPM_CO2);
    lcd.setCursor(6,0);
    lcd.print("#: "),lcd.print(i),lcd.print(" "),lcd.print(bmp.readAltitude(975.7)),lcd.print(" m");
    //The "975.7" is the pressure(hPa) at sea level in day in your region
    lcd.setCursor(6,1), lcd.print(bmp.readTemperature()),lcd.print(" C");
    lcd.setCursor(6,2), lcd.print(bmp.readPressure()/100),lcd.print(" hPa");
  }
  i++;
  }
 }  
