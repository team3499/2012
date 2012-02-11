#include "Accelerometer2.h"
#include "math.h"

#define PI 3.1415926535897932384626433832795




Accelerometer2::Accelerometer2(UINT32 channel):
	acc(channel)
{
}
Accelerometer2::~Accelerometer2(){}

double Accelerometer2::Get(ADXL345_I2C::Axes axis){
	return acc.GetAcceleration(axis);
}
ADXL345_I2C::AllAxes Accelerometer2::GetAll(){
	return acc.GetAccelerations();
}

double Accelerometer2::GetArmDegree(){
	ADXL345_I2C::AllAxes axes = GetAll();
	return (180*atan2(axes.XAxis,axes.YAxis))/PI;
}
