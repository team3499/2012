#ifndef CAMERA_SUBSYSTEM_H
#define CAMERA_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "Target.h"
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
  Camera();
  void InitDefaultCommand() {}

  bool status;//true = good. false = BAIL ON EVERYTHING
  
  Target *GetLastGoodTarget();
  
  Target * GetTarget();

  ColorImage * CaptureImage();
  vector<ParticleAnalysisReport> * GetPotentialParticles(ColorImage *image, Threshold *thresholds[]);
  Target * SelectPreferredTarget(vector<ParticleAnalysisReport> *particles);

private:
  Target *lastGoodTarget;
  void SetLastGoodTarget(Target *target);
  
  Threshold *thresholds[];

  vector<ParticleAnalysisReport> * ProcessImageForReport(ColorImage *image, Threshold *threshold, int index);
  void OutputThreshold(Threshold *threshold);
  void OutputParticle(ParticleAnalysisReport *particle);
  void OutputParticles(vector<ParticleAnalysisReport> *particles);
  void OutputTarget(Target *target);
};

#endif /*CAMERA_SUBSYSTEM_H*/
