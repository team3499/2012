#ifndef __ARM_MOVE_H__
#define __ARM_MOVE_H__

#include "CommandBase.h"

class ArmMove : public CommandBase {

private:
  float targetAngle;     // Arm angle in degrees with horizontal = 0

public:
  ArmMove(float targ);
  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

};

#endif /* __ARM_MOVE_H__ */
