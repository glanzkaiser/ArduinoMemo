
#include <Adafruit_BMP280.h>
int R0 = 6692;
int R2 = 1000;
int sensorPin = A0;  
 
float PPMCO2;
float PPMCO;
float RS;
float MQ7CO;

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
  int sensorValue135 = analogRead(A2);  
  float volts = sensorValue135 * 5;
  volts = volts / 1023;
  RS = R2 * (1-volts);
  RS = RS/volts; 
  
  PPMCO2 = 470.627063 - 330.033*(RS/R0);
  PPMCO = 155.1505 - 129.2524*(RS/R0);

  Serial.print(tempC);
  Serial.print(",");
  Serial.print(altitude);//you can change altitude to pressure
  Serial.print(",");
  Serial.print(PPMCO2);
  Serial.print(",");
  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
   // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   
  MQ7CO = analogRead(sensorPin);  
  
  Serial.println(MQ7CO);
  //delay(3000);
 }  
