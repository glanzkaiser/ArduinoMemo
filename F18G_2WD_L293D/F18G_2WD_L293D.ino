#include <AFMotor.h>

AF_DCMotor motorfrontright(4);
AF_DCMotor motorfrontleft(2);

void setup() 
{
  //Set initial speed of the motor & stop
  motorfrontright.setSpeed(200);
  motorfrontleft.setSpeed(200);
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
}

void loop() 
{
  uint8_t i;

  // Turn on motor
  motorfrontright.run(FORWARD);
  motorfrontleft.run(FORWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    delay(10);
  }
  
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    delay(10);
  }

  // Now change motor direction
  motorfrontright.run(BACKWARD);
  motorfrontleft.run(BACKWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    delay(10);
  }

  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motorfrontright.setSpeed(i);  
    motorfrontleft.setSpeed(i);  
    delay(10);
  }

  // Now turn off motor
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
  delay(1000);
}
