
#include "Commands/AutoGroup.h"

AutoGroup::AutoGroup(bool isAuto)
{
	if(isAuto){
		SmartDashboard::Log(true,"AutoEnabled");
		AddSequential(new DriveForward(2,1.0,false));
	}
	SmartDashboard::Log("Turning", "Shooting Status");
	AddSequential(new Turn());
	SmartDashboard::Log("Calculating arm level and balancing", "Shooting Status");
	AddSequential(new ArmAim());
	SmartDashboard::Log("Shooting", "Shooting Status");
	AddSequential(new ShootBalls());
	SmartDashboard::Log("Done/Ready", "Shooting Status");
}
