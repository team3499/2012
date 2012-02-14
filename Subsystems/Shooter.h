#ifndef __SUBSYSTEM_SHOOTER_H__
#define __SUBSYSTEM_SHOOTER_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter : public Subsystem {

private:
  Victor *          beltTop;
  Victor *          beltBottom;
  DigitalIOButton * buttonMagazineFront;
  DigitalIOButton * buttonMagazineMiddle;
  DigitalIOButton * buttonMagazineBack;

public:
  struct MagazineStatus {
    bool front;
    bool middle;
    bool back;
  };

  Shooter();
  void InitDefaultCommand();

  bool IsReadyToFire();               // Is a ball in the front magazine position
  int BallsInMagazine();              // Number of balls loaded in magazine (0 - 3)
  MagazineStatus GetMagazineStatus(); // Load status of magazine

};

#endif /* __SUBSYSTEM_SHOOTER_H__ */
