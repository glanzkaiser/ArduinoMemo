// GND <-> Resistor from LED
// GND <-> Negative pin of Buzzer
// D8 <-> Positive Pin of Buzzer
// Resistor 110 Ohm <-> Shorter leg of LED (Negative leg)
// D10 <-> Longer leg of LED (Positive leg)

#include <SoftwareSerial.h>
#include "pitches.h"
int LED = 10;
int state;
int flag=0; 
//For repeating melody: Always
int melodyalways[] = {
  NOTE_B4, NOTE_D5, NOTE_D5,
  NOTE_B4, NOTE_D5,
  NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_C5, NOTE_B4, NOTE_G4,
  NOTE_G4, NOTE_E4, NOTE_G4,
  NOTE_C5, NOTE_C5, NOTE_B4,
  NOTE_G4, NOTE_E4,
  NOTE_E4, NOTE_D4,
  NOTE_E4, NOTE_F4,
};

int notealwaysDurations[] = {
  3, 4, 3,
  4, 2,
  2,
  2, 3, 4,
  4, 4, 5,
  4, 4, 4,
  4, 4, 2,
  4, 1,
  4, 4, 
  1, 2
};


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
  Serial.println("HC05 Bluetooth Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  Serial.println("type a: turn on the LED");
  Serial.println("type b: turn off the LED");
  Serial.println("type c: to play a beautiful song: Always by Atlantic Starr");
}  

void loop() 
{ 
  if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
  if (state == 'a') {
        digitalWrite(LED, HIGH);
        if(flag == 0){
          Serial.println("LED: on");
          flag=1;
        }
    }
  else if (state == 'b') {
        digitalWrite(LED, LOW);
        if(flag == 0){
          Serial.println("LED: off");
          flag=1;
        }
    }  
   else if (state == 'c') {
        int size = sizeof(notealwaysDurations) / sizeof(int);

        for (int thisNote = 0; thisNote < size; thisNote++) {
        int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
        tone(8, melodyalways[thisNote], notealwaysDuration);
    
        int pauseBetweenNotes = notealwaysDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
        }
        if(flag == 0){
          Serial.println("Always -the Atlantic Starr");
          flag=1;
        }
    }  
    delay(3000);
}
