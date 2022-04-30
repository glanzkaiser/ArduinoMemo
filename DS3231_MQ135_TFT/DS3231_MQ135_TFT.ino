#define anInput     A0                        
#define co2Zero     55            

#include "MQ135.h"
#define ANALOGPIN A2
#define RZERO 4668.29
MQ135 gasSensor = MQ135(ANALOGPIN);

#include  <Adafruit_ST7735.h>
#include  <Adafruit_GFX.h>
#include <Wire.h>
#include "Sodaq_DS3231.h"
#include  <SPI.h>

#define TFT_CS     10
#define TFT_RST    8                      
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define TFT_SCLK 13   
#define TFT_MOSI 11   

float maxTemperature=0;
float minTemperature=200;
char charMinTemperature[10];
char charMaxTemperature[10];
char timeChar[100];
char dateChar[50];
char temperatureChar[10];
char co2Char[10];

float temperature = 0;
float previousTemperature = 0;

String co2Value;
String dateString;
int minuteNow=0;
int minutePrevious=0;

void setup() {
    pinMode(anInput,INPUT);
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
    printText("Temperature", ST7735_GREEN,30,55,1); 
    printText("CO2 (ppm)", ST7735_GREEN,30,95,1);
    printText("Max", ST7735_RED,18,130,1);
    printText("Min", ST7735_BLUE,95,130,1);
    //setRTCTime();
}

uint32_t old_ts;

void loop() {
  float ppm = gasSensor.getPPM();
  
  float temperature = rtc.getTemperature();                             
  DateTime now = rtc.now();
  uint32_t ts = now.getEpoch();

  if (old_ts == 0 || old_ts != ts) {
  old_ts = ts;
  
  minuteNow = now.minute();
  if(minuteNow!=minutePrevious)
  {
    dateString = getDayOfWeek(now.dayOfWeek())+", ";
    dateString = dateString+String(now.date())+"/"+String(now.month());
    dateString= dateString+"/"+ String(now.year()); 
    minutePrevious = minuteNow;
    String hours = String(now.hour());
    if(now.minute()<10)
    {
      hours = hours+":0"+String(now.minute());
    }else
    {
      hours = hours+":"+String(now.minute());
    }
    
    hours.toCharArray(timeChar,100);
    //tft.fillRect(10,0,160,50,ST7735_BLACK);
    printText(timeChar, ST7735_WHITE,30,25,2);
    dateString.toCharArray(dateChar,50);
    printText(dateChar, ST7735_GREEN,8,5,1);
    
    co2Value = String(ppm);
    co2Value.toCharArray(co2Char,10);
    tft.fillRect(0,125,160,1,ST7735_WHITE);
    printText(co2Char, ST7735_CYAN,30,115,1);
  }
  
  if(temperature != previousTemperature)
  {
    previousTemperature = temperature;
    String temperatureString = String(temperature,1);
    temperatureString.toCharArray(temperatureChar,10);
    tft.fillRect(10,80,128,10,ST7735_BLACK);
    printText(temperatureChar, ST7735_WHITE,30,70,2);
    printText("o", ST7735_WHITE,85,65,1);
    printText("C", ST7735_WHITE,95,70,2);
    
  if(temperature>maxTemperature)
    {
      maxTemperature = temperature;
      dtostrf(maxTemperature,5, 1, charMaxTemperature); 
      tft.fillRect(3,142,33,20,ST7735_BLACK);
      printText(charMaxTemperature, ST7735_WHITE,3,145,1);
      printText("o", ST7735_WHITE,35,140,1);
      printText("C", ST7735_WHITE,41,145,1);
    }
  if(temperature  < minTemperature) 
    {
      minTemperature = temperature;
      dtostrf(minTemperature,5, 1, charMinTemperature); 
      tft.fillRect(75,140,36,18,ST7735_BLACK);
      printText(charMinTemperature, ST7735_WHITE,80,145,1);
      printText("o", ST7735_WHITE,112,140,1);
      printText("C", ST7735_WHITE,118,145,1);
    }
  }
}
    delay(1000);
}

void setRTCTime()
{
  DateTime dt(2021, 12, 30, 11, 25, 30, 4); // Year, Month, Day, Hour, Minutes, Seconds, Day of Week
  rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
}void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

String getDayOfWeek(int i)
{
  switch(i)
  {
    case 1: return "Lundi";break;
    case 2: return "Mardi";break;
    case 3: return "Mercredi";break;
    case 4: return "Jeudi";break;
    case 5: return "Vendredi";break;
    case 6: return "Samedi";break;
    case 7: return "Dimanche";break;
    default: return "Jeudi";break;
  }
}
