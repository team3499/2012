#include "ArmRaise.h"

class ArmRaise;

ArmRaise::ArmRaise(UINT32 u,UINT32 d):
	up(u),
	down(d)//channels
{
	
	
}
	
ArmRaise::~ArmRaise(){}
	
void ArmRaise::Move(bool u, bool d){
	switch(u-d){
		case 1:
			down.Set(false);
			up.Set(true);
			break;
		case 0:
			down.Set(false);
			up.Set(false);
			break;
		case -1:
			up.Set(false);
			down.Set(true);
			break;
		
	}
}
	
//protected:
//private:
