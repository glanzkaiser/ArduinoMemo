#include "pitches.h"

// Initialize pin to control LED, the pin 3,6,9,12
const int pinLED1 = 3;
const int pinLED2 = 6;
const int pinLED3 = 9;
const int pinLED4 = 12;

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
  Serial.begin(9600);  
  Serial.println("Happy Valentine 2024 Freya");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  
  // set pin 3,6,9,12 as OUTPUT
pinMode(pinLED1,OUTPUT);
pinMode(pinLED2,OUTPUT);
pinMode(pinLED3,OUTPUT);
pinMode(pinLED4,OUTPUT);
}

void loop() {
digitalWrite(pinLED1, HIGH);
delay(1000);
digitalWrite(pinLED1, LOW);
delay(1000);
digitalWrite(pinLED2, HIGH);
delay(1000);
digitalWrite(pinLED2, LOW);
delay(1000);
digitalWrite(pinLED3, HIGH);
delay(1000);
digitalWrite(pinLED3, LOW);
delay(1000);
digitalWrite(pinLED4, HIGH);
delay(1000);
digitalWrite(pinLED4, LOW);
delay(1000);

digitalWrite(pinLED1, HIGH);
digitalWrite(pinLED2, HIGH);
digitalWrite(pinLED3, HIGH);
digitalWrite(pinLED4, HIGH);
delay(8100);

digitalWrite(pinLED1, LOW);
digitalWrite(pinLED2, LOW);
digitalWrite(pinLED3, LOW);
digitalWrite(pinLED4, LOW);

// Repeat the melody of Always
int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }

}
