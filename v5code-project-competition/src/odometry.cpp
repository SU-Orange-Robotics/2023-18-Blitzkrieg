#include "vex.h"
using namespace vex;


#include "odometry.h"

Odometry::Odometry() {
  reset();
}

void Odometry::reset() {
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

double Odometry::getX() {
  return locationX;
}

double Odometry::getY() {
  return locationY;
}

double Odometry::getTheta() {
  return locationTheta;
}

vector<double> Odometry::getLocation() {
  return { locationX, locationY, locationTheta };
}

void Odometry::printLocation() {
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

void Odometry::updateOdometry() {
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