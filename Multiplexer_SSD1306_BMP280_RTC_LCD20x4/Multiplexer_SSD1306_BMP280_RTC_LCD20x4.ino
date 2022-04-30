#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h> 
#include <Adafruit_Sensor.h>  
#include <Adafruit_BMP280.h>  

Adafruit_BMP280 bmp280;

//LiquidCrystal_I2C lcd(0x3C,20,4); 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void TCA9548A(uint8_t bus) //function of TCA9548A
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup()   
{                
  Serial.begin(9600);
  Wire.begin();
  delay(100);

  TCA9548A(1);
  TCA9548A(2);
  TCA9548A(7);
  
  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                
  
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();
}

String temp;
String pres;
String Alt;

void loop() {
    TCA9548A(2);
    float temp = bmp280.readTemperature();
    float pres = bmp280.readPressure()/100; 
    float alt = bmp280.readAltitude(975.7); 
    
    display.clearDisplay();
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(1, 1);     // Start point
    display.print("T: ");
    display.print(temp);
    display.println(" °C");

    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(1, 22);     // Start point
    display.print("P: ");
    display.print(pres);
    display.println(" hPa");

    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(1, 45);     // Start point
    display.print("Alt: ");
    display.print(alt);
    display.println(" m");
    display.display();
  
    
    Serial.print(F("Temperature = "));
    Serial.print(bmp280.readTemperature());
    Serial.println(" °C");
  
    Serial.print(F("Pressure = "));
    Serial.print(bmp280.readPressure()/100); //displaying the Pressure in hPa, you can change the unit
    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp280.readAltitude(975.7)); 
    //The "975.7" is the pressure(hPa) at sea level 
    //in day in your region
    //If you don't know it, modify it until you get 
    //your current altitude
    Serial.println(" m");                    
    

    Serial.println();
    delay(1000);
  }
