#ifndef __COMMAND_ARM_AIM_H__
#define __COMMAND_ARM_AIM_H__

#include "CommandBase.h"
#include "Target.h"

class ArmAim : public CommandBase {

private:
  Target *target;      // The target we're shooting at
  float   angle;       // Arm angle in degrees with horizontal = 0
  float   margin;      // Margin of "close enough" for target angle
  float   movePeriod;  // Time to move arm before taking another measurement
  int     iteration;   // Number of iteration attempted to set arm angle
  Timer   timer;

  enum Mode {
    QUIETING,
    MEASURING,
    MOVING,
    FINISHED
  } mode;

public:
  ArmAim();
  ~ArmAim();

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

};

#endif /* __COMMAND_ARM_AIM_H__ */
