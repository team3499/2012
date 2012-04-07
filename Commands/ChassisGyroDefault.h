#ifndef CHASSIS_GYRO_DEFAULT_H
#define CHASSIS_GYRO_DEFAULT_H

#include "CommandBase.h"
#include "Subsystems/ChassisGyro.h"

class ChassisGyroDefault: public CommandBase {
private:
	int counter;
public:
	ChassisGyroDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
