#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ChassisLR = motor(PORT4, ratio18_1, false);
motor ChassisLF = motor(PORT6, ratio18_1, false);
motor ChassisRF = motor(PORT7, ratio18_1, true);
motor ChassisRR = motor(PORT8, ratio18_1, true);
rotation Left = rotation(PORT16, true);
rotation Right = rotation(PORT17, true);
rotation Center = rotation(PORT5, true);
motor IntakeMotor = motor(PORT11, ratio36_1, true);
motor TriggerMotor = motor(PORT9, ratio18_1, false);
motor ShooterMotorsMotorA = motor(PORT18, ratio6_1, false);
motor ShooterMotorsMotorB = motor(PORT19, ratio6_1, true);
motor_group ShooterMotors = motor_group(ShooterMotorsMotorA, ShooterMotorsMotorB);

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