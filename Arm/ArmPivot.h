#include "..\main.h"

#ifndef ARMPIVOT_H
#define ARMPIVOT_H

class ArmPivot
{
	RobotDrive rd;//CRUDE
	//const short chan = 3;//pwm
public:
	
	ArmPivot(UINT32 ch);
	
	~ArmPivot();
	
	void Move(float spd);
	
};

#endif //ARMPIVOT_H
