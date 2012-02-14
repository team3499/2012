#include "Subsystems/Shooter.h"
#include "Robotmap.h"

Shooter::Shooter() : Subsystem("Shooter") {
  beltTop    = new Victor(SHOOTER_BELT_TOP_CHANNEL);
  beltBottom = new Victor(SHOOTER_BELT_BOTTOM_CHANNEL);

  buttonMagazineFront  = new DigitalIOButton(SHOOTER_BUTTON_MAGAZINE_FRONT_CHANNEL);
  buttonMagazineMiddle = new DigitalIOButton(SHOOTER_BUTTON_MAGAZINE_MIDDLE_CHANNEL);
  buttonMagazineBack   = new DigitalIOButton(SHOOTER_BUTTON_MAGAZINE_BACK_CHANNEL);
}

void Shooter::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}

//
// Returns true if a ball is present in the front position
// of the magazine
//
bool Shooter::IsReadyToFire() {
  return buttonMagazineFront->Get();
}

//
// Returns the number of balls loaded in the magazine
//
int Shooter::BallsInMagazine() {
  int count = 0;

  MagazineStatus status = GetMagazineStatus();
  if (status.front) { count++; }
  if (status.middle) { count++; }
  if (status.back) { count++; }

  return count;
}

//
// Returns a MagazineStatus struct with the load status
// of each magazine position as a boolean
//
Shooter::MagazineStatus Shooter::GetMagazineStatus() {
  MagazineStatus status = { buttonMagazineFront->Get(),
                            buttonMagazineMiddle->Get(),
                            buttonMagazineBack->Get() };
  return status;
}
