#include "ArmLevel.h"
#include "WPILib.h"
#include "FiringSolution.h"

#define max(a,b) ((a > b) ? (a) : (b))
#define min(a,b) ((a < b) ? (a) : (b))

ArmLevel::ArmLevel(float targ)
{
	// Use requires() here to declare subsystem dependencies
	Requires(arm);
	Requires(accelerometer);
	this->angle = targ;
	target = NULL;
	direction = (accelerometer->GetArmDegree() > this->angle)? reverse : forward ;
}


ArmLevel::ArmLevel()
{
	// Use requires() here to declare subsystem dependencies
	Requires(arm);
	Requires(accelerometer);
	Requires(camera);
	if (camera->GetLastGoodTarget() == NULL) {
	  target = new Target(Target::Middle);
	} else {
	  target = new Target(camera->GetLastGoodTarget()->GetIdentifier());
	}
	angle = -FiringSolution((float)(rangefinder->GetDistance()), *target).GetAngle();
	  
	direction = (accelerometer->GetArmDegree() > angle)? reverse : forward ;
}

ArmLevel::~ArmLevel(){
	  delete target;
	  target = NULL;
}

// Called just before this Command runs the first time
void ArmLevel::Initialize() {
	this->angle = min(80, this->angle);
	this->angle = max(-75, this->angle);
	float angle = accelerometer->GetArmDegree();
	if((angle < this->angle && angle < 80)){
		direction = forward;
	}else if(angle < this->angle && angle > -75 ){
		direction = reverse;
	} else {
		arm->Stop();
	}
}

// Called repeatedly when this Command is scheduled to run
void ArmLevel::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ArmLevel::IsFinished() {
	float angle = accelerometer->GetArmDegree();
	
	switch(direction){
	case forward: // current angle < target
		if((angle - this->angle) > 2) {direction = (ArmLevel::Moving)-direction;}
		// If the arm has gone by the target, switch directions
		else if(angle > this->angle) {direction = stopped;}
		else arm->Move(false); // dont care if it is already set. set it anyway
		// should also change this function to take a directional enum
		break;
	case reverse: // current angle > target
		if((angle - this->angle) < 2) {direction = (ArmLevel::Moving)-direction;}
		else if(angle < this->angle) {direction = stopped;}
		// if the arm has gone by the target, switch directions
		else arm->Move(true); // dont care if it is already set. set it anyway
		// should also change this function to take a directional enum
		break;
	case stopped:
		return true;
	default:// big problem, so just stop;
		//could restart here but for now...
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ArmLevel::End() {
	arm->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmLevel::Interrupted() {
	End();
}


//
//move(false)
//
//     +===+
//     |   | ->
//     +===+
//       |
//       |
//  +=========+
//  |R       F|
//  +=========+
