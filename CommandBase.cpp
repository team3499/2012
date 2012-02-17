#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
//ExampleSubsystem* CommandBase::examplesubsystem = NULL;
Arm *CommandBase::arm = NULL;
ArmAccelerometer *CommandBase::accelerometer;
Camera *CommandBase::camera = NULL;
Chassis *CommandBase::chassis = NULL;
ChassisGyro *CommandBase::chassisGyro = NULL;
Lights *CommandBase::lights = NULL;
Magazine *CommandBase::magazine = NULL;
Shooter *CommandBase::shooter = NULL;
OI *CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	arm = new Arm();
	accelerometer = new ArmAccelerometer();
	camera = new Camera();
	chassis = new Chassis();
	chassisGyro = new ChassisGyro();
	lights = new Lights();
	magazine = new Magazine();
	shooter = new Shooter();
//	smartDashboard = new SmartDashboard();
	oi = new OI();
}
