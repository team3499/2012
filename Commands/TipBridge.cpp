#include "Commands/TipBridge.h"

TipBridge::TipBridge() {
  needsReset = false;
  moving     = false;

  Requires(arm);
  Requires(accelerometer);
};

// Check if the arm is raised high enough to clear the bridge - if it
// isn't, flag that so execution can raise the arm and then lower it.
// TODO - Get minimum angle to clear bridge in neutral position.
void TipBridge::Initialize() {
  if (accelerometer->GetArmDegree() < 35.0) { needsReset = true; }
}

// Optionally raises the arm to clear the bridge, then lowers it.
// TODO - Get minimum angle to clear bridge in neutral position
void TipBridge::Execute() {
  if (needsReset) {
    if (!moving) { RaiseArm(); }
    if (accelerometer->GetArmDegree() > 35.0) {
      needsReset = false;
      StopArm();
    }
  } else {
    LowerArm();
  }
}

// The arm is finished once it is lowered far enough to tip
// the bridge down to the ground.  TODO - Get degree
bool TipBridge::IsFinished() {
  if (!needsReset && accelerometer->GetArmDegree() < 10.0) { return true; }
  else { return false; }
}

// All done - stop the arm
void TipBridge::End() {
  StopArm();
}

// When interrupted, stop the arm before handing off to
// the interrupting command.
void TipBridge::Interrupted() {
  StopArm();
}

/////////////////////////////////////////////////////////////////////////////

void TipBridge::RaiseArm() {
  moving = true;
  arm->Move(false);
}

void TipBridge::LowerArm() {
  moving = true;
  arm->Move(true);
}

void TipBridge::StopArm() {
  moving = false;
  arm->Stop();
}
