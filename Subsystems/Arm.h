#ifndef ARM_H
#define ARM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Relay.h"

class Arm: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Relay spike;
public:
	Arm();
	void InitDefaultCommand();
	void Move(bool direction);
	void Stop();
};

#endif
