
#include "FltkDisplay.h"

namespace oe {
namespace example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(FltkDisplay, "FltkDisplay")
EMPTY_SERIALIZER(FltkDisplay)
EMPTY_DELETEDATA(FltkDisplay)

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

void FltkDisplay::copyData(const FltkDisplay& org, const bool)
{
   BaseClass::copyData(org);
   initData();
}

// send X rotation down to our graphics
void FltkDisplay::setXRotation(const double x)
{
   send("logo", UPDATE_VALUE, x, xRotationSD);
}

// send Y rotation down to our graphics
void FltkDisplay::setYRotation(const double y)
{
   send("logo", UPDATE_VALUE3, y, yRotationSD);
}

// send Z rotation down to our graphics
void FltkDisplay::setZRotation(const double z)
{
   send("logo", UPDATE_VALUE5, z, zRotationSD);
}

}
}

