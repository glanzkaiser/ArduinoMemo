
#include <Servo.h> 
#include "pitches.h"

int servoPin = 6; 
Servo ServoFreja; 
int pos = 0;
const int numLED = 3;
const int pinLED[numLED] = {9,10,13};

int melodysuikoden[] = {
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
int notesuikodenDurations[] = {
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

int melodyvalhalla[] = {
  NOTE_A2, NOTE_B2, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_C3,
  NOTE_D3, NOTE_G2, NOTE_G3, NOTE_D3,
  NOTE_CS3, NOTE_D2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_C3,
  NOTE_F3, NOTE_E3, NOTE_D3, NOTE_A2, NOTE_F2, NOTE_D2,
  NOTE_F3,
  NOTE_E3, NOTE_B2, NOTE_GS2,
  NOTE_CS3, NOTE_D3, NOTE_E3,
  NOTE_F3, NOTE_E3, NOTE_D3,
  NOTE_D3, NOTE_CS3,
  NOTE_D3, NOTE_E3,
};
int notevalhallaDurations[] = {
  8, 8, 8, 8, 8, 8,
  8, 8, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  2,
  6, 6, 6,
  8, 8, 2,
  6, 6, 6,
  2, 2,
  2, 2
};

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
   for(int i=0; i<3; i++) {
    pinMode(pinLED[i], OUTPUT);
    }
   Serial.begin(9600);
   Serial.println("MicroServo-LEDs-Buzzer Test");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
   // We need to attach the servo to the used pin number 
   ServoFreja.attach(servoPin); 
}
void loop(){ 
    for (pos = 0; pos <= 180; pos += 1) { 
    ServoFreja.write(pos);             
    delay(23);                       
    // waits 23ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    ServoFreja.write(pos); 
    Serial.println(pos);             
    delay(45);       
  }
    //Play the first song Valhalla from Valkyrie Profile
    digitalWrite(pinLED[0], HIGH);
    delay(500);
    int size = sizeof(notevalhallaDurations) / sizeof(int);
    
    for (int thisNote = 0; thisNote < size; thisNote++) {

    int notevalhallaDuration = 1000 / notevalhallaDurations[thisNote];
    tone(8, melodyvalhalla[thisNote], notevalhallaDuration);

    int pauseBetweenNotes = notevalhallaDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
      }
    digitalWrite(pinLED[0], LOW);
    delay(550);

    // Play the second song Always by Atlantic Starr
    digitalWrite(pinLED[1], HIGH);
    delay(500);
    int size2 = sizeof(notealwaysDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size2; thisNote++) {

    int notealwaysDuration = 1000 / notealwaysDurations[thisNote];
    tone(8, melodyalways[thisNote], notealwaysDuration);

    int pauseBetweenNotes = notealwaysDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
      }
    digitalWrite(pinLED[1], LOW);
    delay(550);

    // Play the third song from Suikoden II  
    digitalWrite(pinLED[2], HIGH);
    delay(500);
    int size3 = sizeof(notesuikodenDurations) / sizeof(int);

    for (int thisNote = 0; thisNote < size3; thisNote++) {

    int notesuikodenDuration = 1000 / notesuikodenDurations[thisNote];
    tone(8, melodysuikoden[thisNote], notesuikodenDuration);

    int pauseBetweenNotes = notesuikodenDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
      }
    digitalWrite(pinLED[2], LOW);
    delay(550);

}
