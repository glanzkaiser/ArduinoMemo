#define echoPin 2 
#define trigPin 3
#define freyaled 9
#define yellowled 10
#define redled 11

long duration; 
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redled, OUTPUT); 
  pinMode(yellowled, OUTPUT); 
  pinMode(freyaled, OUTPUT);
  Serial.begin (9600); 
  Serial.println("Ultrasonic Sensor HC-SR04 Traffic Light");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; 
    
    if (distance < 10)
    { 
      digitalWrite(redled,HIGH);
      digitalWrite(yellowled,LOW);
      digitalWrite(freyaled,LOW);
    }
    else if (distance >= 10 && distance < 25)
    { 
      digitalWrite(redled,LOW);
      digitalWrite(yellowled,HIGH);
      digitalWrite(freyaled,LOW);
    }
    else {
      digitalWrite(redled,LOW);
      digitalWrite(yellowled,LOW);
      digitalWrite(freyaled,HIGH);
    }
    Serial.print(distance);
    Serial.println(" cm");
    
    delay(3300); 
}
