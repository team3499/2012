#ifndef STOP_ALL_COMMAND_H
#define STOP_ALL_COMMAND_H

#include "../CommandBase.h"

class StopAll : public CommandBase {
public:
	StopAll();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
