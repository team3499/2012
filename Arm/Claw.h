#include "..\main.h"

#ifndef CLAW_H
#define CLAW_H

class Claw
{
	SpeedController *outp;
public:
	
	Claw(UINT32 ch);
	
	~Claw();
	
	void Set(float pos);
	
	float Get();
	
	void Open();
	
	void Close();
	
private:
	
};

#endif //CLAW_H
