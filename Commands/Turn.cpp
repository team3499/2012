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
	turnAngle = 0;
	//Requires(CHARLIES_VISION_ANGLE);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

Turn::Turn(float angle)
{
	Requires(chassis);
	Requires(chassisGyro);
	turnAngle = angle;
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	if(turnAngle == 0){
		turnAngle = camera->GetTarget()->GetHorizontalAngle();
	}
	turnTo = chassisGyro->GetDesiredAngle(turnAngle);
	if(absolute(turnAngle-turnTo) >= 15){
		turnSpeed = 0.95;
	} else if(absolute(turnAngle-turnTo) >= 10){
		turnSpeed = 0.70;
	} else if(absolute(turnAngle-turnTo) >= 5){
		turnSpeed = 0.55;
	} else {
		turnSpeed = 0.40;
	}
	if(turnTo > turnAngle){
		turnSpeed *= -1;
	}
	chassis->TankDrive(turnSpeed,turnSpeed);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	printf("Executing Turn. Gyro: %f\n",chassisGyro->GetAngle());
	//turnAngle = camera->GetAngleData().xAxisTurn;
	if(absolute(chassisGyro->GetAngle()-turnTo) >= 15){
		turnSpeed = 0.95;
	} else if(absolute(chassisGyro->GetAngle()-turnTo) >= 10){
		turnSpeed = 0.70;
	} else if(absolute(chassisGyro->GetAngle()-turnTo) >= 5){
		turnSpeed = 0.55;
	} else {
		turnSpeed = 0.40;
	}
	if(turnTo > chassisGyro->GetAngle()){
		turnSpeed *= -1;
	}
	chassis->TankDrive(turnSpeed,turnSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	if(chassisGyro->IsAtAngle(turnTo, 1.0)){
		printf("Finished Turn.\n");
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
