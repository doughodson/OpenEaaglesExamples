//=============================================================================
// Class:: BasicGL::Display -> Fltk1::Display
// Description: Simple Display that will rotate our graphics.
//=============================================================================

#ifndef __EAAGLES_FLTK1_DISPLAY_H__
#define __EAAGLES_FLTK1_DISPLAY_H__

#include "openeaagles/basicGL/Display.h"

namespace Eaagles {
namespace Fltk1 {

class Display : public BasicGL::Display
{
    DECLARE_SUBCLASS(Display,BasicGL::Display)

public:
    Display();
    
    // these are our mouse states, so we can 
    // keep track of our mouse state internally
    enum ButtonStates {
        MOUSE_UP = 0,
        MOUSE_DOWN = 1
    };

    // setting rotations
    virtual void setXRotation(const double x);
    virtual void setYRotation(const double y);
    virtual void setZRotation(const double z);

private:
    // send datas for our rotations
    SendData xRotationSD;
    SendData yRotationSD;
    SendData zRotationSD;
};

};  // end Fltk1
};  // end Eaagles

#endif // __EAAGLES_FLTK1_DISPLAY_H__
