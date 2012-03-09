
#include "Commands/DAG.h"

DAG::DAG()
{
	SmartDashboard::Log("Turning", "Shooting Status");
//	AddSequential(new Forward(100));
	AddSequential(new Turn(12));
	SmartDashboard::Log("Calculating arm level and balancing", "Shooting Status");
	AddSequential(new ArmAim());
	SmartDashboard::Log("Shooting", "Shooting Status");
	AddSequential(new ShootBalls());
	SmartDashboard::Log("Done/Ready", "Shooting Status");
}
