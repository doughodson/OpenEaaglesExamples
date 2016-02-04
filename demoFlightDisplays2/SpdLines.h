//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
#ifndef __oe_demo_SpdLines_H__
#define __oe_demo_SpdLines_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace demo {

class SpdLines : public graphics::Graphic
{
    DECLARE_SUBCLASS(SpdLines, graphics::Graphic)

public:
    SpdLines();

    void drawFunc() override;
    bool event(const int event, basic::Object* const obj = nullptr) override;

    // set methods
    virtual bool setIsAlt(const bool newIsAlt)          { isAlt = newIsAlt; return true; }

    // get methods
    bool isAltSelected()                                { return isAlt; }

protected:
    bool setSlotIsAlt(const basic::Number* newIsAlt);

private:
    // event method
    bool onEventSetIsAltSpdLines(const basic::Number* const x);

    bool isAlt;     // are we drawing the altitude lines instead?
};

}; // end of demo namespace
}; // end of oe namespace

#endif

