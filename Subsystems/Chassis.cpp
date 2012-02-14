#include "Chassis.h"
#include "Robotmap.h"
#include "Commands/UserDrive.h"

Chassis::Chassis() : Subsystem("Chassis"),
	left(1,3),
	right(1,4)
{
}
    
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new UserDrive());
}

void Chassis::ArcadeDrive(Joystick &joystick){
	Drive(joystick.GetY(),joystick.GetX());
}

void Chassis::TankDrive(float leftOut, float rightOut){
	if(leftOut > 1.0){leftOut = 1.0;} else if(leftOut < -1.0){leftOut = -1.0;}
	if(rightOut > 1.0){rightOut = 1.0;} else if(rightOut < -1.0){rightOut = -1.0;}
	left.Set(leftOut, 0x80);
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
	left.Set(leftOut, 0x80);
	right.Set(-rightOut, 0x80);
	printf("drive");
}
