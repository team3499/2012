#include "..\main.h"

#ifndef LIGHT_H
#define LIGHT_H

class LS
{
	DigitalInput DICh;
public:
	
	LS(UINT32 ch);
	
	~LS();
	
	bool Get();

private:
	
};

#endif //LIGHT_H
