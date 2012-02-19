#include "Subsystems/Rangefinder.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Robotmap.h"

Rangefinder::Rangefinder(int defaultSmoothCount) : Subsystem("Rangefinder") {
  this->defaultSmoothCount = defaultSmoothCount;
  analog = new AnalogChannel(RANGEFINDER_CHANNEL);
}

Rangefinder::~Rangefinder() {
  delete analog;
  analog = 0;
}

void Rangefinder::InitDefaultCommand() {

}

// Returns the distance in inches
double Rangefinder::GetDistance(int smoothCount) {
  double distance = GetVoltage(smoothCount)/0.0098;
  SmartDashboard::Log(distance, "Rangefinder");

  return distance;
}

//////////////////////////////////////////////////////////////////////////////

double Rangefinder::GetVoltage(int smoothCount) {
  if (smoothCount = 0) { smoothCount = defaultSmoothCount; }

  float voltage = 0.0;
  for (int i = 0; i < smoothCount; ++i) { voltage += analog->GetVoltage(); }

  return voltage/smoothCount;
}
