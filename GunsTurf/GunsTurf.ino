#include <math.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <Servo.h>
#include <Pixy2I2C.h>

//X is pitch, Y is yaw

const int pins[] = {6,7,8,5,4,12}; //MX STEP, DIR, EN, MY STEP, DIR, EN
const int limit_switch = 26, laser_pin = 11, spool_pin = 10, servo_pin = 13, distance_trig = 29, distance_echo = 30;
double velocity = 21.336;
double velocity_squared = 455.225;
float current_angle = 0.0;
float hyp_distance; //distance from gun to target in meters

#define X_MID 164
#define Y_MID 150
#define DEADZONE 15

#define G 9.8
#define STP_PER_DEG_YAW 3.333
#define STP_PER_DEG_PITCH 184859

#define MICROSTEPS 32
#define RPM 120

#define MOTOR_STEPS_Y 200
#define MOTOR_STEPS_X 1036

//17.7777 steps / degree

BasicStepperDriver pitch_stepper(MOTOR_STEPS_X, pins[1], pins[0]);
BasicStepperDriver yaw_stepper(MOTOR_STEPS_X, pins[4], pins[3]);
Servo trigger;
Pixy2I2C pixy;

enum States {
  ACQUIRE,
  POSITION,
  SPOOL,
  FIRE,
  WIND_DOWN,
  RETURN
};

States state = ACQUIRE;

void setup() {
  Serial.begin(115200);
  init_pins();
  delay(1000);
  //home_pitch();
  pixy.init();
  Serial.println("Ready...");
}

void loop() {
  switch(state){
    case ACQUIRE:
      acquire_target();
      state = POSITION;
      digitalWrite(laser_pin,HIGH);
      break;
    case POSITION:
      Serial.println("positioning");
      position_gun();
      state = SPOOL;
      break;
    case SPOOL:
      Serial.println("spooling");
      digitalWrite(spool_pin,HIGH);
      delay(5000);
      state = FIRE;
      break;
    case FIRE:
      fire_gun();
      state = WIND_DOWN;
      break;
    case WIND_DOWN:
      Serial.println("winding down");
      digitalWrite(spool_pin,LOW);
      delay(2000);
      state = RETURN;
      digitalWrite(laser_pin,LOW);
      state = ACQUIRE;
      break;
  }
}

void fire_gun(){
  Serial.println("Firing gun!");
  trigger.write(108);
  delay(400);
  trigger.write(90);
  delay(2000);
}

void position_gun(){
  float x, y;
  hyp_distance = ping();
  hyp_distance /= 100;
  while(!hyp_distance){   
    hyp_distance = ping();
    hyp_distance /= 100;
  }Serial.println(hyp_distance);
  x = cos(current_angle) * hyp_distance;
  y = sin(current_angle) * hyp_distance;
  float target_angle = get_angle(x,y);
  target_angle /= 100;
  Serial.println(target_angle);
  move_pitch(target_angle - current_angle);
  current_angle = target_angle;
}

void acquire_target(){
  int x=0, y=0;
  long steps_taken=0;
  bool lock = false;
  while(!lock){
    pixy.ccc.getBlocks();
    if(pixy.ccc.numBlocks){
      x = pixy.ccc.blocks[0].m_x;
      y = pixy.ccc.blocks[0].m_y;
      Serial.print("Target seen at location X: ");Serial.print(x);Serial.print(", Y: ");Serial.println(y);
      if(x <= (X_MID - DEADZONE)){ //If too far left, move gun left
        move_yaw(1);
      }
      else if(x >= (X_MID + DEADZONE)){
        move_yaw(-1);
      }
      else if(y <= (Y_MID - DEADZONE)){ //too far up, move gun up
        pitch_stepper.move(33152);
        steps_taken += 33152;
      }
      else if(y >= (Y_MID + DEADZONE)){
        pitch_stepper.move(33152);
        steps_taken += 33152;
      }
      else{
        lock = true;
        Serial.print("Target locked at location X: ");Serial.print(x);Serial.print(", Y: ");Serial.println(y);
        Serial.print("Steps taken: ");Serial.println(steps_taken);
      }
    }
    
  }
  current_angle = steps_taken / STP_PER_DEG_PITCH;
  Serial.print("Current angle: ");Serial.println(current_angle);
}

void init_pins(){
  pinMode(pins[2],OUTPUT);
  pinMode(pins[5],OUTPUT);
  pinMode(limit_switch, INPUT_PULLUP);
  pinMode(laser_pin, OUTPUT);
  pinMode(spool_pin, OUTPUT);
  pinMode(distance_echo, INPUT);
  pinMode(distance_trig, OUTPUT);
  digitalWrite(pins[2],LOW);
  digitalWrite(pins[5],LOW);
  digitalWrite(laser_pin,LOW);
  digitalWrite(spool_pin,LOW);
  trigger.attach(servo_pin);
  pitch_stepper.begin(RPM, MICROSTEPS);
  yaw_stepper.begin(5, MICROSTEPS);
  trigger.write(90);
}

void move_yaw(float degrees){
  yaw_stepper.move(degrees*STP_PER_DEG_YAW*32);
}

void move_pitch(float degrees){
  current_angle += degrees;
  pitch_stepper.move(degrees*STP_PER_DEG_PITCH);
}

float get_angle(float distance, float height){
  float i = 2 * height * 455.225;
  float j = G * distance * distance;
  i += j;
  j = 9.8 * i;
  i = sqrt(pow(velocity_squared,2) - j);
  
  return atan((velocity_squared-i) / (G * distance))*(180/PI);
}

float ping(){
  Serial.println("Getting distance...");
  long duration;
  digitalWrite(distance_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(distance_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(distance_trig, LOW);
  duration = pulseIn(distance_echo, HIGH);
  return duration / 2 / 29.1; //distance in meters
}

void home_pitch(){
  Serial.println(digitalRead(limit_switch));
  if(!digitalRead(limit_switch)){ //If switch is active
    pitch_stepper.rotate(720);
  }
  while(digitalRead(limit_switch)){
    //Serial.println(digitalRead(limit_switch));
    pitch_stepper.move(-32);
  }
  pitch_stepper.rotate(2880*2);
}
