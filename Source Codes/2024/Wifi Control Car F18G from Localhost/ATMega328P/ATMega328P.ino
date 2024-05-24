// Upload with SW 3 and 4 ON

#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorfrontright(4);
AF_DCMotor motorfrontleft(1);
AF_DCMotor motorbackright(3);
AF_DCMotor motorbackleft(2);

void setup(){
  Serial.begin(9600);    
  motorfrontright.setSpeed(200);
  motorfrontleft.setSpeed(200);
  motorbackright.setSpeed(200);
  motorbackleft.setSpeed(200);
  motorfrontright.run(RELEASE);
  motorfrontleft.run(RELEASE);
  motorbackright.run(RELEASE);
  motorbackleft.run(RELEASE);

  Serial.println("L293D with F18G Test");
  Serial.println("with Arduino UNO R3 WiFi by Glanz and Freya");
}

void loop(){
  if (Serial.available()>0) {
      int reading = Serial.read();
      if (reading == 1) {
          motorfrontright.setSpeed(150);
          motorfrontleft.setSpeed(150);
          motorfrontright.run(FORWARD);
          motorfrontleft.run(FORWARD);
          motorbackright.run(FORWARD);
          motorbackleft.run(FORWARD);
        }
      else if (reading == 2) {
          motorfrontright.setSpeed(250);
          motorfrontleft.setSpeed(250);
          motorfrontright.run(FORWARD);
          motorfrontleft.run(FORWARD);
          motorbackright.run(FORWARD);
          motorbackleft.run(FORWARD);
        }
      else if (reading == 3) {
          motorfrontright.run(FORWARD);
          motorfrontleft.run(RELEASE); 
          motorbackright.run(FORWARD);
          motorbackleft.run(FORWARD);
        }
      else if (reading == 4) {
          motorfrontright.run(RELEASE);
          motorfrontleft.run(FORWARD); 
          motorbackright.run(FORWARD);
          motorbackleft.run(FORWARD);
        }  
      else if (reading == 5) {
          motorfrontright.run(BACKWARD);
          motorfrontleft.run(BACKWARD); 
          motorbackright.run(BACKWARD);
          motorbackleft.run(BACKWARD); 
        }
      else if (reading == 6) {
          motorfrontright.run(RELEASE);
          motorfrontleft.run(RELEASE);
          motorbackright.run(RELEASE);
          motorbackleft.run(RELEASE);
        }
    }
  
}
