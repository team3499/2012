#include "Chassis.h"
#include "../Robotmap.h"

Chassis::Chassis() : Subsystem("Chassis"),
	drive(1,2,3,4)//front left, rear left, front right, rear right
{
	
}
    
void Chassis::Init() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Chassis::ArcadeDrive(Joystick *joystick){
	drive.ArcadeDrive(joystick);
}

void Chassis::ArcadeDrive(Joystick &joystick){
	drive.ArcadeDrive(joystick);
}
