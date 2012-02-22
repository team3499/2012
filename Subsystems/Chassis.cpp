#include "Chassis.h"
#include "Robotmap.h"
#include "Commands/UserDrive.h"
#include "SmartDashboard/SmartDashboard.h"

Chassis::Chassis() : Subsystem("Chassis"),
	left_front(DRIVE_LEFT_FRONT),
	left_rear(DRIVE_LEFT_REAR),
	right(3)
{
}
    
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
  SmartDashboard::Log("Default", "Chassis Control");
	SetDefaultCommand(new UserDrive());
}

void Chassis::ArcadeDrive(Joystick &joystick){
  SmartDashboard::Log("Arcade", "Chassis Control");
	Drive(joystick.GetY(),joystick.GetX());
}

void Chassis::TankDrive(float leftOut, float rightOut){
	if(leftOut > 1.0){leftOut = 1.0;} else if(leftOut < -1.0){leftOut = -1.0;}
	if(rightOut > 1.0){rightOut = 1.0;} else if(rightOut < -1.0){rightOut = -1.0;}
  SmartDashboard::Log("Tank", "Chassis Control");
  SmartDashboard::Log(leftOut, "Chassis Left Motor");
  SmartDashboard::Log(rightOut, "Chassis Right Motor");
	left_front.Set(leftOut, 0x80);
	left_rear.Set(leftOut, 0x80);
	right.Set(rightOut, 0x80);
}

void Chassis::Drive(float moveValue, float rotateValue)
{

	if(moveValue > 1.0){moveValue = 1.0;} else if(moveValue < -1.0){moveValue = -1.0;}
	if(rotateValue > 1.0){rotateValue = 1.0;} else if(rotateValue < -1.0){rotateValue = -1.0;}
	float leftOut,rightOut;
	if (moveValue > 0.0)
	{
		if (rotateValue > 0.0)
		{
			leftOut = moveValue - rotateValue;
			rightOut = max(moveValue, rotateValue);
		}
		else
		{
			leftOut = max(moveValue, -rotateValue);
			rightOut = moveValue + rotateValue;
		}
	}
	else
	{
		if (rotateValue > 0.0)
		{
			leftOut = - max(-moveValue, rotateValue);
			rightOut = moveValue + rotateValue;
		}
		else
		{
			leftOut = moveValue - rotateValue;
			rightOut = - max(-moveValue, -rotateValue);
		}
	}
	if(leftOut > 1.0){leftOut = 1.0;} else if(leftOut < -1.0){leftOut = -1.0;}
	if(rightOut > 1.0){rightOut = 1.0;} else if(rightOut < -1.0){rightOut = -1.0;}
  SmartDashboard::Log(leftOut, "Chassis Left Motor");
  SmartDashboard::Log(rightOut, "Chassis Right Motor");
	left_rear.Set(leftOut, 0x80);
	left_front.Set(leftOut, 0x80);
	right.Set(-rightOut, 0x80);
}
