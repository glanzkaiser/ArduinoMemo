#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Define analog input
#define ANALOG_IN_PIN A0
 
// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0;
 
float ref_voltage = 5.0;
 
int adc_value = 0;
 
void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("DC Voltage Test");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}
 
void loop() {
  // Read the Analog Input
  adc_value = analogRead(ANALOG_IN_PIN);
 
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
 
  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2)) ;
 
  // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);
 
  display.setCursor(20, 10); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Battery Voltage");
 
 
  display.setCursor(25, 30); //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(in_voltage, 2);
  display.println(" V");
  display.display();
  delay(500);
  display.clearDisplay();
 
}
