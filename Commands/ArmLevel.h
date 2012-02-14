#ifndef __ARM_LEVEL_H__
#define __ARM_LEVEL_H__

#include "CommandBase.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Accelerometer2.h"

class ArmLevel: public CommandBase {
private:
public:
	ArmLevel();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
