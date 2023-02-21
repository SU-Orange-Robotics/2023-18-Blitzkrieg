#pragma once

#include "vex.h"

class Shooter {

public: 
  static void setShooterVelocityPct(double percentage) {
    ShooterMotorA.setVelocity(percentage, velocityUnits::pct);
    ShooterMotorB.setVelocity(percentage, velocityUnits::pct);
  }

  static void spinShooterForward(double percent) {
    ShooterMotorA.spin(vex::forward, percent, velocityUnits::pct);
    ShooterMotorB.spin(vex::forward, percent, velocityUnits::pct);
  }

  static void spinShooterBackward() {
    ShooterMotorA.spin(reverse);
    ShooterMotorB.spin(reverse);
  }

  static void stopShooter() {
    ShooterMotorA.stop();
    ShooterMotorB.stop();
  }

};