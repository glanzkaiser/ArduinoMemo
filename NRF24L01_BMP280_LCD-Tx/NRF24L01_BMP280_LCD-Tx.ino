//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//struct MyData {
//  float a;
//  float t;
//  float p;
//};

//MyData data;
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 2000;

//const byte address[6] = "00001"; //channel
const byte slaveAddress[5] = {'R','x','A','A','A'};

void setup() {
  
  while (!Serial);
  Serial.begin(9600); 
  Serial.println("nRF24L01 and BMP280 Project: Tx");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  Serial.println();
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,    
                  Adafruit_BMP280::SAMPLING_X2,    
                  Adafruit_BMP280::SAMPLING_X16,   
                  Adafruit_BMP280::FILTER_X16,      
                  Adafruit_BMP280::STANDBY_MS_500); 

                  
  //Setup the transmitter
  radio.begin();
  radio.setDataRate(RF24_1MBPS);
  radio.setRetries(3,5);
  //radio.openWritingPipe(address);
  radio.openWritingPipe(slaveAddress);
  radio.setPALevel(RF24_PA_LOW); // set the Power Amplifier level
  // if using a higher level it is recommended to 
  // use a bypass capacitors across GND and 3.3V
  // to have more stable voltage while operating.
  radio.stopListening();
  //radio.setAutoAck(false);
  
}
void loop() {
  currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis) {
    send();
    prevMillis = millis();
  }
}
int i = 1;
void send() {
  while (i>0) {
  //The "975.7" is the pressure(hPa) at sea level in day in your region
  
  float temperatureValue = bmp.readTemperature();
  float pressureValue = bmp.readPressure()/100;
  float altitudeValue = bmp.readAltitude(975.7); 
  
  if (isnan(temperatureValue) || isnan(altitudeValue) || isnan(pressureValue)){
    Serial.println(F("Failed to read from BMP280 sensor!"));
    return;
  }
  else {
      
  Serial.print(F("#  "));
  Serial.print(i);
  Serial.println();
  
  Serial.print(F("Temperature = "));
  Serial.print(temperatureValue);
  Serial.println(" °C");
  
  Serial.print(F("Pressure = "));
  Serial.print(pressureValue);
  Serial.println(" hPa");

  Serial.print(F("Approx altitude = "));
  Serial.print(altitudeValue); 
  Serial.println(" m");
  Serial.println();

  float dataToSend[3];
  dataToSend[0] = temperatureValue;
  dataToSend[1] = pressureValue;
  dataToSend[2] = altitudeValue;
    
  radio.write(&dataToSend, sizeof(dataToSend));
  }
  i++;
  delay(2000);
  }
}
