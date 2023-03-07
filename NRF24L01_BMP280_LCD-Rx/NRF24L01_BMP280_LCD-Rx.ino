//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//const byte address[6] = "00001"; //channel
const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

float temperatureValue;
float pressureValue;
float altitudeValue;
bool newData = false;

void setup() {
  while (!Serial);
  Serial.begin(9600);
  Serial.println("nRF24L01 and BMP280 Project: Rx");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");

  lcd.init(); 
  lcd.clear(); 
  lcd.backlight(); 
  lcd.clear();
  lcd.print("Glanz");
                
  // Setup the receiver
  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
  
  //set the address
  //radio.setAutoAck(false);
  //radio.setDataRate(RF24_250KBPS);
  
}

int i = 1;
void loop(){
  while (i > 0) {
  getData();
  showData();
  i++;
  }
  delay(2000);
}

void getData(){
  if (radio.available()){
    float dataToReceive[3];
    radio.read(&dataToReceive, sizeof(dataToReceive));
    
    temperatureValue = dataToReceive[0];
    pressureValue = dataToReceive[1];
    altitudeValue = dataToReceive[2];
    
    newData = true;
  }
}


void showData(){
  
  if (newData == true){ 
    Serial.print("Data received\t");
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

    lcd.setCursor(6,0);
    lcd.print("#: "),lcd.print(i),lcd.print(" "),lcd.print(altitudeValue),lcd.print(" m");
    lcd.setCursor(6,1), lcd.print(temperatureValue),lcd.print(" C");
    lcd.setCursor(6,2), lcd.print(pressureValue),lcd.print(" hPa");
    
    newData = false;
  }
  delay(2000);
}
