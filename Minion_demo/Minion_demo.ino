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
  minion1.start();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  minion1.HandsDown();
  delay(1000);
  minion1.HandsUp();
  delay(1000);
}
