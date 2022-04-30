
#include <Servo.h> 
int servoPin = 6; 
Servo ServoFreja; 
int pos = 0;
const int numLED = 3;
const int pinLED[numLED] = {9,10,13};

void setup() { 
   for(int i=0; i<3; i++) {
    pinMode(pinLED[i], OUTPUT);
    }
   Serial.begin(9600);
   Serial.println("MicroServo LEDs Test");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
   // We need to attach the servo to the used pin number 
   ServoFreja.attach(servoPin); 
}
void loop(){ 
    for (pos = 0; pos <= 180; pos += 1) { 
    ServoFreja.write(pos);             
    delay(23);                       
    // waits 23ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    ServoFreja.write(pos); 
    Serial.println(pos);             
    delay(45);                       
    for(int i=0; i<3; i++){
    digitalWrite(pinLED[i], HIGH);
    delay(50);
    }
    for(int i=0; i<3; i++){
    digitalWrite(pinLED[i], LOW);
    delay(23);
    }
  }
}
