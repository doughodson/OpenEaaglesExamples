#include "Display.h"

namespace Eaagles {
namespace Fltk1 {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Display,"Fltk1Display")
EMPTY_SERIALIZER(Display)

// ----------------------------------------------------------------------------
// constructor(s)
// ----------------------------------------------------------------------------
Display::Display()
{
    STANDARD_CONSTRUCTOR()
    xRotationSD.empty();
    yRotationSD.empty();
    zRotationSD.empty();
}

// ----------------------------------------------------------------------------
// copyData() 
// ----------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool)
{
    BaseClass::copyData(org);

    xRotationSD.empty();
    yRotationSD.empty();
    zRotationSD.empty();
}

// ----------------------------------------------------------------------------
// deleteData() -
// ----------------------------------------------------------------------------
EMPTY_DELETEDATA(Display)

// ----------------------------------------------------------------------------
// setXRotation() - send our X rotation down to our graphics
// ----------------------------------------------------------------------------
void Display::setXRotation(const double x)
{
    send("logo", UPDATE_VALUE, x, xRotationSD);
}

// ----------------------------------------------------------------------------
// setYRotation() - send our Y rotation down to our graphics
// ----------------------------------------------------------------------------
void Display::setYRotation(const double y)
{
    send("logo", UPDATE_VALUE3, y, yRotationSD);
}

// ----------------------------------------------------------------------------
// setZRotation() - send our Z rotation down to our graphics
// ----------------------------------------------------------------------------
void Display::setZRotation(const double z)
{
    send("logo", UPDATE_VALUE5, z, zRotationSD);
}


};  // end Fltk1 
};  // end Eaagles
