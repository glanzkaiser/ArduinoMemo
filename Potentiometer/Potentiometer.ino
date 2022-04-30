void setup() {
  Serial.begin (9600); 
  Serial.println("Potentiometer Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");

}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" Volts");
  delay(1000);  
}
