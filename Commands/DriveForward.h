#ifndef __DRIVE_FORWARD_H__
#define __DRIVE_FORWARD_H__

#include "CommandBase.h"
#include "Timer.h"

//
// Drive the robot forward for *duration* seconds at *speed* (0.0-1.0)
//
class DriveForward : public CommandBase {

private:

  Timer * timer;
  double  duration;
  float   speed;
  bool    keepGoing;

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

public:
  DriveForward(double duration, float speed, bool keepGoing = false);
};

#endif /* __DRIVE_FORWARD_H__ */
