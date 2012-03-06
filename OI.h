#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Joystick.h"

class OI {
public:
	Joystick js1;
	Joystick js2;
	FILE *fp;
public:
	OI();
	bool GetRawButton(int num, UINT32 button);
	float GetY(int num);
	float GetX(int num);
	float GetZ(int num);
	
public:
};

#endif
