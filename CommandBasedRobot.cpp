/* Include Standerd C Libs */
/* Include WPILib Headers */
using namespace std;
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
//#include "Commands/Rotation.h"
//#include "Commands/ExampleCommand.h"
//#include "Commands/ShootGroup.h"
#include "Commands/AutoGroup.h"
#include "Commands/DAG.h"
#include "Commands/ArmLevel.h"
#include "FiringSolution.h"
#include "Commands/ShootGroup.h"
#include "Commands/StopAll.h"
class Robot : public IterativeRobot {
	private:
	bool wasAcRunning;
	CommandBase *armLevel;
	Command *autonomousCommand;
	Command *stopCommand;
	bool disabled;
private:
	
	virtual void RobotInit()
	{
		//Wait(.2);
		printf("Start ");
		
		//SmartDashboard::init();
		CommandBase::init();
		autonomousCommand = new DAG();
		printf("DAG made\n");
		stopCommand = new StopAll();
		printf("StopAll made\n");
		//SmartDashboard sd = SmartDashboard::GetInstance();
		printf("End");
	}
	
	virtual void AutonomousInit() {
		CommandBase::chassisGyro->Reset();
		printf("Autonomous Init Begin");
		autonomousCommand->Start();
		printf("Autonomous Init End");
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		printf("Teleop init.\n");
		autonomousCommand->Cancel();
		printf("Autonomous Command disabled.\n");
		disabled = false;
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
		if (CommandBase::GetOIInstance()->GetRawButton(1,6)
				|| CommandBase::GetOIInstance()->GetRawButton(1,11)
				|| CommandBase::GetOIInstance()->GetRawButton(2,6)
				|| CommandBase::GetOIInstance()->GetRawButton(2, 11)){
		//Check to see if you should disable stuff
			if(autonomousCommand->IsRunning()){//if the command is running, log that
				autonomousCommand->Cancel();
				wasAcRunning = true;
			}
			stopCommand->Start();//stop EVERYTHING
			disabled = true;
		}
		if (!disabled){//if it is not disabled, check to see the to stop running the DAG command
			if (CommandBase::GetOIInstance()->GetRawButton(1,3)
					&& autonomousCommand->IsRunning()){
				autonomousCommand->Cancel();
			}
			if ((CommandBase::GetOIInstance()->GetRawButton(1,1)
					|| CommandBase::GetOIInstance()->GetRawButton(2,1))
					&& !autonomousCommand->IsRunning()){
				autonomousCommand->Start();
			}
		} else if((CommandBase::GetOIInstance()->GetRawButton(1,8)
				&& CommandBase::GetOIInstance()->GetRawButton(1,9))
				|| (CommandBase::GetOIInstance()->GetRawButton(2,8)
				&& CommandBase::GetOIInstance()->GetRawButton(2,9))){
			//otherwise check to enable everything again
			disabled = false;
			stopCommand->Cancel();
			if(wasAcRunning){
				autonomousCommand->Start();
			}
		}
		if (autonomousCommand->IsRunning()){
			SmartDashboard::Log("Running DAG","Demo Status");
			printf("Running DAG\n");
		} else if (stopCommand->IsRunning()){
			SmartDashboard::Log("STOPPED","Demo Status");
			printf("STOPPED\n");
		} else {
			SmartDashboard::Log("User Control","Demo Status");
			printf("User Control\n");
		}
	}
};

START_ROBOT_CLASS(Robot);

