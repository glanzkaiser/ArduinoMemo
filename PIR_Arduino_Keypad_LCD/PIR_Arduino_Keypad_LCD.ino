#include <DFR_LCD_Keypad.h> //library LCD Keypad Shield

LiquidCrystal lcd(8,9,4,5,6,7);  //inisialisasi lcd
DFR_LCD_Keypad keypad(A0, &lcd); //inisialisasi keypad

//variable untuk keypad
int last_key, key;
int a=2;
int b=0;
int c=3;
int d=0;

//inisialisasi input output
int lampu = 3;               
int sensor = 2;               
int val = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); //menggunakan lcd 16x2
  lcd.clear();     //membersihkan tampilan lcd

  pinMode(lampu, OUTPUT);    //inisialisasi output
  pinMode(sensor, INPUT);    //inisialisasi input

  digitalWrite(lampu, LOW);  //set awal lampu
}

void loop() {
  // put your main code here, to run repeatedly:
   button();        //memanggil fungsi button()
   
   if(a==1 && b==0) //menu geser ke SET
   {
    lcd.clear();                     //membersihkan tampilan lcd
    lcd.setCursor(0,0);              //koordinat lcd
    lcd.println(" JOGJAROBOTIKA  "); //display lcd
    lcd.setCursor(1,1);              //koordinat lcd
    lcd.print("START");              //display lcd
    lcd.setCursor(8,1);              //koordinat lcd
    lcd.print(">SET");               //display lcd
    delay(100);                      //delay
    d=0;
   }

   if(a==2 && b==0) //menu geser ke START
   {
    lcd.clear();                     //membersihkan tampilan lcd
    lcd.setCursor(0,0);              //koordinat lcd
    lcd.println(" JOGJAROBOTIKA  "); //display lcd
    lcd.setCursor(0,1);              //koordinat lcd
    lcd.print(">START");             //display lcd
    lcd.setCursor(9,1);              //koordinat lcd
    lcd.print("SET");                //display lcd
    delay(100);                      //delay
    d=0;
   }

   if(a==2 && b==1)
   {
    val = digitalRead(sensor);   // read sensor value
    if (val == HIGH) {           // check if the sensor is HIGH
      int count=c+1;             // inisialisasi penghitung mundur
      for (int i = 0; i <= c; i++){
        count--;
        digitalWrite(lampu, HIGH);   // turn lampu ON
    
        lcd.clear();                   //membersihkan tampilan lcd
        lcd.setCursor(0,0);            //koordinat lcd
        lcd.print("Motion detected!"); //display lcd
        lcd.setCursor(0,1);            //koordinat lcd
        lcd.print("OFF dalam");        //display lcd
        if(count<10){
          lcd.setCursor(11,1);         //koordinat lcd
          lcd.print(count);}           //display lcd penghitung mundur
        else{
          lcd.setCursor(10,1);         //koordinat lcd
          lcd.print(count);}           //display lcd penghitung mundur
        lcd.setCursor(12,1);           //koordinat lcd
        lcd.print("s");                //display lcd
        delay(1000);                   //delay
      }
      digitalWrite(lampu, LOW);        // turn lampu OFF
    } 
    else {
      digitalWrite(lampu, LOW);     // turn lampu OFF
      lcd.clear();                  //membersihkan tampilan lcd
      lcd.setCursor(2,0);           // posisi karakter pada LCD
      lcd.print("SENSOR PIR");      //LCD Display
      lcd.setCursor(0,1);           // posisi karakter pada LCD
      lcd.print("Motion stopped!"); //LCD Display
      delay(100);                   //delay
    }
   }
   
  if(a==1 && b==1)
   {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SET DELAY");
    if(c<10){
    lcd.setCursor(1,1);
    lcd.print(c);}
    else{
    lcd.setCursor(0,1);
    lcd.print(c);}
    lcd.setCursor(2,1);
    lcd.print("s    (min 3s)");
    delay(100);
    if(d==2){b=0;}
   }
}

void button()
{
  last_key = keypad.get_last_key(); //fungsi library
  key      = keypad.read_key();     //fungsi library
  
  if (key != last_key) {
    lcd.clear();
    lcd.setCursor(0,0);
    
    switch (key) {
      case KEY_RIGHT:
        a=1;
        break;
        
      case KEY_UP:
        c++;
        break;
        
      case KEY_DOWN:
        c--;
        break;
        
      case KEY_LEFT:
        a=2;
        break;

      case KEY_SELECT:
        b=1;
        d++;
        break;
    }
  }
  delay(10);
  }
