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

  static void turnByGyro(double degrees) { // positive for clockwise, negative for counter clockwise

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
    Shooter::spinShooterForward(88);
    wait(10, sec);
    Trigger::launch();
    wait(3, sec);
    Trigger::launch();
    wait(0.5, sec);
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
    wait(0.53, sec);
    MecanumDrive::stop();

    MecanumDrive::adjustRight(20);
    wait(2.57, sec);
    MecanumDrive::stop();

    Shooter::setShooterVelocityPct(80);
    Shooter::spinShooterForward(80);
    wait(10, sec);
    Trigger::launch();
    wait(4, sec);
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
    wait(2.57, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(3.6, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(20);
    wait(0.2, sec);
    MecanumDrive::stop();

    MecanumDrive::moveRight(20);
    wait(.50, sec);
    MecanumDrive::stop();

    // run back slowly
    MecanumDrive::moveFront(20);
    wait(0.3, sec);

    
    // roller
    IntakeMotor.spin(vex::reverse, 100, percent);
    wait(1.50, sec);
    IntakeMotor.stop();
    MecanumDrive::stop();

    MecanumDrive::moveBack(20);
    wait(0.1, sec);
    MecanumDrive::stop();
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