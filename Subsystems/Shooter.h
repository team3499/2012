#ifndef __SUBSYSTEM_SHOOTER_H__
#define __SUBSYSTEM_SHOOTER_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter : public Subsystem {

private:
  static const float minimumSpeed = 0.05;

  Victor * beltTop;
  Victor * beltBottom;

  float RegulateSpeed(float speed);

public:
  Shooter();
  void InitDefaultCommand();

  bool IsShooting();              // Is the shooter shooting?
  bool IsLoading();               // Is the shooter loading?
  bool IsStopped();               // Is the shooter stopped?

  void Shoot(float speed = 1.0);  // Run the belts in the shoot direction
  void Load(float speed = 0.1);   // Run the belts in the load direction
  void Stop();                    // Stop the belts
};

#endif /* __SUBSYSTEM_SHOOTER_H__ */
