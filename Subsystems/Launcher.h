#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


class Launcher: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar arm;
public:
	Launcher();
	void Init();
	void SetArm(float speed);
	//void SetArmAngle(float angle);
public:
	//float armTargetAngle;
};

#endif
