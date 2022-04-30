#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK rf_driver;

String str_co;
String str_co2;
String str_out;

void setup() {
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
    Serial.println("Receive CO and CO2 data with RF433, MQ7 and MQ135");
    Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
  // Set buffer to size of expected message
    uint8_t buf[13]; //46 works
    uint8_t buflen = sizeof(buf);
    // Check if received packet has the correct size
    if (rf_driver.recv(buf, &buflen))
    {
      str_out = String((char*)buf);

      // Split string into two values
      for (int j = 0; j < str_out.length(); j++) 
      {
      if (str_out.substring(j, j+1) == ",") 
        {
        str_co = str_out.substring(0, j);
        str_co2 = str_out.substring(j+1);
        break;
        }
      }
      
      // Print values to Serial Monitor
      Serial.print("CO: ");
      Serial.print(str_co);
      Serial.print(" ppm");
      Serial.print(" \t | CO2: ");
      Serial.print(str_co2);
      Serial.println(" ppm");
    }
 }
