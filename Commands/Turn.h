#ifndef TURN_H
#define TURN_H

#include "CommandBase.h"
#include "Subsystems/Chassis.h"

class Turn: public CommandBase {
private:
public:
	float turnAngle;
	float turnTo;
	Turn();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
