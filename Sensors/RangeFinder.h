#ifndef RANGE_H
#define RANGE_H

#include "AnalogChannel.h"

class RangeFinder {
private:
	AnalogChannel input;
	
public:
public:
	RangeFinder(UINT32 channel);
	~RangeFinder();
	double GetIn();
	double GetRaw();
	double GetSmooth(int count = 5);
	UINT32 GetFT();
	
};




#endif
