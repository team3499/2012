#ifndef __AUTO_GROUP_H__
#define __AUTO_GROUP_H__

#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "Commands/Turn.h"
#include "Commands/ArmAim.h"
#include "Commands/ShootBalls.h"


class AutoGroup: public CommandGroup {
private:
public:
	AutoGroup();
};

#endif
