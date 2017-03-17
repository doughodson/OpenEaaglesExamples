
#ifndef __SpdLines_H__
#define __SpdLines_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
namespace base { class Number; }
}

//------------------------------------------------------------------------------
// Class: SpdLines
//
// Description: Draws the lines for the airspeed graphic
// Inputs:
//      UPDATE_VALUE  -> altitude flag on or off
//------------------------------------------------------------------------------
class SpdLines : public oe::graphics::Graphic
{
    DECLARE_SUBCLASS(SpdLines, oe::graphics::Graphic)

public:
    SpdLines();

    virtual void drawFunc() override;
    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

    // set methods
    virtual bool setIsAlt(const bool newIsAlt)          { isAlt = newIsAlt; return true; }

    // get methods
    bool isAltSelected()                                { return isAlt; }

protected:
    bool setSlotIsAlt(const oe::base::Number* newIsAlt);

private:
    // event method
    bool onEventSetIsAltSpdLines(const oe::base::Number* const x);

    bool isAlt {};     // are we drawing the altitude lines instead?
};

#endif
