#ifndef __ACCELEROMETER2_H__
#define __ACCELEROMETER2_H__

#include "Commands/Subsystem.h"
#include "ADXL345_I2C.h"

class Accelerometer2 : public Subsystem {
private:
	ADXL345_I2C *acc;
	
public:
	Accelerometer2();
	
	void  InitDefaultCommand();
	double GetArmDegree();
	ADXL345_I2C::AllAxes GetAllAxes();
	
	
private:
	
};

#endif //__ACCELEROMETER2_H__
