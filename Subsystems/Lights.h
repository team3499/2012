#ifndef __LIGHTS_H__
#define __LIGHTS_H__

#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include "DigitalOutput.h"

class Lights : public Subsystem {
private:
	DigitalOutput *r,*w1,*b,*w2;
	int on, on2;
public:
	Lights();
	void InitDefaultCommand();
	void Toggle2();
	void All(bool state);
};

#endif
