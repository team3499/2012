/* Include Standerd C Libs */
/* Include WPILib Headers */
using namespace std;
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
#include "Commands/DAG.h"
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
		disabled = false;
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
		if ((CommandBase::GetOIInstance()->GetRawButton(1,6)
				|| CommandBase::GetOIInstance()->GetRawButton(1,11)
				|| CommandBase::GetOIInstance()->GetRawButton(2,6)
				|| CommandBase::GetOIInstance()->GetRawButton(2, 11)) && !disabled){
		//Check to see if you should disable stuff
			printf("Disabled");
			if(autonomousCommand->IsRunning()){//if the command is running, log that
				autonomousCommand->Cancel();
				wasAcRunning = true;
				printf(":and canceled.");
			}
			delete stopCommand;
			stopCommand = 0x00;
			stopCommand = new StopAll();
			stopCommand->Start();//stop EVERYTHING
			disabled = true;
			printf("\n");
		} else if (!disabled){//if it is not disabled, check to see the to stop running the DAG command
			printf("Is Not Disabled:");
			if (CommandBase::GetOIInstance()->GetRawButton(1,3)
					&& autonomousCommand->IsRunning()){
				autonomousCommand->Cancel();
				printf("DAG canceled\n");
			}
			if ((CommandBase::GetOIInstance()->GetRawButton(1,1)
					|| CommandBase::GetOIInstance()->GetRawButton(2,1))
					&& !autonomousCommand->IsRunning()){
				delete autonomousCommand;
				autonomousCommand = 0x00;
				autonomousCommand = new DAG();
				autonomousCommand->Start();
				printf("DAG started\n");
			}
		} else if((CommandBase::GetOIInstance()->GetRawButton(1,8)
				&& CommandBase::GetOIInstance()->GetRawButton(1,9))
				|| (CommandBase::GetOIInstance()->GetRawButton(2,8)
				&& CommandBase::GetOIInstance()->GetRawButton(2,9))){
			//otherwise check to enable everything again
			printf("Robot Reenabled");
			disabled = false;
			stopCommand->Cancel();
			if(wasAcRunning){
				delete autonomousCommand;
				autonomousCommand = new DAG();
				autonomousCommand->Start();
				printf("DAG Restarted.");
			}
			printf("\n");
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

