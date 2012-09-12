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

// Returns the distance in meters
double Rangefinder::GetDistance(int smoothCount) {
  double voltage  = GetVoltage(smoothCount);
  double distance = voltage / 0.0098 / 39.37;  // 0.0098V/inch convert to meters

  if (IS_DEBUG_MODE) { printf("Rangefinder: %0.3fm (%0.2fV)\n", distance, voltage); }
  SmartDashboard::Log((float)distance, "Rangefinder");

  return distance;
}

//////////////////////////////////////////////////////////////////////////////

double Rangefinder::GetVoltage(int smoothCount) {
  if (smoothCount = 0) { smoothCount = 5; }

  float voltage = 0.0;
  for (int i = 0; i < 3; i++) {
	  voltage += analog->GetVoltage();
  }
  SmartDashboard::Log(analog->GetVoltage(),"Rangefinder_Voltage");
  return voltage/3;
}
