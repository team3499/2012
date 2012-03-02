#include "Turn.h"
#include "WPILib.h"
#include "Subsystems/Camera.h"
#include "Commands/ShootBalls.h"

Turn::Turn()
{
	Requires(chassis);
	Requires(chassisGyro);
	Requires(camera);
	//Requires(CHARLIES_VISION_ANGLE);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	turnAngle = camera->GetAngleData().xAxisTurn;
	turnTo = chassisGyro->GetDesiredAngle(turnAngle);
	/* SETUP (reset gyro angle to 0 during autonomus)*/
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	printf("Turn Executing\n");
	if(!IsFinished()){
		double CA = chassisGyro->GetHeading();
		if(turnTo < CA-180){
			chassis->TankDrive(.4,-.4);
		} else {
			chassis->TankDrive(-.4,.4);
		}
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	if( turnTo < chassisGyro->GetAngle()){
		chassis->TankDrive(0.0,0.0);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Turn::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {
}
