#include "ArmMove.h"
#include "WPILib.h"

ArmMove::ArmMove(float angle)
{
  // Use requires() here to declare subsystem dependencies
  Requires(arm);
  Requires(accelerometer);

  targetAngle = angle;
}

// Called just before this Command runs the first time
void ArmMove::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmMove::Execute() {
  float angle = accelerometer->GetArmDegree();
  if((angle < targetAngle && angle > -75)){
    arm->Move(true);
  }else if(angle > targetAngle && angle < 90 ){
    arm->Move(true);
  } else {
    arm->Stop();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ArmMove::IsFinished() {
  float angle = accelerometer->GetArmDegree();
  if (angle > targetAngle - 2 && angle < targetAngle + 2){
    return true;
  }
  return false;
}

// Called once after isFinished returns true
void ArmMove::End() {
  
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmMove::Interrupted() {
}
