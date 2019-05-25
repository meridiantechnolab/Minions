///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Dancing minion 2
// ver. 5.1    
// Last updated: 3/10/2018
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
#define TRIGGER_PIN 9
#define ECHO_PIN 8
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // UltraSonic sensor setup - pins and maximum distance
   
// Motor A
const int MotorDirA  = 12;
const int MotorPWMA  = 11;

// Motor B
const int MotorDirB  = 7;
const int MotorPWMB  = 6;

// Turn and move calibration
//At home
const float K_Right = 1750 / 180;          // Turn right 1 degree, msec
const float K_Left  = 1750 / 180;          // Turn left 1 degree, msec
const float K_Forward  = 1770/ 100;        // Move forward 1 cm, msec
const float K_Backwards  = 1785 / 100;     // Move backwards 1 cm, msec


//Comp
/*const float K_Right = 1800 / 200;          // Turn right 1 degree, msec
const float K_Left  = 1500 / 200;          // Turn left 1 degree, msec
const float K_Forward  = 1770/ 100;        // Move forward 1 cm, msec
const float K_Backwards  = 1785 / 100;     // Move backwards 1 cm, msec
*/
// Turn calibration
void TurnCalibration() {
   HandsDown();
   UltraSonicActivation();
   delay(1000);
   RobotTurnRight(200, 1600);
   RobotStop(1000);
   RobotTurnLeft(200, 1500);
   RobotStop(1000);
}

// Move calibration
void MoveCalibration() {
   HandsDown();
   UltraSonicActivation();
   RobotMoveForwardSpeed(200, 170, 1900);
   RobotStop(1000);
   RobotMoveBackSpeed(200, 170, 1785);
   RobotStop(1000);
}

// Move robot forward
void RobotMoveForwardSpeed(int SpeedLeft, int SpeedRight, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, SpeedLeft);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, SpeedRight);
   delay(iTime);
}

// Move robot back
void RobotMoveBackSpeed(int SpeedLeft, int SpeedRight, int iTime) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, SpeedLeft);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, SpeedRight);
   delay(iTime);
}

// Move robot forward cm
void RobotMoveForwardCM(int iCM) {
   RobotMoveForwardSpeed(200, 190, K_Forward * iCM);
}

// Move robot back cm
void RobotMoveBackCM(int iCM) {
   RobotMoveBackSpeed(200, 160, K_Backwards * iCM);
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
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime); 
}

// Turn robot left degrees
void RobotTurnLeftDegrees(int iDegrees) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, 200);
   delay(K_Left * iDegrees); 
}

// Turn robot right
void RobotTurnRight(int iSpeed, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, iSpeed);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, iSpeed);
   delay(iTime);
}

// Turn robot right degrees
void RobotTurnRightDegrees(int iDegrees) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, 200);
   delay(K_Right * iDegrees);
}

// Stop robot
void RobotStop(int iTime) {
   analogWrite(MotorPWMA, 0);
   analogWrite(MotorPWMB, 0);
   delay(iTime); 
}

// Right hand up
void RightHandUp() {
   pwm.setPWM(1, 0, 600);
}

// Right hand down
void RightHandDown() {
   pwm.setPWM(1, 0, 100);
}

// Right hand Forward
void RightHandForward() {
   pwm.setPWM(1, 0, 285);
}

// Left hand up
void LeftHandUp() {
   pwm.setPWM(0, 0, 150);
}

// Left hand down
void LeftHandDown() {
   pwm.setPWM(0, 0, 460);
}

// Left hand forward
void LeftHandForward() {
   pwm.setPWM(0, 0, 300);
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

// Radio activation
void RadioActivation() {
   uint8_t buf[5];
   uint8_t buflen = 5;
   String st = "     ";

   while (st.substring(0, 5) != "start") {   
      if (radio.recv(buf, &buflen))
      {
        st = (char*)buf;
      }
      delay(50);
   }
   Serial.println("RF: Start dancing");
}

// Hands
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
   RadioActivation();
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
      RobotTurnRightDegrees(100);
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
   RobotTurnRightDegrees(100);
   RobotStop(500);
}

// Happy dance routine
void Happy() {
   // Begining
   RobotMoveForwardCM(50);   
   RobotStop(500);
   HandsUp();
   delay(500);
   HandsDown();
   delay(500);
   RobotTurnLeftDegrees(100);
   RobotStop(500);
   HandsUp();
   delay(500);
   HandsDown();
   delay(500);
   RobotMoveForwardCM(30);     
   RobotStop(500);
   RightHandUp();
   delay(500);
   LeftHandUp();
   RightHandDown();
   delay(500);
   LeftHandDown();
   RightHandUp();
   delay(500);
   LeftHandUp();
   RightHandDown();
   delay(500);
   LeftHandDown();
   delay(500);
   RobotTurnRightDegrees(90);
   RobotStop(500);
   RobotMoveBackCM(50);
   RobotStop(500);
   RobotTurnRightDegrees(90);
   RobotStop(100);
   RadioActivation();
   HandsUp();
   delay(250);
   RobotTurnRightDegrees(90);
   RobotStop(500);
   HandsDown();
   RadioActivation();
   RobotMoveForwardCM(50);  
   RobotStop(500);
   HandsUp();
   delay(2000);
   HandsDown();
   delay(500);
   RobotMoveBackCM(50);
   RobotStop(100);
   RadioActivation();

   // Turns 7s
   HandsUp();
   delay(500);
   HandsDown();
   delay(500);
   RobotTurnRightDegrees(90);
   RobotStop(1000);
   HandsUp();
   delay(500);
   HandsDown();
   delay(500);
   RobotTurnRightDegrees(90);
   RobotStop(500);

   // Hands 23s
   Hands();
   RadioActivation();
   
   // Final moves
   RobotMoveForwardCM(35);   
   RobotStop(500);
   HandsUp();
   delay(500);
   HandsDown();
   delay(1000);
   RobotMoveBackCM(85);   
   RobotStop(500);
   HandsUp();
   delay(500);
   HandsDown();
   delay(1000);
   RobotMoveForwardCM(35);   
   RobotStop(500);
   HandsUp();
   delay(500);
   HandsDown();
   delay(1000);

   // 8 sec
   RobotTurnLeftDegrees(100);
   RobotStop(500);
   RightHandForward();
   delay(500);
   LeftHandForward();
   RightHandDown();
   delay(500);
   LeftHandDown();
   RightHandForward();
   delay(500);
   LeftHandUp();
   delay(500);
   RightHandUp();
   LeftHandForward();
   delay(500);
   RightHandForward();
   LeftHandUp();
   delay(500);
   HandsDown();
   delay(500);
   RobotTurnRightDegrees(100);
   RobotStop(500);
   
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
   HandsDown();

//   UltraSonicTest();

//    UltraSonicActivation(); 
//    TurnCalibration();
//  MoveCalibration();
   RadioActivation();
   Happy();
}

void loop() {
}

