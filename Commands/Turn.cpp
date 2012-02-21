#include "Turn.h"
#include "SmartDashboard/SmartDashboard.h"
#include "WPILib.h"

Turn::Turn(float angle, float speed)
{
  relativeAngle = angle;
  desiredAngle  = 0;
  direction     = Unknown;
  iteration     = 0;
  this->speed   = speed;
  if (speed < 0.0) { speed = -speed; }
  if (this->speed > 1.0) { this->speed = 1.0; }

  Requires(chassis);
  Requires(chassisGyro);
}

void Turn::Initialize() {
  desiredAngle = chassisGyro->GetDesiredAngle(relativeAngle);
  if (relativeAngle > 0) { direction = Right; }
  else { direction = Left; }
}

void Turn::Execute() {
  float turnAngleRemaining = desiredAngle - chassisGyro->GetAngle();
  if (turnAngleRemaining > 0) {    // Right turn needed
    if (direction == Left) {       // Doh!  We're going left so that means
      direction = Right;           // we overshot.  Stop and go back slower
      chassis->Stop();
      Wait(0.5);
      speed = speed / 2;
      iteration++;
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
    } else {                       // AOK - keep going
      chassis->TankDrive(-speed, speed);
    }
  }
}

bool Turn::IsFinished() {
  if (iteration > 3) { return true; }

  return chassisGyro->IsAtAngle(desiredAngle);
}

void Turn::End() {
  chassis->Stop();
}

void Turn::Interrupted() {
  End();
}
