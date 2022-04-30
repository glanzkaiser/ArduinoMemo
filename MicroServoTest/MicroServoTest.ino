// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 6; 
// Create a servo object 
Servo Servo1; 

void setup() { 
   Serial.begin(9600);
   Serial.println("MicroServo Test");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
   // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(60); 
   delay(300);
   Servo1.write(90); 
   delay(300); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000); 
}
