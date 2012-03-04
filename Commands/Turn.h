#ifndef __COMMAND_TURN_H__
#define __COMMAND_TURN_H__

#include "CommandBase.h" 
#include "Subsystems/Chassis.h"

//
//  Turns the chassis to a relative angle
//
class Turn : public CommandBase {

private:
  float relativeAngle;
  float desiredAngle;
  float speed;
  int   iteration;

  enum Direction {
    Unknown,
    Right,
    Left
  };
  Direction direction;

public:
    Turn(float angle = 0.0, float speed = 0.2);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif /* __COMMAND_TURN_H__ */
