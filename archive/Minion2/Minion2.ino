///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Dancing minion 2
// ver. 5.1    
// Last updated: 3/10/2018
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <NewPing.h>
#include <ServoDriver.h>
#include <SPI.h>

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

// Gyro
MPU6050 mpu6050(Wire);

// Light Sensor
int LightSensorPin = A3;
int LightSensor;

// LED
int LED_PIN = 5;

// will store last time pause was updated
unsigned long previousMillis = 0;        

// Turn and move calibration
//At home
const float G_Right = 1.70; // Turn right 1 degree, gyro angle, would ssay 340/180 is 1 (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float G_Left  = -1.70; // Turn left 1 degree, gyro angle (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float K_Forward  = 1770/ 100;        // Move forward 1 cm, msec
const float K_Backwards  = 1785 / 100;     // Move backwards 1 cm, msec


//Comp
/*const float G_Right = 1.70; // Turn right 1 degree, gyro angle, would ssay 340/180 is 1 (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float G_Left  = -1.70; // Turn left 1 degree, gyro angle (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float K_Forward  = 1770/ 100;        // Move forward 1 cm, msec
const float K_Backwards  = 1785 / 100;     // Move backwards 1 cm, msec
*/

// Turn calibration
void TurnCalibration() {
   UltraSonicActivation();
   pause(1000);
   RobotTurnRightDegrees(340);
   pause(1000);
   RobotTurnLeftDegrees(-340);
   pause(1000);
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

//The function we use to check the ultrasonic values while driving
void pause(int interval){
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

// Move robot forward
void RobotMoveForwardSpeed(int SpeedLeft, int SpeedRight, int iTime) {
   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, SpeedLeft);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, SpeedRight);
   pause(iTime);
}

// Move robot back
void RobotMoveBackSpeed(int SpeedLeft, int SpeedRight, int iTime) {
   digitalWrite(MotorDirA, LOW);
   analogWrite(MotorPWMA, SpeedLeft);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, SpeedRight);
   pause(iTime);
}

// Move robot forward cm
void RobotMoveForwardCM(int iCM) {
   RobotMoveForwardSpeed(200, 170, K_Forward * iCM);
}

// Move robot back cm
void RobotMoveBackCM(int iCM) {
   RobotMoveBackSpeed(200, 170, K_Backwards * iCM);
}

// Init
void MinionInit() {
   pinMode(LED_PIN, OUTPUT);
   digitalWrite(LED_PIN, LOW);
   Serial.begin(9600);

   Wire.begin();
   mpu6050.begin();
   mpu6050.calcGyroOffsets(true);
   digitalWrite(LED_PIN, HIGH);
}

// Turn robot left degrees
void RobotTurnLeftDegrees(int iDegrees) {
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

// Turn robot right degrees
void RobotTurnRightDegrees(int iDegrees) {
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
void GyroTurnRightDegrees(int gDegrees) {
  RobotTurnRightDegrees(gDegrees * G_Right);
  Serial.println(gDegrees * G_Right);
  Serial.println(G_Right);
}

//Turn Robot to a gyro angle
void GyroTurnLeftDegrees(int gDegrees) {
  RobotTurnLeftDegrees(gDegrees * G_Left);
  Serial.println(gDegrees * G_Left);
  Serial.println(G_Left);
}

// Stop robot
void RobotStop(int iTime) {
   analogWrite(MotorPWMA, 0);
   analogWrite(MotorPWMB, 0);
   pause(iTime); 
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
   MinionInit();
   
   // Begining
   RobotMoveForwardCM(50);   
   RobotStop(500);
   HandsUp();
   pause(500);
   HandsDown();
   pause(500);
   GyroTurnLeftDegrees(90);
   RobotStop(500);
   HandsUp();
   pause(500);
   HandsDown();
   pause(500);
   RobotMoveForwardCM(30);     
   RobotStop(500);
   RightHandUp();
   pause(500);
   LeftHandUp();
   RightHandDown();
   pause(500);
   LeftHandDown();
   RightHandUp();
   pause(500);
   LeftHandUp();
   RightHandDown();
   pause(500);
   LeftHandDown();
   pause(500);
   GyroTurnRightDegrees(90);
   RobotStop(500);
   RobotMoveBackCM(50);
   RobotStop(500);
   GyroTurnRightDegrees(90);
   RobotStop(100);
   //BluetoothActivation();
   HandsUp();
   pause(250);
   GyroTurnRightDegrees(90);
   RobotStop(500);
   HandsDown();
   //BluetoothActivation();
   RobotMoveForwardCM(50);  
   RobotStop(500);
   HandsUp();
   pause(2000);
   HandsDown();
   pause(500);
   RobotMoveBackCM(50);
   RobotStop(100);
   //BluetoothActivation();

   // Turns 7s
   HandsUp();
   pause(500);
   HandsDown();
   pause(500);
   GyroTurnRightDegrees(90);
   RobotStop(1000);
   HandsUp();
   pause(500);
   HandsDown();
   pause(500);
   GyroTurnRightDegrees(90);
   RobotStop(500);

   // Hands 23s
   Hands();
   //Bluetooth Activation();
   
   // Final moves
   RobotMoveForwardCM(35);   
   RobotStop(500);
   HandsUp();
   pause(500);
   HandsDown();
   pause(1000);
   RobotMoveBackCM(85);   
   RobotStop(500);
   HandsUp();
   pause(500);
   HandsDown();
   pause(1000);
   RobotMoveForwardCM(35);   
   RobotStop(500);
   HandsUp();
   pause(500);
   HandsDown();
   pause(1000);

   // 8 sec
   GyroTurnLeftDegrees(100);
   RobotStop(500);
   RightHandForward();
   pause(500);
   LeftHandForward();
   RightHandDown();
   pause(500);
   LeftHandDown();
   RightHandForward();
   pause(500);
   LeftHandUp();
   pause(500);
   RightHandUp();
   LeftHandForward();
   pause(500);
   RightHandForward();
   LeftHandUp();
   pause(500);
   HandsDown();
   pause(500);
   GyroTurnRightDegrees(100);
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

   // Servos
   pwm.begin();
   pwm.setPWMFreq(50);  // servos run at 50 Hz
   HandsDown();

// UltraSonicTest();

// UltraSonicActivation(); 
// TurnCalibration();
// MoveCalibration();
// BluetoothActivation();

   Happy();
}

void loop() {
}

