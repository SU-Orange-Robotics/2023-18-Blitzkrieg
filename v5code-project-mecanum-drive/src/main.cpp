
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
// TriggerMotor         motor         9               
// ShooterMotors        motor_group   18, 19          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
#include "odometry.h"
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


void setShooterVelocityPct(double percentage) {
  ShooterMotorA.setVelocity(percentage, velocityUnits::pct);
  ShooterMotorB.setVelocity(percentage, velocityUnits::pct);
}

void spinShooterForward() {
  ShooterMotorA.spin(vex::forward);
  ShooterMotorB.spin(vex::forward);
}

void spinShooterBackward() {
  ShooterMotorA.spin(reverse);
  ShooterMotorB.spin(reverse);
}

void stopShooter() {
  ShooterMotorA.stop();
  ShooterMotorB.stop();
}

void triggerInit() {
  int i = 0;
  while(true) {
    if (i > 10) {
      break;
    }
    double position = TriggerMotor.position(degrees);

    TriggerMotor.spin(vex::forward, 10, percent);
    wait(0.3, sec);
    if (abs(position - TriggerMotor.position(degrees)) < 3) {
      Brain.Screen.print(abs(position - TriggerMotor.position(degrees)));
      break;
    }
    i++;
  }

// // dumb init
//   TriggerMotor.spin(forward, 10, percent);
//   wait(0.5, sec);
//   TriggerMotor.stop();

  TriggerMotor.stop();
}

void trigger() {
  double position = TriggerMotor.position(degrees);
  
  TriggerMotor.spinToPosition(position-36,degrees);
  wait(0.5, sec);
  TriggerMotor.spinToPosition(position,degrees);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
  // initialization stuff
  Odometry odo;
  triggerInit();
  setShooterVelocityPct(90.0);

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
  Controller1.ButtonL2.pressed([](){
    stopShooter();
  });

  // Controller1.ButtonL1.pressed([](){
  //   spinShooterForward();
  // });

  Controller1.ButtonA.pressed([](){
    trigger();
  });


  double turnImportance = 0.5;
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................


    ChassisLF.spin(directionType::fwd,-Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisRR.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisRF.spin(directionType::fwd,-Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);
    ChassisLR.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value()
    , velocityUnits::pct);

    IntakeMotor.spin(vex::forward,Controller1.ButtonR1.pressing()*100,velocityUnits::pct);
    // IntakeMotor.spin(vex::reverse,Controller1.ButtonR2.pressing()*100,velocityUnits::pct);
    

    if (Controller1.ButtonL1.pressing()) {
      spinShooterForward();
    }



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
    // odo.updateOdometry();
    // wait(0.5, seconds);
    // odo.printLocation();

    wait(20, msec);
  }
}
