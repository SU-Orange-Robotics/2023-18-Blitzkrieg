#pragma once

#include "vex.h"

class MecanumDrive {
  
public:
  
    // basic function to drive to location
  static void driveToLocation(double y, double x, double theta) {
    while(true){
      // gets current location and assigns them
      new_x = (odometry::getLocation()[0]);
      new_y = (odometry::getLocation()[1]);
      // if the new location - intitial location >= 1 break, then stop
      if (abs(x_new - x) >= 2 && abs(y_new - y) >= 2){
        break;
      }
      // else drive to position
      else{
        drive(y, x, theta);
      }
    }
    // loop breaks and motors stop
    stop();
  }
  
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

  static void drive(double y, double x, double theta) {
    x /= 100;
    y /= 100;
    theta /= 100;
    
    x = pow(x, 2) * ((x > 0) ? 1 : -1);
    y = pow(y, 2) * ((y > 0) ? 1 : -1);
    theta = pow(theta, 2) * ((theta > 0) ? 1 : -1);

    x *= 100;
    y *= 100;
    theta *= 100;

    ChassisLF.spin(directionType::fwd, -y - x - theta, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,  y + x - theta, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd, -y + x + theta, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,  y - x + theta, velocityUnits::pct);
  }

  static void stop() {
    ChassisLF.stop();
    ChassisRR.stop();
    ChassisRF.stop();
    ChassisLR.stop();
  }
};
