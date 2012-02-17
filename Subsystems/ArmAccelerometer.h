#ifndef __ACCELEROMETER2_H__
#define __ACCELEROMETER2_H__

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
	
	
private:
	
};

#endif //__ACCELEROMETER2_H__
