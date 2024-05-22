// Upload with SW 3 and 4 ON

const int LED_PIN1 = 5; // This LED is connected to D5 of Arduino
const int LED_PIN2 = 6; // This LED is connected to D6 of Arduino
const int LED_PIN3 = 7; // This LED is connected to D7 of Arduino

void setup(){
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  Serial.begin(9600);    
  Serial.println("Control LED with WiFi Test");
  
}

void loop(){
  if (Serial.available()>0) {
      int reading = Serial.read();
      if (reading == 1) {
          digitalWrite(LED_PIN1, HIGH); 
        }
      else if (reading == 2) {
          digitalWrite(LED_PIN1, LOW); 
        }
      else if (reading == 3) {
          digitalWrite(LED_PIN2, HIGH); 
        }
      else if (reading == 4) {
          digitalWrite(LED_PIN2, LOW); 
        }  
      else if (reading == 5) {
          digitalWrite(LED_PIN3, HIGH); 
        }
      else if (reading == 6) {
          digitalWrite(LED_PIN3, LOW); 
        }
    }
  
}
