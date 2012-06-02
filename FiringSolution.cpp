#include "FiringSolution.h"
#include "math.h"

FiringSolution::FiringSolution() {
  Init();
}

FiringSolution::FiringSolution(float distance, float angle) {
  Init();
  SetDistance(distance);
  SetHeightFromAngle(angle);
}

FiringSolution::FiringSolution(float distance, Target target) {
  Init();
  SetDistance(distance);
  SetHeightFromTarget(target);
}

FiringSolution::~FiringSolution() {
}

void FiringSolution::SetDistance(float distance) {
  this->distance = distance;
  dirty = true;
}

void FiringSolution::SetVelocity(float velocity) {
  this->velocity = velocity;
  dirty = true;
}

void FiringSolution::SetHeight(float height) {
  this->height = height;
  dirty = true;
}

void FiringSolution::SetHeightFromAngle(float angle) {
  SetHeight(tan(angle)*distance);
}

void FiringSolution::SetHeightFromTarget(Target target) {
  SetHeight(target.GetRimHeight());
}

bool FiringSolution::IsValid() {
  return (distance > 0.0 && height > 0.0 && velocity > 0.0);
}

// Returns the desired shooter angle above horizontal.  Returns 0.0
// if unable to reach the target with an angle between 80 and 30.
float FiringSolution::GetAngle() {
  Recalculate();
  return angle;
}

float FiringSolution::GetVelocity() {
  return velocity;
}

// Recalculate the shooter angle.
void FiringSolution::Recalculate() {
  if (IsValid() && dirty) {
    float g = 9.81;         // gravitational acceleration
    //
    // The math is really hard to isolate shooter angle.  Instead, iterate down
    // from 80 degrees until the desired distance is achieved.  The equation:
    //
    // x = vx * ( vy / g +- sqrt(vy^2/g^2 - 2*y/g) )
    //
    // See http://hyperphysics.phy-astr.gsu.edu/hbase/traj.html#tra9
    //
    for (int i = 80 ; i >= 30 ; --i) {
      float vy = sin((float)i*3.1415/180.0) * velocity;
      float vx = cos((float)i*3.1415/180.0) * velocity;
      float y  = height - shooterHeight;
      float x = vx * (vy/g + sqrt((vy*vy)/(g*g) - 2*y/g));
      if (x > distance) {
        angle = (float)i;
        dirty = false;
        return;
      }
    }
    angle = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////

void FiringSolution::Init() {
  angle         = 0.0;
  velocity      = 5.6;  // TODO - GUESSING! Measure this!
  shooterHeight = .9;   // TODO - GUESSING! Measure this!
  distance      = 0.0;
  height        = 0.0;
  dirty         = true;
}
