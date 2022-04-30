#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);  // Debugging only
    Serial.println("RF 433MHz Test");
    Serial.println("With Arduino Uno R3 by Glanz and Freya");
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[33];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
}
