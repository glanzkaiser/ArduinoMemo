// The logic can be applied to work on Bluetooth funduino joystick
// Can be upgraded to TRANSFORM INTO QUADCOPTER with stepper
// the the tires movement is reversed, instead of changing the code
// exchange the wire (black and red) from DC motor to L293D terminal port
#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorfrontright(4);
AF_DCMotor motorfrontleft(1);
AF_DCMotor motorbackright(3);
AF_DCMotor motorbackleft(2);

void setup() 
{
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  motorfrontright.setSpeed(200);
  motorfrontleft.setSpeed(200);
  motorbackright.setSpeed(200);
  motorbackleft.setSpeed(200);
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
  motorbackright.run(RELEASE);
  motorbackleft.run(RELEASE);
  Serial.println("L293D with F18G Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() 
{ 
  uint8_t i;
  // Drive Forward
  motorfrontright.run(FORWARD);
  motorfrontleft.run(FORWARD);
  motorbackright.run(FORWARD);
  motorbackleft.run(FORWARD);
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i); 
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i);   
    delay(10);
  }
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i); 
    delay(10);
  }
  // Now turn left forward  
  motorfrontright.run(RELEASE);
  motorfrontleft.run(FORWARD);
  motorbackright.run(FORWARD);
  motorbackleft.run(FORWARD);
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i); 
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i);   
    delay(10);
  }
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i); 
    delay(10);
  }
  // Now turn right forward  
  motorfrontright.run(FORWARD);
  motorfrontleft.run(RELEASE);
  motorbackright.run(FORWARD);
  motorbackleft.run(FORWARD);
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i); 
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i);   
    delay(10);
  }
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i); 
    delay(10);
  }
  // Now change drive the motor backward 
  motorfrontright.run(BACKWARD);
  motorfrontleft.run(BACKWARD);
  motorbackright.run(BACKWARD);
  motorbackleft.run(BACKWARD);
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i); 
    delay(10);
  }

  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i); 
    motorbackright.setSpeed(i);  
    motorbackleft.setSpeed(i);  
    delay(10);
  }

  // Now turn off motor
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
  motorbackright.run(RELEASE);
  motorbackleft.run(RELEASE);
  delay(1000);
}
