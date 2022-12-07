#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <vector>

#include "vex.h"

using namespace vex;

using namespace std;

class odometry {

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
    return { locationX, locationY, locationTheta };
  }

  void updateOdometry() {
    // 1. get new encoder readings

    // Check if values should be reversed
    double newEncoderLeft = Rotation1.position(turns);
    double newEncoderRight = Rotation2.position(turns);
    double newEncoderCenter = Rotation3.position(turns);


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