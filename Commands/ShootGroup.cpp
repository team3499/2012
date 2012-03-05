#include "Commands/Turn.h"
#include "Commands/ArmMove.h"
#include "Commands/ShootBalls.h"
#include "Commands/ShootGroup.h"
#include "WPILib.h"

ShootGroup::ShootGroup()
{
	AddParallel(new Turn());
	AddParallel(new ArmMove(-35));
	printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
	AddSequential(new ShootBalls());
}
