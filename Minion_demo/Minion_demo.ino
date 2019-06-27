//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  Minion_demo.ino - Demo minion
//
//  ver. 1.1
//  Last updated: 16/06/2019
//
//
//  14/06/2019 - Added comments
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Minion.h>

//             LHD, RHD, LHU, RHU, LHF, RHF, G_R ,  G_L , K_F     , K_B     , LC
Minion minion1(460, 105, 120, 470, 270, 275, 1.70, -1.70, 1770/100, 1785/100, 990);
  
void Demo (){
  //Init
  minion1.start();
  delay(500);

  //Ultrasonic Activation
  minion1.RobotMoveForwardCM(50);
  delay(500);
  minion1.RobotStop(500);
  minion1.pause(500);

   //Gyro turning
  minion1.UltraSonicActivation();
  delay(500);
  minion1.GyroTurnRightDegrees(90);
  minion1.RobotStop(500);
  minion1.GyroTurnLeftDegrees(90);
  minion1.RobotStop(500);
  
  //Colour Sensor
  minion1.UltraSonicActivation();
  delay(500);
  minion1.RobotMoveForwardCM(50);
  minion1.pause(3000);
  delay(1500);
  minion1.RobotStop(500);

  //Show LED
  minion1.UltraSonicActivation();
  delay(500);
  minion1.start();
  minion1.pause(500);

  //Obstacle avoidance
  minion1.UltraSonicActivation();
  delay(500);
  minion1.RobotMoveForwardCM(100);
  minion1.RobotStop(500);
  minion1.GyroTurnLeftDegrees(45);
  minion1.RobotStop(500);
  minion1.RobotMoveForwardCM(100);
  minion1.RobotStop(500);
  minion1.GyroTurnLeftDegrees(45);
  minion1.RobotStop(500);
  minion1.RobotMoveForwardCM(100);
  minion1.RobotStop(500);
  minion1.GyroTurnLeftDegrees(45);
  minion1.RobotStop(500);
  minion1.RobotMoveForwardCM(100);
  minion1.RobotStop(500);
  minion1.GyroTurnLeftDegrees(45);
  minion1.RobotStop(500);
  minion1.pause(500);
}
void setup() {
  // put your setup code here, to run once:
   Demo();
  
  }

void loop() {
  // put your main code here, to run repeatedly:

}
