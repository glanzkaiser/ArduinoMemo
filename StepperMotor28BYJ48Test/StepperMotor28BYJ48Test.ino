//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
  // Rotate CW slowly at 10 RPM
  myStepper.setSpeed(10);
  myStepper.step(2038);
  delay(1000);
  
  // Rotate CCW quickly at 15 RPM
  myStepper.setSpeed(15);
  myStepper.step(-2038);
  delay(1000);

  myStepper.setSpeed(20);
  myStepper.step(-4038);
  delay(1000);
}
