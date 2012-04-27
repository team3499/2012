#ifndef STOP_ALL_COMMAND_H
#define STOP_ALL_COMMAND_H

#include "../CommandBase.h"

class StopAll : public CommandBase {
public:
	bool stop;
	StopAll();
	StopAll(bool stop);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
