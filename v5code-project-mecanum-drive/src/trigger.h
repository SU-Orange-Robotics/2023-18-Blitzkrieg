#pragma once

#include "vex.h"
#include <cmath>

class Trigger {
public:

  static void init() {
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

    TriggerMotor.stop();
  }

  static void launch() {
    TriggerMotor.setVelocity(40, percent);
    double position = TriggerMotor.position(degrees);
    
    TriggerMotor.spinToPosition(position-38,degrees);
    wait(0.2, sec);
    TriggerMotor.spinToPosition(position,degrees);
  }

};