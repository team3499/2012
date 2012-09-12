#ifndef __ACC_DEFAULT_H__
#define __ACC_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/ArmAccelerometer.h"

class GyroDefault: public CommandBase {
private:
public:
	GyroDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
