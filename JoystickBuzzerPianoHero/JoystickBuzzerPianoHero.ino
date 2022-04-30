#include "pitches.h"
const int VRx = A0;
const int VRy = A1;
const int SW = 2;

long analogInputValX;
long analogInputValY;
int digitalInputVal;

const int ledgreen = 9;
const int ledyellow = 10;
const int ledred = 13;

int melodyc[] = {
  NOTE_C4
};
int melodycs[] = {
  NOTE_CS4
};
int melodyd[] = {
  NOTE_D4
};
int melodyds[] = {
  NOTE_DS4
};
int melodye[] = {
  NOTE_E4
};
int melodyf[] = {
  NOTE_F4
};
int melodyfs[] = {
  NOTE_FS4
};
int melodyg[] = {
  NOTE_G4
};
int melodygs[] = {
  NOTE_GS4
};
int melodya[] = {
  NOTE_A4
};
int melodyas[] = {
  NOTE_AS4
};
int melodyb[] = {
  NOTE_B4
};
int noteDurations[] = {
  2
};

void setup() {
    pinMode(VRx, INPUT); 
    pinMode(VRy, INPUT);
    pinMode(SW, INPUT);
    digitalWrite(SW, HIGH);
    pinMode(ledgreen, OUTPUT); 
    pinMode(ledyellow, OUTPUT); 
    pinMode(ledgreen, OUTPUT);
    Serial.begin (9600); 
    Serial.println("Arduino Hero");
    Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
    int position_x = analogRead(VRx);
    int position_y = analogRead(VRy);
    int switch_status = digitalRead(SW);

    Serial.print("Switch:  ");
    Serial.print(digitalRead(SW));
    Serial.print("\n");
    Serial.print("X-axis: ");
    Serial.print(analogRead(VRx));
    Serial.print("\n");
    Serial.print("Y-axis: ");
    Serial.println(analogRead(VRy));
    Serial.print("\n\n");
    delay(500);

     
     if (position_x <= 750 && position_x >= 520) {
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodyd[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, HIGH);
     }
     if (position_x > 750) {
      int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodyds[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, LOW);
     }
     if (position_x <= 500 && position_x >= 300) {
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodyfs[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, LOW);
     }
     if (position_x < 300) {
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodyg[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, LOW);
     }
     if (position_y >= 520 && position_y <= 750){
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodygs[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, LOW);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, HIGH);   
     }
    if (position_y > 750) {
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodya[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, LOW);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, HIGH); 
    }
    if (position_y <= 500 && position_y >= 300){
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodye[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, LOW);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, HIGH);
    }
     if (position_y < 300) {
        int size = sizeof(noteDurations) / sizeof(int);
        for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melodyf[thisNote], noteDuration); 
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); 
        }
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, HIGH);
     }

}
