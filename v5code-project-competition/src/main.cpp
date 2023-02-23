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
#include "robot-config.h"

#include "mecanum-drive.h"
#include "trigger.h"
#include "shooter.h"
#include "odometry.h"
#include "auto-controller.h"

#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;
Odometry odo; // not correct, need to add to robot-config later

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
  
  // initialization stuff
  Trigger::init();

  Inertial16.calibrate();
  odo.reset();
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

  MecanumDrive::driveToLocation(86, 17.39, odo, 50);
  // MecanumDrive::moveFront(30);
  // wait(0.3, sec);
  // MecanumDrive::stop();

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
  // Controller1.ButtonR2.pressed([](){
  //   IntakeMotor.stop();
  // });

  // disabled for now in favor of hold-button control
  /*Controller1.ButtonL2.pressed([](){
    stopShooter();
  });*/
  

  // idling -- dont use duirng practice, causing overheat
  // Controller1.ButtonL1.pressed([](){
  //   Shooter::spinShooterForward(79);
  // });
  // Shooter::spinShooterForward(50);
  // Controller1.ButtonL1.released([](){
  //   Shooter::spinShooterForward(50);
  // });

  Controller1.ButtonA.pressed([](){
    Trigger::launch();
  });

  Controller1.ButtonLeft.pressed([](){
    MecanumDrive::adjustLeft(18);
    angleAjustTimer.reset();
  });

  Controller1.ButtonRight.pressed([](){
    MecanumDrive::adjustRight(18);
    angleAjustTimer.reset();
  });

  Controller1.ButtonR1.pressed([](){
    IntakeMotor.spin(vex::forward,100,velocityUnits::pct);
  });

  Controller1.ButtonR1.released([](){
    IntakeMotor.stop();
  });

  Controller1.ButtonR2.pressed([](){
    IntakeMotor.spin(vex::reverse, 100, velocityUnits::pct);
  });

  Controller1.ButtonR2.released([](){
    IntakeMotor.stop();
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
    if (Controller1.ButtonL1.pressing()) {
      Shooter::spinShooterForward(79);
    } else {
      Shooter::stopShooter();
    }
 

    {
      if (!Controller1.ButtonLeft.pressing() && !Controller1.ButtonRight.pressing()) {
        if (!Controller1.ButtonL2.pressing()) {
          MecanumDrive::drive(Controller1.Axis3.value(), Controller1.Axis4.value(), Controller1.Axis1.value());
        } else {
          MecanumDrive::drive(-Controller1.Axis3.value(), -Controller1.Axis4.value(), Controller1.Axis1.value());
        }
      }
    }

    odo.printLocation();

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
    odo.updateOdometry();

    wait(50, msec);
  }
}
