#ifndef ROTATION_H
#define ROTATION_H

#include "../CommandBase.h"
#include "../Sensors/Lights.h"
#include "../Sensors/Accelerometer2.h"

class Rotation: public CommandBase {
private:
	Lights lights;
	Accelerometer2 acc;
	int i;
public:
	Rotation();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
