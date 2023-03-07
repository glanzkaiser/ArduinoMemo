#include "pitches.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 
byte Heart[8] = {
0b00000,
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000
};
byte Southwest[8] =
{
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00001,
0b00010
};

byte Northeast[8] =
{
0b11100,
0b01100,
0b10100,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

// notes in the melody:
int melody[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};

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
   lcd.init();
   lcd.backlight();
   lcd.createChar(0, Heart);
   lcd.createChar(1, Southwest);
   lcd.createChar(2, Northeast);
   lcd.clear();
   lcd.print("Glanz");
   
  Serial.begin (9600); 
  Serial.println("Piezo Buzzer Always by Atlantic Starr for my Wife");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  // iterate over the notes of the melody:

  
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);
    
  }
}

void loop() {
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(0);
    lcd.setCursor(3, 1);
    lcd.write(2);
    lcd.setCursor(0, 2);
    lcd.print("Freya");
   
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
