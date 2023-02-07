#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <vector>
#include <string>
// #include <string.h>

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
  const double width = 10;
  const double length = 10;
  const double circ = 10;


public:
  vector<double> getLocation() {
    // string odometryInfo = to_string(locationX) + " " + to_string(locationY) + " " + to_string(locationTheta);
    // Brain.Screen.clearLine(0,color::black);
    // Brain.Screen.clearLine(1,color::black);
    // Brain.Screen.setPenColor(white);
    // Brain.Screen.setCursor(1,1);
    // Brain.Screen.print(locationX);

    Brain.Screen.clearScreen();

    // Display the X position on row 1
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("X: %.3f", locationX);

    // Display the Y position on row 2
    Brain.Screen.newLine();
    Brain.Screen.print("Y: %.3f", locationY);

    // Display the Z position on row 3
    Brain.Screen.newLine();
    Brain.Screen.print("Theta: %.3f", locationTheta);

    return { locationX, locationY, locationTheta };
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