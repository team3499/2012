#ifndef SHOOTER_DRIVE_H
#define SHOOTER_DRIVE_H

#include "CommandBase.h"
#include "Subsystems/Shooter.h"

class ShooterMan: public CommandBase {
private:
public:
	ShooterMan();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
