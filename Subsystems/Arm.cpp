 #include "Arm.h"
#include "../Robotmap.h"

Arm::Arm() : Subsystem("Arm"),
	spike((UINT8)1, 1)
{	
}
    
void Arm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
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
