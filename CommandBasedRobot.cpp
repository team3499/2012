/* Include Standerd C Libs */
/* Include WPILib Headers */
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
#include "Commands/Rotation.h"
#include "Commands/ExampleCommand.h"
#include "Commands/UserDrive.h"
/* Include Custom Subsystems */
#include "Subsystems/Launcher.h"
#include "Subsystems/Chassis.h"

class Robot : public IterativeRobot {
private:
	Command *autonomousCommand;
	Command *userDrive;
	Launcher *launcher;
	Chassis *chassis;
	//Gyro *gyro;
	
	virtual void RobotInit()
	{
		//init subsystems first, then commands
		launcher = new Launcher();
		chassis = new Chassis();
		//gyro = new Gyro();
		//SmartDashboard::init();
		CommandBase::init();
//		SmartDashboard sd = SmartDashboard::GetInstance();
		autonomousCommand = new ExampleCommand();
		userDrive = new UserDrive(chassis);
	}
	
	virtual void AutonomousInit() {
		autonomousCommand->Start();
		//autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		autonomousCommand->Cancel();
		//rotation->Start();
		userDrive->Start();
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);

