#ifndef __COMMAND_CROSS_BRIDGE_H__
#define __COMMAND_CROSS_BRIDGE_H__

#include "Commands/CommandGroup.h"

class CrossBridge : public CommandGroup {

public:

  //
  // Command Group to cross a tilting bridge in neutral position.
  //
  // Expects the robot to be positioned square to the edge of the bridge
  // and close enough to touch with the arm rotated forward.
  //
  CrossBridge();
};

#endif /* __COMMAND_CROSS_BRIDGE_H__ */
