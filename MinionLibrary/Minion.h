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

    void pause(int interval);
    void RobotStop(int iTime);
    void RobotMoveForwardCM(int iCM);
    void RobotMoveBackwardCM(int iCM);

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

  private:

};

#endif
