#ifndef __SHOOT_BALLS_H__
#define __SHOOT_BALLS_H__

#include "CommandBase.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Magazine.h"

class ShootBalls: public CommandBase {
private:
	int stat;
	Timer *timer;
public:
	ShootBalls();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
