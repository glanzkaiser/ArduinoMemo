#include "AvgStd.h"
AvgStd mySamples;

int R0 = 6692;
int R2 = 1000;
float RS;
float PPM_acetone;
//Acetone indeed Acetone

void setup() {
   Serial.begin(9600);
   Serial.print("GlanzFreya Acetone Measurement");
   Serial.print("With MQ135 and Arduino Uno R3");
   mySamples = AvgStd();
   mySamples.setRejectionSigma(7.0);
}
 
void loop() {
   // read the input on analog pin 0:
   int sensorValue = analogRead(A2);
   // convert to voltage:
   float volts = sensorValue * 5;
   volts = volts / 1023;
   
   // calculate RS
   RS = R2 * (1-volts);
   RS = RS/volts;
   // calculate acetone PPM
   PPM_acetone = 159.6 - 133.33*(RS/R0);
   Serial.println(PPM_acetone);
   delay(1000); // delay in between reads for stability
}
