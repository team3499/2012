#include "Accelerometer2.h"
#include "math.h"

#define PI 3.1415926535897932384626433832795

Accelerometer2::Accelerometer2() : Subsystem("Acceleromter2")
{
	acc = new ADXL345_I2C(ARM_ACCELEROMETER_CHANNEL);
}

void  InitDefaultCommand(){
	//SetDefaultCommand();
}

ADXL345_I2C::AllAxes Accelerometer2::GetAllAxes(){
	return acc->GetAccelerations();
}

double Accelerometer2::GetArmDegree(){
	ADXL345_I2C::AllAxes axes = GetAllAxes();
	return (180*atan2(axes.XAxis,axes.YAxis))/PI;
}
