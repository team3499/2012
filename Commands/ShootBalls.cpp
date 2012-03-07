#include "ShootBalls.h"
#include "ArmLevel.h"
#include "WPILib.h"

ShootBalls::ShootBalls()
{
	// Use requires() here to declare subsystem dependencies
	Requires(shooter);
	Requires(magazine);
}

// Called just before this Command runs the first time
void ShootBalls::Initialize() {
	shooter->Move(1.0);
	timer = new Timer();
	timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ShootBalls::Execute() {
	/*------------------------------------\
	| spin belts for 1/10 sec,            |
	| shoot belts for 1/4 sec.            |
	\------------------------------------*/
	if (timer->HasPeriodPassed(.1)){
		magazine->Set(.5);
	} else if(timer->HasPeriodPassed(.35)){
		magazine->Stop();
	} else if(timer->HasPeriodPassed(.45)){
		magazine->Set(.5);
	} else if(timer->HasPeriodPassed(.7)){
		magazine->Stop();
	} else if(timer->HasPeriodPassed(.8)){
		magazine->Set(.5);
	} else if(timer->HasPeriodPassed(1.05)){
		magazine->Stop();
	}
	printf("Time passed:%f\n",timer->Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBalls::IsFinished() {
	if(timer->HasPeriodPassed(1.05)){
		shooter->Stop();
		magazine->Stop();
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ShootBalls::End() {
	printf("ShootBalls Finished\n");
	delete timer;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBalls::Interrupted() {
}
