// The logic can be applied to work on Bluetooth funduino joystick
// Can be upgraded to 4WD
// the the tires movement is reversed, instead of changing the code
// exchange the wire (black and red) from DC motor to L293D terminal port
#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorfrontright(4);
AF_DCMotor motorfrontleft(2);

void setup() 
{
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  motorfrontright.setSpeed(200);
  motorfrontleft.setSpeed(200);
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
  Serial.println("L293D with F18G Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  Serial.println("type a: turn left");
  Serial.println("type d: turn right");
  Serial.println("type w: move forward");
  Serial.println("type s: move backward");
}

void loop() 
{ 
  if(Serial.available() > 0)
    {
      char data= Serial.read();
      switch(data)
      {
        case 'w': 
        motorfrontright.run(FORWARD);
        motorfrontleft.run(FORWARD);
        break;
        case 'a': 
        motorfrontright.run(RELEASE);
        motorfrontleft.run(FORWARD);
        break;
        case 's': 
        motorfrontright.run(BACKWARD);
        motorfrontleft.run(BACKWARD);
        break;
        case 'd': 
        motorfrontright.run(FORWARD);
        motorfrontleft.run(RELEASE);
        default : break;
      }
      Serial.println(data);
    }  
    delay(2000);
}
