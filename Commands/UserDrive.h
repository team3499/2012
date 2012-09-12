#ifndef USERDRIVE_H
#define USERDRIVE_H

#include "CommandBase.h"
#include "Subsystems/Chassis.h"

class UserDrive: public CommandBase {
private:
public:
	UserDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
