#include "Commands/DriveForward.h"

DriveForward::DriveForward(double duration, float speed, bool keepGoing) {
  this->duration  = duration;
  this->speed     = speed;
  this->keepGoing = keepGoing;

  timer = new Timer;

  Requires(chassis);
};

void DriveForward::Initialize() {
  timer->Start();
  chassis->TankDrive(-speed, speed);
}

void DriveForward::Execute() {

}

bool DriveForward::IsFinished() {
  return timer->HasPeriodPassed(duration);
}

void DriveForward::End() {
  if (!keepGoing) { chassis->TankDrive(0.0, 0.0); }
}

void DriveForward::Interrupted() {
  chassis->TankDrive(0.0, 0.0);
}

/////////////////////////////////////////////////////////////////////////////

