// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define MotorInterfaceType 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, 8, 10, 9, 11);

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(1000.0);
  myStepper.setAcceleration(50.0);
  myStepper.setSpeed(200);
  myStepper.moveTo(2038);
}

void loop() {
  // Change direction once the motor reaches target position
  if (myStepper.distanceToGo() == 0) 
    myStepper.moveTo(-myStepper.currentPosition());

  // Move the motor one step
  myStepper.run();
}
