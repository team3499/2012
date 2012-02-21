#include "TurnToCamera.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"

TurnToCamera::TurnToCamera(float speed)
{
  desiredAngle  = 0;
  direction     = Unknown;
  iteration     = 0;
  this->speed   = speed;
  if (speed < 0.0) { speed = -speed; }
  if (this->speed > 1.0) { this->speed = 1.0; }

  Requires(chassis);
  Requires(chassisGyro);
  Requires(camera);
}

void TurnToCamera::Initialize() {
  desiredAngle = GetAbsoluteCameraAngle();
  if (chassisGyro->GetAngle() < desiredAngle) { direction = Right; }
  else { direction = Left; }
}

void TurnToCamera::Execute() {
  float turnAngleRemaining = desiredAngle - chassisGyro->GetAngle();
  if (turnAngleRemaining > 0) {    // Right turn needed
    if (direction == Left) {       // Doh!  We're going left so that means
      direction = Right;           // we overshot.  Stop and go back slower
      chassis->Stop();
      Wait(0.5);
      speed = speed / 2;
      iteration++;
      desiredAngle = GetAbsoluteCameraAngle();
    } else {                       // AOK - keep going
      chassis->TankDrive(speed, -speed);
    }
  } else {                         // Left turn needed
    if (direction == Right) {      // Doh!  We're going right so that means
      direction = Left;            // we overshot.  Stop and go back slower
      chassis->Stop();
      Wait(0.5);
      speed = speed / 2;
      iteration++;
      desiredAngle = GetAbsoluteCameraAngle();
    } else {                       // AOK - keep going
      chassis->TankDrive(-speed, speed);
    }
  }
}

bool TurnToCamera::IsFinished() {
  if (iteration > 3) { return true; }

  return chassisGyro->IsAtAngle(desiredAngle);
}

void TurnToCamera::End() {
  chassis->Stop();
}

void TurnToCamera::Interrupted() {
  End();
}

//////////////////////////////////////////////////////////////////////////////

float TurnToCamera::GetAbsoluteCameraAngle() {
  return chassisGyro->GetDesiredAngle(camera->GetAngleData().xAxisTurn);
}
