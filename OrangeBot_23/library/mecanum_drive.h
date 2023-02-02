#pragma once

#include "vex.h"

class MeccanumDrive {
private:
  double wheelSize = 4; // inches, just an example
  vex::motor leftFront, leftBack, rightFront, rightBack;

public:
  // Constructor
  MeccanumDrive(vex::motor& leftFront, vex::motor& leftBack, vex::motor& rightFront, vex::motor& rightBack, double wheelSize = 4) {
    this->leftFront = leftFront;
    this->leftBack = leftBack;
    this->rightFront = rightFront;
    this->rightBack = rightBack;
    this->wheelSize = wheelSize;
  }

  void spin(vex::controller& Controller1) {
    leftFront.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);
    leftBack.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);
    rightFront.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);
    rightBack.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);

  }


  // TODO: write some functions that makes the drive perform actions
  

};


