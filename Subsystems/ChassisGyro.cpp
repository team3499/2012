#include "Subsystems/ChassisGyro.h"
#include "Robotmap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/GyroDefault.h"

ChassisGyro::ChassisGyro() : Subsystem("ChassisGyro") {
  gyro = new Gyro(CHASSIS_GYRO_CHANNEL);
}

void ChassisGyro::InitDefaultCommand() {
	SetDefaultCommand(new GyroDefault());
}

//
// Reset the gyro to 0 degrees
//
void ChassisGyro::Reset() {
  SmartDashboard::Log(0.0, "Chassis Gyro");
  gyro->Reset();
}

//
// Returns the compass heading (0-360 degrees)
//
float ChassisGyro::GetHeading() {
  float angle = GetAngle();
  float heading = angle - (float)((int)(angle / 360.0) * 360.0);
  if (heading < 0.0) { heading += 360.0; }
  SmartDashboard::Log(heading, "Chassis Heading");
  
  return heading;
}

//
// Returns the degrees away from the last call to Reset().
// Does not wrap at 360 -> 0
//
float ChassisGyro::GetAngle() {
  float angle = gyro->GetAngle();
  SmartDashboard::Log(angle, "Chassis Gyro");

  return angle;
}

//
// Returns true if the rotation is within *margin* degrees
// of *target*.  Defaults to 1.0 degrees *margin*.
//
bool ChassisGyro::IsAtAngle(float target, float margin) {
  float currentAngle = GetAngle();
  return (currentAngle + margin > target && currentAngle - margin < target);
}

//
// Returns the absolute angle (i.e. return from GetAngle()) for the
// passed relative *rotation* value.
//
float ChassisGyro::GetDesiredAngle(float rotation) {
  return GetAngle() + rotation;
}
