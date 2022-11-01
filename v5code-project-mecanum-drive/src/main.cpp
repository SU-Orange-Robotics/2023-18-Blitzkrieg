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
// Motor1               motor         1               
// Motor3               motor         3               
// Motor2               motor         2               
// Motor4               motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
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
    double turnVal = Controller1.Axis1.position(percent);
    double forwardVal = Controller1.Axis3.position(percent);
    double horizontalVal = Controller1.Axis4.position(percent);

    double turnVolts = turnVal * 0.12;
    double horizontalVolts = horizontalVal * 0.12;
    double forwardVolts = forwardVal * 0.12 * (1 - (std::abs(turnVolts) / 12.0) * turnImportance);


    Motor1.spin(forward, forwardVolts - horizontalVolts - turnVolts, voltageUnits::volt);
    Motor3.spin(forward, forwardVolts + horizontalVolts - turnVolts, voltageUnits::volt);
    Motor2.spin(forward, forwardVolts + horizontalVolts + turnVolts, voltageUnits::volt);
    Motor4.spin(forward, forwardVolts - horizontalVolts + turnVolts, voltageUnits::volt);

    // Motor1.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value() , velocityUnits::pct);
    // Motor3.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value() , velocityUnits::pct);
    // Motor2.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value() , velocityUnits::pct);
    // Motor4.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value() , velocityUnits::pct);
    

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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
