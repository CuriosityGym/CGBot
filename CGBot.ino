#include <NewPing.h>
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SWITCH_PIN 2     // The digital pin number where the switch has been connected.

int leftIRPin = 4;        //select pin for left IR sensor
int rightIRPin = 5;       //select pin for right IR sensor
int IRleft = 0;           //initialise variable to store left IR sensor value
int IRright = 0;          //initialise variable to store right IR sensor value
int lmotorA = 10 ;        //select pin for left motor A pin
int lmotorB = 11;         //select pin for left motor B pin
int rmotorA = 2;          //select pin for right motor A pin
int rmotorB = 3;          //select pin for right motor B pin
int switchstate = 0;      //Initialise the variable to store the mode switch state.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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
  digitalWrite(lmotorA, HIGH);
  digitalWrite(lmotorB, HIGH);
  digitalWrite(rmotorA, LOW);
  digitalWrite(rmotorB, HIGH);
}

void right(){
  digitalWrite(lmotorA, HIGH);
  digitalWrite(lmotorB, LOW);
  digitalWrite(rmotorA, HIGH);
  digitalWrite(rmotorB, HIGH);
}

void reverse(){
  digitalWrite(lmotorA, LOW);
  digitalWrite(lmotorB, HIGH);
  digitalWrite(rmotorA, HIGH);
  digitalWrite(rmotorB, LOW);
}

void setup(){
  pinMode(lmotorA, OUTPUT);
  pinMode(lmotorB, OUTPUT);
  pinMode(rmotorA, OUTPUT);
  pinMode(rmotorB, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);
  //frwd();
  pinMode(13, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  delay(3000);
  digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
  Serial.begin(9600);
}

void loop(){  
 switchstate = digitalRead(SWITCH_PIN);
 if ( switchstate == HIGH )
 {
  int distance=sonar.ping_cm();
  if(distance>0 && distance<10)
  {
      reverse();
      delay(1000);
      left();
      delay(1000);

      frwd();
      
      
  }
  else
  {
       frwd();
    
  }
 }
 else
 {  
  IRleft = !digitalRead(leftIRPin);
  IRright = !digitalRead(rightIRPin);
  if( IRleft==0 && IRright==1 )
  {
   
    left();

    Serial.println("Right");
  }  
 
  if( IRleft==1 && IRright==0)
  {
  
      right();

      Serial.println("Left");
 }

  if( IRleft==1 && IRright==1)
  {
  
      frwd();
 }
 if( IRleft==0 && IRright==0)
  {
  
      frwd();
 }
 delay(50);
 }
}

