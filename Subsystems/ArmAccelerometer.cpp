#include "ArmAccelerometer.h"
#include "Commands/AccDefault.h"
#include "SmartDashboard/SmartDashboard.h"
#include "math.h"

#define PI 3.1415926535897932384626433832795

ArmAccelerometer::ArmAccelerometer() : Subsystem("ArmAccelerometer"),
	acc(ARM_ACCELEROMETER_CHANNEL)
{
}

void  ArmAccelerometer::InitDefaultCommand(){
	SetDefaultCommand(new AccDefault());
}

ADXL345_I2C::AllAxes ArmAccelerometer::GetAllAxes(){
	return acc.GetAccelerations();
}

double ArmAccelerometer::GetArmDegree(){
  ADXL345_I2C::AllAxes axes = GetAllAxes();
  double result = ConvertVectorsToDegrees(-axes.XAxis, -axes.YAxis);
  SmartDashboard::Log(result, "Arm Angle");
  return result;
}

double ArmAccelerometer::ConvertVectorsToDegrees(double x, double y) {
  return 180*atan2(x, y)/PI;
}
