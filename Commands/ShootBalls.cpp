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
	magazine->Set(-0.45);
	this->timer = new Timer();
	timer->Start();
	stat = 0;
}

// Called repeatedly when this Command is scheduled to run
void ShootBalls::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBalls::IsFinished() {
	if(timer->HasPeriodPassed(2)){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ShootBalls::End() {
	shooter->Stop();
	magazine->Stop();
	printf("ShootBalls Finished. Time Taken:%f\n",timer->Get());
	delete timer;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBalls::Interrupted() {
	End();
}
