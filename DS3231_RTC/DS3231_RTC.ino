#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

void setup() {
    Serial.begin(9600);
    Serial.println("Real-Time Clock DS3231 Test ");
    Serial.println("with Arduino UNO R3 by Glanz and Freya");
    delay(3000);
    if (! rtc.begin()) {
    Serial.println("RTC couldn't be found");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // Comment out below lines once you set the date & time.
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtc.adjust(DateTime(2021, 12, 30, 11, 24, 0));
  }
}

void loop() {
    DateTime now = rtc.now();
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(", ");
    Serial.print(now.day(), DEC); 
    Serial.print('/');
    Serial.print(now.month(), DEC); 
    Serial.print('/');
    Serial.print(now.year(), DEC); 
    Serial.print(' ');
    Serial.print(now.hour(), DEC); 
    Serial.print(':');
    Serial.print(now.minute(), DEC); 
    Serial.print(':');
    Serial.print(now.second(), DEC); 
    Serial.println();
    delay(1000);

}
