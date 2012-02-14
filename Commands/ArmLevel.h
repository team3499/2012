#ifndef __ARM_LEVEL_H__
#define __ARM_LEVEL_H__

#include "CommandBase.h"

class ArmLevel: public CommandBase {
public:
	ArmLevel();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
