#include "ArmMove.h"
#include "WPILib.h"

ArmMove::ArmMove(float angle, float margin)
{
  Requires(arm);
  Requires(accelerometer);

  iteration    = 0;
  targetAngle  = angle;
  this->margin = margin;
}

// Initialize will set the iteration counter to zero, wait a bit,
// measure the current arm angle, and then start the motors moving
// in the right direction.
void ArmMove::Initialize() {
  iteration = 0;
  MeasureAndMove();
}


// Checks if we've reached the target angle.  If so, stop, wait a bit
// and then check if we are still there.  If not, start moving again.
void ArmMove::Execute() {
  if (IsAtTargetAngle()) {
    ++iteration;
    StopAndQuiet();
    if (!IsAtTargetAngle()) { MeasureAndMove(); }
  }
}

// Bail out once we are at the target angle or if we've tried 3 times
// TODO - is 3 times enough?
bool ArmMove::IsFinished() {
  return (IsAtTargetAngle() || iteration > 3 );  
}

void ArmMove::End() {
  arm->Stop();
}

void ArmMove::Interrupted() {
  End();
}

//////////////////////////////////////////////////////////////////////////////

// Stop the arm and wait for it to cease bouncing, take an angle measurement,
// and then start moving again.
void ArmMove::MeasureAndMove() {
  StopAndQuiet();
  if (!IsAtTargetAngle()) { arm->Move(GetDesiredDirection()); }
}

// Stop the arm and wait for it to cease bouncing
void ArmMove::StopAndQuiet() {
  arm->Stop();
  Wait(0.5);
}

// Returns true if the arm needs to move forward, false if backward
// (see Subsystems/Arm.cpp)
bool ArmMove::GetDesiredDirection() {
  return (accelerometer->GetArmDegree() > targetAngle);
}

// Returns true if the arm is close to the desired target angle or if
// it's going to hit the robot
bool ArmMove::IsAtTargetAngle() {
  float currentAngle = accelerometer->GetArmDegree();
  return (currentAngle < -75 || currentAngle > 90.0 || (currentAngle + margin > targetAngle && currentAngle - margin < targetAngle));
}
