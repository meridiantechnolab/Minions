#include <Minion.h>

//             LHD, RHD, LHU, RHU, LHF, RHF, G_R ,  G_L , K_F     , K_B
Minion minion1(460, 105, 120, 470, 270, 275, 1.70, -1.70, 1770/100, 1785/100);

void Hands() {
   minion1.HandsUp();
   minion1.pause(400);
   minion1.RightHandForward();
   minion1.pause(400);

   for (int i=1; i <= 4; i++){
      minion1.RightHandUp();
      minion1.LeftHandForward();
      minion1.pause(400);
      minion1.RightHandForward();
      minion1.LeftHandUp();
      minion1.pause(400);
   }

   minion1.HandsDown();
   minion1.pause(800);
   //RadioActivation();
   minion1.RightHandUp();
   minion1.pause(800);

   for (int i=1; i <= 4; i++){
      minion1.RightHandDown();
      minion1.LeftHandUp();
      minion1.pause(800);
      minion1.RightHandUp();
      minion1.LeftHandDown();
      minion1.pause(800);
   }

   minion1.HandsDown();
   minion1.pause(800);

   for (int j = 1; j <= 3; j++) {
      minion1.GyroTurnRightDegrees(100);
      minion1.RobotStop(500);
      minion1.RightHandUp();
      minion1.pause(400);
      for (int i=1; i <= 2; i++){
         minion1.RightHandDown();
         minion1.LeftHandUp();
         minion1.pause(400);
         minion1.RightHandUp();
         minion1.LeftHandDown();
         minion1.pause(400);
      }
      minion1.HandsDown();
      minion1.pause(800);
   }
   minion1.GyroTurnRightDegrees(100);
   minion1.RobotStop(500);
}

void Happy() {
   minion1.start();
   delay(600);

   // Begining
   minion1.RobotMoveForwardCM(50);
   minion1.RobotMoveForwardCM(50);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.GyroTurnLeftDegrees(90);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.RobotMoveForwardCM(30);
   minion1.RobotStop(500);
   minion1.RightHandUp();
   minion1.pause(500);
   minion1.LeftHandUp();
   minion1.RightHandDown();
   minion1.pause(500);
   minion1.LeftHandDown();
   minion1.RightHandUp();
   minion1.pause(500);
   minion1.LeftHandUp();
   minion1.RightHandDown();
   minion1.pause(500);
   minion1.LeftHandDown();
   minion1.pause(500);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(500);
   minion1.RobotMoveBackCM(50);
   minion1.RobotStop(500);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(100);
   //BluetoothActivation();
   minion1.HandsUp();
   minion1.pause(250);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(500);
   minion1.HandsDown();
   //BluetoothActivation();
   minion1.RobotMoveForwardCM(50);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(2000);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.RobotMoveBackCM(50);
   minion1.RobotStop(100);
   //BluetoothActivation();

   // Turns 7s
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(1000);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(500);

   // Hands 23s
   Hands();
   //Bluetooth Activation();

   // Final moves
   minion1.RobotMoveForwardCM(35);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(1000);
   minion1.RobotMoveBackCM(85);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(1000);
   minion1.RobotMoveForwardCM(35);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(1000);

   // 8 sec
   minion1.GyroTurnLeftDegrees(100);
   minion1.RobotStop(500);
   minion1.RightHandForward();
   minion1.pause(500);
   minion1.LeftHandForward();
   minion1.RightHandDown();
   minion1.pause(500);
   minion1.LeftHandDown();
   minion1.RightHandForward();
   minion1.pause(500);
   minion1.LeftHandUp();
   minion1.pause(500);
   minion1.RightHandUp();
   minion1.LeftHandForward();
   minion1.pause(500);
   minion1.RightHandForward();
   minion1.LeftHandUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(500);
   minion1.GyroTurnRightDegrees(100);
   minion1.RobotStop(500);

}

void setup() {
  Happy();
}

void loop(){
}
