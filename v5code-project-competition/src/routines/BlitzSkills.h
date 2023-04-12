#pragma once

#include "../../include/routine.h"

// routines
void BlitzSkillsInit(Routine& currentRoutine, std::string routineName) {
  currentRoutine = Routine(routineName);
  currentRoutine.addInstruction(std::make_shared<MoveForward>(10.0, 10.0));
  currentRoutine.addInstruction(std::make_shared<Turn>(19.0, 2));
}