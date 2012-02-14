#include "Subsystems/Shooter.h"
#include "Robotmap.h"

Shooter::Shooter() : Subsystem("Shooter") {
  beltTop    = new Victor(SHOOTER_BELT_TOP_CHANNEL);
  beltBottom = new Victor(SHOOTER_BELT_BOTTOM_CHANNEL);

  buttonLoaded        = new DigitalIOButton(SHOOTER_BUTTON_LOADED_CHANNEL);
  buttonMagazineFront = new DigitalIOButton(SHOOTER_BUTTON_MAGAZINE_FRONT_CHANNEL);
  buttonMagazineBack  = new DigitalIOButton(SHOOTER_BUTTON_MAGAZINE_BACK_CHANNEL);
}

void Shooter::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}
