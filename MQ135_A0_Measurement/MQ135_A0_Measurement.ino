#include "AvgStd.h"
AvgStd mySamples;

int R0 = 176;
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
   int sensorValue = analogRead(A0);
   // convert to voltage:
   float volts = sensorValue * 5;
   volts = volts / 1023;
   
   float value = volts;
   mySamples.checkAndAddReading(value);
   float average = mySamples.getMean();
   float std = mySamples.getStd();
   float min = mySamples.getMin();
   float max = mySamples.getMax();
   int N = mySamples.getN();
   
   // print out the voltage:
   Serial.print("Voltage = "),Serial.println(volts);
   Serial.print("\tAverage = "),Serial.println(average);
   Serial.print("\tStandard Deviation = "),Serial.println(std);
   Serial.print("\tMinimum = "),Serial.println(min);
   Serial.print("\tMaximum = "),Serial.println(max);

   delay(1000); // delay in between reads for stability
}
