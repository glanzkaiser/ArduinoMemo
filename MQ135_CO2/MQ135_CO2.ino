#define anInput     A0                        
#define co2Zero     55                       
//calibrated CO2 0 level

void setup() 
{
  pinMode(anInput,INPUT);                     
  Serial.begin(9600);   
  Serial.println("MQ135 CO2 Sensor Test");
  Serial.println("with Arduino UNO R3 by Glanz and Freya");
}
  
void loop() 
{
  
  int co2now[10];                               
  int co2raw = 0;                            
  int co2ppm = 0;                               
  int zzz = 0;                                

  for (int x = 0;x<10;x++)  //sample co2 10x over 2 seconds
  {                   
    co2now[x]=analogRead(A0);
    delay(200);
  }

  for (int x = 0;x<10;x++)  //add samples together
  {                     
    zzz=zzz + co2now[x];  
  }
  
  co2raw = zzz/10;                            
  co2ppm = co2raw - co2Zero;                

  Serial.print("Air Quality=");
  Serial.print(co2ppm);  
  Serial.println(" PPM");
  delay(5000);             

}
