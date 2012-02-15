#include "Arm.h"
#include "Robotmap.h"
#include "Commands/ArmLevel.h"

Arm::Arm() : Subsystem("Arm"),
	spike((UINT8)1, ARM_MOVEMENT_CHANNEL)
{	
}
    
void Arm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ArmLevel());
}
void Arm::Move(bool direction){
	if (direction == true){
		spike.Set(Relay::kForward);
	}
	else if (direction == false){
		spike.Set(Relay::kReverse);
	}
	else{
		;//ERROR : unset variable (null)
	}
}
void Arm::Stop(){
	spike.Set(Relay::kOff);
}
