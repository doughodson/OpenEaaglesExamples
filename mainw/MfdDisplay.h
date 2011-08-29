//------------------------------------------------------------------------------
// Class:	MfdDisplay
// Base class:	Object > BasicGL::Graphic > Page -> Display -> MfdDisplay
//
// Description:	Example display pages (e.g., MFD, CDU, etc).  Manages the
//              display's pages.
//              -- All it really does for this example is accept the ESC event.
//
//------------------------------------------------------------------------------
#ifndef	__MfdDisplay_H__
#define __MfdDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace MainW {

class MfdDisplay : public BasicGL::Display {
   DECLARE_SUBCLASS(MfdDisplay,BasicGL::Display)

public:
   MfdDisplay();
};

} // End MainW namespace
} // End Eaagles namespace

#endif	/* __MfdDisplay_H__ */
