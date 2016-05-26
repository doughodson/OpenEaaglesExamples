
#ifndef __oe_demo_SpdLines_H__
#define __oe_demo_SpdLines_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace demo {

//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:  Slots only
//------------------------------------------------------------------------------
class SpdLines : public graphics::Graphic
{
    DECLARE_SUBCLASS(SpdLines,graphics::Graphic)

public:
    SpdLines();

    virtual void drawFunc() override;

    // set functions
    virtual bool setIsAlt(const bool newIsAlt);
    virtual bool setDrawBack(const bool newDB);

    // get functions
    bool isAltOn()          { return isAlt; }
    bool isBackgroundOn()   { return drawBack; }

protected:
    // slot functions
    bool setSlotIsAlt(const base::Number* newIsAlt);
    bool setSlotDrawBack(const base::Number* newDB);

private:
    bool isAlt;     // are we drawing the altitude lines instead?
    bool drawBack;  // draw the background (for transparency purposes)
};

}
}

#endif
