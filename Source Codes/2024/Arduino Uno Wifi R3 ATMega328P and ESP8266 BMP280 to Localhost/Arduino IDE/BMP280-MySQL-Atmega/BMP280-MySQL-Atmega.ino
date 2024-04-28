// Upload this with SW 3 and SW 4 ON
#include <Wire.h> // 
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h> 
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface
float pressure, alt, temperature;
SoftwareSerial ss(2,3);
// default address 0x27
// LCD 20x4 (20,4)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

byte Heart[8] = {
0b00000,
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000
};
byte Southwest[8] =
{
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00001,
0b00010
};

byte Northeast[8] =
{
0b11100,
0b01100,
0b10100,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};
 
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, Heart);
  lcd.createChar(1, Southwest);
  lcd.createChar(2, Northeast);
  lcd.clear();
  lcd.print("Glanz");
  Serial.begin(9600);
  Serial.println("BMP280 Sensor with LCD");
  Serial.println("with Arduino UNO WiFi R3-ESP8266 by Glanz and Freya");
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  
  ss.begin(115200);
  delay(5000);
}

void loop() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure()/100; //displaying the Pressure in hPa, you can change the unit
  alt = bmp.readAltitude(975.7); //The "975.7" is the pressure(hPa) at sea level in day in your region
  //If you don't know it, modify it until you get your current altitude

  // Write the data captured by BMP280 in Serial Monitor / PC 
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" C");
  
  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure()/100); 
  Serial.println(" hPa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(975.7)); 
  Serial.println(" m");              

  // Write the data captured by BMP280 in LCD 20x4
  lcd.setCursor(1, 1);
  lcd.write(1);   
  lcd.setCursor(2, 1);
  lcd.write(0);
  lcd.setCursor(3, 1);
  lcd.write(2);
  lcd.setCursor(0, 2);
  lcd.print("Freya");
  
  lcd.setCursor(6,1);
  lcd.print("T: ");
  lcd.print(bmp.readTemperature());lcd.print(" C");
    
  lcd.setCursor(6,2);
  lcd.print("P: ");
  lcd.print(bmp.readPressure()/10);lcd.print(" hPa");
    
  lcd.setCursor(6,3);
  lcd.print("h: ");
  lcd.print(bmp.readAltitude(975.7));lcd.print(" m");

  // send data to ESP8266 with serial communication
  String sendToESP = "";
  sendToESP += bmp.readAltitude(975.7);
  sendToESP += ";";
  sendToESP += bmp.readTemperature();
  ss.println(sendToESP);
  delay(3300);
  
}
