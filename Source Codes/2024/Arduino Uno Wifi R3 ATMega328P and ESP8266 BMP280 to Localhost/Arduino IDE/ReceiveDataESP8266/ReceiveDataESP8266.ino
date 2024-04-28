// After upload BMP280-MySQL-Atmega
// Upload this with SW 5, 6 and SW 7 ON
// Unplug the board
// Connect :
// TXD (ESP) - D2 (Atmega)
// RXD (ESP) - D3 (Atmega)
// Plug the board again
// Try the code with SW 1 and SW 2 (Atmega328+ESP8266) ON and open localhost/bmp280postcustom/view.php
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;

const char *ssid = "yourSSID";
const char *password = "yourpassword";

//Web/Server address to read/write from 
const char *host = "192.168.100.55";   //https://circuits4you.com website or IP address of server

float altitudedata = 0;
float temperature = 0;

void setup() {
  Serial.begin(115200);
  connectToWifi();
}

void connectToWifi(){
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print("not connected, ");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

String splitString(String data, char separator, int index)
{
int found = 0;
int strIndex[] = { 0, -1 };
int maxIndex = data.length() - 1;
for (int i = 0; i <= maxIndex && found <= index; i++) {
if (data.charAt(i) == separator || i == maxIndex) {
found++;
strIndex[0] = strIndex[1] + 1;
strIndex[1] = (i == maxIndex) ? i+1 : i;
}
}
return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
  String postData, pelanggan, suhu, ketinggian, link;

  if(Serial.available()){
    String msg = "";
    while(Serial.available()){
      msg += char(Serial.read());
      delay(50);
  }
  altitudedata = splitString(msg, ';', 0).toFloat(); 
  temperature = splitString(msg, ';', 1).toFloat();
  
  suhu= String(temperature);   //String to interger conversion
  ketinggian= String(altitudedata);   //String to interger conversion
  pelanggan= "Boginya Freya";
  
  //Post Data
  postData = "&status1=" + suhu+ "&status2=" + ketinggian+ "&pelanggan=" + pelanggan;
  link = "http://192.168.100.55/bmp280postcustom/postdemo.php";
  
  http.begin(client,link);              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  }
  delay(10000);  //Post Data at every 10 seconds
}
//=======================================================================
