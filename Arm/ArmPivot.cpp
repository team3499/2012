#include "ArmPivot.h"

class ArmPivot;

ArmPivot::ArmPivot(UINT32 ch):
	rd(ch,ch)
	//	channel	
{
	
	
}
	
ArmPivot::~ArmPivot(){}

void ArmPivot::Move(float spd){
	rd.TankDrive(0,spd);
}
	
//protected:
//private:
