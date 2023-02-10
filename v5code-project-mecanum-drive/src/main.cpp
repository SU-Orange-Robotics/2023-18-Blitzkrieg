// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ChassisLR            motor         11              
// ChassisLF            motor         13              
// ChassisRF            motor         14              
// ChassisRR            motor         12              
// Left                 rotation      1               
// Right                rotation      20              
// Center               rotation      3               
// IntakeMotor          motor         10              
// TriggerMotor         motor         8               
// ShooterMotorA        motor         2               
// ShooterMotorB        motor         17              
// Inertial16           inertial      16              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ChassisLR            motor         11              
// ChassisLF            motor         13              
// ChassisRF            motor         14              
// ChassisRR            motor         12              
// Left                 rotation      1               
// Right                rotation      20              
// Center               rotation      3               
// IntakeMotor          motor         10              
// TriggerMotor         motor         8               
// ShooterMotorA        motor         2               
// ShooterMotorB        motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

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
#include "mecanum-drive.h"
#include "robot-config.h"
using namespace vex;

// A global instance of competition
competition Competition;
Odometry odo;


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
  TriggerMotor.setVelocity(5, percent);
  
  while(i < 5) {
    double position = TriggerMotor.position(degrees);
    TriggerMotor.spin(vex::forward, 5, percent);
    wait(0.15, sec);
    TriggerMotor.stop();
    if (abs(position - TriggerMotor.position(degrees)) < 1) {
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
  TriggerMotor.setVelocity(40, percent);
  double position = TriggerMotor.position(degrees);
  
  TriggerMotor.spinToPosition(position-38,degrees);
  wait(0.2, sec);
  TriggerMotor.spinToPosition(position,degrees);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
  // initialization stuff
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

  Controller1.ButtonA.pressed([](){
    trigger();
  });

  Controller1.ButtonLeft.pressed([](){
    MecanumDrive::adjustLeft(18);
    angleAjustTimer.reset();
  });

  Controller1.ButtonRight.pressed([](){
    MecanumDrive::adjustRight(18);
    angleAjustTimer.reset();
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


    {
      if (!Controller1.ButtonLeft.pressing() && !Controller1.ButtonRight.pressing()) {
        ChassisLF.spin(directionType::fwd,-Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value()
        , velocityUnits::pct);
        ChassisRR.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value()
        , velocityUnits::pct);
        ChassisRF.spin(directionType::fwd,-Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value()
        , velocityUnits::pct);
        ChassisLR.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value()
        , velocityUnits::pct);
      }

    }

    {
      // if (Controller1.ButtonLeft.pressing()) {
      //   MecanumDrive::adjustLeft(20);
      // } else {
      //   angleAjustTimer.reset();
      // }
      // if (Controller1.ButtonRight.pressing()) {
      //   MecanumDrive::adjustRight(20);
      // }

      if ((Controller1.ButtonLeft.pressing() || Controller1.ButtonRight.pressing()) && angleAjustTimer.time(vex::sec) > 0.2) {
        MecanumDrive::stop();
      }
    }

    
    // IntakeMotor.spin(vex::reverse,Controller1.ButtonR2.pressing()*100,velocityUnits::pct);
    

    if (Controller1.ButtonL1.pressing()) {
      spinShooterForward();
    }

    if (Controller1.ButtonR1.pressing()) {
      IntakeMotor.spin(vex::forward,100,velocityUnits::pct);
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
