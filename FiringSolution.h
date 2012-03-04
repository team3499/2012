#ifndef __FIRING_SOLUTION_H__
#define __FIRING_SOLUTION_H__

#include "target.h"

//
// Given information about the target (height and distance), calculate
// the necessary arm angle for a swish or a bank shot assuming maximum
// exit velocity on the shooter.
//
class FiringSolution {

public:
  FiringSolution();
  FiringSolution(float distance, float angle);
  FiringSolution(float distance, Target target);
  virtual ~FiringSolution();

  void SetDistance(float distance);        // Rim center distance in meters
  void SetHeight(float height);            // Rim height in meters
  void SetHeightFromAngle(float angle);    // Must call SetDistance() first!
  void SetHeightFromTarget(Target target); //

  bool IsValid();                          // Valid data will be returned

  float GetDistance();
  float GetHeight();
  float GetShooterAngle();
  float GetShooterVelocity();

private:
  float angle;         // shooter angle in degrees
  float velocity;      // shooter exit velocity in meters/sec - defaulted
  float distance;      // distance to backboard in meters
  float height;        // height of rim in meters
  float shooterHeight; // height of the shooter in meters

  void Recalculate();
};

#endif /* __FIRING_SOLUTION_H__ */

