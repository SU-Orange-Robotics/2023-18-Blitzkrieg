#include "vex.h"
#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ChassisLF = motor(PORT8, ratio18_1, false);
motor ChassisLR = motor(PORT6, ratio18_1, false);
motor ChassisRF = motor(PORT7, ratio18_1, true);
motor ChassisRR = motor(PORT5, ratio18_1, true);
rotation Left = rotation(PORT20, true);
rotation Right = rotation(PORT19, true);
rotation Center = rotation(PORT11, true);
motor IntakeMotor = motor(PORT18, ratio36_1, true);
motor TriggerMotor = motor(PORT17, ratio18_1, false);
motor ShooterMotorA = motor(PORT9, ratio6_1, false);
motor ShooterMotorB = motor(PORT10, ratio6_1, true);
inertial Inertial16 = inertial(PORT16);

/*vex-vision-config:begin*/
signature Vision12__SIG_1 = signature (1, 4859, 6935, 5897, -2699, -1501, -2100, 3, 0);
signature Vision12__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0); // maybe not needed
vision Vision12 = vision (PORT12, 50, Vision12__SIG_1, Vision12__SIG_2);
/*vex-vision-config:end*/

// custom made variables/objects
vex::timer angleAjustTimer;
Odometry odo;

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