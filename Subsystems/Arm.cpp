#include "Arm.h"
#include "Robotmap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ArmDefault.h"

Arm::Arm() : Subsystem("Arm"),
  spike((UINT8)1, ARM_MOVEMENT_CHANNEL)
{  
}

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  //SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new ArmDefault());
}

void Arm::Move(bool direction){
  if (direction == true){
    SmartDashboard::Log("Forward", "Arm Motor");
    spike.Set(Relay::kForward);
  }
  else if (direction == false){
    SmartDashboard::Log("Reverse", "Arm Motor");
    spike.Set(Relay::kReverse);
  }
}
void Arm::Stop(){
  SmartDashboard::Log("Stopped", "Arm Motor");
  spike.Set(Relay::kOff);
}
