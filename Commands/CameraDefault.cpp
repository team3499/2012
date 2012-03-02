#include "CameraDefault.h"
#include "WPILib.h"
#include "Subsystems/Camera.h"

CameraDefault::CameraDefault()
{
	Requires(camera);
	//Requires(CHARLIES_VISION_ANGLE);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CameraDefault::Initialize() {
	counter = 0;
	/* SETUP (reset gyro angle to 0 during autonomus)*/
}

// Called repeatedly when this Command is scheduled to run
void CameraDefault::Execute() {
	printf("<>>%f<<>",camera->GetAngleData().xAxisTurn);
	printf("\nOn 50th time\n");
}

// Make this return true when this Command no longer needs to run execute()
bool CameraDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CameraDefault::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraDefault::Interrupted() {
}
