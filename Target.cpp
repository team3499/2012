#include "target.h"

Target::Target(ID id) {
  this->id = id;
  SetHorizontalAngle(0.0);
}

Target::Target(ID id, float angle) {
  this->id = id;
  SetHorizontalAngle(angle);
}

Target::~Target() {

}

//
// Returns the target rim height in meters
//
float Target::GetRimHeight() {
  switch (id) {
    case Bottom : return 0.711;
    case Left   : return 1.559;
    case Right  : return 1.559;
    case Middle : return 1.559;
    case Top    : return 2.489;
  }

  return 0.0;
}

//
// Returns the arc height in meters
//
float Target::GetArcHeight() {
  switch (id) {
    case Bottom : return GetRimHeight() + 1.0;      // TODO - GUESSES! - tune this
    case Left   : return GetRimHeight() + 1.0;      // TODO - GUESSES! - tune this
    case Right  : return GetRimHeight() + 1.0;      // TODO - GUESSES! - tune this
    case Middle : return GetRimHeight() + 1.0;      // TODO - GUESSES! - tune this
    case Top    : return GetRimHeight() + 1.0;      // TODO - GUESSES! - tune this
  }

  return 0.0;
}

//
// Returns the target point value
//
int Target::GetPointValue() {
  switch (id) {
    case Bottom : return 1;
    case Left   : return 2;
    case Right  : return 2;
    case Middle : return 2;
    case Top    : return 3;
  }

  return 0;
}

//
// Returns the target identifer
//
Target::ID Target::GetIdentifier() {
  return id;
}


//
// Returns the horizontal angle necessary to turn to center the target
//
float Target::GetHorizontalAngle() {
  return hAngle;
}

//
// Set the horizontal angle necessary to tern to center the target
//
void Target::SetHorizontalAngle(float angle) {
  hAngle = angle;
}
