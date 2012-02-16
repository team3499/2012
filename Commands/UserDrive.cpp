#include "UserDrive.h"
#include "WPILib.h"
#include "Turn.h"

UserDrive::UserDrive()
{
	Requires(chassis);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void UserDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void UserDrive::Execute() {
	chassis->ArcadeDrive(oi->js1);
	if (oi->GetRawButton(1,3)){
		Command *turn = new Turn();
		turn->Start();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool UserDrive::IsFinished() {
	//if(!IsOperatorControl() && !IsEnabled()){
	//	return true;
	//}
	return false;
}

// Called once after isFinished returns true
void UserDrive::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UserDrive::Interrupted() {
}
