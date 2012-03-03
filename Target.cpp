#include "target.h"

Target::Target(ID id) {
  this->id = id;
}

Target::~Target() {

}

//
// Returns the target rim height in inches
//
float Target::GetHeight() {
  switch (id) {
    case Bottom : return 28.0;
    case Left   : return 61.0;
    case Right  : return 61.0;
    case Top    : return 98.0;
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
