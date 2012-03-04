#include "Turn.h"
#include "WPILib.h"
#include "Subsystems/Camera.h"
#include "Commands/ShootBalls.h"

float absolute(float x){
	if(x < 0){return -x;}
	else return x;
}

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
	if(absolute(turnAngle-turnTo) >= 15){
		turnSpeed = 0.75;
	} else if(absolute(turnAngle-turnTo) >= 10){
		turnSpeed = 0.50;
	} else if(absolute(turnAngle-turnTo) >= 5){
		turnSpeed = 0.35;
	} else {
		turnSpeed = 0.20;
	}
	if(turnTo < turnAngle){
		turnSpeed *= -1;
	}
	chassis->TankDrive(turnSpeed,-turnSpeed);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	turnAngle = camera->GetAngleData().xAxisTurn;
	if(absolute(turnAngle-turnTo) >= 15){
		turnSpeed = 0.75;
	} else if(absolute(turnAngle-turnTo) >= 10){
		turnSpeed = 0.50;
	} else if(absolute(turnAngle-turnTo) >= 5){
		turnSpeed = 0.35;
	} else {
		turnSpeed = 0.20;
	}
	if(turnTo < turnAngle){
		turnSpeed *= -1;
	}
	chassis->TankDrive(turnSpeed,-turnSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	if(chassisGyro->IsAtAngle(turnTo, 1.0)){
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
