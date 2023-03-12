
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface
float tempC;
float pressure;
float altitude;
int analogPin = 0;     
int data = 0;           
char userInput;

void setup(){

  Serial.begin(9600);                        //  setup serial
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

void loop(){
tempC = bmp.readTemperature();
if(Serial.available()> 0){ 
    
    userInput = Serial.read();               // read user input
      
      if(userInput == 'g'){                  // if we get expected value 
            Serial.println(tempC);            
            
      } // if user input 'g' 
  } // Serial.available
  delay(1000);
} // Void Loop
