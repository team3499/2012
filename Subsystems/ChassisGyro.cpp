#include "Subsystems/ChassisGyro.h"
#include "Robotmap.h"

ChassisGyro::ChassisGyro() : Subsystem("Chassis Gyro") {
  gyro = new Gyro(CHASSIS_GYRO_CHANNEL);
}

void ChassisGyro::InitDefaultCommand() {
  SetDefaultCommand(new Arm90());
}

//
// Reset the gyro to 0 degrees
//
void ChassisGyro::Reset() {
  gyro->Reset();
}

//
// Returns the compass heading (0-360 degrees)
//
float ChassisGyro::GetHeading() {
  float angle = GetAngle();
  float heading = angle - (float)((int)(angle / 360.0) * 360.0);
  return heading < 0.0 ? heading + 360.0 : heading;
}

//
// Returns the degrees away from the last call to Reset().
// Does not wrap at 360 -> 0
//
float ChassisGyro::GetAngle() {
  return gyro->GetAngle();
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
