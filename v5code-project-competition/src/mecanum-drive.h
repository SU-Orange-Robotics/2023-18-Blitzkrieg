#pragma once

#include "vex.h"
#include "robot-config.h"
#include <cmath>
#include <iostream>

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

  double getAngleError(double target, Odometry& odo) {
    double currHeading = fmod(odo.getTheta(), 2 * M_PI); // gets angle and then restricts it to a fixed range
    if (abs(currHeading) > M_PI) { //converts a (0 to 2pi) value to a (-pi to pi) value
      currHeading -= (2 * M_PI) * (currHeading > 0 ? 1 : -1);
    }
    double error = currHeading - target;
    return error;
  }

  double getAngleError2(double target, Odometry& odo) {
    double currAngle = odo.getTheta();
    int rotations = floor(currAngle / (2*M_PI));
    rotations += rotations < 0 ? 1 : 0;

    double trueTarget1 = target + (rotations * (2*M_PI));
    double error1 = currAngle - trueTarget1;

    double error2;
    if (abs(error1) > M_PI && error1 != 0) {
      error2 = error1 + (2*M_PI * error1 > 0 ? -1 : 1); //positive error --> subtract a rotation, negative error --> add a rotation
    } else {
      error2 = error1;
    }
    
    return error2;

    /*
    double trueTarget2 = trueTarget1 - 2*M_PI;
    error2 = currAngle - trueTarget2;

    if (abs(error1) > abs(error2)) {
      return error2;
    } else {
      return error1;
    }*/
  }

  double getTarget(double target, Odometry& odo) {
    /*double currHeading = fmod(odo.getTheta(), 2 * M_PI); // gets angle and then restricts it to a fixed range
    if (abs(currHeading) > M_PI) { //converts a (0 to 2pi) value to a (-pi to pi) value
      currHeading -= (2 * M_PI) * (currHeading > 0 ? 1 : -1);
    }
    double error = currHeading - target;*/
    double error = getAngleError(target, odo);
    double targetPos = odo.getTheta() + error;
    return targetPos;
  }

  const double a_P = 50;  //50
  const double a_I = 0;   //0
  const double a_D = 0.1; //0.1

  vex::timer pid_timer;
  
  void turnPID(double targetHeading, Odometry& odo) {
    double error = 0;
    double errorLast;
    double lastTime = 0;
    double dt;
    double integrationStored = 0;
    pid_timer.reset();
    while(true) {
      errorLast = error;
      error = getAngleError2(targetHeading, odo);
      dt = pid_timer.time() - lastTime;

      double P_comp = a_P * error;
      double D_comp = 0;

      if (errorLast != 0) {
        double D_comp = a_D * (error - errorLast) / dt;
      }

      integrationStored += (error * dt);
      double I_comp = a_I * integrationStored;

      double output = P_comp + I_comp + D_comp;

      adjustRight(output);

      if (abs(error) < 0.02 && abs((error-errorLast)/dt) < 0.02) {
        break;
      }
    }
    stop();
  }

  void turnToHeading(double targetHeading, Odometry& odo) {
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

  void driveToLocation(double x, double y, Odometry& odo, double speed) { //OUTDATED
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

  double getAngleToPoint(double x2, double y2, Odometry& odo) {
    double x1 = odo.getX();
    double y1 = odo.getY();

    double theta = atan2(y2 - y1, x2 - x1);

    return theta;
  }
  
  // find error between target point, and current point
  double getDistanceError(double targetX, double targetY, Odometry& odo){

    // get current x, and y position
    double currentX = odo.getX();
    double currentY = odo.getY();

    // find the distance between the targets, and currents 
    double errorX = targetX - currentX;
    double errorY = targetY - currentY;

    // find the length of the hypotenuse
    double errorTan = sqrt(pow(errorX, 2) + pow(errorY, 2));

    // accounts for the angle always being positive by making it negative if the robot is facing away from the target point
    double angleDifference = abs(getAngleToPoint(targetX, targetY, odo) - abs(fmod(odo.getTheta(), 2*M_PI)));
    errorTan *= (angleDifference < 2*M_PI || angleDifference > 2*M_PI/3) ? 1 : -1;
    //errorTan *= abs(getAngleToPoint(targetX, targetY, odo) - fmod(odo.getTheta(), 2*M_PI)) < M_PI/2 ? 1 : -1; // angle from where robot is facing to angle towards desired location

    return errorTan;
  }

  // function to go to a point using PID

  const double d_P = 1.0;
  const double d_D = 0.0;
  const double d_I = 0.0;

  vex::timer pid_timer2;

  void goToPointPID(double targetX, double targetY, Odometry& odo){
    double currentX = odo.getX();
    double currentY = odo.getY();

    double error = 0;
    double errorLast;
    double dt;
    double lastTime = 0;
    double integrationStored = 0;
    pid_timer2.reset();
  
    while(true){
      errorLast = error;
      error = getDistanceError(targetX, targetY, odo);
      dt = pid_timer2.time() - lastTime;
      
      double P_comp = d_P * error;
      double D_comp = 0;

      if (errorLast != 0) {
        double D_comp = d_D * (error - errorLast) / dt;
      }

      integrationStored += (error * dt);
      double I_comp = d_I * integrationStored;

      double output = P_comp + I_comp + D_comp;

      moveFront(output);

      if (abs(error) < 0.02 && abs(error-errorLast) / dt) {
        break;
      }
    }
    stop();
  }

  void turnAndDrivePID(double targetX, double targetY, Odometry& odo) {
    double theta = getAngleToPoint(targetX, targetY, odo);
    turnPID(theta, odo);
    goToPointPID(targetX, targetY, odo);
  }

  // simple turn until feature - need to do better in future
  void turnToTheta(double targetTheta, Odometry& odo) {
    while (odo.getTheta() < (targetTheta - 0.05) || odo.getTheta() > (targetTheta + 0.05) ) {
      adjustLeft(20); 
    }

    stop();
  }


  void turnTowardsLocation(double x, double y, Odometry& odo) {
    
  }

  void shootToNearGoal(Odometry& odo) {

    double botX = odo.getX();
    double botY = odo.getY();
    double goalX = 0;
    double goalY = 0;

    double goalHeading = tan((botY - goalY) / (botX - goalX));

    goalHeading = goalHeading < 0 ? goalHeading += 2*3.14159 : goalHeading;

    turnPID(goalHeading, odo);
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
