#include "Commands/CrossBridge.h"
#include "Commands/TipBridge.h"
#include "Commands/DriveForward.h"
#include "Commands/ArmLevel.h"

//
// Command Group to cross a tilting bridge in neutral position.
//
// Expects the robot to be positioned square to the edge of the bridge
// and close enough to touch with the arm rotated forward.
//

CrossBridge::CrossBridge() {
  AddSequential(new TipBridge);
  AddSequential(new DriveForward(2.0, 0.3, true));
  AddParallel(new DriveForward(6.0, 0.5));
  AddParallel(new ArmLevel(0.0));
}
