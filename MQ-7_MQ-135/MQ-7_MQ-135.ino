
int R0 = 6692;
int R2 = 1000;
int sensorPin = A0;  
int sensorValue = 0; 

float RS;
float PPM_acetone;
float PPM_alcohol;
float PPM_CO2;
float PPM_CO;
float PPM_NH4;
float PPM_toluene;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);  
   Serial.begin(9600);
   Serial.println("****************************************");
   Serial.println("MQ-135 and MQ-7 All Gases Measurement");
   Serial.println("With Arduino Uno R3 by Glanz and Freya");
   Serial.println("****************************************");
}
 
void loop() {
   // read the input on analog pin 0:
   int sensorValue135 = analogRead(A2);
   // convert to voltage:
   float volts = sensorValue135 * 5;
   volts = volts / 1023;
  
   // calculate RS
   RS = R2 * (1-volts);
   RS = RS/volts;

   PPM_alcohol = 154.92838 - 76.27765*(RS/R0);
   PPM_NH4 = 154.54826 - 54.54645*(RS/R0);
   PPM_CO2 = 470.627063 - 330.033*(RS/R0);
   PPM_CO = 155.1505 - 129.2524*(RS/R0);
   PPM_toluene = 606.3291 - 632.91139*(RS/R0);
   PPM_acetone = 379.2846 - 244.55857*(RS/R0);

   analogWrite(LED_BUILTIN, 255);   
   delay(60000);            
   analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
   delay(90000);            

   digitalWrite(LED_BUILTIN, HIGH);  
   delay (50); 
   sensorValue = analogRead(sensorPin);  
   
   Serial.print("Alcohol = "),Serial.print(PPM_alcohol),Serial.print(" ppm");
   Serial.print("| \tNH4 = "),Serial.print(PPM_NH4),Serial.print(" ppm");
   Serial.print("| \tCO2 = "),Serial.print(PPM_CO2),Serial.print(" ppm");
   Serial.print("| \tCO = "),Serial.print(PPM_CO),Serial.print(" ppm");
   Serial.print("| \tToluene = "),Serial.print(PPM_toluene),Serial.print(" ppm");
   Serial.print("| \tAcetone = "),Serial.print(PPM_acetone),Serial.print(" ppm");
   Serial.print("| \tCO from MQ-7 = "),Serial.print(sensorValue), Serial.println(" ppm");
   
}
