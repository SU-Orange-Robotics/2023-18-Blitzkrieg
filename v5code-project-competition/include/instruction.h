#pragma once

class Instruction {
public:
  virtual ~Instruction() = default;
  virtual void execute() const = 0;
}; 

class MoveForward : public Instruction {
public:
  MoveForward(double targetX, double targetY) : targetX_(targetX), targetY_(targetY) {}

  void execute() const override {
    // call the functions to move to this point
  }

private:
  double targetX_;
  double targetY_;
};

class Turn : public Instruction{ 

public:
  Turn(double targetX, double targetY) : targetX_(targetX), targetY_(targetY) {}

  void execute() const override {
    // call the functions to turn to a point
  }

private:
  double targetX_;
  double targetY_;
};