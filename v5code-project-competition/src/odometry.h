#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <vector>
#include <string>
// #include <string.h>
#include <math.h>

#include "vex.h"

using namespace vex;

using namespace std;



class Odometry {

private:
  double encoderLeft;
  double encoderRight;
  double encoderCenter;

  double locationX;
  double locationY;
  double locationTheta;

// measure the robot to set this
  const double width = 6.5;   // distance from center of bot -> back tracking wheel
  const double length = 13.8; // distance between center of left and rigtht wheels
  const double circ = 4 * M_PI;


public:
  Odometry() {
    reset();
  }

  // aginst rite side white lane. facing up. (x = 86, y = 8, t = pi/2)
  void reset() {
    locationX = 86.0;
    locationY = 8.0;
    locationTheta = M_PI / 2;

    encoderLeft = 0.0;
    encoderRight = 0.0;
    encoderCenter = 0.0;

    Left.resetPosition();
    Right.resetPosition();
    Center.resetPosition();
  }

  double getX() {
    return locationX;
  }

  double getY() {
    return locationY;
  }

  double getTheta() {
    return locationTheta;
  }

  vector<double> getLocation() {
    return { locationX, locationY, locationTheta };
  }

  void printLocation() {
    Brain.Screen.clearScreen();
    
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("X: %f", locationX);

    // Display the Y position on row 2
    Brain.Screen.newLine();
    Brain.Screen.print("Y: %f", locationY);

    // Display the Z position on row 3
    Brain.Screen.newLine();
    Brain.Screen.print("Theta: %f", locationTheta);


    Controller1.Screen.setCursor(0,0);
    Controller1.Screen.clearScreen();
    
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("X: %f", locationX);

    // Display the Y position on row 2
    Controller1.Screen.newLine();
    Controller1.Screen.print("Y: %f", locationY);

    // Display the Z position on row 3
    Controller1.Screen.newLine();
    Controller1.Screen.print("Theta: %f", locationTheta);
  }

  void updateOdometry() {
    // 1. get new encoder readings

    // Check if values should be reversed
    double newEncoderLeft = Left.position(turns);
    double newEncoderRight = Right.position(turns);
    double newEncoderCenter = Center.position(turns);


    double diffLeft = newEncoderLeft - encoderLeft;
    double diffRight = newEncoderRight - encoderRight;
    double diffCenter = newEncoderCenter - encoderCenter;

    // overwrite old values
    encoderLeft = newEncoderLeft;
    encoderRight = newEncoderRight;
    encoderCenter = newEncoderCenter;

    // 2. calculate delta u

    // 3. calculate delta x,y,theta
    double dx = circ * (diffRight + diffLeft) / 2;
    double dy = circ * (diffCenter - (diffRight - diffLeft) * (width / length));
    double dt = circ * (diffRight - diffLeft) / length;

    // 4. use trig to calculate new location x,y,theta
    double newTheta = locationTheta + (dt / 2.0);
    locationX += dx * cos(newTheta) - dy * sin(newTheta);
    locationY += dx * sin(newTheta) + dy * cos(newTheta);
    locationTheta += dt;
  }
};

#endif