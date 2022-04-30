#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;
const int ledGreen  =  9;
const int ledYellow  =  10;
const int ledRed  =  13;

float temperature = 25,tdsValue = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("TDS Analog for Water Quality Test");
    Serial.println("with Arduino UNO R3 by Glanz and Freya");
    pinMode(ledGreen, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledRed, OUTPUT);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}

void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    
    if (tdsValue < 60){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    Serial.println("Very healthy water, you can drink it ");
    Serial.println("Water Quality: ");
    Serial.print(tdsValue,0);
    Serial.println(" ppm");
    } 
    if (tdsValue > 60 && tdsValue < 100){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    Serial.println("Quite healthy water, you can drink it ");
    Serial.println("Water Quality: ");
    Serial.print(tdsValue,0);
    Serial.println(" ppm");
    }
    if (tdsValue > 100){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    Serial.println("Contaminated water, Do not drink it ");
    Serial.println("Water Quality: ");
    Serial.print(tdsValue,0);
    Serial.println(" ppm");
}
    delay(3000);
}
