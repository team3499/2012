#include "MagazineDefault.h"
#include "WPILib.h"

MagazineDefault::MagazineDefault()
{
	// Use requires() here to declare subsystem dependencies
	Requires(magazine);
}

// Called just before this Command runs the first time
void MagazineDefault::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void MagazineDefault::Execute() {
	magazine->Set(oi->GetY(2));
}

// Make this return true when this Command no longer needs to run execute()
bool MagazineDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MagazineDefault::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MagazineDefault::Interrupted() {
}
