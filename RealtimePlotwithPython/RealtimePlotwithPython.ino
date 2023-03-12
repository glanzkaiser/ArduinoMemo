void setup() {
  Serial.begin(9600);

}

void loop() {
  for(int i = 1; i<=10; i++){
    Serial.println(1);
  }
  for(int j = 1; j<=10; j++){
    Serial.println(0);
  }
}
