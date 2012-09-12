/* Include Standerd C Libs */
using namespace std;
/* Include WPILib Headers */
#include "WPILib.h"
#include "DigitalOutput.h"
/* Include Custom Headers */
#include "CommandBase.h"
/* Include Custom Commands */
#include "Commands/Command.h"
#include "Commands/AutoGroup.h"
#include "Commands/DAG.h"
#include "Commands/ArmLevel.h"
#include "FiringSolution.h"
#include "Commands/ShootGroup.h"
#include "Commands/StopAll.h"
class Robot : public IterativeRobot {
  private:
  CommandBase *armLevel;
  Command *autonomousCommand;
private:
  
  virtual void RobotInit()
  {
    //Wait(.2);
    
    //SmartDashboard::init();
    CommandBase::init();	
    autonomousCommand = new AutoGroup();
//delete autonomousCommand;
//autonomousCommand = new ArmLevel(0.0);
    //SmartDashboard sd = SmartDashboard::GetInstance();
  }
  
  virtual void AutonomousInit() {
    autonomousCommand->Start();
  }
  
  virtual void AutonomousPeriodic() {
    Scheduler::GetInstance()->Run();
  }
  
  virtual void TeleopInit() {
    //autonomousCommand->Cancel();
  }
  
  virtual void TeleopPeriodic(){
    Scheduler::GetInstance()->Run();
/*
    if (CommandBase::GetOIInstance()->GetRawButton(1,3) && !armLevel->IsRunning()){
      armLevel = new ArmLevel((float)45.0);
      armLevel->Start();
    } else if (CommandBase::GetOIInstance()->GetRawButton(1,2) && !armLevel->IsRunning()){
      armLevel = new ArmLevel((float)-45.0);
      armLevel->Start();
    }
    if (CommandBase::GetOIInstance()->GetRawButton(2,3) && armLevel->IsRunning()){
      armLevel->Cancel();
      delete(armLevel);
    }
    if (CommandBase::GetOIInstance()->GetRawButton(2,3) && armLevel->IsRunning()){
      armLevel->Cancel();
      delete(armLevel);
    }
    
    if (CommandBase::GetOIInstance()->GetRawButton(1,4)){// && !turn->IsRunning()){
      new ShootGroup();
      //turn = new Turn();
      //turn->Start();
    } else if (CommandBase::GetOIInstance()->GetRawButton(1,5)){// && !turn->IsRunning()){
      new ShootGroup();
    }
*/
    if (CommandBase::GetOIInstance()->GetRawButton(1,1) && !autonomousCommand->IsRunning()){// && turn->IsRunning()){
      delete autonomousCommand; autonomousCommand = NULL;
      autonomousCommand = new AutoGroup();
      autonomousCommand->Start();
    }
    //if (CommandBase::GetOIInstance()->GetRawButton(1,3) && !autonomousCommand->IsRunning()){// && turn->IsRunning()){
    //  autonomousCommand = new DAG();
    //  autonomousCommand->Start();
    //}
  }
};

START_ROBOT_CLASS(Robot);

