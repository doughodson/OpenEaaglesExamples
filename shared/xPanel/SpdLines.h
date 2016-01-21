//------------------------------------------------------------------------------
// Class: SpdLines
//------------------------------------------------------------------------------
#ifndef __oe_XPanel_SpdLines_H__
#define __oe_XPanel_SpdLines_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
namespace xPanel {

//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
class SpdLines : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(SpdLines,BasicGL::Graphic)

public:
    SpdLines();

    // set functions
    virtual bool setIsAlt(const bool newIsAlt)      { isAlt = newIsAlt; return true; }

    // get functions
    bool isAltSelected()                            { return isAlt; }

    void drawFunc() override;

    bool event(const int event, Basic::Object* const obj = nullptr) override;

protected:
    bool setSlotIsAlt(const Basic::Number* newIsAlt);

private:
    // event function
    bool onEventSetIsAltSpdLines(const Basic::Number* const x);

    bool isAlt;     // are we drawing the altitude lines instead?
};

} // End xPanel namespace
} // End oe namespace

#endif

