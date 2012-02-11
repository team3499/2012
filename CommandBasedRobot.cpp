/* Include Standerd C Libs */

/* Include WPILib Headers */
#include "WPILib.h"
#include "DigitalOutput.h"

/* Include Custom Headers */
#include "Commands/Command.h"
#include "Commands/Rotation.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Subsystems/Launcher.h"

class Robot : public IterativeRobot {
private:
	Command *autonomousCommand;
	Command *rotation;
	Launcher *launcher;
	
	virtual void RobotInit()
	{
		//init subsystems first, then commands
		launcher = new Launcher();
		//SmartDashboard::init();
		CommandBase::init();
//		SmartDashboard sd = SmartDashboard::GetInstance();
		autonomousCommand = new ExampleCommand();
		rotation = new Rotation(launcher);
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
		rotation->Start();
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);

