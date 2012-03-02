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
	printf("CommandBase init\n");
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	arm = new Arm();
	printf("Arm");
	accelerometer = new ArmAccelerometer();
	printf("Acc");
	camera = new Camera();
	chassis = new Chassis();
	printf("Chas");
	chassisGyro = new ChassisGyro();
	printf("Gyro");
	lights = new Lights();
	printf("Lights");
	magazine = new Magazine();
	printf("Mag");
	shooter = new Shooter();
	printf("Shooter");
//	smartDashboard = new SmartDashboard();
	oi = new OI();
	printf("OI");
	printf("End of CommandBase init");
}

OI* CommandBase::GetIOInstance(){
	return oi;
}

