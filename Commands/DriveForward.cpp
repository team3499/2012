#include "Commands/DriveForward.h"

DriveForward::DriveForward(double duration) {
  this->duration = duration;
  timer = new Timer;

  Requires(chassis);
};

void DriveForward::Initialize() {
  timer->Start();
  chassis->TankDrive(0.2, 0.2);
}

void DriveForward::Execute() {

}

bool DriveForward::IsFinished() {
  return timer->HasPeriodPassed(duration);
}

void DriveForward::End() {
  chassis->TankDrive(0.0, 0.0);
}

void DriveForward::Interrupted() {
  chassis->TankDrive(0.0, 0.0);
}

/////////////////////////////////////////////////////////////////////////////

