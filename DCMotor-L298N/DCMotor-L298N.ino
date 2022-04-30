const int motor1pin1 = 3;
const int motor1pin2 = 5;
const int motor2pin1 = 6;
const int motor2pin2 = 9;



void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600); 
  Serial.println("DC Motor and L298N Test with RC Car F18G");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  //pinMode(motor3pin1, OUTPUT);
  //pinMode(motor3pin2, OUTPUT);
  //pinMode(motor4pin1, OUTPUT);
  //pinMode(motor4pin2, OUTPUT);

}

void demoOne() {

  //Controlling spin direction of motors:
  //Spin forward
  Serial.println("Forward");
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  delay(2300);
  //Spin Backward
  Serial.println("Reverse");
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  
  delay(2300);

  //Stop
  Serial.println("Brake");
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  
}

void loop()
{
  demoOne();
  delay(1000);
}
