//------------------------------------------------------------------------------
// Class: RdrAlt
//
// Description: radar altitude display and minimums.  It take the min value
// of the radar, and will compare it to our current alt, and determine the color
// and visibility based on that value
// Inputs:
//      UPDATE_VALUE  -> actual radar alt
//      UPDATE_VALUE2 -> minimum radar alt
//------------------------------------------------------------------------------
#ifndef __oe_demo_RdrAlt_H__
#define __oe_demo_RdrAlt_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace demo {

class RdrAlt : public graphics::Graphic
{
    DECLARE_SUBCLASS(RdrAlt,graphics::Graphic)

public:
    RdrAlt();

    // set functions
    virtual bool setRAlt(const double newRA);       // Sets RADAR altitude (ft)
    virtual bool setRAltMin(const double newRM);    // Sets RADAR altitude minimum (ft)

    // get functions
    double getRadarAltFt()  { return rAlt; }
    double getRdrMinAltFt() { return rAltMin; }

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, base::Object* const obj = nullptr) override;

private:
    // event functions
    bool onEventSetRAltRdrAlt(const base::Number* const x);
    bool onEventSetRAltMinRdrAlt(const base::Number* const x);

    double rAlt;        // ft -- our actual radar alt
    SendData rAltSD;

    double rAltMin;     // ft -- our minimum radar altitude setting
    SendData rAltMinSD;
};

}; // end of demo namespace
}; // end of oe namespace

#endif

