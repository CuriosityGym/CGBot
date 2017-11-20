#include <NewPing.h>
int distance;
NewPing sonar_A0(A0,A1);
int leftIRPin = 4; //select pin for left IR sensor
int rightIRPin = 5; //select pin for right IR sensor
int IRleft = 0; //initialise variable to store left IR sensor value
int IRright = 0; //initialise variable to store right IR sensor value
int lmotorA = 6 ; //select pin for left motor A pin
int lmotorB = 11; //select pin for left motor B pin
int rmotorA = 2; //select pin for right motor A pin
int rmotorB = 3; //select pin for right motor B pin
int switchpin=8; //select pin for the switch
void setup(){
  pinMode(lmotorA, OUTPUT);
  pinMode(lmotorB, OUTPUT);
  pinMode(rmotorA, OUTPUT);
  pinMode(rmotorB, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  analogWrite(9,75);
  analogWrite(10,75);
}

void loop(){ 
  switchpin=digitalRead(7); 
  if(switchpin==HIGH)
  {
        distance= sonar_A0.ping_cm();
      if(distance>=15)
      { 
         frwd();
      }  
      else 
       {
         stopmotors();
         delay(100);
         turnright();
       }
  }
  else
  {
        IRleft = digitalRead(leftIRPin);
        IRright = digitalRead(rightIRPin);
        if( !IRleft && IRright ){
          digitalWrite(13, HIGH);
          //left();
          right();
        }  
        else {
          if( IRleft && !IRright){
            digitalWrite(13, HIGH);
            //right();
            left();
          }
          else {
            if( IRleft && IRright){
              digitalWrite(13, HIGH);
              stopmotors();
              //frwd();
            }
            else{
              if( !IRleft && !IRright){
              digitalWrite(13, LOW);
              //stopmotors();
              frwd();
              }
            }
          }
        }
      }
}

void stopmotors(){
  digitalWrite(lmotorA, LOW);
  digitalWrite(lmotorB, LOW);
  digitalWrite(rmotorA, LOW);
  digitalWrite(rmotorB, LOW);
}

void frwd(){
  digitalWrite(lmotorA, HIGH);  
  digitalWrite(lmotorB, LOW);
  digitalWrite(rmotorA, LOW);
  digitalWrite(rmotorB, HIGH);
}

void left(){
  digitalWrite(lmotorA, LOW);
  digitalWrite(lmotorB, HIGH);
  digitalWrite(rmotorA, LOW);
  digitalWrite(rmotorB, HIGH);
}

void right(){
  digitalWrite(lmotorA, HIGH);
  digitalWrite(lmotorB, LOW);
  digitalWrite(rmotorA, HIGH);
  digitalWrite(rmotorB, LOW);
}

void reverse(){
  digitalWrite(lmotorA, LOW);
  digitalWrite(lmotorB, HIGH);
  digitalWrite(rmotorA, HIGH);
  digitalWrite(rmotorB, LOW);
}

void turnright(){
  digitalWrite(lmotorA, HIGH);
  digitalWrite(lmotorB, LOW);
  digitalWrite(rmotorA, HIGH);
  digitalWrite(rmotorB, LOW);
  delay(1000);
}
