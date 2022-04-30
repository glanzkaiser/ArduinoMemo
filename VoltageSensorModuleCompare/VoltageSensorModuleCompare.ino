#define ANALOG_IN_PIN A0
float adc_voltage = 0.0;
float in_voltage = 0.0;

float R1 = 30000.0;
float R2 = 7500.0; 
float ref_voltage = 5.0;
int adc_value = 0;

int offset =20;// set the correction offset value

void setup() {

  Serial.begin(9600);
  Serial.println("GlanzFreya DC Voltage Test Comparison");
  Serial.println("With Arduino Uno R3");
}

void loop() {
  int volt = analogRead(A0);
  //First Code
  adc_value = analogRead(ANALOG_IN_PIN);
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
  in_voltage = adc_voltage / (R2/(R1+R2)) ; 
  Serial.print("Input Voltage Code 1 = "),Serial.print(in_voltage, 2), Serial.print(" V");;

  //Second Code
  double voltage = map(volt,0,1023, 0, 2500) + offset;
  voltage /=100;
  Serial.print("|  \t Input Voltage Code 2: "),Serial.print(voltage),Serial.println(" V");

delay(1000);
  
  
}
