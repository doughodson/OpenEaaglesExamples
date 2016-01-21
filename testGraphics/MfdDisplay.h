//------------------------------------------------------------------------------
// Class: MfdDisplay
//
// Description: Example display pages (e.g., MFD, CDU, etc).  Manages the
//              display's pages.
//              -- All it really does for this example is accept the ESC event.
//
//------------------------------------------------------------------------------
#ifndef __oe_Example_MfdDisplay_H__
#define __oe_Example_MfdDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace Example {

class MfdDisplay : public BasicGL::Display
{
   DECLARE_SUBCLASS(MfdDisplay, BasicGL::Display)

public:
   MfdDisplay();
};

} // End Example namespace
} // End oe namespace

#endif
