#include "ShooterDefault.h"
#include "WPILib.h"

ShooterDefault::ShooterDefault()
{
	// Use requires() here to declare subsystem dependencies
	Requires(shooter);
}

// Called just before this Command runs the first time
void ShooterDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShooterDefault::Execute() {
	if(oi->GetRawButton(2,4)){
		shooter->Shoot(1.0);
	} else if (oi->GetRawButton(2,5)){
		shooter->Shoot(-.50);
	} else {shooter->Stop();}
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterDefault::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterDefault::Interrupted() {
}
