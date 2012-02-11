//#ifndef ACCELEROMETER_H
//#define ACCELEROMETER_H

#include "ADXL345_I2C.h"

class Accelerometer2
{
private:
	ADXL345_I2C acc;
	
public:
	Accelerometer2(UINT32 channel);
	
	~Accelerometer2();
	double GetArmDegree();
	double Get(ADXL345_I2C::Axes axis);
	ADXL345_I2C::AllAxes GetAll();
	
	
private:
	
};

//#endif //ACCELEROMETER_H
