#include "ArmDefault.h"
#include "WPILib.h"

ArmDefault::ArmDefault()
{
	// Use requires() here to declare subsystem dependencies
	Requires(arm);
}

// Called just before this Command runs the first time
void ArmDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmDefault::Execute() {
	if(oi->GetRawButton(2,2)){
		arm->Move(true);
	} else if (oi->GetRawButton(2,3)){
		arm->Move(false);
	} else {arm->Stop();}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmDefault::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmDefault::Interrupted() {
}
