#pragma once

#include "vex.h"
#include "robot-config.h"

#include "mecanum-drive.h"
#include "trigger.h"
#include "gyro.h"
#include "shooter.h"

#include "routine.h"

#include <string>

// routines
#include "./routines/BlitzSkills.h"

// HOW TO USE:
// 1. Add your routine as a new member variable
// 2. Add your "routineInit" function
// 3. Add your to the constructor

class AutoController {

private:
  Routine currentRoutine; 
  bool routineLoaded;

public:
  AutoController() {}
  AutoController(std::string routineName) {
    routineLoaded = false;

    // CONTRIBUTE: add new routines here, add your routintInit function with specific instructions added inside it.
    if (routineName == "BlitzSkills") {
      // initalize routines (add instructions)
      BlitzSkillsInit(currentRoutine, routineName);
    }

    routineLoaded = true;
  }

  void executeRoutine() {
    while (!routineLoaded) {
      vex::task::sleep(100);
    }
    currentRoutine.execute();
  }

  // start on left of closer goal, two high goal, two roller
  void skilledAuto() {
  
    MecanumDrive::moveBack(20);
      wait(0.53, sec);
      MecanumDrive::stop();

      MecanumDrive::adjustRight(20);
      wait(2.5, sec);
      MecanumDrive::stop();
      wait(1, sec);

      Shooter::setShooterVelocityPct(80);
      Shooter::spinShooterForward(80);
      wait(10, sec);
      Trigger::launch();
      wait(6, sec);
      Trigger::launch();
      wait(1, sec);
      Trigger::launch();
      wait(1, sec);
      Trigger::launch();
      wait(1, sec);
      Trigger::launch();
      wait(1, sec);
      Trigger::launch();
      wait(0.5, sec);
      Shooter::stopShooter();

      MecanumDrive::adjustLeft(20);
      wait(2.5, sec);
      MecanumDrive::stop();

      MecanumDrive::moveRight(20);
      wait(3.8, sec);
      MecanumDrive::stop();

      // run back slowly
      MecanumDrive::moveFront(20);
      wait(0.2, sec);
      MecanumDrive::stop();

      MecanumDrive::moveRight(20);
      wait(.50, sec);
      MecanumDrive::stop();

      // run back slowly
      MecanumDrive::moveFront(18);
      wait(0.3, sec);

      
      // roller
      IntakeMotor.spin(vex::reverse, 100, percent);
      wait(1.0, sec);
      IntakeMotor.stop();
      MecanumDrive::stop();

      // skill only auto, second roller
      MecanumDrive::moveRight(20);
      wait(0.5, sec);
      MecanumDrive::stop();
      MecanumDrive::moveBack( 20);
      wait(2.3, sec);
      MecanumDrive::stop();

      MecanumDrive::adjustRight(20);
      wait(2.6, sec);
      MecanumDrive::stop();

      MecanumDrive::moveFront( 20);
      wait(2.0, sec); // 
      MecanumDrive::stop();
      wait(0.5, sec);
      
      // roller
      IntakeMotor.spin(vex::reverse, 100, percent);
      MecanumDrive::moveFront( 18);
      wait(1.2, sec);
      IntakeMotor.stop();
      MecanumDrive::stop();

      // move back a bit more

      MecanumDrive::moveBack( 20);
      wait(2.0, sec); // 
      MecanumDrive::stop();

      wait(0.5, sec);
      MecanumDrive::moveLeft(20);
      wait(0.5, sec);
      MecanumDrive::stop();

  }

  // start on left of own goal, two low goal, one roller
  void userAuto() {
    
    MecanumDrive::moveBack(20);
    wait(0.53, sec);
    MecanumDrive::stop();

    MecanumDrive::adjustRight(20);
    wait(2.5, sec);
    MecanumDrive::stop();
    wait(1, sec);

    Shooter::setShooterVelocityPct(60);
    Shooter::spinShooterForward(60);
    wait(10, sec);
    Trigger::launch();
    wait(6, sec);
    Trigger::launch();
    wait(1, sec);
    Trigger::launch();
    wait(1, sec);
    Trigger::launch();
    wait(1, sec);
    Trigger::launch();
    wait(1, sec);
    Trigger::launch();
    wait(0.5, sec);
    Shooter::stopShooter();

    MecanumDrive::adjustLeft(20);
    wait(2.5, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(3.8, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(20);
    wait(0.2, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(.50, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(18);
    wait(0.3, sec);

    
    // roller
    IntakeMotor.spin(vex::reverse, 100, percent);
    wait(1.0, sec);
    IntakeMotor.stop();
    MecanumDrive::stop();

  }
  
};