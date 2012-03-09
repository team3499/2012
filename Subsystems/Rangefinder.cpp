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
  double distance = (GetVoltage(smoothCount) / 0.0098)/ 39.37;
  printf("Distance:%f\nVoltage:%f\n",distance,GetVoltage(smoothCount));
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
