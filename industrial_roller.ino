/*
  LiquidCrystal Library - display() and noDisplay()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 display() and noDisplay() functions to turn on and off
 the display.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay

*/
const int ir_Pin=7;
const int triggPin=8;
const int echoPin=6; 
int motorPin=3;
int ir_count=0;
int ultra_count=0;
int irState;

// include the library code:
#include <LiquidCrystal.h>
#include<Servo.h>

Servo  myServo;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  myServo.attach(9);
  pinMode(ir_Pin,INPUT);
  pinMode(triggPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(motorPin,OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}



int distance_measured(){
  digitalWrite(triggPin,LOW);
  digitalWrite(triggPin,HIGH);
  delayMicroseconds(20);
  digitalWrite(triggPin,LOW);
  int time_taken=pulseIn(echoPin,HIGH);
  int distance=0.0165*time_taken;
  return distance;
}

void loop() {


  //<...........Motor..........>
  
analogWrite(motorPin, 100);



  irState=digitalRead(ir_Pin);
  if(irState==LOW){
  delay(200);
   ir_count=ir_count;
   
    lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("White Goods:");
   lcd.setCursor(12,0);
   lcd.print(ir_count);
   
   Serial.print("white goods   ");
   Serial.println(ir_count);
   delay(500);
 
irState=digitalRead(ir_Pin);
while(irState==LOW){
  ir_count=ir_count;
  myServo.write(0);
  Serial.println(ir_count);
  delay(500);

   irState=digitalRead(ir_Pin);
     if (irState==HIGH)
      
      ir_count=ir_count+1;
     /* lcd.setCursor(0,0);
      lcd.print(ir_count);*/
      
       lcd.clear();
       lcd.setCursor(12,0);
       lcd.print(ir_count);
   
      Serial.println(ir_count);
      delay(5000);
      myServo.write(90);
   }
 }

  irState=digitalRead(ir_Pin);
     if (irState==HIGH){
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Goods coming...   ");
 
      Serial.println("goods coming...   ");
    }
   
   
  int distance_calculated=distance_measured();
  if(distance_calculated<20){
      ultra_count=ultra_count;
 

    distance_calculated=distance_measured();
while(distance_calculated<20){
      ultra_count=ultra_count;


    distance_calculated=distance_measured();
  if(distance_calculated>20)
    ultra_count=ultra_count+1;
    
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Black Goods:");
     lcd.setCursor(12,1);
     lcd.print(ultra_count);
     delay(4000);
   

   
    Serial.print("distance_calculated   ");
    Serial.print(distance_calculated);
    Serial.print("    ");
    Serial.println("ultra_count");
    Serial.println(ultra_count);
} 
}

   
    Serial.print("ultra_count   ");
    Serial.println(ultra_count);
    delay(500);
    
   
}
