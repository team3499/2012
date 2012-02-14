#ifndef _MAIN_COMMAND_H
#define _MAIN_COMMAND_H

#include "../CommandBase.h"

class MainCommand: public CommandBase {
public:
	MainCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
