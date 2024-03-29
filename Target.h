#ifndef __TARGET_H__
#define __TARGET_H__

//
// Contains data about a target:
//   * Rim height
//   * Location
//   * Point Value
//   * Horizontal Angle
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
  Target(ID id, float angle);
  virtual ~Target();

  float GetRimHeight();   // Rim height in meters
  float GetArcHeight();   // Recommended shooting arc height in meters
  int GetPointValue();    // Point value for scoring on this target
  Target::ID GetIdentifier();     // The target

  float GetHorizontalAngle();  // The amount to turn to center the target
  void SetHorizontalAngle(float angle);

  const char * AsString();     // String rep of Target

private:
  ID id;
  float hAngle;
  char stringRep[64];

  Target() {};

};

#endif /* __TARGET_H__ */
