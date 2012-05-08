#include "ArmLevel.h"
#include "WPILib.h"
#include "FiringSolution.h"

ArmLevel::ArmLevel(float targ)
{
	// Use requires() here to declare subsystem dependencies
	Requires(arm);
	Requires(accelerometer);
	angle = targ;
	direction = (accelerometer->GetArmDegree() > angle)? reverse : forward ;
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
	float angle = accelerometer->GetArmDegree();
	if((angle < angle && angle > -75)){
		direction = forward;
	}else if(angle > angle && angle < 90 ){
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
		if((angle - angle) > 2) {direction = (ArmLevel::Moving)-direction;}
		// If the arm has gone by the target, switch directions
		else if(angle > angle) {direction = stopped;}
		else arm->Move(true); // dont care if it is already set. set it anyway
		// should also change this function to take a directional enum
		break;
	case reverse: // current angle > target
		if((angle - angle) < 2) {direction = (ArmLevel::Moving)-direction;}
		else if(angle < angle) {direction = stopped;}
		// if the arm has gone by the target, switch directions
		else arm->Move(false); // dont care if it is already set. set it anyway
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
