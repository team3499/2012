#include "ArmAim.h"
#include "FiringSolution.h"

//
// Aim the arm at the passed target.  Note!  ArmAim "owns" the
// Target object passed and will destroy it when finished.
//
ArmAim::ArmAim(Target *target) {
  Requires(arm);
  Requires(accelerometer);
  Requires(rangefinder);

  iteration = 0;
  angle     = 0.0;
  margin    = 1.0;

  if (target == NULL) { target = new Target(Target::Middle); }
}

ArmAim::~ArmAim() {
  delete target;
  target = NULL;
}

// Initialize will set the iteration counter to zero, wait a bit,
// measure the current arm angle, and then start the motors moving
// in the right direction.
void ArmAim::Initialize() {
  iteration = 0;
  angle = FiringSolution((float)(rangefinder->GetDistance()), *target).GetAngle();
  MeasureAndMove();
}


// Checks if we've reached the target angle.  If so, stop, wait a bit
// and then check if we are still there.  If not, start moving again.
void ArmAim::Execute() {
  if (IsAtTargetAngle()) {
    ++iteration;
    StopAndQuiet();
    if (!IsAtTargetAngle()) { MeasureAndMove(); }
  }
}

// Bail out once we are at the target angle or if we've tried 3 times
// TODO - is 3 times enough?
bool ArmAim::IsFinished() {
  return (IsAtTargetAngle() || iteration > 3 );
}

void ArmAim::End() {
  arm->Stop();
}

void ArmAim::Interrupted() {
  End();
}

//////////////////////////////////////////////////////////////////////////////

// Stop the arm and wait for it to cease bouncing, take an angle measurement,
// and then start moving again.
void ArmAim::MeasureAndMove() {
  StopAndQuiet();
  if (!IsAtTargetAngle()) { arm->Move(GetDesiredDirection()); }
}

// Stop the arm and wait for it to cease bouncing
void ArmAim::StopAndQuiet() {
  arm->Stop();
  Wait(0.5);
}

// Returns true if the arm needs to move forward, false if backward
// (see Subsystems/Arm.cpp)
bool ArmAim::GetDesiredDirection() {
  return (accelerometer->GetArmDegree() > angle);
}

// Returns true if the arm is close to the desired target angle or if
// it's going to hit the robot
bool ArmAim::IsAtTargetAngle() {
  float currentAngle = accelerometer->GetArmDegree();
  return (currentAngle < -75 || currentAngle > 90.0 || (currentAngle + margin > angle && currentAngle - margin < angle));
}

