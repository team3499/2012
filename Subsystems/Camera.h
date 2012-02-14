#ifndef CAMERA_SUBSYSTEM_H
#define CAMERA_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


class Camera: public Subsystem {
public:
	struct AngleData{
		float xAxisTurn;
		float yAxisTurn;
	};
	
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AxisCamera *camera;
public:
	Camera();
	void InitDefaultCommand();
	AngleData GetAngleData();
};

#endif /*CAMERA_SUBSYSTEM_H*/
