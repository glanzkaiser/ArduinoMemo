void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(500);
  Serial.println("AT+NAME=Bluino#01");
  delay(500);
  Serial.println("AT+UART=115200,0,0");
  delay(500);
  Serial.println("AT+POLAR=1,0");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
