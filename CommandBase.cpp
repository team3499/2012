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
	Wait(1);
	printf("CommandBase init\n");
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	arm = new Arm();
	printf("Arm\n");
	accelerometer = new ArmAccelerometer();
	printf("Acc\n");
	camera = new Camera();
	printf("Camera\n");
	chassis = new Chassis();
	printf("Chas\n");
	chassisGyro = new ChassisGyro();
	printf("Gyro\n");
	lights = new Lights();
	printf("Lights\n");
	magazine = new Magazine();
	printf("Mag\n");
	shooter = new Shooter();
	printf("Shooter\n");
//	smartDashboard = new SmartDashboard();
	oi = new OI();
	printf("OI\n");
	printf("End of CommandBase init\n");
}

OI* CommandBase::GetOIInstance(){
	return oi;
}

OI* CommandBase::GetIOInstance(){
	return oi;
}

