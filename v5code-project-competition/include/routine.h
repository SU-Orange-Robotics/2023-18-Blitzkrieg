#pragma once

#include <vector>
#include <memory>

#include "instruction.h"


class Routine {
public:
  Routine(const std::string& name) : name_(name) {}
  Routine() {
    name_ = "none";
  }

  void addInstruction(const std::shared_ptr<Instruction>& instruction) {
    instructions_.push_back(instruction);
  }

  void execute() const {
    for (const auto& instruction : instructions_) {
      instruction->execute();
    }
  }

private:
  std::string name_;
  std::vector<std::shared_ptr<Instruction>> instructions_;
};