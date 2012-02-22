/* Include Standerd C Libs */
/* Include WPILib Headers */
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
//#include "Commands/Rotation.h"
//#include "Commands/ExampleCommand.h"
//#include "Commands/ShootGroup.h"
#include "Commands/ArmLevel.h"
#include "Commands/ShootGroup.h"
class Robot : public IterativeRobot {
	private:
	CommandBase *armLevel;
	//CommandBase *turn;
private:
	
	virtual void RobotInit()
	{
		//SmartDashboard::init();
		CommandBase::init();
		//SmartDashboard sd = SmartDashboard::GetInstance();
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
		if (CommandBase::GetIOInstance()->GetRawButton(1,3) && !armLevel->IsRunning()){
			armLevel = new ArmLevel((float)45.0);
			armLevel->Start();
		} else if (CommandBase::GetIOInstance()->GetRawButton(1,2) && !armLevel->IsRunning()){
			armLevel = new ArmLevel((float)-45.0);
			armLevel->Start();
		}
		if (CommandBase::GetIOInstance()->GetRawButton(2,3) && armLevel->IsRunning()){
			armLevel->Cancel();
			delete(armLevel);
		}
		if (CommandBase::GetIOInstance()->GetRawButton(2,3) && armLevel->IsRunning()){
			armLevel->Cancel();
			delete(armLevel);
		}
		
		if (CommandBase::GetIOInstance()->GetRawButton(1,4)){// && !turn->IsRunning()){
			new ShootGroup();
			//turn = new Turn();
			//turn->Start();
		} else if (CommandBase::GetIOInstance()->GetRawButton(1,5)){// && !turn->IsRunning()){
			//turn = new Turn();
			//turn->Start();
		}
		if (CommandBase::GetIOInstance()->GetRawButton(2,1)){// && turn->IsRunning()){
			//turn->Cancel();
			//delete(turn);
		}
		
		
	}
};

START_ROBOT_CLASS(Robot);

