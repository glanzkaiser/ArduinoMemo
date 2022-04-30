
#include <Arduino.h>
#include "ML8511.h"

#define ANALOGPIN A0
#define ENABLEPIN 7

ML8511 light(ANALOGPIN, ENABLEPIN);

void setup()
{
  Serial.begin(9600);
  Serial.println("UV Sensor Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");

  // manually enable / disable the sensor.
  light.enable();

  light.setDUVfactor(1.80);    // calibrate your sensor
  light.setVoltsPerStep(3.3, 4095); 
  
  Serial.print("mW cm^2");
  Serial.print("\tDUV index");
  Serial.println();
}


void loop()
{
  float UV = light.getUV();
  float DUV = light.estimateDUVindex(UV);
  Serial.print(UV, 4);
  Serial.print("\t");
  Serial.print(DUV, 1);
  Serial.println();
  delay(1000);
}
