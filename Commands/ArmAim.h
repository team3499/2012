#ifndef __COMMAND_ARM_AIM_H__
#define __COMMAND_ARM_AIM_H__

#include "CommandBase.h"
#include "Target.h"

class ArmAim : public CommandBase {

private:
  Target *target;      // The target we're shooting at
  float   angle;       // Arm angle in degrees with horizontal = 0
  float   margin;      // Margin of "close enough" for target angle
  int     iteration;   // Number of iteration attempted to set arm angle

  void MeasureAndMove();      // Take an angle measurement and start moving
  void StopAndQuiet();        // Stop and wait for bounding to settle
  bool GetDesiredDirection(); // Determine which direction to go
  bool IsAtTargetAngle();     // Are we there yet?

public:
  ArmAim(Target *target = NULL);  // Defaults to middle target
  ~ArmAim();

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

};

#endif /* __COMMAND_ARM_AIM_H__ */
