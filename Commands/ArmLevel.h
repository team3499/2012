#ifndef __ARM_LEVEL_H__
#define __ARM_LEVEL_H__

#include "CommandBase.h"
#include "Subsystems/Arm.h"
#include "Subsystems/ArmAccelerometer.h"

class ArmLevel: public CommandBase {
private:
	float target;
	enum Moving {
		forward = -1,
		stopped =  0,
		reverse =  1
	} direction;
public:
	ArmLevel(float targ);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
