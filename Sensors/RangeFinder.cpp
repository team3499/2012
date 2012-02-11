#include "RangeFinder.h"

RangeFinder::RangeFinder(UINT32 channel):
	input(channel)
{
}
RangeFinder::~RangeFinder(){
	
}
double RangeFinder::GetIn(){
	return GetSmooth()/.0098;
}
double RangeFinder::GetSmooth(int count){
	float vol;
	int i = 0;
	while(i < count){
		vol += input.GetVoltage();
		i++;
	}
	return vol/count;
}
double RangeFinder::GetRaw(){
	return input.GetVoltage();
}
UINT32 RangeFinder::GetFT(){
	return (UINT32)(GetIn()/12);
}
