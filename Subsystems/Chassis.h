#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar left_front, left_rear, right;
public:
	Chassis();
	void InitDefaultCommand();
	void ArcadeDrive(Joystick &joystick);
	void TankDrive(float leftOut, float rightOut);
private:
	void Drive(float moveValue,float rotateValue);
};

#endif
