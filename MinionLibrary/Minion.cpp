#include "Minion.h"
#include <ServoDriver.h>
// #include <NewPing.h>
// #include <MPU6050_tockn.h>
// #include "../ServoCOntrol/ServoDriver.h"

ServoDriver pwm = ServoDriver();

int lHandDown;
int rHandDown;
int lHandUp;
int rHandUp;
int lHandForward;
int rHandForward;

float G_Right; 
float G_Left;
float K_Forward;
float K_Backwards;


Minion::Minion(int _lHandDown, int _rHandDown, int _lHandUp, int _rHandUp, int _lHandForward, int _rHandForward, float G_Right, float G_Left, float K_Forward, float K_Backwards){
  lHandDown = _lHandDown;
  rHandDown = _rHandDown;
  lHandUp = _lHandUp;
  rHandUp = _rHandUp;
  lHandForward = _lHandForward;
  rHandForward = _rHandForward;
}


void Minion::start(){
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}




// void Minion::pause(int interval) {
//
//   int uS = sonar.ping_cm();
//   unsigned long currentMillis = millis();
//
//   while(currentMillis - previousMillis <= interval){
//     currentMillis = millis();
//     int uS = sonar.ping_cm();
//     if ((uS > 0) && (uS < 12)){
//       // RobotStop(20);
//
//       while ((uS > 0) && (uS < 12)){
//         uS = sonar.ping_cm();
//         delay(10);
//       }
//     }
//
//
//   }
//   previousMillis = currentMillis;
// }

// void Minion::MotorStop(int iTime) {
//    analogWrite(MotorPWMA, 0);
//    analogWrite(MotorPYMB, 0);
//    pause(iTime);
// }
//
// void Minion::RobotMoveForwardSpeed(int SpeedLeft, int SpeedRight, int iTime) {
//    digitalWrite(MotorDirA, HIGH);
//    analogWrite(MotorPWMA, SpeedLeft);
//    digitalWrite(MotorDirB, HIGH);
//    analogWrite(MotorPWMB, SpeedRight);
//    pause(iTime);
// }

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
