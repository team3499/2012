#include "LightsCommand.h"
#include "WPILib.h"

LightsCommand::LightsCommand()
{
	// Use requires() here to declare subsystem dependencies
	Requires(lights);
}

// Called just before this Command runs the first time
void LightsCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void LightsCommand::Execute() {
	lights->Toggle2();
}

// Make this return true when this Command no longer needs to run execute()
bool LightsCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LightsCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LightsCommand::Interrupted() {
}
