#pragma once

#include "vex.h"
//#include "robot-config.h"
#include "odometry.h"

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

    //if (x + y + theta >= 3) {
    ChassisLF.spin(directionType::fwd, -y - x - theta, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,  y + x - theta, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd, -y + x + theta, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,  y - x + theta, velocityUnits::pct);
    //}
  }

  static void drivePure(double y, double x, double theta) {
    ChassisLF.spin(directionType::fwd, -y - x - theta, velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,  y + x - theta, velocityUnits::pct);
    ChassisRF.spin(directionType::fwd, -y + x + theta, velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,  y - x + theta, velocityUnits::pct);
  }
  
  static void turnToHeading(double lowBound, double uppBound, bool dir, Odometry& odo) { //dir = true --> counterclockwise
    while (true) {
      double currHeading = fmod(odo.getTheta(), 2*3.14159);
      if (currHeading >= lowBound && currHeading <= uppBound) {
        break;
      }
      drivePure(0, 0, dir ? -50 : 50);
    }
  }

  static void shootToNearGoal(Odometry& odo) {
    double botX = odo.getX();
    double botY = odo.getY();
    double goalX = 0;
    double goalY = 0;

    double goalHeading = tan((botY - goalY) / (botX - goalX));

    goalHeading = goalHeading < 0 ? goalHeading += 2*3.14159 : goalHeading;

    turnToHeading(goalHeading - 3.14159/24, goalHeading + 3.14159/24, false, odo);
  }
  /*
  static void shootToFarGoal(Odometry& odo) {
    double botX = odo.getX();
    double botY = odo.gety();
    double goalX = 0;
    double goalY = 0;

    double goalHeading = tan((botY - goalY) / (botX - goalX));

    turnToHeading(goalHeading - 3.14159/30, goalHeading + 3.14159/30, false, odo);
  }*/

  static void stop() {
    ChassisLF.stop();
    ChassisRR.stop();
    ChassisRF.stop();
    ChassisLR.stop();
  }
};