#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Joystick.h"
#include "Preferences.h"
#include "Robotmap.h"

class OI {
private:
	Joystick *js[];
	Preferences *preferences;
public:
	OI();
	
	// For now, maybe it will change, These numbers START AT 1
	// this is also in accordance to the JOYSTICK_ defines, which start at one
	bool GetRawButton(int js, UINT32 button);
	bool GetTrigger(int js);
	float GetY(int js);
	float GetX(int js);
	float GetZ(int js);
	
	Joystick *GetDriveJS();
	Joystick *GetAccessoryJS();
	
	/* Setting A Preference Value */
	void Log(char *name, bool value);
	void Log(char *name, int value);
	void Log(char *name, char value);
	void Log(char *name, char *value);
	void Log(char *name, long value);
	void Log(char *name, double value);
	void Log(char *name, float value);

	/* Getting A Preference Value */
	/* these do not return because they would not be able to be overloaded */
	void Get(char *name, bool *output);
	void Get(char *name, int *output);
	void Get(char *name, long *output);
	void Get(char *name, char *output);
	void Get(char *name, char *output[]);
	void Get(char *name, double *output);
	void Get(char *name, float *output);
	
public:
};

#endif
