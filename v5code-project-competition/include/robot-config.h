#pragma once

#include "odometry.h"

using namespace vex;
using signature = vision::signature;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor ChassisLR;
extern motor ChassisLF;
extern motor ChassisRF;
extern motor ChassisRR;
extern rotation Left;
extern rotation Right;
extern rotation Center;
extern motor IntakeMotor;
extern motor TriggerMotor;
extern motor ShooterMotorA;
extern motor ShooterMotorB;
extern inertial Inertial16;
extern signature Vision12__SIG_1;
extern signature Vision12__SIG_2;

extern vision Vision12;

// custom stuff
extern vex::timer angleAjustTimer;
extern Odometry odo;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );