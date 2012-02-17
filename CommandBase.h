#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
/* Include WPILib files */
#include "Commands/Command.h"
#include "OI.h"
#include "SmartDashboard.h"
/* Include Subsystems*/
#include "Subsystems/Arm.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/ChassisGyro.h"
#include "Subsystems/ArmAccelerometer.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Magazine.h"
#include "Subsystems/Camera.h"
#include "Subsystems/Lights.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static Arm *arm;
	static Chassis *chassis;
	static ChassisGyro *chassisGyro;
	static ArmAccelerometer *accelerometer;
	static Camera *camera;
	static SmartDashboard *smartDashboard;
	static Shooter *shooter;
	static Magazine *magazine;
	static Lights *lights;
	static OI *oi;
};

#endif
