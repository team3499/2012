#include "ArmLevel.h"
#include "WPILib.h"

ArmLevel::ArmLevel(float targ)
{
	// Use requires() here to declare subsystem dependencies
	Requires(arm);
	Requires(accelerometer);
	target = targ;
}

// Called just before this Command runs the first time
void ArmLevel::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmLevel::Execute() {
	float angle = accelerometer->GetArmDegree();
	if(angle > target && angle < 135){
		arm->Move(-.60);
	}else if(angle < target || angle >= 135){
		arm->Move(.6);
	} else {
		arm->Stop();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmLevel::IsFinished() {
	float angle = accelerometer->GetArmDegree();
	if (angle > target - 2 && angle < target + 2){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ArmLevel::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmLevel::Interrupted() {
}
