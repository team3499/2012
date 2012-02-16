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
  enum StatusEnum {
	  stopped = 0x00 , shooting = 0x02, readying = 0x04 , loading = 0x08
  };
  
  struct LoadStatus {
    bool front;
    bool middle;
    bool back;
  };
private:
  static StatusEnum status;
public:

  Magazine();
  void InitDefaultCommand();

  bool IsReadyToFire();       // Is a ball in the front magazine position
  int BallCount();            // Number of balls loaded in magazine (0 - 3)
  LoadStatus GetLoadStatus(); // Load status of magazine
  void Move(bool direction);
  void Set(float speed);
  void Stop();
  void SetShooting(bool in);
  StatusEnum Status();

};

#endif /* __SUBSYSTEM_MAGAZINE_H__ */
