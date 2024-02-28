// The logic can be applied to work on Bluetooth funduino joystick
// Can be upgraded to TRANSFORM INTO QUADCOPTER with stepper
// the the tires movement is reversed, instead of changing the code
// exchange the wire (black and red) from DC motor to L293D terminal port
// https://randomnerdtutorials.com/arduino-control-dc-motor-via-bluetooth/

#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorfrontright(4);
AF_DCMotor motorfrontleft(1);
AF_DCMotor motorbackright(3);
AF_DCMotor motorbackleft(2);

int state;
int flag=0; 

void setup() 
{
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  Serial.println("F18G");
  Serial.println("with Bluino feat L293D by Glanz and Freya");
}

void loop() 
{ 
  if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
  if (state == '0') {
        motorfrontright.run(RELEASE);
        motorfrontleft.run(RELEASE);
        motorbackright.run(RELEASE);
        motorbackleft.run(RELEASE);
        if(flag == 0){
          Serial.println("Motor: off");
          flag=1;
        }
    } 
  // if the state is 'w' F18G will move forward
  else if (state == 'w') {
        motorfrontright.setSpeed(255);  
        motorfrontleft.setSpeed(255); 
        motorbackright.setSpeed(255);  
        motorbackleft.setSpeed(255);
        motorfrontright.run(FORWARD);
        motorfrontleft.run(FORWARD);
        motorbackright.run(FORWARD);
        motorbackleft.run(FORWARD);
        if(flag == 0){
          Serial.println("Motor: forward");
          flag=1;
        }
    } 
  // if the state is 'a' F18G will turn left
  else if (state == 'a') {
        motorfrontright.setSpeed(255);  
        motorfrontleft.setSpeed(255); 
        motorbackright.setSpeed(255);  
        motorbackleft.setSpeed(255);
        motorfrontright.run(FORWARD);
        motorfrontleft.run(RELEASE);
        motorbackright.run(FORWARD);
        motorbackleft.run(FORWARD);
        if(flag == 0){
          Serial.println("Motor: turn left");
          flag=1;
        }
    }
  // if the state is 'd' F18G will turn right
  else if (state == 'd') {
        motorfrontright.setSpeed(255);  
        motorfrontleft.setSpeed(255); 
        motorbackright.setSpeed(255);  
        motorbackleft.setSpeed(255);
        motorfrontright.run(RELEASE);
        motorfrontleft.run(FORWARD);
        motorbackright.run(FORWARD);
        motorbackleft.run(FORWARD);
        if(flag == 0){
          Serial.println("Motor: turn right");
          flag=1;
        }
    }
  // if the state is 's' F18G will turn left
  else if (state == 's') {
        motorfrontright.setSpeed(255);  
        motorfrontleft.setSpeed(255); 
        motorbackright.setSpeed(255);  
        motorbackleft.setSpeed(255);
        motorfrontright.run(BACKWARD);
        motorfrontleft.run(BACKWARD);
        motorbackright.run(BACKWARD);
        motorbackleft.run(BACKWARD);
        if(flag == 0){
          Serial.println("Motor: backward");
          flag=1;
        }
    }  
}
