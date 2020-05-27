/*
MiCROBOT V12.2

Julkifli Awang Besar
C0d3
PID for MiCROBOT

Suite with MiCROBOT PCB.

using IR remote

*/
#include <QTRSensors.h>
#include <Servo.h>
Servo ESC;

#define BUTTON  2

#define NUM_SENSORS 8 
#define TIMEOUT 2500 
#define EMITTER_PIN 11 

#define PWMA 5 
#define AIN2 4
#define AIN1 9 

#define PWMB 6  
#define BIN2 8 
#define BIN1 7


//#define motorPower 9


#define A_BaseSpeed 60
#define B_BaseSpeed 60

int PRESS;
int motorSpeed;
int error;
int position;

    int lastError = 0; 
    float Kp = 0.01; 
    float Kd = 1.0; 
    float Ki = 0.000; 
    int MotorA_Speed = 0; 
    int MotorB_Speed = 0; 
    int integral = 0;
    int state;


QTRSensorsRC qtra((unsigned char[]) {A6, A0, A1, A2, A3, A4 ,A5, A7 } , NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS]; 

void setup() { 
  Serial.begin(9600);

  int state = 0;

  pinMode(AIN2, OUTPUT); 
  pinMode(AIN1, OUTPUT); 
  pinMode(PWMA, OUTPUT);
   
  pinMode(BIN2, OUTPUT); 
  pinMode(BIN1, OUTPUT); 
  pinMode(PWMB, OUTPUT);

  pinMode(BUTTON,INPUT);

  
  int i; 
  for (int i = 0; i < 200; i++) 
    { 
    qtra.calibrate(); 
    digitalWrite(13, HIGH); delay(20); 
    
    } 
  
    //digitalWrite(motorPower, LOW);
    digitalWrite(13, LOW); 
    delay(500); 

  ESC.attach(3);//Brushless attach
  ESC.writeMicroseconds(1000);//1000-2500 maxspeed for Brushless
  delay(1000);

  Serial.println(state);

  } 
    
    

 void loop() { 
           
      PRESS = digitalRead(BUTTON);

      switch (PRESS) {

      case HIGH:
      state = 1;
      Serial.println(state);

      ESC.writeMicroseconds(1100);//1000-2500 maxspeed for Brushless
   
      position = qtra.readLine(sensorValues); 

      
      error = position - 3500; 
 
      
      motorSpeed = Kp * error + Kd * (error - lastError)+ Ki * integral; 
      lastError = error;

      MotorA_Speed = A_BaseSpeed - motorSpeed ; 
      MotorB_Speed = B_BaseSpeed + motorSpeed ; 
      MotorA_Speed = constrain(MotorA_Speed, 0, 255); 
      MotorB_Speed = constrain(MotorB_Speed, 0, 255);


      digitalWrite(AIN2, HIGH); 
      digitalWrite(AIN1, LOW); 
      analogWrite(PWMA, MotorA_Speed);
       
      digitalWrite(BIN2, HIGH); 
      digitalWrite(BIN1, LOW); 
      analogWrite(PWMB, MotorB_Speed);


      ESC.writeMicroseconds(1100);//1000-2500 maxspeed for Brushless


       break;

       case LOW:
       analogWrite(PWMA, 0);
       analogWrite(PWMB, 0);

       if (state == 1){

       state=0;
       ESC.writeMicroseconds(0); //stop EDF
       }

       Serial.println(state);
       break;
 

      }
      
  } 
      
      
 //************************ BASE CODE***********\\﻿




