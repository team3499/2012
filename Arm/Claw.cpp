#include "ArmRaise.h"

class ArmRaise;



Claw::Claw(UINT32 ch)
	//outp(ch)//channel
{
	outp = new Jaguar(ch);
	
	
}
	
Claw::~Claw(){}
	
void Claw::Set(float pos){
	outp->Set(pos);
}

float Claw::Get(){
	return outp->Get();
}

void Claw::Open(void){
	outp->Set(.5);//experiment with these values
}


void Claw::Close(void){
	outp->Set(-.5);//experiment with these values
}


//protected:
//private:
