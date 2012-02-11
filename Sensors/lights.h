#ifndef LIGHTS_H
#define LIGHTS_H

#include "DigitalOutput.h"

class Lights {
private:
	DigitalOutput bigRed,y1,r,y2;
public:
public:
	Lights();
	~Lights();
	void Toggle();
	void Toggle2();
	void All(bool val);
	void Red(bool val);
	void Yellow(bool val);
private:
	int on;
	int on2;
};
#endif
