
int FirstShotX, FirstShotY;

void setup() {
  for(int i=2; i<9; i++)
  {
  pinMode(i, INPUT);
  digitalWrite(i, 1);
  }
  Serial.begin(9600);
  Serial.println("Funduino Joystick Shield Test");
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
      case 2: Serial.println("--------> Button A"); break;
      case 3: Serial.println("--------> Button B"); break;
      case 4: Serial.println("--------> Button C"); break;
      case 5: Serial.println("--------> Button D"); break;
      case 6: Serial.println("--------> Button E"); break;
      case 7: Serial.println("--------> Button F"); break;
      case 8: Serial.println("--------> Button KEY"); break;
      default: break;
    }
      flag=0;
    }
    
    int sensorValueX = analogRead(A0);
    int sensorValueY = analogRead(A1);
      Serial.print("Position of X = ");
      Serial.println(sensorValueX);
      Serial.print("Position of Y = ");
      Serial.println(sensorValueY);
      Serial.print("+------------------* ");
      Serial.print('\n');
    delay(1500);
}
