#include "ArmLevel.h"
#include "WPILib.h"

ArmLevel::ArmLevel()
{
	// Use requires() here to declare subsystem dependencies
	Requires(accelerometer);
	Requires(arm);
}

// Called just before this Command runs the first time
void ArmLevel::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmLevel::Execute() {
	double deg = accelerometer->GetArmDegree();
	if(deg > -88 && deg < 45){
		arm->Move(true);
	} else if (deg < -92 || deg >= 45){
		arm->Move(0);
	} else {arm->Stop();}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmLevel::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmLevel::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmLevel::Interrupted() {
}
