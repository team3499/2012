#include "ArmAim.h"
#include "FiringSolution.h"

//
// Aim the arm at the passed target.
//
ArmAim::ArmAim() {
  Requires(arm);
  Requires(accelerometer);
  Requires(rangefinder);

  iteration  = 0;
  angle      = 0.0;
  margin     = 1.0;
  movePeriod = 0.0;
  if (camera->GetLastGoodTarget() == NULL) {
    target = new Target(Target::Middle);
  } else {
    target = new Target(camera->GetLastGoodTarget()->GetIdentifier());
  }
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

  angle = -FiringSolution((float)(rangefinder->GetDistance()), *target).GetAngle();
  SmartDashboard::Log(angle, "Angle (Target)");
  SmartDashboard::Log("QUIETING", "Arm State");
  mode = QUIETING;
  timer.Reset();
  timer.Start();
}

// Moves through a simple state machine:
//  START -> QUIETING for 5 seconds
//  QUIETING -> MEASURING
//  At target angle?  MEASURING -> FINISHED
//  Not at target angle?  MEASURING -> MOVING for period to reach angle
//  MOVING -> QUIETING
void ArmAim::Execute() {
  if (mode == QUIETING) {
    if (timer.HasPeriodPassed(3.5)) {
      mode = MEASURING;
      SmartDashboard::Log("MEASURING", "Arm State");
    }
  } else if (mode == MEASURING) {
	iteration++;
    float currentAngle = accelerometer->GetArmDegree();
    SmartDashboard::Log(angle, "Angle (Arm)");
    if (currentAngle < -85.0 || currentAngle > 70.0 || (currentAngle + margin > angle && currentAngle - margin < angle)) {
      mode = FINISHED;
      SmartDashboard::Log("FINISHED", "Arm State");
    } else if (currentAngle > angle) { // move forward
      movePeriod = (currentAngle - angle) / 65.0;     // GUESS 20 degrees per second when aiming up
      arm->Move(true);
    } else {  // move backward
      movePeriod = (angle - currentAngle) / 20.0;     // GUESS 20 degrees per second when aiming up
      arm->Move(false);
    }
    mode = MOVING;
    SmartDashboard::Log("MOVING", "Arm State");
    timer.Reset();
    timer.Start();
  } else if (mode == MOVING) {
    if (timer.HasPeriodPassed(movePeriod)) {
      arm->Stop();
      mode = QUIETING;
      SmartDashboard::Log("QUIETING", "Arm State");
      timer.Reset();
      timer.Start();
    }
  }
}

// Bail out once we are FINISHED or if we've tried 3 times
// TODO - is 3 times enough?
bool ArmAim::IsFinished() {
  return (mode == FINISHED || iteration > 3);
}

void ArmAim::End() {
  arm->Stop();
}

void ArmAim::Interrupted() {
  End();
}

