#ifndef __ARM_DEFAULT_H__
#define __ARM_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/Arm.h"
#include "Subsystems/ArmAccelerometer.h"

class ArmDefault: public CommandBase {
private:
public:
	ArmDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
