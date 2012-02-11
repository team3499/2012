#include "Launcher.h"
#include "../Robotmap.h"

Launcher::Launcher() : Subsystem("Launcher"),
	arm(5)
{
	
}
    
void Launcher::Init() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Launcher::SetArm(float speed){
	arm.Set(speed);
}
