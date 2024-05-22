// Upload with SW 5,6,7 ON
// Unplug the board and turn SW 5 and SW 6 ON
// Open serial monitor at 9600 Baud
// Then see the webserver' IP address

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "yourSSID";
const char *password = "wifipassword";

// IP Address configuration
// IPAddress IP(192,168,100,55);
// IPAddress NETMASK(255,255,255,0);
// IPAddress NETWORK(192,168,100,1);
// IPAddress DNS(192,168,100,1);

ESP8266WebServer server(80);

String webpage;

void setup(){
  Serial.begin(9600);
   WiFi.begin(ssid, password);
   // Uncomment below if you want to use IP config
   //WiFi.config(IP,NETWORK,NETMASK,DNS);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(500);
       Serial.print(".");
   }
     Serial.println();
     Serial.print("Connected, IP Address:");
     Serial.println(WiFi.localIP());
     Serial.println();
     Serial.print("Connect to: ");
     Serial.println(ssid);
     

     // Webpage
     webpage+="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
     webpage+="<center><h1> LED with Arduino Uno WiFi R3 </h1></center>";
     webpage+= "<br></br>";
     webpage+= "<style> .button1 {width: 250px; background-color: #00a86b; Height: 100px} .button2 {background-color: #CD5C5C;}";
     webpage+= ".button {border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style>";
     webpage+= "<center><a href=\"led1on\"\"><button class='button button1'>LED 1 ON</button></a>";
     webpage+= "<a href=\"led1off\"\"><button class='button button1'>LED 1 OFF</button></a></p><br></br>";
     webpage+= "<a href=\"led2on\"\"><button class='button button1'>LED 2 ON</button></a>";
     webpage+= "<a href=\"led2off\"\"><button class='button button1'>LED 2 OFF</button></a></pr><br></br>";
     webpage+= "<a href=\"led3on\"\"><button class='button button1'>LED 3 ON</button></a>";
     webpage+= "<a href=\"led3off\"\"><button class='button button1'>LED 3 OFF</button></a></pr></center>";
     webpage+= "</head>";   

     server.on("/", [](){
        server.send(200, "text/html", webpage);
      });

     server.on("/led1on", []() {
        server.send(200, "text/html", webpage);
          Serial.write(1); // Data send through serial communication to ATMega328P 
          delay(1000);
      });  
     server.on("/led1off", []() {
        server.send(200, "text/html", webpage);
          Serial.write(2); // Data send through serial communication to ATMega328P 
          delay(1000);
      }); 
     server.on("/led2on", []() {
        server.send(200, "text/html", webpage);
          Serial.write(3); // Data send through serial communication to ATMega328P 
          delay(1000);
      });  
     server.on("/led2off", []() {
        server.send(200, "text/html", webpage);
          Serial.write(4); // Data send through serial communication to ATMega328P 
          delay(1000);
      }); 
     server.on("/led3on", []() {
        server.send(200, "text/html", webpage);
          Serial.write(5); // Data send through serial communication to ATMega328P 
          delay(1000);
      });  
     server.on("/led3off", []() {
        server.send(200, "text/html", webpage);
          Serial.write(6); // Data send through serial communication to ATMega328P 
          delay(1000);
      });
      server.begin();
      Serial.println("The webserver is running..");
}

void loop(){
  server.handleClient();
}
