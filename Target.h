#ifndef __TARGET_H__
#define __TARGET_H__

//
// Contains data about a target:
//   * Rim height
//   * Location
//   * Point Value
//
class Target {

public:

  enum ID {
    Bottom,
    Left,
    Right,
    Middle,    // Either left or right
    Top
  };

  Target(ID id);
  virtual ~Target();

  float GetRimHeight();   // Rim height in meters
  float GetArcHeight();   // Recommended shooting arc height in meters
  int GetPointValue();    // Point value for scoring on this target
  ID GetIdentifier();     // The target

private:
  ID id;

  Target() {};

};

#endif /* __TARGET_H__ */
