////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  Minion1.ino - Dancing Minion 1
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

// IR
int IR_RECV_PIN = 3;

//             LHD, RHD, LHU, RHU, LHF, RHF, G_R ,  G_L , K_F     , K_B     , LC
Minion minion1(460, 105, 120, 470, 270, 275, 1.70, -1.70, 1770/100, 1785/100, 990);

void IR_Activation() {
  while (digitalRead(IR_RECV_PIN) == 1) {
  }  
  Serial.println("IR Start dancing...");
}

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
   IR_Activation();

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
   delay(1200);
   minion1.HandsUp();
   minion1.pause(250);
   minion1.GyroTurnRightDegrees(90);
   minion1.RobotStop(500);
   minion1.HandsDown();
   //BluetoothActivation();
   delay(1000);
   minion1.RobotMoveForwardCM(50);
   delay(300);
   minion1.RobotStop(100);
   delay(500);
   minion1.HandsUp();
   delay(2000);
   minion1.HandsDown();
   delay(500);
   minion1.RobotMoveBackCM(50);
   delay(300);
   minion1.RobotStop(100);
   //BluetoothActivation();
   delay(1000);

   // Turns 7s
   minion1.HandsUp();
   delay(500);
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
   delay(1000);

   // Final moves
   minion1.RobotMoveForwardCM(40);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(1000);
   minion1.RobotMoveBackCM(50);
   minion1.RobotStop(500);
   delay(1000);
   minion1.HandsUp();
   delay(700);
   minion1.HandsDown();
   minion1.pause(1000);
   minion1.RobotMoveForwardCM(50);
   minion1.RobotStop(500);
   minion1.HandsUp();
   minion1.pause(500);
   minion1.HandsDown();
   minion1.pause(1000);
   delay(000);
   
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
   minion1.HandsForward();
   minion1.pause(200);
   delay(50);
   minion1.HandsUp();
   delay(150);
   minion1.HandsDown();
   delay(50);
   minion1.HandsUp();
   delay(150);
   minion1.HandsDown();
   delay(50);
   minion1.HandsUp();
   delay(100);
   minion1.HandsDown();
   delay(50);
   minion1.HandsUp();
   delay(100);
   minion1.HandsDown();
   delay(50);
   minion1.HandsUp();
   delay(50);
   minion1.HandsDown();
   delay(50);
   minion1.HandsUp();
   delay(50);
   minion1.HandsDown();
   

}

void setup() {
   pinMode(IR_RECV_PIN, INPUT);
   Happy();
}

void loop(){
}

