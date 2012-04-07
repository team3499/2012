#include "ChassisGyroDefault.h"
#include "WPILib.h"
#include "Subsystems/ChassisGyro.h"

ChassisGyroDefault::ChassisGyroDefault()
{
	Requires(chassisGyro);
}

// Called just before this Command runs the first time
void ChassisGyroDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ChassisGyroDefault::Execute() {
	SmartDashboard::Log(chassisGyro->GetAngle(),"Chassis Gyro Angle");
}

// Make this return true when this Command no longer needs to run execute()
bool ChassisGyroDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ChassisGyroDefault::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChassisGyroDefault::Interrupted() {
}
