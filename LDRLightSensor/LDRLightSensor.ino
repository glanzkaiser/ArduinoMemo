
int ldr=A0;//Set A0(Analog Input) for LDR.
int value=0;
const int pinLED = 9;

void setup() {
Serial.begin(9600);
Serial.println("Lighting a Dark Room");
Serial.println("with Arduino UNO R3 by Glanz and Freya");
pinMode(pinLED,OUTPUT);
}

void loop() {
value=analogRead(ldr);//Reads the Value of LDR(light).
Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
Serial.println(value);
if(value<50)
  {
    Serial.println(" It is dark in here.");
    digitalWrite(pinLED,HIGH);//Makes the LED glow in Dark.
    delay(3300);
  }
  else
  {
    Serial.println(" We do not need LED in this room.");
    digitalWrite(pinLED,LOW);//Turns the LED OFF in Light.
    delay(3300);
  }
}
