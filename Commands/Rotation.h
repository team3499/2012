#ifndef ROTATION_H
#define ROTATION_H

#include "../CommandBase.h"
#include "../Sensors/Lights.h"
#include "../Sensors/Accelerometer2.h"
#include "../OI.h"
#include "../Subsystems/Launcher.h"

class Rotation: public CommandBase {
private:
	Lights lights;
	Accelerometer2 acc;
	int i;
public:
	Rotation(Launcher *launcher);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	Launcher *launcher;
};

#endif
