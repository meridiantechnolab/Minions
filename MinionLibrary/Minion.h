////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  Minion.h - Library for dancing minions
//
//  ver. 1.1
//  Last updated: 16/06/2019
//
//
//  14/06/2019 - Added comments
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef minion
#define minion

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Minion {

  public:


    Minion(int _lHandDown, int _rHandDown, int _lHandUp, int _rHandUp, int _lHandForward, int _rHandForward, float _G_Right, float _G_Left, float K_Forward, float K_Backward);

    void start();

    void UltraSonicActivation();
    void pause(int interval);
    void RobotStop(int iTime);
    void RobotMoveForwardCM(int iCM);
    void RobotMoveBackCM(int iCM);

    //Left Hand Control
    void LeftHandUp();
    void LeftHandDown();
    void LeftHandForward();

    //Right Hand Control
    void RightHandUp();
    void RightHandDown();
    void RightHandForward();

    //All Hand Control
    void HandsUp();
    void HandsDown();
    void HandsForward();

    //Turning
    void GyroTurnRightDegrees(int iDegrees);
    void GyroTurnLeftDegrees(int iDegrees);

  private:

};

#endif
