#define pirPin 2
#define relayPin 5
const int ledPin  =  13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Relay-PIR Motion Detection Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
}
void loop() {
  bool state_pir = digitalRead(pirPin);
  
  if (state_pir == 0){
  Serial.println("Nothing is detected");  
  digitalWrite(relayPin, HIGH); 
  digitalWrite(ledPin, LOW);
  } 
  else {
  Serial.println("Detected a Presence");    
  digitalWrite(relayPin, LOW); 
  digitalWrite(ledPin, HIGH);
  }
  delay(5000);
}
