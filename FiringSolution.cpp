#include "FiringSolution.h"
#include "math.h"

FiringSolution::FiringSolution() {
  angle         = 0.0;
  velocity      = 6.0;  // TODO - GUESSING! Measure this!
  shooterHeight = 1.0;  // TODO - GUESSING! Measure this!
  distance      = 0.0;
  height        = 0.0;
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
  Recalculate();
}

void FiringSolution::SetHeight(float height) {
  this->height = height;
  Recalculate();
}

void FiringSolution::SetHeightFromAngle(float angle) {
  SetHeight(tan(angle)*distance);
}

void FiringSolution::SetHeightFromTarget(Target target) {
  SetHeight(target.GetRimHeight());
}

bool FiringSolution::IsValid() {
  return (distance > 0.0 && height > 0.0);
}

float FiringSolution::GetShooterAngle() {
  return angle;
}

float FiringSolution::GetShooterVelocity() {
  return velocity;
}

void FiringSolution::Recalculate() {
  if (IsValid()) {
    float g = 9.81;         // gravitational acceleration

    //
    // The math is really hard to isolate shooter angle.  Instead, iterate down
    // from 80 degrees until the desired distance is achieved.  The equation:
    //
    // x = vx * ( vy / g +- sqrt(vy^2/g^2 - 2(h3-h1)/g) )
    //
    for (int i = 80 ; i >= 30 ; --i) {
      float vy = sin((float)i) * velocity;
      float vx = cos((float)i) * velocity;
      float x = vx * (vy/g + sqrt((vy*vy) / (g*g) - 2*(height-shooterHeight)/g));
      if (x > distance) {
        angle = (float)i;
        return;
      }
    }
    angle = 0.0;
  }
}
