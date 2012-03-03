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
    Top
  };

  Target(ID id);
  virtual ~Target();

  float GetHeight();      // Rim height in inches
  int GetPointValue();    // Point value for scoring on this target
  ID GetIdentifier();     // The target

private:
  ID id;

  Target() {};

};

#endif /* __TARGET_H__ */
