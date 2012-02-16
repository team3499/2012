#ifndef __MAGAZINE_DEFAULT_H__
#define __MAGAZINE_DEFAULT_H__

#include "CommandBase.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/ArmAccelerometer.h"

class MagazineDefault: public CommandBase {
private:
public:
	MagazineDefault();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
