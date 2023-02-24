#pragma once

#include "vex.h"
//#include "robot-config.h"
#include "odometry.h"
#include <cmath>
#include <iostream>

double calculateDistance(double x1, double x2, double y1, double y2) {
  return pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2);
}

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

  static void moveLeft(double speed) {
    ChassisLF.spin(directionType::fwd, speed
    , velocityUnits::pct);
    ChassisRR.spin(directionType::fwd, -speed
    , velocityUnits::pct);
    ChassisRF.spin(directionType::fwd, -speed
    , velocityUnits::pct);
    ChassisLR.spin(directionType::fwd, speed
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

  static double getTarget(double target, Odometry& odo) {
    double currHeading = fmod(odo.getTheta(), 2 * M_PI); // gets angle and then restricts it to a fixed range
    if (abs(currHeading) > M_PI) { //converts a (0 to 2pi) value to a (-pi to pi) value
      currHeading -= (2 * M_PI) * (currHeading > 0 ? 1 : -1);
    }
    double targetPos = odo.getTheta() + (target - currHeading) * -1;
    return targetPos;
  }
  
  static void turnToHeading(double targetHeading, Odometry& odo) { //dir = true --> counterclockwise
    double targetAngle = getTarget(targetHeading, odo);
    while (odo.getTheta() < (targetAngle - 0.05) || odo.getTheta() > (targetAngle + 0.05)) {
      //drivePure(0, 0, (targetAngle > odo.getTheta()) ? 20 : -20);
      adjustRight(targetAngle > odo.getTheta() ? 20 : -20);
      //targetAngle = getTarget(targetHeading, odo);
    }
    stop();
  }

  // simply drive to a certain location by diriving forward, only temporary solution
  // basic function to drive to location, assume already facing the location
  static void driveToLocation(double x, double y, Odometry& odo, double speed) {
    // stage 1: turn to that location
    turnTowardsLocation(x, y, odo);

    // stage 2: drive forward
    while(true){
      odo.updateOdometry();
      odo.printLocation();
      // gets current location and assigns them
      double x_new = odo.getX();
      double y_new = odo.getY();
      // if the new location - intitial location >= 1 break, then stop
      if (abs(x_new - x) <= 5 && abs(y_new - y) <= 5){
        cout << "reaching the point" << endl;
        break;
      }
      // else drive to position
      else{
        moveFront(speed);
      }
    }

    // loop breaks and motors stop
    stop();
  }

  // simple turn until feature - need to do better in future
  static void turnToTheta(double targetTheta, Odometry& odo) {
    while (odo.getTheta() < (targetTheta - 0.05) || odo.getTheta() > (targetTheta + 0.05) ) {
      adjustLeft(20); 
    }

    stop();
  }

  static void turnTowardsLocation(double x, double y, Odometry& odo) {
    
  }

  static void shootToNearGoal(Odometry& odo) {
    double botX = odo.getX();
    double botY = odo.getY();
    double goalX = 0;
    double goalY = 0;

    double goalHeading = tan((botY - goalY) / (botX - goalX));

    goalHeading = goalHeading < 0 ? goalHeading += 2*3.14159 : goalHeading;

    turnToHeading(goalHeading, odo);
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
