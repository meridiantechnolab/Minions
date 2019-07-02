#include "Minion.h"
#include <ServoDriver.h>
#include <NewPing.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

ServoDriver pwm = ServoDriver();

unsigned long previousMillis = 0;

MPU6050 mpu6050(Wire);


int TRIGGER_PIN = 9;
int ECHO_PIN = 8;
int MAX_DISTANCE = 200;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Motor A
int MotorDirA  = 12;
int MotorPWMA  = 11;

// Motor B
int MotorDirB  = 7;
int MotorPWMB  = 6;

int LED_PIN = 5;

int LightSensorPin = A0;
int LightSensor;

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

int LightCal;

Minion::Minion(int _lHandDown, int _rHandDown, int _lHandUp, int _rHandUp, int _lHandForward, int _rHandForward, float _G_Right, float _G_Left, float _K_Forward, float _K_Backward, int _LightCal) {
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

  LightCal = _LightCal;

}


void Minion::start(){
  //Making the LED off so we know that the robot is not ready
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

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

  //Gyro
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  //LED on saying that the robot is ready
  digitalWrite(LED_PIN, HIGH);

 // UltraSonicActivation();
}

void Minion::UltraSonicActivation() {
   int uS = sonar.ping_cm();
   delay(50);
   while ((uS == 0) || (uS > 30)) {
      uS = sonar.ping_cm();
      delay(50);
   }
   Serial.println("Start dancing");
}

void Minion::pause(int interval){
    int uS = sonar.ping_cm();
    unsigned long currentMillis = millis();
    int Colour = analogRead(LightSensorPin);

    while(currentMillis - previousMillis <= interval){
      currentMillis = millis();
      int uS = sonar.ping_cm();
      int Colour = analogRead(LightSensorPin);
      if ((uS > 0) && (uS < 15)){
        RobotStop(20);

        while ((uS > 0) && (uS < 15)){
          uS = sonar.ping_cm();
          delay(400);
        }
      } else {
        if (Colour > LightCal){
          RobotMoveBackCM(45);
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
   analogWrite(MotorPWMB, 200);
   pause(iTime);
}
void Minion::RobotMoveBackCM(int iCM) {
   int iTime = iCM * K_Backward;
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, 200);
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

//Turn Robot to a gyro angle
void Minion::GyroTurnRightDegrees(int iDegrees) {
  iDegrees = iDegrees * G_Right;
  float StartAngle = 0;
  float Angle = 0;
  float diff = 0;

  mpu6050.update();
  StartAngle = mpu6050.getAngleZ();
  Angle = StartAngle;

  digitalWrite(MotorDirA, LOW);
  analogWrite(MotorPWMA, 200);
  digitalWrite(MotorDirB, HIGH);
  analogWrite(MotorPWMB, 200);

  while ((Angle - StartAngle) < iDegrees) {
     mpu6050.update();
     Angle = mpu6050.getAngleZ();
     diff = Angle - StartAngle;
  }
  RobotStop(100);

}

//Turn Robot to a gyro angle
void Minion::GyroTurnLeftDegrees(int iDegrees) {
  iDegrees = iDegrees * G_Left;
  float StartAngle = 0;
  float Angle = 0;
  float diff = 0;

  mpu6050.update();
  StartAngle = mpu6050.getAngleZ();
  Angle = StartAngle;

  digitalWrite(MotorDirA, HIGH);
  analogWrite(MotorPWMA, 200);
  digitalWrite(MotorDirB, LOW);
  analogWrite(MotorPWMB, 200);

  while ((Angle - StartAngle) > iDegrees) {
     mpu6050.update();
     Angle = mpu6050.getAngleZ();
     diff = Angle - StartAngle;
  }
  RobotStop(100);

}
