#ifndef __SUBSYSTEM_CHASSIS_GYRO_H__
#define __SUBSYSTEM_CHASSIS_GYRO_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ChassisGyro : public Subsystem {

private:

public:
  ChassisGyro();
  void InitDefaultCommand();

};

#endif /* __SUBSYSTEM_CHASSIS_GYRO_H__ */
