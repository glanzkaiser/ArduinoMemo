#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>          
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
LiquidCrystal_I2C lcd(0x27,20,4); 

// ST7789 TFT module connections
#define TFT_CS    10  
#define TFT_DC     9  
#define TFT_RST    8 


// Choose two Arduino pins to use for software serial
int RXPin = 4;
int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  Serial.println("BMP280, GPS Neo-6M and LCD Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");

  lcd.init();   
  lcd.clear(); 
  lcd.backlight();
  
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

void loop()
{
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print(F("Pressure = "));
  Serial.println(bmp.readPressure()/100); 

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(975.7)); 
  //The "975.7" is the pressure(hPa) at sea level in day 
  //in your region
  Serial.println(" m");  
  Serial.println(" ");
  
  lcd.setCursor(1,1);
  lcd.print("La Temperature :");
  lcd.print(bmp.readTemperature());
  lcd.print(" C");

  lcd.setCursor(1,2);
  lcd.print("La Pression Atmospherique :");
  lcd.print(bmp.readPressure()/100);
  lcd.print(" hPa");

  lcd.setCursor(1,3);
  lcd.print("L'altitude :");
  lcd.print(bmp.readAltitude(975.7));
  lcd.print(" m");
  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      {
        displayInfo();
      
      lcd.setCursor(1,0);
      lcd.print("GPS detecte");
      }
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("Aucun GPS détecté");
    lcd.setCursor(1,0);
    lcd.print("Aucun GPS detecte");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("La latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("La Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("L'altitude: ");
    Serial.println(gps.altitude.meters());
    

    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 6);
    lcd.print(", Long: ");
    lcd.print(gps.location.lng(), 6);
    lcd.print(" GPS' alt: ");
    lcd.print(gps.altitude.meters(), 6);
  }
  else
  {
    Serial.println("Location: Not Available");

    lcd.setCursor(0, 0);
    lcd.print("Emplacement: non disponible");
  }
  
    Serial.print("Date: ");
  
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());

  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  delay(5000);
}
