#include "lights.h"

Lights::Lights():
	bigRed(3),
	y1(4),
	r(2),
	y2(1)
{
	on = 0;
	on2 = 1;
}
Lights::~Lights(){
	
}
void Lights::Toggle(){
	if(on == 1){
		bigRed.Set(0);
		y1.Set(1);
		on++;
		printf("1");
	} else if(on == 2) {
		y1.Set(0);
		r.Set(1);
		on++;
		printf("2");
	} else if(on == 3){
		r.Set(0);
		y2.Set(1);
		on++;
		printf("3");
	} else {
		y2.Set(0);
		bigRed.Set(1);
		on = 1;
		printf("4");
	}
}

void Lights::All(bool val){
	bigRed.Set(val);
	y1.Set(val);
	r.Set(val);
	y2.Set(val);
}

void Lights::Red(bool val){
	bigRed.Set(val);
	r.Set(val);
}
void Lights::Yellow(bool val){
	y1.Set(val);
	y2.Set(val);
}

void Lights::Toggle2(){
	if(on2 == 1){
		bigRed.Set(1);
		y2.Set(0);
		on2++;
		printf("1");
	} else if(on2 == 2){
		y1.Set(1);
		//y1.Set(0);
		on2++;
		printf("2");
	} else if(on2 == 3) {
		bigRed.Set(0);
		//r.Set(1);
		on2++;
		printf("3");
	} else if(on2 == 4){
		//r.Set(0);
		r.Set(1);
		on2++;
		printf("4");
	} else if(on2 == 5){
		//r.Set(0);
		y1.Set(0);
		on2++;
		printf("5");
	} else if(on2 == 6){
		//r.Set(0);
		y2.Set(1);
		on2++;
		printf("6");
	} else if(on2 == 7){
		r.Set(0);
		//y2.Set(1);
		on2++;
		printf("7");
	} else if(on == 8){
		//y2.Set(0);
		bigRed.Set(1);
		on2 = 1;
		printf("8");
	} else {
		on2 = 1;
	}
}
