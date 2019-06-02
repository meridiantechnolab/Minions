#include "Minion.h"
#include <ServoDriver.h>
#include <NewPing.h>
// #include <MPU6050_tockn.h>
// #include "../ServoCOntrol/ServoDriver.h"

ServoDriver pwm = ServoDriver();

unsigned long previousMillis = 0;



// Could define these variables when instatiating the object minion in the main code
int TRIGGER_PIN = 11;
int ECHO_PIN = 12;
int MAX_DISTANCE = 200;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Motor A
int MotorDirA  = 8;
int MotorPWMA  = 9;

// Motor B
int MotorDirB  = 7;
int MotorPWMB  = 6;

// Everything above this and below the comment that talks about this, can be put into instatiation of the minion object in the main code



// Tells the Servo Motors how far to turn
int lHandDown;
int rHandDown;
int lHandUp;
int rHandUp;
int lHandForward;
int rHandForward;

// Used to turn and move forward, Passed in through the instatiation of the minion object
float G_Right;
float G_Left;
float K_Forward;
float K_Backward;


Minion::Minion(int _lHandDown, int _rHandDown, int _lHandUp, int _rHandUp, int _lHandForward, int _rHandForward, float _G_Right, float _G_Left, float _K_Forward, float _K_Backward){
  lHandDown = _lHandDown;
  rHandDown = _rHandDown;
  lHandUp = _lHandUp;
  rHandUp = _rHandUp;
  lHandForward = _lHandForward;
  rHandForward = _rHandForward;

  G_Right = _G_Right;
  G_Left = _G_Left;
  K_Forward = _K_Forward;
  K_Backward = _K_Backward;

}


void Minion::start(){

  // DC Motors
  pinMode(MotorDirA, OUTPUT);
  pinMode(MotorPWMA, OUTPUT);
  pinMode(MotorDirB, OUTPUT);
  pinMode(MotorPWMB, OUTPUT);

  // Ultrasonic Sensor
  Serial.begin(9600);

  //Servo Motor
  pwm.begin();
  pwm.setPWMFreq(50);
  HandsDown();
  delay(500);
}

void Minion::pause(int interval){
    int uS = sonar.ping_cm();
    unsigned long currentMillis = millis();

    while(currentMillis - previousMillis <= interval){
      currentMillis = millis();
      int uS = sonar.ping_cm();
      if ((uS > 0) && (uS < 15)){
        RobotStop(20);

        while ((uS > 0) && (uS < 15)){
          uS = sonar.ping_cm();
          delay(10);
        }
      }
     }
    previousMillis = currentMillis;
}

void Minion::RobotStop(int iTime) {
   analogWrite(MotorPWMA, 0);
   analogWrite(MotorPWMB, 0);
   pause(iTime);
}


void Minion::RobotMoveForwardCM(int iCM) {
   int iTime = iCM * K_Forward;
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, 170);
   pause(iTime);
}
void Minion::RobotMoveBackwardCM(int iCM) {
   int iTime = iCM * K_Backward;
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, 170);
   pause(iTime);
}

void Minion::LeftHandUp(){
  pwm.setPWM(1, 0, lHandUp);
}

void Minion::LeftHandDown(){
  pwm.setPWM(1, 0, lHandDown);
}

void Minion::LeftHandForward(){
  pwm.setPWM(1, 0, lHandForward);
}

void Minion::RightHandUp() {
  pwm.setPWM(0, 0, rHandUp);
}

void Minion::RightHandDown() {
  pwm.setPWM(0, 0, rHandDown);
}

void Minion::RightHandForward() {
  pwm.setPWM(0, 0, rHandForward);
}

void Minion::HandsUp() {
  LeftHandUp();
  RightHandUp();
}

void Minion::HandsDown() {
  LeftHandDown();
  RightHandDown();
}

void Minion::HandsForward() {
  LeftHandForward();
  RightHandForward();
}
