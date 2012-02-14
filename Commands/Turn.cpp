#include "Turn.h"
#include "WPILib.h"

Turn::Turn()
{
	Requires(chassis);
	Requires(chassisGyro);
	//Requires(CHARLIES_VISION_ANGLE);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	/* SETUP (reset gyro angle to 0 during autonomus)*/
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	//double turnTo = chassisGyro->GetDesiredAngle(GHARLIES_VISION_ANGLE);
	//if(!IsFinished()){
	//	double CA = chassisGyro->GetCurrentAngle();
	//	if(turnTo < CA-180){
	//		chassis->TankDrive(.4,-.4);
	//	} else {
	//		chassis->TankDrive(-.4,.4);
	//	}
	//}
	
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	//if( CHARLIES_VISION_ANGLE < 1 || CHARLIES_VISION_ANGLE > -1){
	//	return true;
	//}
	return false;
}

// Called once after isFinished returns true
void Turn::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {
}
