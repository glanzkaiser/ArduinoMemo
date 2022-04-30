#define MIC_IN A0
#include "pitches.h"

const int ledred = 2;
const int buzzer = 8;
const int sampleWindow = 50;
unsigned int sample;
int currentstate;

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

void setup() {
   Serial.begin(9600);
   Serial.println("MAX4466 Electret Microphone-LED-Buzzer");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
  unsigned long startMillis= millis();
  unsigned int peakTopeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)
    { 
      if (sample > signalMax)
      {
        signalMax = sample; 
      }
      else if (sample < signalMin)
      {
        signalMin = sample;
      }
    }
  }
  peakTopeak = signalMax - signalMin;
  double volts = (peakTopeak * 5.00) / 1024;

  Serial.print("Voltage: "), Serial.println(volts);

  if (volts > 3) 
  {
    if (currentstate == 0) 
    {

      digitalWrite(ledred, HIGH);
      
      // For a tone only sound as alarm (optional)
      //tone(buzzer, 659, 1000);
      
      int size = sizeof(notevalhallaDurations) / sizeof(int);
      
      //Play Valhalla from Valkyrie Profile 
      for (int thisNote = 0; thisNote < size; thisNote++) {
  
      int notevalhallaDuration = 1000 / notevalhallaDurations[thisNote];
      tone(8, melodyvalhalla[thisNote], notevalhallaDuration);
  
      int pauseBetweenNotes = notevalhallaDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8);
       }
      
      currentstate = 1;
      
    }
    else 
    {
      digitalWrite(ledred, LOW);
      currentstate = 0;
    }
  }
  delay(1000);
}
