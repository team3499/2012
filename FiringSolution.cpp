#include "FiringSolution.h"
#include "math.h"

FiringSolution::FiringSolution() {
  angle    = 0.0;
  velocity = 0.0;
  distance = 0.0;
  height   = 0.0;
}

FiringSolution::FiringSolution(float distance, float angle) {
  SetDistance(distance);
  SetHeightFromAngle(angle);
}

FiringSolution::FiringSolution(float distance, Target target) {
  SetDistance(distance);
  SetHeightFromTarget(target);
}

FiringSolution::~FiringSolution() {

}

void FiringSolution::SetDistance(float distance) {
  this->distance = distance;
}

void FiringSolution::SetHeight(float height) {
  this->height = height;
}

void FiringSolution::SetHeightFromAngle(float angle) {
  SetHeight(tan(angle)*distance);
}

void FiringSolution::SetHeightFromTarget(Target target) {
  SetHeight(target.GetHeight());
}

bool FiringSolution::IsValid() {
  return (distance > 0.0 && height > 0.0);
}

float FiringSolution::GetShooterAngle() {
 return 0.0;
}

float FiringSolution::GetShooterVelocity() {
  return 0.0;
}
