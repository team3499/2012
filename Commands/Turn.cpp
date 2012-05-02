#include "Turn.h"
#include "WPILib.h"
#include "Subsystems/Camera.h"
#include "Commands/ShootBalls.h"

#define absolute(A) (A<0)?(-A):(A)

Turn::Turn()
{
  Requires(chassis);
  Requires(chassisGyro);
  Requires(camera);
  turnAngle = 0.0;
}

Turn::Turn(float angle)
{
  Requires(chassis);
  Requires(chassisGyro);
  turnAngle = angle;
}

// Called just before this Command runs the first time
void Turn::Initialize() {
  if (turnAngle != 0.0) {
    turnTo = chassisGyro->GetDesiredAngle(turnAngle);
  } else {
    turnTo = chassisGyro->GetDesiredAngle(camera->GetTarget()->GetHorizontalAngle());
  }
  turnSpeed = TurnSpeedForAngle(chassisGyro->GetAngle());
  chassis->TankDrive(turnSpeed,turnSpeed);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
  turnSpeed = TurnSpeedForAngle(chassisGyro->GetAngle());
  chassis->TankDrive(turnSpeed,turnSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
  return chassisGyro->IsAtAngle(turnTo, 1.0);
}

// Called once after isFinished returns true
void Turn::End() {
  chassis->TankDrive(0.0,0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {
  End();
}

// Calculate the turn speed (and direction) for the given angle
float Turn::TurnSpeedForAngle(float angle) {
  float offsetAngle = absolute(angle - turnTo);
  float speed = 0.40;

  SmartDashboard::Log(offsetAngle, "Turn Remaining");
  SmartDashboard::Log(speed, "Turn Speed");

  if (offsetAngle >= 15.0) { speed = 0.95; }
  else if (offsetAngle >= 10.0) { speed = 0.70; }
  else if (offsetAngle >= 5.0) { speed = 0.55; }

  if (angle > turnTo) { speed = -speed; }

  return speed;
}
