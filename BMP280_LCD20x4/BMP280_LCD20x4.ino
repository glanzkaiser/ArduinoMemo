#include <Adafruit_BMP280.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BMP280_I2C_ADDRESS 0x77

Adafruit_BMP280 bmp; // I2C Interface

LiquidCrystal_I2C lcd(0x27,20,4); 

void setup() {
  Serial.begin(9600);
  Serial.println("BMP280 and LCD Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  lcd.init();   
  lcd.clear(); 
  lcd.backlight();
  if (!bmp.begin(BMP280_I2C_ADDRESS)) {
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

void loop() {
    lcd.setCursor(1,0);
    lcd.print("Cet endroit:");
    lcd.setCursor(1,1);
    lcd.print("Temp: ");
    lcd.print(bmp.readTemperature());lcd.print(" C");
    
    lcd.setCursor(1,2);
    lcd.print("Pres: ");
    lcd.print(bmp.readPressure()/10);lcd.print(" hPa");
    
    lcd.setCursor(1,3);
    lcd.print("Alt: ");
    lcd.print(bmp.readAltitude(975.7));lcd.print(" m");
    
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" °C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()/100); //displaying the Pressure in hPa, you can change the unit
    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(975.7)); //The "975.7" is the pressure(hPa) at sea level in day in your region
    Serial.println(" m");                    //If you don't know it, modify it until you get your current altitude

    Serial.println();
    delay(3300);
}
