#ifndef __TIP_BRIDGE_H__
#define __TIP_BRIDGE_H__

#include "CommandBase.h"

class TipBridge : public CommandBase {

private:
  bool needsReset;  // Does the arm need to be reset to pass over the bridge
  bool moving;      // Is the arm in motion

  void RaiseArm();
  void LowerArm();
  void StopArm();

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

public:
  TipBridge();      // Extend Arm forward enough to tip bridge to ground
};

#endif /* __TIP_BRIDGE_H__ */
