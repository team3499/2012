
#include "Commands/AutoGroup.h"

AutoGroup::AutoGroup()
{
	SmartDashboard::Log("Turning", "Shooting Status");
	AddSequential(new DriveForward(1,1.0,false));
	AddSequential(new Turn());
	SmartDashboard::Log("Calculating arm level and balancing", "Shooting Status");
	AddSequential(new ArmAim());
	SmartDashboard::Log("Shooting", "Shooting Status");
	AddSequential(new ShootBalls());
	SmartDashboard::Log("Done/Ready", "Shooting Status");
}
