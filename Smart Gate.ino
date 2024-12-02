
const int servoPin=9;
const int irOpen=7;
const int irClose=8;




#include <Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  pinMode(irOpen,INPUT);
  pinMode(irClose,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int irOpenState= digitalRead(irOpen);
Serial.println("irOpen");
Serial.println(irOpenState);
delay(500);

/*if(irOpenState==LOW){
  myServo.write(0);
  delay(2000);*/


int irCloseState=digitalRead(irClose);
Serial.println("irClose");
Serial.println(irCloseState);
delay(500);

  /* while(irCloseState==HIGH){
    myServo.write(0);
   delay(200); 
  }*/


  if(irOpenState==LOW) {
       myServo.write(0);
 
  }
  
 irCloseState=digitalRead(irClose);
Serial.println("while");
Serial.println(irCloseState);
delay(500);
  while(irCloseState==LOW){
    myServo.write(0);


    
irCloseState=digitalRead(irClose);
Serial.println("if");
Serial.println(irCloseState);
delay(500);
  if(irCloseState==HIGH)
   myServo.write(90);
   }
  }
