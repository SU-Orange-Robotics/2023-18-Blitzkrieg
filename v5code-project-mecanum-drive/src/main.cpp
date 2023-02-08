/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ChassisLR            motor         4               
// ChassisLF            motor         6               
// ChassisRF            motor         7               
// ChassisRR            motor         8               
// Left                 rotation      16              
// Right                rotation      17              
// Center               rotation      5               
// IntakeMotor          motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
#include "odometry.cpp"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // Motor15.spin(forward, 6 + 0, voltageUnits::volt);
  // Motor16.spin(forward, 6 - 0, voltageUnits::volt);

  // wait(1, sec);

  // Motor15.spin(forward, 0 + 0, voltageUnits::volt);
  // Motor16.spin(forward, 0 - 0, voltageUnits::volt);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  double turnImportance = 0.5;
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................


    ChassisLF.spin(directionType::fwd,-Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,-Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);

    // flywheel test code
    // ChassisLF.spin(forward,Controller1.Axis3.value(), velocityUnits::pct);
    // ChassisLR.spin(forward,Controller1.Axis3.value(), velocityUnits::pct);

    IntakeMotor.spin(directionType::fwd,Controller1.ButtonR1.pressing()*100,velocityUnits::pct);


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

    Odometry odo;

  // Prevent main from exiting with an infinite loop.
  while (true) {
    //wait(100, msec);

    odo.updateOdometry();
    wait(0.5, seconds);
    odo.getLocation();
  }
}
