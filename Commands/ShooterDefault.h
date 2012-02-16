#ifndef __SHOOTER_DEFAULT_H__
#define __SHOOTER_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/ArmAccelerometer.h"

class ShooterDefault: public CommandBase {
private:
public:
	ShooterDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
