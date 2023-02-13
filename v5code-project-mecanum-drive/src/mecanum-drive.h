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

  static void adjustFront(double speed) {
    ChassisLF.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,speed, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,speed, velocityUnits::pct);
  }

  static void autoTurn(double targetDegree) {
    int sign = targetDegree > 0;
    ChassisLF.spin(directionType::fwd,sign *20, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,sign *20, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,sign *-20, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,sign *-20, velocityUnits::pct);
  }

  static void moveFront(double speed) {
        ChassisLF.spin(directionType::fwd, -speed
        , velocityUnits::pct);
        ChassisRR.spin(directionType::fwd, speed
        , velocityUnits::pct);
        ChassisRF.spin(directionType::fwd,-speed
        , velocityUnits::pct);
        ChassisLR.spin(directionType::fwd, speed
        , velocityUnits::pct);
  }

  static void moveBack(double speed) {
      ChassisLF.spin(directionType::fwd, speed
      , velocityUnits::pct);
      ChassisRR.spin(directionType::fwd, -speed
      , velocityUnits::pct);
      ChassisRF.spin(directionType::fwd, speed
      , velocityUnits::pct);
      ChassisLR.spin(directionType::fwd, -speed
      , velocityUnits::pct);
  }

  static void moveRight(double speed) {
        ChassisLF.spin(directionType::fwd, -speed
        , velocityUnits::pct);
        ChassisRR.spin(directionType::fwd,speed
        , velocityUnits::pct);
        ChassisRF.spin(directionType::fwd,speed
        , velocityUnits::pct);
        ChassisLR.spin(directionType::fwd, -speed
        , velocityUnits::pct);
  }

  

  static void stop() {
    ChassisLF.stop();
    ChassisRR.stop();
    ChassisRF.stop();
    ChassisLR.stop();
  }
};