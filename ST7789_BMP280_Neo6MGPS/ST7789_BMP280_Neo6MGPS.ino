#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>          

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

// ST7789 TFT module connections
#define TFT_CS    10  
#define TFT_DC     9  
#define TFT_RST    8 
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

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
  Serial.println("BMP280, GPS Neo-6M and ST7789 Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
  tft.init(240, 240, SPI_MODE3);    
  tft.setRotation(2);

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
  Serial.print(bmp.readPressure()/100); 

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(975.7)); 
  //The "975.7" is the pressure(hPa) at sea level in day 
  //in your region
  Serial.println(" m");  
  
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 23);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("La Temperature : ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(bmp.readTemperature());
  tft.println(" C");
  tft.println(" ");
  
  tft.setTextColor(ST77XX_WHITE);
  tft.println("La Pression Atmospherique : ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(bmp.readPressure()/100);
  tft.println(" hPa");
  tft.println(" ");
  
  tft.setTextColor(ST77XX_WHITE);
  tft.println("L'altitude : ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(bmp.readAltitude(975.7));
  tft.println(" m");
  tft.println(" ");
  
  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("Aucun GPS détecté");
    tft.setCursor(0, 223);
    tft.setTextColor(ST77XX_YELLOW);
    tft.println("Aucun GPS detecte");
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
    

    tft.setCursor(0, 108);
    tft.setTextColor(ST77XX_GREEN);
    tft.println("Freya!");
    tft.print("Latitude: ");
    tft.println(gps.location.lat(), 6);
    tft.print("Longitude: ");
    tft.println(gps.location.lng(), 6);
    tft.print("GPS' alt: ");
    tft.println(gps.altitude.meters(), 6);
  }
  else
  {
    Serial.println("Location: Not Available");

    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(0, 108);
    tft.println("Freya!");
    tft.setTextColor(ST77XX_YELLOW);
    tft.println("Emplacement: non disponible ");
  }
  
  Serial.print("Date: ");

  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(0, 82);
  tft.print("Date: ");
  
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());

    tft.print(gps.date.month());
    tft.print("/");
    tft.print(gps.date.day());
    tft.print("/");
    tft.println(gps.date.year());

  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Temps: ");

  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(0, 108);
  tft.print("Temps: ");
  
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());

    tft.print(gps.time.hour());
    tft.print(":");
    if (gps.time.minute() < 10) tft.print(F("0"));
    tft.print(gps.time.minute());
    tft.print(":");
    if (gps.time.second() < 10) tft.print(F("0"));
    tft.print(gps.time.second());
    tft.print(".");
    if (gps.time.centisecond() < 10) tft.print(F("0"));
    tft.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}
