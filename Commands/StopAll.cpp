#include "StopAll.h"

StopAll::StopAll() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(arm);
	Requires(accelerometer);
	Requires(camera);
	Requires(chassis);
	Requires(chassisGyro);
	Requires(magazine);
	Requires(rangefinder);
	Requires(shooter);
	stop = false;
}

StopAll::StopAll(bool stop) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(arm);
	Requires(accelerometer);
	Requires(camera);
	Requires(chassis);
	Requires(chassisGyro);
	Requires(magazine);
	Requires(rangefinder);
	Requires(shooter);
	this->stop = stop;
}

// Called just before this Command runs the first time
void StopAll::Initialize() {
	arm->Stop();		// Stop the arm
	chassis->Stop();	// Stop the drive system
	magazine->Stop();	// Stop the launcher (1)
	shooter->Stop();	// Stop the launcher (2)
}

// Called repeatedly when this Command is scheduled to run
void StopAll::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StopAll::IsFinished() {
	return stop;
}

// Called once after isFinished returns true
void StopAll::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAll::Interrupted() {
}
