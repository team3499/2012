#ifndef __ARM_MOVE_H__
#define __ARM_MOVE_H__

#include "CommandBase.h"

//
// Move the arm to a given degree
//
class ArmMove : public CommandBase {

private:
  float targetAngle;     // Arm angle in degrees with horizontal = 0
  float margin;          // Margin of "close enough" for target angle
  int   iteration;       // Number of iteration attempted to set arm angle

  void MeasureAndMove();      // Take an angle measurement and start moving
  void StopAndQuiet();        // Stop and wait for bounding to settle
  bool GetDesiredDirection(); // Determine which direction to go
  bool IsAtTargetAngle();     // Are we there yet?

public:
  ArmMove(float angle, float margin = 1.0);

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

};

#endif /* __ARM_MOVE_H__ */
