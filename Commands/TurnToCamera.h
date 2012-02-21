#ifndef __COMMAND_TURN_TO_CAMERA_H__
#define __COMMAND_TURN_TO_CAMERA_H__

#include "CommandBase.h"
#include "Commands/Turn.h"

//
//  Turns the chassis to the angle specified by the camera
//
class TurnToCamera : public CommandBase {

private:
  float desiredAngle;
  float speed;
  int   iteration;

  enum Direction {
    Unknown,
    Right,
    Left
  };
  Direction direction;

  float GetAbsoluteCameraAngle();

public:

  TurnToCamera(float speed = 0.2);

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();
};

#endif /* __COMMAND_TURN_TO_CAMERA_H__ */
