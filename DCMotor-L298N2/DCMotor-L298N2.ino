#define A1 3  // Motor A pins
#define A2 5
#define B1 6 // Motor B pins
#define B2 9

int incomingByte = 0; // for incoming serial data

void setup() {
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  
  Serial.begin(9600); 
  Serial.println("DC Motor and L298N Test with RC Car F18G");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  Serial.println("select direction of movement");
  Serial.println("1.forward");
  Serial.println("2.backward");
  Serial.println("3.stop");

}
int  input = 0;
void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    input = incomingByte - 48; //convert ASCII code of numbers to 1,2,3

  switch (input) { 
    case 1:         // if input=1 ....... motors turn forward
      forward();
      Serial.println("Forward");
      break;
    case 2:         // if input=2 ....... motors turn backward
      backward();
      Serial.println("Reverse");
      break;
    case 3:         // if input=1 ....... motors turn stop
      Stop();
      Serial.println("Brake");
      break;
  }
  delay(200);
  input=0;
}
}
void forward() {          //function of forward 
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  analogWrite(B1, 255);
  analogWrite(B2, 0);
}

void backward() {         //function of backward
  analogWrite(A1, 0);
  analogWrite(A2, 210);
  analogWrite(B1, 0);
  analogWrite(B2, 210);
}

void Stop() {              //function of stop
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
}
