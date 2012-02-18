#ifndef __DRIVE_FORWARD_H__
#define __DRIVE_FORWARD_H__

#include "CommandBase.h"
#include "Timer.h"

class DriveForward : public CommandBase {

private:

  Timer * timer;
  double duration;

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

public:
  DriveForward(double duration = 1.0);      // Extend Arm forward enough to tip bridge to ground
};

#endif /* __DRIVE_FORWARD_H__ */
