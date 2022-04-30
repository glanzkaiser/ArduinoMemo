const int pinLED1 = 8;
const int pinLED2 = 9;
const int pinLED3 = 10;
const int pinLED4 = 11;

void setup() {
 pinMode(pinLED1, OUTPUT);
 pinMode(pinLED2, OUTPUT);
 pinMode(pinLED3, OUTPUT);
 pinMode(pinLED4, OUTPUT);

}

void loop() {
  for(int i=0; i<5; i++){
  if(i==1){

  digitalWrite(pinLED1, HIGH);
  digitalWrite(pinLED2, LOW);
  digitalWrite(pinLED3, LOW);
  digitalWrite(pinLED4, LOW);
  }else if(i==2){

  digitalWrite(pinLED1, HIGH);
  digitalWrite(pinLED2, HIGH);
  digitalWrite(pinLED3, LOW);
  digitalWrite(pinLED4, LOW);
  }else if(i==3){

  digitalWrite(pinLED1, HIGH);
  digitalWrite(pinLED2, HIGH);
  digitalWrite(pinLED3, HIGH);
  digitalWrite(pinLED4, LOW);
  }else if(i==4){
   
  digitalWrite(pinLED1, HIGH);
  digitalWrite(pinLED2, HIGH);
  digitalWrite(pinLED3, HIGH);
  digitalWrite(pinLED4, HIGH);
  }else{
  // Turn off all LEDs
  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED2, LOW);
  digitalWrite(pinLED3, LOW);
  digitalWrite(pinLED4, LOW);
  }
  // delay for 1.882 seconds
  delay(1882);
  }
}
