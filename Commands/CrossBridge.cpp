#include "Commands/CrossBridge.h"
#include "Commands/TipBridge.h"

//
// Command Group to cross a tilting bridge in neutral position.
//
// Expects the robot to be positioned square to the edge of the bridge
// and close enough to touch with the arm rotated forward.
//

CrossBridge::CrossBridge() {
  AddSequential(new TipBridge());
}
