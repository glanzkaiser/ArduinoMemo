const int VRx = A0;
const int VRy = A1;
const int SW = 2;

long analogInputValX;
long analogInputValY;
int digitalInputVal;

void setup() {
  Serial.begin(9600); 
  Serial.println("Joystick Analog Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  pinMode(VRx, INPUT); 
  pinMode(VRy, INPUT); 
  pinMode(SW, INPUT); 
}

void loop() {
  int xPosition = analogRead(VRx);
  int yPosition = analogRead(VRy);
  int SW_state = digitalRead(SW);
  
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(500);
  
}
