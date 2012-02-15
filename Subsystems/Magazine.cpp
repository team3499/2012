#include "Subsystems/Magazine.h"
#include "Robotmap.h"

Magazine::Magazine() : Subsystem("Magazine") {
  belt  = new Victor(MAGAZINE_BELT_CHANNEL);

  buttonFront  = new DigitalIOButton(MAGAZINE_BUTTON_FRONT_CHANNEL);
  buttonMiddle = new DigitalIOButton(MAGAZINE_BUTTON_MIDDLE_CHANNEL);
  buttonBack   = new DigitalIOButton(MAGAZINE_BUTTON_BACK_CHANNEL);
}

void Magazine::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}

//
// Returns true if a ball is present in the front position
// of the magazine
//
bool Magazine::IsReadyToFire() {
  return buttonFront->Get();
}

//
// Returns the number of balls loaded in the magazine
//
int Magazine::BallCount() {
  int count = 0;

  LoadStatus status = GetLoadStatus();
  if (status.front) { count++; }
  if (status.middle) { count++; }
  if (status.back) { count++; }

  return count;
}

//
// Returns a LoadStatus struct with the load status
// of each magazine position as a boolean
//
Magazine::LoadStatus Magazine::GetLoadStatus() {
  LoadStatus status = { buttonFront->Get(),
                        buttonMiddle->Get(),
                        buttonBack->Get() };
  return status;
}
