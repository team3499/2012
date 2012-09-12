#ifndef TURN_H
#define TURN_H

#include "CommandBase.h" 
#include "Subsystems/Chassis.h"

class Turn: public CommandBase {
private:
  float TurnSpeedForAngle(float angle);
  bool nullTarget;
public:
  float turnAngle;
  float turnTo;
  float turnSpeed;
  Turn();
  Turn(float angle);
  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();
};

#endif
