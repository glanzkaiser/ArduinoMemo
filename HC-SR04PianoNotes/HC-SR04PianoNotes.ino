
const int greenLED = 9;
const int yellowLED = 10;
const int redLED = 12;

//musical instrument for HC-SR04 (4 pin) Ultrasonic Sensor
void setup() {
  pinMode (2,OUTPUT);//attach pin 2 to vcc
  pinMode (5,OUTPUT);//attach pin 5 to GND
  pinMode(redLED, OUTPUT); 
  pinMode(yellowLED, OUTPUT); 
  pinMode(greenLED, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  Serial.println("Piezo Buzzer and HC-SR04 Piano by Distance Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop()
{
digitalWrite(2, HIGH);
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(3, OUTPUT);// attach pin 3 to Trig
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode (4, INPUT);//attach pin 4 to Echo
  duration = pulseIn(4, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
  delay(230);
  
  int toneToPlay = 0;
  
  if(cm <= 160 && cm > 140)
  {
     toneToPlay = 523; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, LOW);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 140 && cm > 120)
  {
     toneToPlay = 493; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, LOW);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 120 && cm > 100)
  {
     toneToPlay = 440; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, LOW);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 100 && cm > 80)
  {
     toneToPlay = 392; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, LOW);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 80 && cm > 60)
  {
     toneToPlay = 349; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, HIGH);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 60 && cm > 40)
  {
     toneToPlay = 329; 
     digitalWrite(greenLED, HIGH);
     digitalWrite(yellowLED, HIGH);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 40 && cm > 20)
  {
     toneToPlay = 294; 
     digitalWrite(greenLED, LOW);
     digitalWrite(yellowLED, HIGH);
     digitalWrite(redLED, LOW);
  }
  if(cm <= 20)
  {
     toneToPlay = 261; 
     digitalWrite(greenLED, LOW);
     digitalWrite(yellowLED, LOW);
     digitalWrite(redLED, HIGH);
  }
  
  if (toneToPlay == 0)
  {
    noTone(11);
  }
  else
  {
    tone(11, toneToPlay, 200);
    
  }
  
  //if you want the sound to just change based on distance, 
  //but not necessarily have frequencies that correspond 
  //to notes on a piano you can do this instead
  //tone(11, in*10, 200); 
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
