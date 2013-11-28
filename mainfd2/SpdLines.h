//------------------------------------------------------------------------------
// Class: SpdLines
// 
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
#ifndef __Eaagles_MainFlightDisplay2_SpdLines_H__
#define __Eaagles_MainFlightDisplay2_SpdLines_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainFlightDisplay2 {

class SpdLines : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(SpdLines,BasicGL::Graphic)

public:
    SpdLines();

    // BasicGL::Graphic interface
    virtual void drawFunc();

    // Basic::Component interface
    virtual bool event(const int event, Basic::Object* const obj = 0);

    // set functions
    virtual bool setIsAlt(const bool newIsAlt) { isAlt = newIsAlt; return true; }

    // get functions
    bool isAltSelected()    { return isAlt; }

protected:
    bool setSlotIsAlt(const Basic::Number* newIsAlt);

private:
    // event function
    bool onEventSetIsAltSpdLines(const Basic::Number* const x);

    bool isAlt;     // are we drawing the altitude lines instead?
};

}; // end of MainFlightDisplay2 namespace
}; // end of Eaagles namespace

#endif

