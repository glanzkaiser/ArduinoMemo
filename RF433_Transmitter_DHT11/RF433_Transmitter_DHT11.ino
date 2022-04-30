#include <RH_ASK.h>
#include <SPI.h> 
#include "DHT.h";

#define DHTPIN 3
#define DHTTYPE DHT11   

RH_ASK rf_driver;

DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20,4);

float hum;    
float temp; 
String str_humid;
String str_temp;
String str_out;

void setup() {
   Serial.begin(9600);
   Serial.println("Send  Temperature and Humidity data with RF433 and DHT11");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
   rf_driver.init();
   dht.begin();
   lcd.init(); 
   lcd.clear(); 
   lcd.backlight(); 
}

void loop() {
  delay(2300);
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    Serial.print("Humidity = "),Serial.print(hum);
    Serial.print("%");
    Serial.print("\t | Temperature = "),Serial.print(temp);
    Serial.println(" °C");

    lcd.setCursor(1,0);
    lcd.print("GFreya DHT11 & RF433");
    lcd.setCursor(0,1);
    lcd.print("Humidity : "),lcd.print(hum),lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("Temp : "),lcd.print(temp),lcd.print(" C");
    
    // Convert Humidity to string
    str_humid = String(hum);
    
    // Convert Temperature to string
    str_temp = String(temp);
 
    // Combine Humidity and Temperature
    str_out = str_humid + "," + str_temp;
    
    // Compose output character
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
}
