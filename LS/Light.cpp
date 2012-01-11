#include "Light.h"

class LS;

LS::LS(UINT32 ch):
	DICh(ch)//channels
{
}
	
LS::~LS(){}
	
bool LS::Get(){
	return DICh.Get();
}
	
//protected:
//private:
