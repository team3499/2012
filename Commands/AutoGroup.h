#ifndef __AUTO_GROUP_H__
#define __AUTO_GROUP_H__

#include "Commands/CommandGroup.h"
#include "Subsystems/ArmAccelerometer.h"

#define AUTONOMUS_DEGREE 45

class AutoGroup: public CommandGroup {
private:
public:
	AutoGroup();
};

#endif
