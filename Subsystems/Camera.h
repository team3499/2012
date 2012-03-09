#ifndef CAMERA_SUBSYSTEM_H
#define CAMERA_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "WPILib.h"
#include "Target.h"

#define ASPECT_RATIO (24.0/18.0)
#define ASPECT_RATIO_TOLERANCE 0.15
#define ASPECT_MIN ((1-ASPECT_RATIO_TOLERANCE)*ASPECT_RATIO)
#define ASPECT_MAX ((1+ASPECT_RATIO_TOLERANCE)*ASPECT_RATIO)
#define WIDTH_FRACTION_MIN 0.1

#ifdef TEST_TARGET
#define TEST_MSG(S,...) printf(S,##__VA_ARGS__)
#else
#define TEST_MSG(S,...)
#endif

class Camera: public Subsystem {
public:
	unsigned int particleCount;
	struct Thresh{
		Threshold *threshold;
		Threshold *changeBy;
		Threshold *limits;
		int counter;

	};
	struct AngleData{
		float xAxisTurn;
		float yAxisTurn;
	};
	
  Target::ID lastTarget;

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	//AxisCamera *camera;
  Target::ID GuessTarget(ParticleAnalysisReport *);

public:
	Camera();
	void InitDefaultCommand();
	AngleData GetAngleData();
	void FixThreshold(Camera::Thresh *thresh);
	ParticleAnalysisReport* FindBottomRectangle(ParticleAnalysisReport *reports[], unsigned int reportCount);
  Target::ID LastTargetFound();
};

#endif /*CAMERA_SUBSYSTEM_H*/
