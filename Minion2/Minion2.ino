////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        
//
//  Minion2.ino - Dancing Minion 2
//
//  ver. 5.2
//  Last updated: 02/07/2019
//
//
//  02/07/2019 - Added IR communication
//  14/06/2019 - Added comments
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Minion.h>
#include <IRremote.h>
 
IRsend irsend;

//             LHD, RHD, LHU, RHU, LHF, RHF, G_R ,  G_L , K_F     , K_B     , LC
Minion minion2(450, 105, 150, 490, 300, 275, 1.70, -1.70, 1770/100, 1785/100, 990);

void IR_send() {
   irsend.sendRC5(0x2, 8);
   delay(100);
   irsend.sendRC5(0x3, 8); 
}

void Hands() {
   minion2.HandsUp();
   minion2.pause(400);
   minion2.RightHandForward();
   minion2.pause(400);

   for (int i=1; i <= 4; i++){
      minion2.RightHandUp();
      minion2.LeftHandForward();
      minion2.pause(400);
      minion2.RightHandForward();
      minion2.LeftHandUp();
      minion2.pause(400);
   }

   minion2.HandsDown();
   minion2.pause(800);
   //RadioActivation();
   minion2.RightHandUp();
   minion2.pause(800);

   for (int i=1; i <= 4; i++){
      minion2.RightHandDown();
      minion2.LeftHandUp();
      minion2.pause(800);
      minion2.RightHandUp();
      minion2.LeftHandDown();
      minion2.pause(800);
   }

   minion2.HandsDown();
   minion2.pause(800);

   for (int j = 1; j <= 3; j++) {
      minion2.GyroTurnRightDegrees(100);
      minion2.RobotStop(500);
      minion2.RightHandUp();
      minion2.pause(400);
      for (int i=1; i <= 2; i++){
         minion2.RightHandDown();
         minion2.LeftHandUp();
         minion2.pause(400);
         minion2.RightHandUp();
         minion2.LeftHandDown();
         minion2.pause(400);
      }
      minion2.HandsDown();
      minion2.pause(800);
   }
   minion2.GyroTurnRightDegrees(45);
   minion2.RobotStop(500);
}

void Happy() {
   minion2.start();
   minion2.UltraSonicActivation();
   delay(500);
   IR_send();

   // Begining
   minion2.RobotMoveForwardCM(50);
   minion2.RobotMoveForwardCM(50);
   minion2.RobotStop(500);
   minion2.HandsUp();
   delay(500);
   minion2.HandsDown();
   delay(500);
   minion2.GyroTurnRightDegrees(90);
   minion2.RobotStop(500);
   minion2.HandsUp();
   delay(500);
   minion2.HandsDown();
   delay(500);
   minion2.RobotMoveForwardCM(30);
   minion2.RobotMoveForwardCM(30);
   minion2.RobotStop(500);
   minion2.RightHandUp();
   delay(400);
   minion2.LeftHandUp();
   minion2.RightHandDown();
   delay(400);
   minion2.LeftHandDown();
   minion2.RightHandUp();
   delay(400);
   minion2.LeftHandUp();
   minion2.RightHandDown();
   delay(400);
   minion2.LeftHandDown();
   delay(500);
   minion2.GyroTurnLeftDegrees(90);
   minion2.RobotStop(500);
   minion2.RobotMoveBackCM(50);
   minion2.RobotStop(500);
   minion2.GyroTurnLeftDegrees(90);
   minion2.RobotStop(100);
   //BluetoothActivation();
   delay(900);
   minion2.HandsUp();
   delay(250);
   minion2.GyroTurnLeftDegrees(90);
   minion2.RobotStop(500);
   minion2.HandsDown();
   //BluetoothActivation();
   delay(1000);
   minion2.RobotMoveForwardCM(100);
   delay(300);
   minion2.RobotStop(100);
   delay(500);
   minion2.HandsUp();
   delay(2000);
   minion2.HandsDown();
   delay(500);
   minion2.RobotMoveBackCM(50);
   minion2.RobotMoveBackCM(50);
   minion2.RobotStop(100);
   //BluetoothActivation();
   delay(1000);

   // Turns 7s
   minion2.HandsUp();
   delay(500);
   minion2.HandsDown();
   delay(500);
   minion2.GyroTurnRightDegrees(90);
   minion2.RobotStop(1000);
   minion2.HandsUp();
   delay(500);
   minion2.HandsDown();
   delay(500);
   minion2.GyroTurnRightDegrees(90);
   minion2.RobotStop(500);

   // Hands 23s
   Hands();
   //Bluetooth Activation();
   delay(1000);

   // Final moves
   minion2.RobotMoveBackCM(40);
   minion2.RobotMoveBackCM(40);
   minion2.RobotStop(500);
   minion2.HandsUp();
   delay(500);
   minion2.HandsDown();
   delay(1000);
   minion2.RobotMoveForwardCM(100);
   minion2.RobotMoveForwardCM(100);
   minion2.RobotStop(500);
   delay(1500);
   minion2.HandsUp();
   delay(700);
   minion2.HandsDown();
   delay(1000);
   minion2.RobotMoveBackCM(50);
   minion2.RobotMoveBackCM(50);
   minion2.RobotStop(500);
   minion2.HandsUp();
   delay(1000);
   minion2.HandsDown();
   delay(1000);
   
   // 8 sec
   minion2.GyroTurnLeftDegrees(100);
   minion2.RobotStop(500);
   minion2.RightHandForward();
   delay(500);
   minion2.LeftHandForward();
   minion2.RightHandDown();
   delay(500);
   minion2.LeftHandDown();
   minion2.RightHandForward();
   delay(500);
   minion2.LeftHandUp();
   delay(500);
   minion2.RightHandUp();
   minion2.LeftHandForward();
   delay(500);
   minion2.RightHandForward();
   minion2.LeftHandUp();
   delay(500);
   minion2.HandsDown();
   delay(500);
   minion2.GyroTurnRightDegrees(100);
   minion2.RobotStop(500);
   minion2.HandsForward();
   delay(250);
   minion2.HandsUp();
   delay(150);
   minion2.HandsDown();
   delay(50);
   minion2.HandsUp();
   delay(150);
   minion2.HandsDown();
   delay(50);
   minion2.HandsUp();
   delay(100);
   minion2.HandsDown();
   delay(50);
   minion2.HandsUp();
   delay(100);
   minion2.HandsDown();
   delay(50);
   minion2.HandsUp();
   delay(50);
   minion2.HandsDown();
   delay(50);
   minion2.HandsUp();
   delay(50);
   minion2.HandsDown();
   

}

void setup() {
   Happy();
}

void loop(){
}
