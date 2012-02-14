/* Include Standerd C Libs */
/* Include WPILib Headers */
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
#include "Commands/Rotation.h"
//#include "Commands/ExampleCommand.h"
#include "Commands/UserDrive.h"

class Robot : public IterativeRobot {
private:
	//Command *autonomousCommand;
	
	virtual void RobotInit()
	{
		//SmartDashboard::init();
		CommandBase::init();
		//SmartDashboard sd = SmartDashboard::GetInstance();
		//autonomousCommand = new ExampleCommand();
	}
	
	virtual void AutonomousInit() {
		//autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		//autonomousCommand->Cancel();
		//rotation->Start();
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);

