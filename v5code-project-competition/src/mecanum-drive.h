#pragma once

#include "vex.h"
#include "robot-config.h"
#include <cmath>
#include <iostream>

#include "odometry.h"
#include "shooter.h"
#include "trigger.h"

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
  /*
  double getAngleErrorOLD(double target) {
    double currHeading = fmod(odo.getTheta(), 2 * M_PI); // gets angle and then restricts it to a fixed range
    if (abs(currHeading) > M_PI) { //converts a (0 to 2pi) value to a (-pi to pi) value
      currHeading -= (2 * M_PI) * (currHeading > 0 ? 1 : -1);
    }
    double error = currHeading - target;
    return error;
  }*/

  double getAngleError(double target) {
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
  }
  /*
  double getTarget(double target) {
    //double currHeading = fmod(odo.getTheta(), 2 * M_PI); // gets angle and then restricts it to a fixed range
    //if (abs(currHeading) > M_PI) { //converts a (0 to 2pi) value to a (-pi to pi) value
    //  currHeading -= (2 * M_PI) * (currHeading > 0 ? 1 : -1);
    //}
    //double error = currHeading - target;
    double error = getAngleError(target);
    double targetPos = odo.getTheta() + error;
    return targetPos;
  }*/

  const double a_P = 50;  //50
  const double a_I = 0;   //0
  const double a_D = 0.1; //0.1

  vex::timer pid_timer;
  
  void turnPID(double targetHeading) {
    double error = 0;
    double errorLast;
    double lastTime = 0;
    double dt;
    double integrationStored = 0;
    pid_timer.reset();
    while(true) {
      errorLast = error;
      error = getAngleError(targetHeading);
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
  /*
  void turnToHeading(double targetHeading) {
    double targetAngle = getTarget(targetHeading);
    while (odo.getTheta() < (targetAngle - 0.05) || odo.getTheta() > (targetAngle + 0.05)) {
      //drivePure(0, 0, (targetAngle > odo.getTheta()) ? 20 : -20);
      adjustRight(targetAngle > odo.getTheta() ? 20 : -20);
      //targetAngle = getTarget(targetHeading);
    }
    stop();
  }*/

  double getAngleToPoint(double x2, double y2) {
    double x1 = odo.getX();
    double y1 = odo.getY();

    double theta = atan2(y2 - y1, x2 - x1);

    return theta;
  }
  
  // find error between target point, and current point
  double getDistanceError(double targetX, double targetY, int count){

    // get current x, and y position
    double currentX = odo.getX();
    double currentY = odo.getY();

    // find the distance between the targets, and currents 
    double errorX = targetX - currentX;
    double errorY = targetY - currentY;

    // find the length of the hypotenuse
    double errorTan = sqrt(pow(errorX, 2) + pow(errorY, 2));

    if(count % 100 == 0){
      cout << "first: " << errorTan << endl;
    }

    // accounts for the angle always being positive by making it negative if the robot is facing away from the target point
    double currAngle = fmod(odo.getTheta(), 2*M_PI);
    currAngle += currAngle < 0 ? 2*M_PI : 0;
    double angleDifference = abs(getAngleToPoint(targetX, targetY) - currAngle);
    errorTan *= (angleDifference < M_PI/2 || angleDifference > 3*M_PI/2) ? 1 : -1;
    //errorTan *= abs(getAngleToPoint(targetX, targetY) - fmod(odo.getTheta(), 2*M_PI)) < M_PI/2 ? 1 : -1; // angle from where robot is facing to angle towards desired location
    
    if(count % 100 == 0){
      cout << "second: " << errorTan << endl;
    }

    return errorTan;
  }

  // function to go to a point using PID

  const double d_P = 3.0;
  const double d_D = 3.0;
  const double d_I = 0.00;

  vex::timer pid_timer2;

  void goToPointPID(double targetX, double targetY ){
    double currentX = odo.getX();
    double currentY = odo.getY();

    double error = 0;
    double errorLast;
    double dt;
    double lastTime = 0;
    double integrationStored = 0;
    pid_timer2.reset();

    int count = 0;
  
    while(true){
      errorLast = error;
      error = getDistanceError(targetX, targetY, count++);
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

      if (abs(error) < 2.0 && abs(error-errorLast) / dt) {
        break;
      }
    }
    stop();
  }

  void turnToPoint(double targetX, double targetY, bool flipped = false) {
    double theta = getAngleToPoint(targetX, targetY);
    theta += flipped ? -1*M_PI : 0; 
    turnPID(theta);
  }

  void turnAndDrivePID(double targetX, double targetY) {
    turnToPoint(targetX, targetY);
    goToPointPID(targetX, targetY);
  }

  // simple turn until feature - need to do better in future
  /*void turnToTheta(double targetTheta) {
    while (odo.getTheta() < (targetTheta - 0.05) || odo.getTheta() > (targetTheta + 0.05) ) {
      adjustLeft(20); 
    }

    stop();
  }*/

  void shootToNearGoal(int disks = 1) { //can specifiy number of disks to fire, but fires 1 by default
    turnToPoint(17.78, 17.78, true);

    Shooter::spinShooterForward(78);
    for (int i = 0; i < disks; i++) {
      Trigger::launch();
      wait(1000, msec);
    }
    Shooter::stopShooter();
  }
  
  void shootToFarGoal(int disks = 1) { //can specifiy number of disks to fire, but fires 1 by default
    turnToPoint(122.63, 122.63, true);

    Shooter::spinShooterForward(78);
    for (int i = 0; i < disks; i++) {
      wait(7000, msec);
      Trigger::launch();
    }
    Shooter::stopShooter();
  }

  static void stop() {
    ChassisLF.stop();
    ChassisRR.stop();
    ChassisRF.stop();
    ChassisLR.stop();
  }
};
