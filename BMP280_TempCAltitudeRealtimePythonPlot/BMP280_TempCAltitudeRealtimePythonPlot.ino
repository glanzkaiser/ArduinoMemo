
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface
float tempC;
float pressure;
float altitude;
 
 void setup() {  
  // initialize the serial port  
  Serial.begin(115200);  
  if (!bmp.begin()) {
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
  tempC = bmp.readTemperature();
  pressure = bmp.readPressure()/100;
  altitude = bmp.readAltitude(975.7); //The "975.7" is the pressure(hPa) at sea level in your region
  Serial.print(tempC);
  Serial.print(",");
  Serial.println(altitude);//you can change altitude to pressure
  delay(3000);
 }  
