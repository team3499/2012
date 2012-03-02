#ifndef CAMERA_DEFAULT_H
#define CAMERA_DEFAULT_H

#include "CommandBase.h"
#include "Subsystems/Camera.h"

class CameraDefault: public CommandBase {
private:
	int counter;
public:
	CameraDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
