#include "Rotation.h"
#include "WPILib.h"

Rotation::Rotation():
	lights()
{
	i = 0;
	//Requires();
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	//requires(accJ);
}

// Called just before this Command runs the first time
void Rotation::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void Rotation::Execute() {
/*	double deg = acc.GetArmDegree();
	printf("%.10f\n",deg);
	if(oi->GetRawButton(2,3)){
		if( deg > -134 && deg < 0){
			;//launcher->SetArm(-.3);
		} else if(deg < -136 || deg > 140){
			;//launcher->SetArm(.3);
		} else {
			;//launcher->SetArm(0);
		}
	} else if(oi->GetRawButton(2,4) && !oi->GetRawButton(2,5)){
		if( deg > -89 && deg < 0){
			;//launcher->SetArm(-.45);
		} else if(deg < -91 || deg > 140){
			;//launcher->SetArm(.45);
		} else {
			;//launcher->SetArm(0);
		}
	} else if(oi->GetRawButton(2,5) && !oi->GetRawButton(2,4)){
		if( deg > -178 && deg < 0){
			;//launcher->SetArm(-.45);
		} else if(deg > 140){
			;//launcher->SetArm(.45);
		} else {
			;//launcher->SetArm(0);
		}
	} else {
		;//launcher->SetArm(oi->GetY(2));
	}*/
	printf("Rexec");
}

// Make this return true when this Command no longer needs to run execute()
bool Rotation::IsFinished() {
	//if(i==150){
	//	return true;
	//}
	return false;
}

// Called once after isFinished returns true
void Rotation::End() {
	printf("Rend");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotation::Interrupted() {
	i = 150;
}
