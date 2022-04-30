const int sensor=A1; // Assigning analog pin A1 to variable 'sensor'
float tempc; //variable to store temperature in degree Celsius
float tempf; //variable to store temperature in Fahreinheit
float vout; //temporary variable to hold sensor reading 

void setup() {
  pinMode(sensor,INPUT); // Configuring sensor pin as input 
  Serial.begin(9600);
  Serial.println("LM35 Temperature Measurement");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}

void loop() {
  vout=analogRead(sensor); //Reading the value from sensor
  
  vout=(vout*500)/1023;
  tempc=vout; // Storing value in Degree Celsius
  tempf=(vout*1.8)+32; // Converting to Fahrenheit
  
  Serial.print("in Degree Celcius = ");
  Serial.print(tempc);
  Serial.print(" ");
  Serial.print("\t");
  
  Serial.print("in Fahrenheit = ");
  Serial.print(tempf);
  Serial.print("\t");
  Serial.println();
  
  delay(3300); 
}
