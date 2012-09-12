#include "AccDefault.h"
#include "WPILib.h"

AccDefault::AccDefault()
{
	// Use requires() here to declare subsystem dependencies
	Requires(accelerometer);
}

// Called just before this Command runs the first time
void AccDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AccDefault::Execute() {
	SmartDashboard::Log(accelerometer->GetArmDegree(),"Arm Angle");
}

// Make this return true when this Command no longer needs to run execute()
bool AccDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AccDefault::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AccDefault::Interrupted() {
}
