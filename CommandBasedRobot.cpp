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
#include "Commands/Turn.h"

class Robot : public IterativeRobot {
private:
	Command *turn;
	
	virtual void RobotInit()
	{
		//SmartDashboard::init();
		CommandBase::init();
		//SmartDashboard sd = SmartDashboard::GetInstance();
		turn = new Turn();
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

