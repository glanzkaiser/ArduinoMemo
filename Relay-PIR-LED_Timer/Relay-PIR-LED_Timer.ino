#include "Temporizador.h"

// constants won't change. They're used here to set pin numbers:
const int pirPin  =   2;     // the number of the PIR pin
const int relayPin =   5;     // the number of the Relay pin
const int ledPin  =  13;      // the number of the LED pin
const uint32_t alarm = 1200000; // When the PIR is activate the counter restart a new count.
uint8_t  pirState = LOW;

Temporizador count(&activarRelay);

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lamp Management Timer With Relay and PIR"); 
  Serial.println("with Arduino UNO R3 by Glanz and Freya"); 
}

void loop() {
  // read the state of the pushbutton value:
  pirState = digitalRead(pirPin);
  count.loop();
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (pirState == HIGH) {
    // turn LED on:
    Serial.println("Someone is in the room"); 
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, HIGH);
    count.set(alarm);  
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    Serial.println("Turn off the light after the timer off"); 
  }
  delay(1000);
}

void activarRelay(){
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, LOW);  //When the timer is over the light is off
}
