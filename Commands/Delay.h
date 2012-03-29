#ifndef DELAY_COMMAND_H
#define DELAY_COMMAND_H

#include "../CommandBase.h"
#include "Timer.h"

class Delay: public CommandBase {
private:
	Timer *timer;
	float time;
public:
	Delay(float time = 1.0);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
