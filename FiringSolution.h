#ifndef __FIRING_SOLUTION_H__
#define __FIRING_SOLUTION_H__

#include "target.h"

class FiringSolution {

public:
  FiringSolution();
  FiringSolution(float distance, float angle);
  FiringSolution(float distance, Target target);
  virtual ~FiringSolution();

  void SetDistance(float distance);
  void SetHeight(float height);            // Rim height in inches
  void SetHeightFromAngle(float angle);    // Call SetDistance() first!
  void SetHeightFromTarget(Target target);

  bool IsValid();                          // Valid data will be returned

  float GetShooterAngle();
  float GetShooterVelocity();

private:
  float angle;
  float velocity;
  float distance;
  float height;

};

#endif /* __FIRING_SOLUTION_H__ */

