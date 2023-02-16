#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ChassisLR = motor(PORT11, ratio18_1, false);
motor ChassisLF = motor(PORT13, ratio18_1, false);
motor ChassisRF = motor(PORT14, ratio18_1, true);
motor ChassisRR = motor(PORT12, ratio18_1, true);
rotation Left = rotation(PORT1, true);
rotation Right = rotation(PORT20, true);
rotation Center = rotation(PORT3, true);
motor IntakeMotor = motor(PORT10, ratio36_1, true);
motor TriggerMotor = motor(PORT8, ratio18_1, false);
motor ShooterMotorA = motor(PORT2, ratio6_1, false);
motor ShooterMotorB = motor(PORT17, ratio6_1, true);
inertial Inertial16 = inertial(PORT16);

// custom made variables/objects
vex::timer angleAjustTimer;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}