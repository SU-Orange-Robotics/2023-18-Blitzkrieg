#pragma once

#include "vex.h"

class MecanumDrive {
  
public:
  static void adjustLeft(double speed) {
    ChassisLF.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,-speed, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,-speed, velocityUnits::pct);
    // wait(0.5, sec);
    // stop();
  }

  static void adjustRight(double speed) {
    ChassisLF.spin(directionType::fwd,-speed, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,-speed, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,speed, velocityUnits::pct);
    // wait(0.5, sec);
    // stop();
  }

  static void stop() {
    ChassisLF.stop();
    ChassisRR.stop();
    ChassisRF.stop();
    ChassisLR.stop();
  }
};