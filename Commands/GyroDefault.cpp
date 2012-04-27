#include "GyroDefault.h"
#include "WPILib.h"

GyroDefault::GyroDefault()
{
	// Use requires() here to declare subsystem dependencies
	Requires(chassisGyro);
}

// Called just before this Command runs the first time
void GyroDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void GyroDefault::Execute() {
	SmartDashboard::Log(chassisGyro->GetAngle(),"Chassis Gyro Angle");
}

// Make this return true when this Command no longer needs to run execute()
bool GyroDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void GyroDefault::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GyroDefault::Interrupted() {
}
