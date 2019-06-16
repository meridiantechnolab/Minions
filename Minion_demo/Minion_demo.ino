////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Minion.h>

//             LHD, RHD, LHU, RHU, LHF, RHF, G_R ,  G_L , K_F     , K_B
Minion minion1(460, 105, 120, 470, 270, 275, 1.70, -1.70, 1770/100, 1785/100);

void setup() {
  // put your setup code here, to run once:
  minion1.start();
  delay(500);
  RobotMoveForwardCM(30);
  delay(1000);
  UltraSonicActivation();
  GyroTurnRightDegrees(90);
  pause(500);
  GyroTurnLeftDegrees(90);
  delay(1000);
  UltraSonicActivation();
  RobotMoveForwardCM(50);
  delay(1000);
  UltraSonicActivation();
  Start();
  delay(1000);
  UltraSonicActivation();
  RobotMoveForwardCM(50);
  GyroTurnLeftDegrees(90);
  RobotMoveForwardCM(50);
  GyroTurnLeftDegrees(90);
  RobotMoveForwardCM(50);
  GyroTurnLeftDegrees(90);
  RobotMoveForwardCM(50);
  GyroTurnLeftDegrees(90);
  delay(1000);
  
  }

void loop() {
}
