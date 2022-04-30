#include "pitches.h"
const int buzzer1 = 3;
const int buzzer2 = 4;
const int buzzer3 = 5;
const int buzzer4 = 7;
int buttonPin1 = 8;
int buttonPin2 = 9;
int buttonPin3 = 10;
int buttonPin4 = 11;
int buttonPin5 = 2;
int buttonPin6 = 13;
int buttonPin7 = 12;
int buttonPin8 = 1;

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
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  pinMode(buzzer4, OUTPUT);
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin3,INPUT);
  pinMode(buttonPin4,INPUT);
  pinMode(buttonPin5,INPUT);
  pinMode(buttonPin6,INPUT);
}

void loop() {
  if (digitalRead(buttonPin1)==LOW){
    tone(buzzer1, 523, 300); // Note C5, Send 1KHz sound signal.
    noTone(buzzer1);     
  }
  if (digitalRead(buttonPin2)==LOW){
    tone(buzzer2, 587, 30);  
    noTone(buzzer2);
  }
  if (digitalRead(buttonPin3)==LOW){
    tone(buzzer3, 659, 300); 
    noTone(buzzer3);    
  } 
  if (digitalRead(buttonPin4)==LOW){
    tone(buzzer1, 698, 300); 
    noTone(buzzer1);    
  } 
  if (digitalRead(buttonPin5)==LOW){
    tone(buzzer2, 784, 300); 
    noTone(buzzer2);    
  } 
  if (digitalRead(buttonPin6)==LOW){
    tone(buzzer3, 880, 300); 
    noTone(buzzer3);    
  } 
  if (digitalRead(buttonPin7)==LOW){
    tone(buzzer3, 988, 300); 
    noTone(buzzer3);    
  } 
  if (digitalRead(buttonPin8)==LOW){
    // Repeat the melody of Always
    int size = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size; thisNote++) {

    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(buzzer4, melodyalways[thisNote], notealwaysDuration);
    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer4);    
    }
  } 
  else
  {
    noTone(buzzer1);
    noTone(buzzer2);
    noTone(buzzer3);
    noTone(buzzer4);
  }

  
  }
