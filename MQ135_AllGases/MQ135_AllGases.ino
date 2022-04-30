
int R0 = 6692;
int R2 = 1000;
float RS;
float PPM_acetone;
float PPM_alcohol;
float PPM_CO2;
float PPM_CO;
float PPM_NH4;
float PPM_tolueno;

void setup() {
   Serial.begin(9600);
   Serial.println("****************************************");
   Serial.println("MQ-135 All Gases Measurement");
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
   PPM_tolueno = 606.3291 - 632.91139*(RS/R0);
   PPM_acetone = 379.2846 - 244.55857*(RS/R0);
   
   
   Serial.print("\tAlcohol = "),Serial.print(PPM_alcohol);
   Serial.print("| \tNH4 = "),Serial.print(PPM_NH4);
   Serial.print("| \tCO2 = "),Serial.print(PPM_CO2);
   Serial.print("| \tCO = "),Serial.print(PPM_CO2);
   Serial.print("| \tTolueno = "),Serial.print(PPM_tolueno);
   Serial.print("| \tAcetone = "),Serial.println(PPM_acetone);
   
   delay(5000); // delay in between reads for stability
}
