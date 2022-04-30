#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK driver;

void setup()
{
    Serial.begin(9600);    // Debugging only
    Serial.println("RF 433MHz Test");
    Serial.println("With Arduino Uno R3 by Glanz and Freya");
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Hey beautiful, I miss the eagle";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
