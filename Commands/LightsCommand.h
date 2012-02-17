#ifndef __LIGHTS_DEFAULT_H__
#define __LIGHTS_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/ArmAccelerometer.h"

class LightsCommand: public CommandBase {
private:
public:
	LightsCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
