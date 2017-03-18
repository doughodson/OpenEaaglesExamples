
#ifndef __oe_xpanel_SpdLines_H__
#define __oe_xpanel_SpdLines_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
namespace xpanel {

//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
class SpdLines : public graphics::Graphic
{
    DECLARE_SUBCLASS(SpdLines,graphics::Graphic)

public:
    SpdLines();

    // set functions
    virtual bool setIsAlt(const bool newIsAlt)      { isAlt = newIsAlt; return true; }

    // get functions
    bool isAltSelected()                            { return isAlt; }

    virtual void drawFunc() override;

    virtual bool event(const int event, base::Object* const obj = nullptr) override;

protected:
    bool setSlotIsAlt(const base::Number* newIsAlt);

private:
    // event function
    bool onEventSetIsAltSpdLines(const base::Number* const x);

    bool isAlt {};     // are we drawing the altitude lines instead?
};

}
}

#endif
