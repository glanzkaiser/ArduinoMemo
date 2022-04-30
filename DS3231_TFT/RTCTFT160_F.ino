    /////////////////////////////////////////////////////////////////
   //         Arduino Real Time Clock fahrenheit         v1.02    //
  //       Get the latest version of the code here:              //
 //       http://educ8s.tv/arduino-real-time-clock/             //
/////////////////////////////////////////////////////////////////


#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "Sodaq_DS3231.h"
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    8                     
#define TFT_DC     9
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13 
#define TFT_MOSI 11

float maxTemperature=0;
float minTemperature=200;
char charMinTemperature[10];
char charMaxTemperature[10];
char timeChar[100];
char dateChar[50];
char temperatureChar[10];
uint32_t old_ts;

float temperature = 0;
float previousTemperature = 0;

String dateString;
int minuteNow=0;
int minutePrevious=0;

void setup () 
{
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
    printText("TEMPERATURE", ST7735_GREEN,30,65,1);  // Temperature Static Text
    printText("MAX", ST7735_RED,18,130,1);
    printText("MIN", ST7735_BLUE,95,130,1);
    //setRTCTime();
}

//uint32_t old_ts;

void loop () 
{
  rtc.convertTemperature();
  float temperature = Celcius2Fahrenheit(rtc.getTemperature());
  DateTime now = rtc.now(); //get the current date-time
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
    tft.fillRect(10,0,160,65,ST7735_BLACK);
    printText(timeChar, ST7735_WHITE,20,25,3);
    dateString.toCharArray(dateChar,50);
    printText(dateChar, ST7735_GREEN,8,5,1);
  }
  
  if(temperature != previousTemperature)
  {
    previousTemperature = temperature;
    String temperatureString = String(temperature,0);
    temperatureString.toCharArray(temperatureChar,10);
    tft.fillRect(10,80,128,30,ST7735_BLACK);
    printText(temperatureChar, ST7735_WHITE,35,80,3);
    printText("o", ST7735_WHITE,85,75,2);
    printText("F", ST7735_WHITE,100,80,3);

    if(temperature>maxTemperature)
    {
      maxTemperature = temperature;
      dtostrf(maxTemperature,3, 0, charMaxTemperature); 
      tft.fillRect(3,142,33,20,ST7735_BLACK);
      printText(charMaxTemperature, ST7735_WHITE,10,145,1);
      printText("o", ST7735_WHITE,35,140,1);
      printText("F", ST7735_WHITE,41,145,1);
    }
    if(temperature<minTemperature)
    {
      minTemperature = temperature;
      dtostrf(minTemperature,4, 0, charMinTemperature); 
      tft.fillRect(75,140,36,18,ST7735_BLACK);
      printText(charMinTemperature, ST7735_WHITE,80,145,1);
      printText("o", ST7735_WHITE,112,140,1);
      printText("F", ST7735_WHITE,118,145,1);
    }
  }
}
    delay(1000);
}

void setRTCTime()
{
  DateTime dt(2016, 5, 4, 7, 38, 30, 3); //Year, Month, Day, Hour, Minutes, Seconds, Day of the Week
  rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
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
    case 1: return "Monday";break;
    case 2: return "Tuesday";break;
    case 3: return "Wednesday";break;
    case 4: return "Thursday";break;
    case 5: return "Friday";break;
    case 6: return "Saturday";break;
    case 7: return "Sunday";break;
    default: return "Monday";break;
  }
}

float Celcius2Fahrenheit(float celsius)
{
  return 1.8 * celsius + 32;
}
