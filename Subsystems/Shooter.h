#ifndef __SUBSYSTEM_SHOOTER_H__
#define __SUBSYSTEM_SHOOTER_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter : public Subsystem {

private:
  Victor *          beltTop;
  Victor *          beltBottom;
  DigitalIOButton * buttonLoaded;
  DigitalIOButton * buttonMagazineFront;
  DigitalIOButton * buttonMagazineBack;

public:
  Shooter();
  void InitDefaultCommand();


};

#endif /* __SUBSYSTEM_SHOOTER_H__ */
