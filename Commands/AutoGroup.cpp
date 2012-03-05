
#include "Commands/AutoGroup.h"
//#include "Commands/Forward.h"
#include "Commands/Turn.h"
#include "Commands/ArmMove.h"
#include "Commands/ShootBalls.h"
#include "WPILib.h"

AutoGroup::AutoGroup()
{
//	AddSequential(new Forward(100));
	AddParallel(new Turn());
	AddParallel(new ArmMove(AUTONOMUS_DEGREE));
	AddSequential(new ShootBalls());
}
