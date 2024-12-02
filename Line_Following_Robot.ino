int leftMotorPin1=11;
int leftMotorPin2=10;
int rightMotorPin1=9;
int rightMotorPin2=8;

  //EN1 and EN2//
int leftMotorSpeed=5;
int rightMotorSpeed=6;

  //Ultrasonic sensor//
int trigPin=3;
int echoPin=4;

int l_ir=12;  //left ir sensor
int r_ir=2;  // right ir sensor
int l_irState;
int r_irState;



void setup() {
  // put your setup code here, to run once:
  pinMode (leftMotorPin1, OUTPUT);
  pinMode (leftMotorPin2, OUTPUT);
  pinMode (rightMotorPin1, OUTPUT);
  pinMode (rightMotorPin2, OUTPUT);
  pinMode (leftMotorSpeed, OUTPUT);
  pinMode (rightMotorSpeed, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(l_ir, INPUT);
  pinMode(r_ir, INPUT);
  Serial.begin(9600);
}




  void Move(){
   digitalWrite(leftMotorPin1, LOW);
   digitalWrite(leftMotorPin2, HIGH);
   digitalWrite(rightMotorPin1, HIGH);
   digitalWrite(rightMotorPin2, LOW);
  
   analogWrite(leftMotorSpeed, 80);
   analogWrite(rightMotorSpeed, 100);
  }

  void Stop (){
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  
    analogWrite(leftMotorSpeed, 0);
    analogWrite(rightMotorSpeed, 0);
  }


  void turnRight(){
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
 
  }

  void turnLeft(){
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }  
  
  int distance_measured(){
      digitalWrite(trigPin, LOW);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(20);
      digitalWrite(trigPin, LOW);
      int time_taken=pulseIn(echoPin, HIGH);
      int distance=0.0165*time_taken;
      return distance;  
  }
  
  

void loop() {
  // put your main code here, to run repeatedly:

        /////////////////////obstacle detection///////////////////////
 int distance_calculated=distance_measured();
   if(distance_calculated<=40){
      delay(500);
        Stop(); 
        Serial.println(distance_calculated);
        Serial.println("car stopped");
   }
   else {
           //////////////Line detection//////////////////////
   l_irState=digitalRead(l_ir);
   r_irState=digitalRead(r_ir);
   //delay(500);
   Serial.print("l_ir    ");
   Serial.println(l_irState);
   Serial.print("r_ir  ");
   Serial.println(r_irState);
 // delay(500);

   if (l_irState == 1 && r_irState == 0){
      turnLeft();
      Serial.println("car turning left");
   }else if(l_irState == 0 && r_irState == 1){
     turnRight();
     Serial.println("car turning right");
   } else if(l_irState == 0 && r_irState == 0){
    Move();
     Serial.println("car moving");
   } else {
          Stop();
         Serial.println("car stop");
   }
     delay(100);

   }  
}

  

 
