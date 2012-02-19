#include "Subsystems/Magazine.h"
#include "Commands/MagazineDefault.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Robotmap.h"

Magazine::Magazine() : Subsystem("Magazine") {
  belt  = new Jaguar(MAGAZINE_BELT_CHANNEL);
  status = stopped;
  buttonFront  = new DigitalIOButton(MAGAZINE_BUTTON_FRONT_CHANNEL);
  buttonMiddle = new DigitalIOButton(MAGAZINE_BUTTON_MIDDLE_CHANNEL);
  buttonBack   = new DigitalIOButton(MAGAZINE_BUTTON_BACK_CHANNEL);
}

void Magazine::InitDefaultCommand() {
  SetDefaultCommand(new MagazineDefault());
}

//
// Returns true if a ball is present in the front position
// of the magazine
//
bool Magazine::IsReadyToFire() {
  bool ready = buttonFront->Get();
  if (ready) { SmartDashboard::Log("YES", "Magazine Ready to Fire"); }
  else { SmartDashboard::Log("NO", "Magazine Ready to Fire"); }

  return ready;
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

void Magazine::Move(float direction){
  UpdateStatus(direction);
  belt->Set(direction);
}

void Magazine::Stop(){
  UpdateStatus(0);
  belt->Set(0);
}

void Magazine::Set(float speed){
  UpdateStatus(speed);
  belt->Set(speed);
}

Magazine::StatusEnum Magazine::Status(){
	return status;
}

void Magazine::SetShooting(bool in){
  if (in == 0){
    status = stopped;
  } else {
    status = shooting;
  }
}

//////////////////////////////////////////////////////////////////////////////

void Magazine::UpdateStatus(float speed) {
  if(speed > 0) {
    SmartDashboard::Log("Readying", "Magazine Status");
    status = readying;
  } else if (speed < 0 ) {
    SmartDashboard::Log("Loading", "Magazine Status");
    status = loading;
  } else {
    SmartDashboard::Log("Stopped", "Magazine Status");
    status = stopped;
  }
}
