/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zhuowz                                                    */
/*    Created:      Mon Feb 06 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// shooterMotorA        motor         10              
// shooterMotorB        motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void setShooterVelocityPct(double percentage) {
  shooterMotorA.setVelocity(percentage, percent);
  shooterMotorB.setVelocity(percentage, percent);
}

void spinShooter(vex::directionType dir) {
  shooterMotorA.spin(dir);
  shooterMotorB.spin(dir);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  setShooterVelocityPct(0.9);
  
  while(1) {
    spinShooter(forward);
  }
}
