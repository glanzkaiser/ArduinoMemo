 int sensorPin = A0;  
 int sensorValue = 0; 

 void setup() {  

  pinMode(LED_BUILTIN, OUTPUT);  
  // initialize the serial port  
  Serial.begin(9600);  
  Serial.println("MQ-7 Carbon Monoxide Sensor");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
 }  

 void loop() {  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
 // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   

  sensorValue = analogRead(sensorPin);  
  Serial.print("CO = "),Serial.print(sensorValue);
  Serial.println(" ppm");
    
 }  
