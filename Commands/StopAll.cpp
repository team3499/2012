#include "StopAll.h"

StopAll::StopAll() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(arm);
	Requires(accelerometer);
	Requires(camera);
	Requires(chassis);
	Requires(chassisGyro);
	Requires(lights);
	Requires(magazine);
	Requires(rangefinder);
	Requires(shooter);
}

// Called just before this Command runs the first time
void StopAll::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void StopAll::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StopAll::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StopAll::End() {
	this->Interrupted();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAll::Interrupted() {
	arm->Stop();
	chassis->Stop();
	magazine->Stop();
	shooter->Stop();
	lights->All(true);
}
