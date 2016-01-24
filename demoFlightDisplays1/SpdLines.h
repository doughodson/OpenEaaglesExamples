//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:  Slots only
//------------------------------------------------------------------------------
#ifndef __oe_demo_SpdLines_H__
#define __oe_demo_SpdLines_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
namespace demo {

class SpdLines : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(SpdLines,BasicGL::Graphic)

public:
    SpdLines();

    void drawFunc() override;

    // set functions
    virtual bool setIsAlt(const bool newIsAlt);
    virtual bool setDrawBack(const bool newDB);

    // get functions
    bool isAltOn()          { return isAlt; }
    bool isBackgroundOn()   { return drawBack; }

protected:
    // slot functions
    bool setSlotIsAlt(const basic::Number* newIsAlt);
    bool setSlotDrawBack(const basic::Number* newDB);

private:
    bool isAlt;     // are we drawing the altitude lines instead?
    bool drawBack;  // draw the background (for transparency purposes)
};

}; // end of demo namespace
}; // end of oe namespace

#endif

