#include "OI.h"

OI::OI():
	js1(1),
	js2(2)
{
	// Process operator interface input here.
	if((fp = fopen("/PROGRAMLOG.TXT","w"))==NULL){
		if((fp = fopen("/PROGRAMLOG.TXT","r"))==NULL){
			fprintf(stderr,"EROOROROOROROROROROROROROROROROR");
		} else {
		}
	} else {
		fprintf(fp,"HELLO!\n");
	}
}

bool OI::GetRawButton(int num, UINT32 button){
	switch(num){
	case 1:
		return js1.GetRawButton(button);
	case 2:
		return js2.GetRawButton(button);
	case 3:
		//return js3.GetRawButton(button);
	case 4:
		//return js4.GetRawButton(button);
	default:
		printf("Joystick out of range");
		return NULL;
	}
}

float OI::GetY(int num){
	switch(num){
	case 1:
		return js1.GetY();
	case 2:
		return js2.GetY();
	case 3:
		//return js3.GetRawButton(button);
	case 4:
		//return js4.GetRawButton(button);
	default:
		printf("Joystick out of range");
		return (float)NULL;
	}
}

float OI::GetX(int num){
	switch(num){
		case 1:
			return js1.GetX();
		case 2:
			return js2.GetX();
		case 3:
			//return js3.GetRawButton(button);
		case 4:
			//return js4.GetRawButton(button);
		default:
			printf("Joystick out of range");
			return (float)NULL;
		}
}

float OI::GetZ(int num){
	switch(num){
		case 1:
			return js1.GetZ();
		case 2:
			return js2.GetZ();
		case 3:
			//return js3.GetRawButton(button);
		case 4:
			//return js4.GetRawButton(button);
		default:
			printf("Joystick out of range");
			return (float)NULL;
		}
}
