#ifndef CAMERA_SUBSYSTEM_H
#define CAMERA_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "WPILib.h"

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
	Threshold *thresholds[];
	
	struct AngleData{
		float xAxisTurn;
		float yAxisTurn;
	};
	
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	//AxisCamera *camera;
public:
	Camera();
	void InitDefaultCommand();
	AngleData GetAngleData();
	ParticleAnalysisReport* FindBottomRectangle(ParticleAnalysisReport *reports[], unsigned int reportCount);
	vector<ParticleAnalysisReport> *ProcessImageForReport(ColorImage *image,int whatThreshold);
};

#endif /*CAMERA_SUBSYSTEM_H*/
