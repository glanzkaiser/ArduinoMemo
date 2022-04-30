
int FirstShotX, FirstShotY;

const int ledgreen = 9;
const int ledyellow = 10;
const int ledred = 13;
const int buzzer = 11;

void setup() {
  for(int i=2; i<9; i++)
  {
  pinMode(i, INPUT);
  digitalWrite(i, 1);
  }
  pinMode(ledgreen, OUTPUT); 
  pinMode(ledyellow, OUTPUT); 
  pinMode(ledred, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Arduino Melody Hero");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
  FirstShotX = 0;
  FirstShotY = 0;
}

void loop() {
  int i, someInt, flag = 0;
  for(i=2; i<9; i++)
  {
    someInt = digitalRead(i);
    if(someInt == 0)
    {
      flag =1;
      break;
    }
  }
    if(flag == 1)
    {
      switch(i)
    {
      case 2: Serial.println("--------> Button A"); 
              Serial.print("A4 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, HIGH);
              digitalWrite (ledyellow, LOW);
              digitalWrite (ledred, HIGH);
              tone(buzzer, 440, 1000);
      break;
      case 3: Serial.println("--------> Button B"); 
              Serial.print("B4 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, LOW);
              digitalWrite (ledyellow, HIGH);
              digitalWrite (ledred, HIGH);
              tone(buzzer, 494, 1000);
      break;
      case 4: Serial.println("--------> Button C"); 
              Serial.print("C5 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, HIGH);
              digitalWrite (ledyellow, LOW);
              digitalWrite (ledred, LOW);
              tone(buzzer, 523, 1000);
      break;
      case 5: Serial.println("--------> Button D"); 
              Serial.print("D5 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, LOW);
              digitalWrite (ledyellow, HIGH);
              digitalWrite (ledred, LOW);
              tone(buzzer, 587, 1000);
      break;
      case 6: Serial.println("--------> Button E"); 
              Serial.print("E5 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, HIGH);
              digitalWrite (ledyellow, HIGH);
              digitalWrite (ledred, LOW);
              tone(buzzer, 659, 1000);
      break;
      case 7: Serial.println("--------> Button F"); 
              Serial.print("F5 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, LOW);
              digitalWrite (ledyellow, HIGH);
              digitalWrite (ledred, LOW);
              tone(buzzer, 698, 1000);
      break;
      case 8: Serial.println("--------> Button KEY"); 
              Serial.print("G5 Notes is played");
              Serial.print('\n');
              digitalWrite (ledgreen, HIGH);
              digitalWrite (ledyellow, HIGH);
              digitalWrite (ledred, HIGH);
              tone(buzzer, 784, 1000);
      break;
      default: break;
    }
      flag=0;
    }

    int toneToPlay = 0;
    int sensorValueX = analogRead(A0);
    int sensorValueY = analogRead(A1);
      
      if (sensorValueX >= 421 && sensorValueY >= 330) {
        tone(buzzer, 262, 1000); 
        noTone(buzzer);
        Serial.print("C4 Notes is played ");
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, HIGH);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
      if (sensorValueX <= 420 && sensorValueX >= 331 && sensorValueY >= 330) {
        tone(buzzer, 277, 1000);
        Serial.print("CS4 Notes is played");
        Serial.print('\n');
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, HIGH);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
      if (sensorValueX <= 330 && sensorValueX >= 200 && sensorValueY >= 330) {
        tone(buzzer, 294, 1000); 
        noTone(buzzer);
        Serial.print("D4 Notes is played ");
        Serial.print('\n');
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, LOW);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
       if (sensorValueX <= 199 && sensorValueY >= 330) {
        tone(buzzer, 311, 1000);
        noTone(buzzer);  
        Serial.print("DS4 Notes is played ");
        Serial.print('\n');
        digitalWrite (ledgreen, LOW);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, LOW);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }

      if (sensorValueX >= 421 && sensorValueY <= 329) {
        tone(buzzer, 330, 1000); 
        noTone(buzzer);
        Serial.print("E4 Notes is played ");
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, HIGH);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
      if (sensorValueX <= 420 && sensorValueX >= 331 && sensorValueY <= 329) {
        tone(buzzer, 349, 1000);
        noTone(buzzer);
        Serial.print("F4 Notes is played");
        Serial.print('\n');
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, HIGH);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
      if (sensorValueX <= 330 && sensorValueX >= 200 && sensorValueY <= 329) {
        tone(buzzer, 370, 1000); 
        noTone(buzzer);
        Serial.print("FS4 Notes is played ");
        Serial.print('\n');
        digitalWrite (ledgreen, HIGH);
        digitalWrite (ledyellow, LOW);
        digitalWrite (ledred, LOW);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
       if (sensorValueX <= 199 && sensorValueY <= 329) {
        tone(buzzer, 392, 1000);  
        noTone(buzzer);
        Serial.print("G4 Notes is played ");
        Serial.print('\n');
        digitalWrite (ledgreen, LOW);
        digitalWrite (ledyellow, HIGH);
        digitalWrite (ledred, LOW);
        Serial.print("Position of X = ");
        Serial.println(sensorValueX);
        Serial.print("Position of Y = ");
        Serial.println(sensorValueY);
        Serial.print("+------------------* ");
        Serial.print('\n');
        }
    delay(1000);
}
