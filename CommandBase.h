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
#include "Subsystems/Rangefinder.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Magazine.h"
#include "Subsystems/Camera.h"


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
  static ArmAccelerometer *accelerometer;
  static Camera *camera;
  static Chassis *chassis;
  static ChassisGyro *chassisGyro;
  static Magazine *magazine;
  static Rangefinder *rangefinder;
  static Shooter *shooter;
  static SmartDashboard *smartDashboard;
  static OI *oi;
  static OI *GetOIInstance();
};

#endif
