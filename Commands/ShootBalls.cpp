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
	shooter->Move(-1.0);
	this->timer = new Timer();
	timer->Start();
	stat = 0;
}

// Called repeatedly when this Command is scheduled to run
void ShootBalls::Execute() {
	/*------------------------------------\
	| spin belts for 1/10 sec,            |
	| shoot belts for 1/4 sec.            |
	\------------------------------------*/
	if (stat == 0 && timer->HasPeriodPassed(.1)){
		magazine->Set(-.5);
		stat = 1;
	} else if(stat == 1 && timer->HasPeriodPassed(.25)){
		magazine->Stop();
		stat = 2;
	} else if(stat == 2 && timer->HasPeriodPassed(.1)){
		magazine->Set(-.5);
		stat = 3;
	} else if(stat == 3 && timer->HasPeriodPassed(.25)){
		magazine->Stop();
		stat = 4;
	} else if(stat == 4 && timer->HasPeriodPassed(.1)){
		magazine->Set(-.5);
		stat = 5;
	} else if(stat == 5 && timer->HasPeriodPassed(.25)){
		magazine->Stop();
		stat = 6;
	}
	printf("Time passed:%f\n",timer->Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBalls::IsFinished() {
	if(stat == 6 && timer->HasPeriodPassed(1.05)){
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
