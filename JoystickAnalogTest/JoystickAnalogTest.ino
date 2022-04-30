hint analogInputPinX   = A0;
int analogInputPinY   = A1;
int digitalInputPin  = 2;
int wait = 300; 
long analogInputValX;
long analogInputValY;
long last_analogInputValX;
long last_analogInputValY;
int digitalInputVal;

void setup()
{
  pinMode(analogInputPinX, INPUT);
  pinMode(analogInputPinY, INPUT);
  pinMode(digitalInputPin, INPUT);
  
  Serial.begin(9600);  
  Serial.println("Joystick Analog Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop()
{
  analogInputValX = analogRead(analogInputPinX);
  analogInputValY = analogRead(analogInputPinY);
  digitalInputVal = digitalRead(digitalInputPin);
  if (digitalInputVal != 1)
      {
      Serial.print("Digital is ");
      Serial.print(digitalInputVal);
      Serial.println(" "); 
      }        
  if (digitalInputVal != 0)
      {
      Serial.print("YAY ! Digital is ");
      Serial.print(digitalInputVal);
      Serial.println(" "); 
      }        
  if (analogInputValX != last_analogInputValX)
      {
      Serial.print("Change X to ");
      Serial.print(analogInputValX);    
      Serial.println(" "); 
      last_analogInputValX = analogInputValX;
      }
  if (analogInputValY != last_analogInputValY)
      {
      Serial.print("Change Y to ");
      Serial.print(analogInputValY);    
      Serial.println(" "); 
      last_analogInputValY = analogInputValY;
      }
      delay(1000);
}
