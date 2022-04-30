#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK rf_driver;

String str_humid;
String str_temp;
String str_out;

void setup() {
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
    Serial.println("Receive Temperature and Humidity data with RF433 and DHT11");
    Serial.println("with Arduino UNO R3 by Glanz and Freya");

}

void loop() {
  // Set buffer to size of expected message
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
      str_humid = str_out.substring(0, i);
      str_temp = str_out.substring(i+1);
      break;
      }
    }
      
      // Print values to Serial Monitor
      Serial.print("Humidity: ");
      Serial.print(str_humid);
      Serial.print("\t | Temperature: ");
      Serial.print(str_temp);
      Serial.println(" °C");         
    }

}
