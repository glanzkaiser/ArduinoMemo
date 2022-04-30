
int UVOUT = A0; 
int REF_3V3 = A1; 

void setup() {
  Serial.begin(9600);
  Serial.println("UV Sensor Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
}

void loop() {
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); 
  //Convert the voltage to a UV intensity level
 
  Serial.print("output: ");
  Serial.print(refLevel);
  Serial.print('\n');
  
  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);
  Serial.print('\n');
  
  Serial.print(" * ML8511 voltage: ");
  Serial.print(outputVoltage);
  Serial.print('\n');
 
  Serial.print(" * UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);
  Serial.print('\n');
  Serial.print('\n');
  delay(5000);
}

int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
