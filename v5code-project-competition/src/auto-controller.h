#pragma once

#include "vex.h"
#include "robot-config.h"

#include "mecanum-drive.h"
#include "trigger.h"
#include "gyro.h"
#include "shooter.h"

class AutoController {

public:

  static void executeRoutine(void (*func)()) {
    func();
  }

// routines
  static void twoHighAuto() {
    // plan b for turning red
    MecanumDrive::moveBack(20);
    wait(1, sec);
    MecanumDrive::stop();


    MecanumDrive::adjustLeft(20);
    wait(0.9, sec);
    MecanumDrive::stop();

    wait(0.2, sec);

    // shoot two discs
    Shooter::spinShooterForward();
    wait(4, sec);
    Trigger::launch();
    wait(0.5, sec);
    Trigger::launch();
    wait(0.2, sec);
    Shooter::stopShooter();

    MecanumDrive::adjustRight(20);
    wait(0.8,sec);
    MecanumDrive::stop();

    // move right
    MecanumDrive::moveRight(20);
    wait(4.9, sec);
    MecanumDrive::stop();


    // run back slowly
    MecanumDrive::moveFront(20);
    wait(1.1, sec);
    MecanumDrive::stop();
    
    // roller
    IntakeMotor.spin(vex::reverse, 100, percent);
    wait(1.0, sec);
    IntakeMotor.stop();
  }

  
  static void threeLowAuto() {
    MecanumDrive::moveBack(20);
    wait(0.5, sec);
    MecanumDrive::stop();

    MecanumDrive::adjustRight(20);
    wait(2.6, sec);
    MecanumDrive::stop();

    Shooter::setShooterVelocityPct(50.0);
    Shooter::spinShooterForward();
    wait(3, sec);
    Trigger::launch();
    wait(0.5, sec);
    Trigger::launch();
    wait(0.5, sec);
    Trigger::launch();
    wait(0.5, sec);

    Shooter::stopShooter();
    Shooter::setShooterVelocityPct(92.0);

    MecanumDrive::adjustLeft(20);
    wait(2.6, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(3.9, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(20);
    wait(0.3, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(1.2, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(20);
    wait(0.4, sec);
    MecanumDrive::stop();
    
    // roller
    IntakeMotor.spin(vex::reverse, 100, percent);
    wait(1.0, sec);
    IntakeMotor.stop();
  }
  
};