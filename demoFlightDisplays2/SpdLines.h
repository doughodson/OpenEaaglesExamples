//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
#ifndef __oe_demo_SpdLines_H__
#define __oe_demo_SpdLines_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
namespace demo {

class SpdLines : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(SpdLines, BasicGL::Graphic)

public:
    SpdLines();

    void drawFunc() override;
    bool event(const int event, Basic::Object* const obj = nullptr) override;

    // set methods
    virtual bool setIsAlt(const bool newIsAlt)          { isAlt = newIsAlt; return true; }

    // get methods
    bool isAltSelected()                                { return isAlt; }

protected:
    bool setSlotIsAlt(const Basic::Number* newIsAlt);

private:
    // event method
    bool onEventSetIsAltSpdLines(const Basic::Number* const x);

    bool isAlt;     // are we drawing the altitude lines instead?
};

}; // end of demo namespace
}; // end of oe namespace

#endif

