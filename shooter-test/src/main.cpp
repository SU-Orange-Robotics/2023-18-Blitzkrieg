// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// shooterMotorA        motor         11              
// shooterMotorB        motor         12              
// TriggerMotor         motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// shooterMotorA        motor         11              
// shooterMotorB        motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// shooterMotorA        motor         11              
// shooterMotorB        motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// shooterMotorA        motor         11              
// shooterMotorB        motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// shooterMotorA        motor         19              
// shooterMotorB        motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cstdlib>

using namespace vex;


void setShooterVelocityPct(double percentage) {
  shooterMotorA.setVelocity(percentage, velocityUnits::pct);
  shooterMotorB.setVelocity(percentage, velocityUnits::pct);
}

void spinShooter(vex::directionType dir) {
  shooterMotorA.spin(dir);
  shooterMotorB.spin(dir);
}

void triggerInit() {
  int i = 0;
  while(true) {
    if (i > 10) {
      break;
    }
    double position = TriggerMotor.position(degrees);

    TriggerMotor.spin(forward, 10, percent);
    wait(0.3, sec);
    if (abs(position - TriggerMotor.position(degrees)) < 3) {
      Brain.Screen.print(abs(position - TriggerMotor.position(degrees)));
      break;
    }
    i++;
  }

// // dumb init
//   TriggerMotor.spin(forward, 10, percent);
//   wait(0.5, sec);
//   TriggerMotor.stop();

  TriggerMotor.stop();
}

void trigger() {
  double position = TriggerMotor.position(degrees);
  
  TriggerMotor.spinToPosition(position-36,degrees);
  wait(0.5, sec);
  TriggerMotor.spinToPosition(position,degrees);
}

void triggerTest() {
  TriggerMotor.spinToPosition(-36,degrees);
  wait(0.5, sec);
  TriggerMotor.spinToPosition(0,degrees);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  triggerInit();
  setShooterVelocityPct(87.0);

  Brain.Screen.clearScreen();
  
  while(1) {
    // spinShooter(reverse);
    // Brain.Screen.print(shooterMotorA.velocity(percent));


    // trigger();
    // triggerTest();

    wait(20, msec);
  }
}
