//
#include "FltkDisplay.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(FltkDisplay, "FltkDisplay")
EMPTY_SERIALIZER(FltkDisplay)
EMPTY_DELETEDATA(FltkDisplay)

// ----------------------------------------------------------------------------
// constructor(s)
// ----------------------------------------------------------------------------
FltkDisplay::FltkDisplay()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

void FltkDisplay::initData()
{
   xRotationSD.empty();
   yRotationSD.empty();
   zRotationSD.empty();
}

// ----------------------------------------------------------------------------
// copyData() 
// ----------------------------------------------------------------------------
void FltkDisplay::copyData(const FltkDisplay& org, const bool)
{
   BaseClass::copyData(org);
   initData();
}

// ----------------------------------------------------------------------------
// setXRotation() - send our X rotation down to our graphics
// ----------------------------------------------------------------------------
void FltkDisplay::setXRotation(const double x)
{
   send("logo", UPDATE_VALUE, x, xRotationSD);
}

// ----------------------------------------------------------------------------
// setYRotation() - send our Y rotation down to our graphics
// ----------------------------------------------------------------------------
void FltkDisplay::setYRotation(const double y)
{
   send("logo", UPDATE_VALUE3, y, yRotationSD);
}

// ----------------------------------------------------------------------------
// setZRotation() - send our Z rotation down to our graphics
// ----------------------------------------------------------------------------
void FltkDisplay::setZRotation(const double z)
{
   send("logo", UPDATE_VALUE5, z, zRotationSD);
}

}  // end Example 
}  // end Eaagles
