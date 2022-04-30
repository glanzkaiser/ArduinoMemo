const int kPinSensor = A5;
const int kPinLed = 13;
const int k_threshold = 100;

int ledState = LOW; 
// variable used to store the last LED status, to toggle the light

void setup()
{
Serial.begin(9600);
Serial.println("Detecting Knocking");
Serial.println("with Arduino UNO R3 by Glanz and Freya");
pinMode(kPinLed, OUTPUT); 
}

void loop()
{
  int val = analogRead(kPinSensor);
  
  if (val >= k_threshold) {
  ledState = !ledState;
  // toggle the value of ledState
  Serial.println("The vibration value is :");
  Serial.println(val);
  digitalWrite(kPinLed, ledState);
  delay(2000); 

  }
}
