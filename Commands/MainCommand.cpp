#include "MainCommand.h"
#include "C:\WindRiver\vxworks-6.3\target\h\WPIlib\DigitalOutput.h"

MainCommand::MainCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void MainCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void MainCommand::Execute() {
	if (oi->GetRawButton(1,3)){
		//turn and shoot
	} else if(oi->GetRawButton(2,3)){
		//raise the arm
	} else if(oi->GetRawButton(2,2)){
		
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MainCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MainCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MainCommand::Interrupted() {
}
