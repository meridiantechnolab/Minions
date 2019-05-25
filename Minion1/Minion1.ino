///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Dancing minion 1
// ver. 5.1
// Last updated: 29/09/2018
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <NewPing.h>
#include <ServoDriver.h>
#include <RH_ASK.h>
#include <SPI.h>

// Radio reciever - pin 3, transmitter - pin 4
RH_ASK radio(2000, 3, 4);

// Servo control
ServoDriver pwm = ServoDriver();

// Ultrasonic Sensor
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // UltraSonic sensor - setup of pins and maximum distance

// Motor A
const int MotorDirA  = 8;
const int MotorPWMA  = 9;

// Motor B
const int MotorDirB  = 7;
const int MotorPWMB  = 6;

// Turn calibration, sec to turn 1 degree
const float K_Right = 1700 / 180;
const float K_Left  = 1300 / 180;

// Turn calibration
void TurnCalibration() {
   HandsDown();
//   UltraSonicActivation();
   delay(1000);
   RobotTurnRight(200, 1700);
   RobotStop(1000);
   RobotTurnLeft(200, 1300);
   RobotStop(1000);
}

void setup(){
   // DC motors
   pinMode(MotorDirA, OUTPUT);
   pinMode(MotorPWMA, OUTPUT);
   pinMode(MotorDirB, OUTPUT);
   pinMode(MotorPWMB, OUTPUT);

   // Ultrasonic Sensor
   Serial.begin(9600);

   // Radio receiver/transmitter
   if (!radio.init()) Serial.println("init failed");

   // Servos
   pwm.begin();
   pwm.setPWMFreq(50);  // servos run at 50 Hz

   UltraSonicActivation();
   SendStart();
   HandsTest();
}

// Ultrasonic sensor test
void UltraSonicTest() {
   int uS = sonar.ping_cm();
   delay(50);

   Serial.print("Ultrasonic test: ");
   Serial.print(uS);
   Serial.println("cm");
}

// Ultrasonic activation
void UltraSonicActivation() {
   int uS = sonar.ping_cm();
   delay(50);
   while ((uS == 0) || (uS > 30)) {
      uS = sonar.ping_cm();
      Serial.print("Activation: ");
      Serial.print(uS);
      Serial.println("cm");
      delay(50);
   }
   Serial.println("US: Start dancing");
}

// Tell another minion to start dancing
void SendStart() {
   const char *msg = "start";
   radio.send((uint8_t *)msg, strlen(msg));
   radio.waitPacketSent();
   delay(50);
   radio.send((uint8_t *)msg, strlen(msg));
   radio.waitPacketSent();
   Serial.println("RF: Sent start");
}

// Move robot forward
void RobotMoveForward(int iSpeed, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime);
}

// Move robot back
void RobotMoveBack(int iSpeed, int iTime) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime); 
}

// Turn robot Left
void RobotTurnLeft(int iSpeed, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime); 
}

// Turn robot left degrees
void RobotTurnLeftDegrees(int iDegrees) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, 200);
   delay(K_Left * iDegrees); 
}

// Turn robot right
void RobotTurnRight(int iSpeed, int iTime) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime);
}

// Turn robot right degrees
void RobotTurnRightDegrees(int iDegrees) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, 200);
   delay(K_Right * iDegrees);
}

// Smooth turn robot
void RobotSmoothTurn(int iSpeedA, int iSpeedB, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, iSpeedA);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, iSpeedB);
   delay(iTime);
}

// Stop robot
void RobotStop(int iTime) {
   analogWrite(MotorPWMA, 0);
   analogWrite(MotorPWMB, 0);
   delay(iTime); 
}

// Left hand up
void LeftHandUp() {
   pwm.setPWM(1, 0, 150);
}

// Left hand down
void LeftHandDown() {
   pwm.setPWM(1, 0, 600);
}

// Left hand forward
void LeftHandForward() {
   pwm.setPWM(1, 0, 320);
}

// Right hand up
void RightHandUp() {
   pwm.setPWM(0, 0, 600);
}

// Right hand down
void RightHandDown() {
   pwm.setPWM(0, 0, 150);
}

// Right hand forward
void RightHandForward() {
   pwm.setPWM(0, 0, 350);
}

// Both hands up
void HandsUp() {
   LeftHandUp();
   RightHandUp();
}

// Both hands down
void HandsDown() {
   LeftHandDown();
   RightHandDown();
}

// Both hands forward
void HandsForward() {
   LeftHandForward();
   RightHandForward();
}

// Hands test
void HandsTest() {
   HandsUp();
   delay(800);
   HandsDown();
   delay(800);
   HandsForward();
   delay(800);
}

// Hands solo
void Hands() {
   HandsUp();
   delay(400);
   RightHandForward();
   delay(400);

   for (int i=1; i <= 4; i++){
      RightHandUp();
      LeftHandForward();
      delay(400);
      RightHandForward();
      LeftHandUp();
      delay(400);
   }

   HandsDown();
   delay(800);
   RightHandUp();
   delay(800);

   for (int i=1; i <= 4; i++){
      RightHandDown();
      LeftHandUp();
      delay(800);
      RightHandUp();
      LeftHandDown();
      delay(800);
   }

   HandsDown();
   delay(800);

   for (int j = 1; j <= 3; j++) {
      RobotTurnRightDegrees(90);
      RobotStop(500);
      RightHandUp();
      delay(400);
      for (int i=1; i <= 2; i++){
         RightHandDown();
         LeftHandUp();
         delay(400);
         RightHandUp();
         LeftHandDown();
         delay(400);
      }
      HandsDown();
      delay(800);
   }   
   RobotTurnRightDegrees(90);
   RobotStop(500);
}

// Happy dance routine
void Happy() {
   HandsDown();
//   UltraSonicActivation();

   // Zig Zag
   RobotMoveForward(200, 1000);   
   RobotStop(500);
   RobotTurnRightDegrees(145);
   RobotStop(500);
   RobotMoveForward(200, 2500);   
   RobotStop(500);
   RobotTurnLeftDegrees(135);
   RobotStop(500);
   RobotMoveForward(200, 1800); 
   RobotStop(500);

   // Back to the center
   RobotMoveBack(200, 800);
   RobotStop(500);
   RobotTurnRightDegrees(90);
   RobotStop(500);
   RobotMoveBack(200, 700);
   RobotStop(500);
   RobotTurnLeftDegrees(90);
   RobotStop(500);

   // Turns 12s
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(1000);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(1000);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(1000);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(1000);

   // Hands 23s
   Hands();

   // Final moves
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveBack(200, 1400);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveBack(200, 1400);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnRightDegrees(90);
   RobotStop(1000);
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveBack(200, 1400);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotMoveForward(200, 700);   
   RobotStop(100);
   HandsUp();
   delay(400);
   HandsDown();
   delay(400);
   RobotTurnLeftDegrees(90);
   RobotStop(1000);

   HandsDown();
}

void loop() {
   RobotMoveForward(200, 500);
   RobotStop(500);
   RobotTurnRightDegrees(90);
   RobotStop(500);
}
   
