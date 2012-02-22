#include "Commands/Turn.h"
#include "Commands/ArmLevel.h"
#include "Commands/ShootBalls.h"
#include "Commands/ShootGroup.h"
#include "WPILib.h"

ShootGroup::ShootGroup()
{
	AddParallel(new Turn());
	AddParallel(new ArmLevel(-35));
	AddSequential(new ShootBalls());
}
