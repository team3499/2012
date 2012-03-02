#include "Lights.h"
#include "Commands/LightsCommand.h"
#include "Robotmap.h"
#include "WPILib.h"

Lights::Lights(): Subsystem("Lights")
{
	// Use requires() here to declare subsystem dependencies
	w1 = new DigitalOutput(LEDS_WHITE_1_CHANNEL);
	w2 = new DigitalOutput(LEDS_WHITE_2_CHANNEL);
	r = new DigitalOutput(LEDS_RED_CHANNEL);
	b = new DigitalOutput(LEDS_BLUE_CHANNEL);
	on = 0;
	on2 = 1;
}

// Called just before this Command runs the first time
void Lights::InitDefaultCommand() {
	SetDefaultCommand(new LightsCommand());
}

// Called repeatedly when this Command is scheduled to run
void Lights::Toggle2() {
	if(on2 == 0){
		w1->Set(1);
		b->Set(0);
		on2++;
	} else if(on2 == 5){
		r->Set(1);
		//y1.Set(0);
		on2++;
	} else if(on2 == 10) {
		w1->Set(0);
		//r.Set(1);
		on2++;
	} else if(on2 == 15){
		//r.Set(0);
		w2->Set(1);
		on2++;
	} else if(on2 == 20){
		//r.Set(0);
		r->Set(0);
		on2++;
	} else if(on2 == 25){
		//r.Set(0);
		b->Set(1);
		on2++;
	} else if(on2 == 30){
		w2->Set(0);
		//y2.Set(1);
		on2++;
	} else if(on == 35){
		//y2.Set(0);
		w1->Set(1);
		on2 = 1;
	} else {
		on2 = 0;
	}
}

void Lights::All(bool state){
	w1->Set(state);
	w2->Set(state);
	r->Set(state);
	b->Set(state);
}
