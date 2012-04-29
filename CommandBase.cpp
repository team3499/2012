#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name):
  Command(name)
{
}

CommandBase::CommandBase():
  Command()
{
}

// Initialize a single static instance of all of your subsystems to NULL
//ExampleSubsystem* CommandBase::examplesubsystem = NULL;
Arm *CommandBase::arm = NULL;
ArmAccelerometer *CommandBase::accelerometer = NULL;
Camera *CommandBase::camera = NULL;
Chassis *CommandBase::chassis = NULL;
ChassisGyro *CommandBase::chassisGyro = NULL;
Lights *CommandBase::lights = NULL;
Rangefinder *CommandBase::rangefinder = NULL;
Magazine *CommandBase::magazine = NULL;
Shooter *CommandBase::shooter = NULL;
OI *CommandBase::oi = NULL;

void CommandBase::init() {
  Wait(1);

  if (IS_DEBUG_MODE) { printf("#### CommandBase::init START\n"); }
  arm = new Arm();
  if (IS_DEBUG_MODE) { printf("Arm\n"); }
  accelerometer = new ArmAccelerometer();
  if (IS_DEBUG_MODE) { printf("Acc\n"); }
  camera = new Camera();
  if (IS_DEBUG_MODE) { printf("Camera\n"); }
  chassis = new Chassis();
  if (IS_DEBUG_MODE) { printf("Lights\n"); }
  lights = new Lights();
  if (IS_DEBUG_MODE) { printf("Chas\n"); }
  chassisGyro = new ChassisGyro();
  if (IS_DEBUG_MODE) { printf("Gyro\n"); }
    rangefinder = new Rangefinder();
  if (IS_DEBUG_MODE) { printf("Rangefinder\n"); }
  magazine = new Magazine();
  if (IS_DEBUG_MODE) { printf("Mag\n"); }
  shooter = new Shooter();
  if (IS_DEBUG_MODE) { printf("Shooter\n"); }
//  smartDashboard = new SmartDashboard();
  oi = new OI();
  if (IS_DEBUG_MODE) { printf("OI\n"); }
  if (IS_DEBUG_MODE) { printf("#### CommandBase::init END\n"); }
}

OI* CommandBase::GetOIInstance(){
  return oi;
}

