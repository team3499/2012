#ifndef __SUBSYSTEM_CHASSIS_GYRO_H__
#define __SUBSYSTEM_CHASSIS_GYRO_H__

#include "Commands/Subsystem.h"
#include "Commands/ArmLevel.h"
#include "WPILib.h"

class ChassisGyro : public Subsystem {

private:
  Gyro *gyro;

public:
  ChassisGyro();
  void  InitDefaultCommand();

  void  Reset();                          // Reset the gyro to zero degrees
  float GetHeading();                     // Compass heading (0-360 degrees) since reset
  float GetAngle();                       // Absolute angle rotated to since reset
  bool  IsAtAngle(float target, float margin = 1.0);  // Is gyro at *target* with *margin* ?
  float GetDesiredAngle(float rotation);  // Calculate absolute angle for given relative *rotation*

};

#endif /* __SUBSYSTEM_CHASSIS_GYRO_H__ */
