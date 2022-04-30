// When someone enter a room an LED will be turned on
// and a song will be played
#include "pitches.h"

int ledPin = 9; 
int pirPin = 2;                
int pirStat = 0;           
int melodyalways[] = {
  NOTE_B5, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_B5, 
  NOTE_E6, NOTE_C6, NOTE_C6, NOTE_E6,
  NOTE_B5, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_B5, 
  NOTE_E6, NOTE_C6, NOTE_C6, NOTE_E6,
  NOTE_B5, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_B5, 
  NOTE_E6, NOTE_C6, NOTE_C6, NOTE_E6,
  NOTE_A6, NOTE_G6, NOTE_F6, NOTE_E6,
  NOTE_DS6,
  NOTE_E6,
};

int notealwaysDurations[] = {
  5, 5, 5, 5, 3,
  5, 5, 5, 5,
  5, 5, 5, 5, 3, 
  5, 5, 5, 5,
  5, 5, 5, 5, 3, 
  5, 5, 5, 5,
  5, 5, 6, 6,
  2, 
  1
};
 
void setup() {
  pinMode(ledPin, OUTPUT);     
  pinMode(pirPin, INPUT);     
 
  Serial.begin(9600);
  Serial.println("Motion Detection Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");

}

void loop() {
  pirStat = digitalRead(pirPin); 
   // if motion detected turn LED on
  if (pirStat == HIGH) {    
    digitalWrite(ledPin, HIGH);  
    Serial.println("A motion detected");
    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {
    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8);
    delay(1000);
    }
  } 
  else {
    digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
   
  }

}
