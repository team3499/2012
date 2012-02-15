#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
//ExampleSubsystem* CommandBase::examplesubsystem = NULL;
Arm *CommandBase::arm = NULL;
ChassisGyro *CommandBase::chassisGyro = NULL;
Chassis *CommandBase::chassis = NULL;
Camera *CommandBase::camera = NULL;
ArmAccelerometer *CommandBase::accelerometer;
Shooter *CommandBase::shooter = NULL;
Magazine *CommandBase::magazine = NULL;
OI *CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	arm = new Arm();
	chassis = new Chassis();
	chassisGyro = new ChassisGyro();
	accelerometer = new ArmAccelerometer();
	camera = new Camera();
	shooter = new Shooter();
	magazine = new Magazine();
//	smartDashboard = new SmartDashboard();
	oi = new OI();
}
