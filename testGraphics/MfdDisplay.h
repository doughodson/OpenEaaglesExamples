//------------------------------------------------------------------------------
// Class: MfdDisplay
//
// Description: Example display pages (e.g., MFD, CDU, etc).  Manages the
//              display's pages.
//              -- All it really does for this example is accept the ESC event.
//
//------------------------------------------------------------------------------
#ifndef __oe_example_MfdDisplay_H__
#define __oe_example_MfdDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace example {

class MfdDisplay : public graphics::Display
{
   DECLARE_SUBCLASS(MfdDisplay, graphics::Display)

public:
   MfdDisplay();
};

} // End example namespace
} // End oe namespace

#endif
