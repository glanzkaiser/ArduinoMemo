#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//int msg[1];
RF24 radio(9,10); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
        Serial.begin(9600);
        radio.begin();
        radio.openWritingPipe(pipe);
        radio.setPALevel(RF24_PA_MIN);
        radio.stopListening();
        Serial.println("################## Set up complete ######################");
}

void loop(){
        const char data[] = "hello world!";
        if(radio.write(&data[0], sizeof(data))){
        Serial.println("message sent");
        }
        else{
        Serial.println("Message not sent");
        }
        delay(1000);
}
