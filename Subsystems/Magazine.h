#ifndef __SUBSYSTEM_MAGAZINE_H__
#define __SUBSYSTEM_MAGAZINE_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Magazine : public Subsystem {

private:
  Victor          * belt;
  DigitalIOButton * buttonFront;
  DigitalIOButton * buttonMiddle;
  DigitalIOButton * buttonBack;

public:
  struct LoadStatus {
    bool front;
    bool middle;
    bool back;
  };

  Magazine();
  void InitDefaultCommand();

  bool IsReadyToFire();       // Is a ball in the front magazine position
  int BallCount();            // Number of balls loaded in magazine (0 - 3)
  LoadStatus GetLoadStatus(); // Load status of magazine
  void Move(bool direction);
  void Stop();

};

#endif /* __SUBSYSTEM_MAGAZINE_H__ */
