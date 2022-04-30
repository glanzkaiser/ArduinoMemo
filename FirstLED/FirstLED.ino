// Initialize pin to control LED, the pin 8
const int pinLED = 8;

void setup() {
  // set pin 8 as OUTPUT
pinMode(pinLED,OUTPUT);

}

void loop() {
digitalWrite(pinLED, HIGH);
delay(1000);
digitalWrite(pinLED, LOW);
delay(1000);
}
