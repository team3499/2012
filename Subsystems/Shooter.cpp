#include "Subsystems/Shooter.h"
#include "Robotmap.h"

Shooter::Shooter() : Subsystem("Shooter") {
  beltTop    = new Victor(SHOOTER_BELT_TOP_CHANNEL);
  beltBottom = new Victor(SHOOTER_BELT_BOTTOM_CHANNEL);
}

void Shooter::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}

// Make sure the value passed for speed is between 0.0 and 1.0
float Shooter::RegulateSpeed(float speed) {
  if (speed < 0.0) { speed = -speed; }
  if (speed < minimumSpeed) { speed = minimumSpeed; }
  if (speed > 1.0) { speed = 1.0; }

  return speed;
}

//
// Returns true if both belts are running forward
//
bool Shooter::IsShooting() {
  return (beltBottom->Get() > minimumSpeed && beltTop->Get() > minimumSpeed);
}

//
// Returns true if both belts are running backward
//
bool Shooter::IsLoading() {
  return (beltBottom->Get() < -minimumSpeed && beltTop->Get() < -minimumSpeed);
}

//
// Returns true if both belts are stopped
//
bool Shooter::IsStopped() {
  float topSpeed    = beltTop->Get();
  float bottomSpeed = beltBottom->Get();

  return (bottomSpeed < minimumSpeed && bottomSpeed > -minimumSpeed &&
          topSpeed    < minimumSpeed && topSpeed    > -minimumSpeed);
}

//
// Run the belts in the shoot direction.  Pass *speed* as a positive
// value between 0.0 and 1.0.
//
void Shooter::Shoot(float speed) {
  speed = RegulateSpeed(speed);

  beltBottom->Set(speed);
  beltTop->Set(speed);
}

//
// Run the belts in the shoot direction.  Pass *speed* as a positive
// value between 0.0 and 1.0.
//
void Shooter::Load(float speed) {
  speed = RegulateSpeed(speed);

  beltBottom->Set(-speed);
  beltTop->Set(-speed);
}

//
// Stop the belts
//
void Shooter::Stop() {
  beltBottom->Disable();
  beltTop->Disable();
}
