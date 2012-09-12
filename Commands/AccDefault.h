#ifndef __ACC_DEFAULT_H__
#define __ACC_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/ArmAccelerometer.h"

class AccDefault: public CommandBase {
private:
public:
	AccDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
