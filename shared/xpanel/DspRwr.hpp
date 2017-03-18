
#ifndef __oe_xpanel_DspRwr_H__
#define __oe_xpanel_DspRwr_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
namespace models { class Rwr; }
namespace xpanel {

//------------------------------------------------------------------------------
// Class: DspRwr
// Description: Simple Radar Warning Receiver (RWR) display.  Displays received
//              R/F signal as a ray, with power as length, in the direction of
//              the angle of arrival.
// Factory name: DspRwr
//------------------------------------------------------------------------------
class DspRwr : public graphics::Graphic
{
    DECLARE_SUBCLASS(DspRwr, graphics::Graphic)

public:
    DspRwr();

    models::Rwr* getRwr()             { return rwr; }
    const models::Rwr* getRwr() const { return rwr; }
    void setRwr(models::Rwr* s)       { rwr = s; }

    virtual void drawFunc() override;

    virtual void updateData(const double dt = 0.0) override;

private:
    models::Rwr* rwr {};     // The test RWR sensor
};

}
}

#endif
