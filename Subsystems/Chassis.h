#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive drive;
public:
	Chassis();
	void Init();
	void ArcadeDrive(Joystick *joystick);
	void ArcadeDrive(Joystick &joystick);
public:
};

#endif
