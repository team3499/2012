#include "Subsystems/Shooter.h"
#include "Robotmap.h"

Shooter::Shooter() : Subsystem("Shooter") {
  beltTop    = new Victor(SHOOTER_BELT_TOP_CHANNEL);
  beltBottom = new Victor(SHOOTER_BELT_BOTTOM_CHANNEL);
}

void Shooter::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}
