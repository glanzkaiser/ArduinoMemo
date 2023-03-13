 int R0 = 6692;
 int R2 = 1000;
 int sensorPin = A0;  
 int MQ7sensorValue = 0;

 float PPMCO2;
 float PPMCO;
 float RS;
 float MQ7CO;

void setup() {  
  // initialize the serial port  
  Serial.begin(115200);  
   
  }

void loop() {  
  int sensorValue135 = analogRead(A2);  
  float volts = sensorValue135 * 5;
  volts = volts / 1023;
  RS = R2 * (1-volts);
  RS = RS/volts; 
  
  PPMCO2 = 470.627063 - 330.033*(RS/R0);
  PPMCO = 155.1505 - 129.2524*(RS/R0);
  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
   // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   
  
  MQ7CO = analogRead(sensorPin);  
  Serial.print(PPMCO2);
  Serial.print(",");
  Serial.println(MQ7CO);
  //delay(3000);   
 }
