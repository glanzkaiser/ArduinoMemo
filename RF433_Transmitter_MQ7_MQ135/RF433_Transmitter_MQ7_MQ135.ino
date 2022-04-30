#include <RH_ASK.h>
#include <SPI.h> 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20,4);

RH_ASK rf_driver;

int R0 = 6692;
int R2 = 1000;
int sensorPin = A0;  
int MQ7sensorValue = 0;
int sensorValue = 0; 
float PPM_CO2;
float PPM_CO;
float RS;

String str_co;
String str_co2;
String str_out;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  lcd.init(); 
  lcd.clear(); 
  lcd.backlight(); 
  
   Serial.begin(9600);
   Serial.println("Send CO and CO2 data with RF433, MQ7 and MQ135");
   Serial.println("with Arduino UNO R3 by Glanz and Freya");
   rf_driver.init();

}

int i = 1;
void loop() {
  while (i > 0) {
  
  int sensorValue135 = analogRead(A2);  
  float volts = sensorValue135 * 5;
  volts = volts / 1023;
  RS = R2 * (1-volts);
  RS = RS/volts; 
  
  PPM_CO2 = 470.627063 - 330.033*(RS/R0);
  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);            
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            

  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50);   

  MQ7sensorValue = analogRead(sensorPin);  
  PPM_CO = float(MQ7sensorValue);
  
  Serial.print("CO = "),Serial.print(PPM_CO);
  Serial.print(" ppm");
  Serial.print("\t | CO2 = "),Serial.print(PPM_CO2);
  Serial.print(" ppm");
  Serial.print("Measurement #: "),Serial.println(i);

    lcd.setCursor(1,0);
    lcd.print("GFreya MQ7 & MQ135");
    lcd.setCursor(0,1);
    lcd.print("CO : "),lcd.print(PPM_CO),lcd.print(" ppm");
    lcd.setCursor(0,2);
    lcd.print("CO2 : "),lcd.print(PPM_CO2),lcd.print(" ppm");
    lcd.setCursor(0,3);
    lcd.print("Measurement #: "),lcd.print(i);
    
    // Convert CO, CO2 and i values to string
    str_co = String(PPM_CO);
    str_co2 = String(PPM_CO2);
    
    // Combine CO and CO2
    str_out = str_co + "," + str_co2;
    
    // Compose output character
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    
    i++;
    }
    delay(1000);
}
