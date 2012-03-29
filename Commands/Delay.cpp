#include "Delay.h"

Delay::Delay(float time) {
	this->time = time;
}

// Called just before this Command runs the first time
void Delay::Initialize() {
	timer = new Timer();
}

// Called repeatedly when this Command is scheduled to run
void Delay::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Delay::IsFinished() {
	if(timer->HasPeriodPassed(time)){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Delay::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Delay::Interrupted() {
}
