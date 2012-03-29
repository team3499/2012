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
class Robot : public IterativeRobot {
	private:
	CommandBase *armLevel;
	Command *autonomousCommand;
	bool disabled;
private:
	
	virtual void RobotInit()
	{
		//Wait(.2);
		printf("Start ");
		
		//SmartDashboard::init();
		CommandBase::init();
		autonomousCommand = new AutoGroup(true);
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
	}
	
	virtual void TeleopPeriodic(){
		Scheduler::GetInstance()->Run();
		if (CommandBase::GetOIInstance()->GetRawButton(1,6) || CommandBase::GetOIInstance()->GetRawButton(1,11) || CommandBase::GetOIInstance()->GetRawButton(2,6) || CommandBase::GetOIInstance()->GetRawButton(2, 11)){
			disabled = true;
		}
		if (!disabled){
			if (CommandBase::GetOIInstance()->GetRawButton(1,3) && autonomousCommand->IsRunning()){
				autonomousCommand->Cancel();
			}
			if ((CommandBase::GetOIInstance()->GetRawButton(1,1) || CommandBase::GetOIInstance()->GetRawButton(2,1)) && !autonomousCommand->IsRunning()){// && turn->IsRunning()){
				autonomousCommand = new DAG();
				autonomousCommand->Start();
			}
		} else if(CommandBase::GetOIInstance()->GetRawButton(1,8) || CommandBase::GetOIInstance()->GetRawButton(1,9) || CommandBase::GetOIInstance()->GetRawButton(2,8) || CommandBase::GetOIInstance()->GetRawButton(2,9)){
			disabled = false;
		}
	}
};

START_ROBOT_CLASS(Robot);

