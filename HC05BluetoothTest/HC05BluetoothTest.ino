#include <SoftwareSerial.h>
SoftwareSerial module_bluetooth(0, 1); // pin RX | TX

void setup() {
    Serial.begin(9600); 
    Serial.println("Input command AT:");
    module_bluetooth.begin(38400);

}

void loop() {
  if (module_bluetooth.available())
  Serial.write(module_bluetooth.read()); 
  if (Serial.available())
  module_bluetooth.write(Serial.read());
}
