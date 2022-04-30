int const UP_BTN = 2;
int const DOWN_BTN = 4;
int const LEFT_BTN = 5;
int const RIGHT_BTN = 3;
int const E_BTN = 6;
int const F_BTN = 7;
int const JOYSTICK_BTN = 8;
int const JOYSTICK_AXIS_X = A0;
int const JOYSTICK_AXIS_Y = A1;
int buttons[] = {UP_BTN, DOWN_BTN, LEFT_BTN, RIGHT_BTN, E_BTN, F_BTN, JOYSTICK_BTN};
//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  for (int i; i < 7; i++)  pinMode(buttons[i], INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Funduino Joystick Shield Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  Serial.print("UP="),Serial.print(digitalRead(UP_BTN));
  Serial.print("\tDOWN="),Serial.print(digitalRead(DOWN_BTN));
  Serial.print("\tLEFT="),Serial.print(digitalRead(LEFT_BTN));
  Serial.print("\tRIGHT="),Serial.print(digitalRead(RIGHT_BTN));
  Serial.print("\tE="),Serial.print(digitalRead(E_BTN));
  Serial.print("\tF="),Serial.print(digitalRead(F_BTN));
  Serial.print("\tJOYSTICK BTN="),Serial.print(digitalRead(JOYSTICK_BTN));
      
  // Print the full X/Y joystick values (0-1023)
  Serial.print("\tX="),Serial.print(analogRead(JOYSTICK_AXIS_X));
  Serial.print("\tY="),Serial.println(analogRead(JOYSTICK_AXIS_Y)); 
  delay(550);
 }
