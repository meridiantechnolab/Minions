///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Dancing minion 1
// ver. 6.0    
// Last updated: 29/04/2019
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <NewPing.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

// Ultrasonic Sensor
#define TRIGGER_PIN 9
#define ECHO_PIN 8
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // UltraSonic sensor setup - pins and maximum distance

// Turn and move calibration
//const float K_Right = 1750 / 180;          // Turn right 1 degree, msec
//const float K_Left  = 1750 / 180;          // Turn left 1 degree, msec
const float G_Right = 1.70; // Turn right 1 degree, gyro angle, would ssay 340/180 is 1 (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float G_Left  = -1.70; // Turn left 1 degree, gyro angle (This number [1.88] was derived by finding the angle at which it actually turned 180 and dividing it by 180)
const float K_Forward  = 1770/ 100;        // Move forward 1 cm, msec
const float K_Backwards  = 1785 / 100;     // Move backwards 1 cm, msec
   
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

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was update

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
   UltraSonicActivation();
   RobotMoveForwardSpeed(200, 170, 1770);
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
   Serial.println("Start dancing");
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
      Serial.print("StartAngle: ");
      Serial.print(StartAngle);
      Serial.print(" Angle: ");
      Serial.print(Angle);
      Serial.print(" diff: ");
      Serial.println(diff);
   }
   Serial.println("Robot Stop");
   
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
      Serial.print("StartAngle: ");
      Serial.print(StartAngle);
      Serial.print(" Angle: ");
      Serial.print(Angle);
      Serial.print(" diff: ");
      Serial.println(diff);
   }
   Serial.println("Robot Stop");

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

void setup() {
   MinionInit();

/*   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, LOW);
   analogWrite(MotorPWMB, 200);
   pause(1000);*/
 
//   TurnCalibration();
//   RobotMoveForwardCM(50);

   
//   UltraSonicActivation();
//   RobotTurnRightDegrees(90);
//   RobotStop(1000);  

/*   digitalWrite(MotorDirA, HIGH);
   analogWrite(MotorPWMA, 200);
   digitalWrite(MotorDirB, HIGH);
   analogWrite(MotorPWMB, 200);
*/

}

void loop() {
     RobotMoveForwardCM(50);
     RobotMoveForwardCM(50);
     GyroTurnLeftDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnLeftDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnLeftDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnLeftDegrees(90);
     delay(2000);
     RobotMoveForwardCM(50);
     RobotMoveForwardCM(50);
     GyroTurnRightDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnRightDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnRightDegrees(90);
     RobotMoveForwardCM(50);
     GyroTurnRightDegrees(90);
     delay(2000);
       
/*  LightSensor = analogRead(sensorPin);
  Serial.println(LightSensor);
  delay(500);

//  mpu6050.update();
/*  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
//  Serial.print("\tangle : ");
//  Serial.println(mpu6050.getAngleZ());
//  delay(500);
*/   
}
