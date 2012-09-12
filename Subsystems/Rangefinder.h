#ifndef __SUBSYSTEM_RANGEFINDER_H__
#define __SUBSYSTEM_RANGEFINDER_H__

#include "Commands/Subsystem.h"
#include "AnalogChannel.h"
#include "WPILib.h"

class Rangefinder : public Subsystem {

private:
  AnalogChannel *analog;
  int defaultSmoothCount;

  double GetVoltage(int smoothCount = 0);    // Get voltage reading

public:
  Rangefinder(int defaultSmoothCount = 5);
  virtual ~Rangefinder();

  void InitDefaultCommand();

  double GetDistance(int smoothCount = 0);   // Get distance in meters
};

#endif /* __SUBSYSTEM_RANGEFINDER_H__ */

