#include "ShootBalls.h"
#include "WPILib.h"

ShootBalls::ShootBalls()
{
	// Use requires() here to declare subsystem dependencies
	Requires(shooter);
	Requires(magazine);
	stat = 1;
}

// Called just before this Command runs the first time
void ShootBalls::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShootBalls::Execute() {
	Magazine::StatusEnum status = magazine->Status();
	if (stat > 50){
		shooter->Stop();
		stat = 0;
	} else if (stat > 10 && stat < 50){
		stat++;
	} else if (status == Magazine::shooting && !magazine->BallCount()){
		magazine->Stop();
		stat = 10;
	} else if (magazine->IsReadyToFire()){
		shooter->Shoot(true);
		magazine->Move(0.5);
		magazine->SetShooting(1);
	} else {
		magazine->Move(.5);
	}
	;
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBalls::IsFinished() {
	if(stat = 0){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ShootBalls::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBalls::Interrupted() {
}
