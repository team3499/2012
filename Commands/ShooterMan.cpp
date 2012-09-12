#include "ShooterMan.h"
#include "WPILib.h"

ShooterMan::ShooterMan()
{
	Requires(shooter);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ShooterMan::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShooterMan::Execute() {
	shooter->Shoot(oi->GetY(2));
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterMan::IsFinished() {
	//if(!IsOperatorControl() && !IsEnabled()){
	//	return true;
	//}
	return false;
}

// Called once after isFinished returns true
void ShooterMan::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterMan::Interrupted() {
}
