#include "..\main.h"

#ifndef ARMRAISE_H
#define ARMRAISE_H

class ArmRaise
{
	DigitalOutput up;
	DigitalOutput down;
public:
	
	ArmRaise(UINT32 u, UINT32 d);
	
	~ArmRaise();
	
	void Move(bool up, bool down);

private:
	
};

#endif //ARMRAISE_H
