// defines pins numbers
//#define echoPin 2
//#define trigPin 3
const int trigPin = 3;
const int echoPin = 2;

long duration; 
int distance, inches;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
    // Clears the trigPin condition
    digitalWrite(trigPin,LOW);
    delayMicroseconds(200);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
     // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; 
    // Speed of sound wave divided by 2 (go and back)
  
    inches = distance * 2.54;

     // Displays the distance on the Serial Monitor
    Serial.print("Distance in cm: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    Serial.print("Distance in inch: ");
    Serial.println(inches);
    Serial.println(" inch");
    delay(3000);
}
