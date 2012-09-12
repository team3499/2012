#ifndef __ARM_ACCELEROMETER_H__
#define __ARM_ACCELEROMETER_H__

#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include "ADXL345_I2C.h"

class ArmAccelerometer : public Subsystem {
private:
	ADXL345_I2C acc;
	
public:
	ArmAccelerometer();
	
	void  InitDefaultCommand();
	double GetArmDegree();
	ADXL345_I2C::AllAxes GetAllAxes();
	
protected:
  double ConvertVectorsToDegrees(double x, double y);
};

#endif //__ARM_ACCELEROMETER_H__
