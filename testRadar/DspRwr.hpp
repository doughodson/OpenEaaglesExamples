
#ifndef __DspRwr_H__
#define __DspRwr_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
namespace models { class Rwr; }
}

//------------------------------------------------------------------------------
// Class: DspRwr
// Description: Simple Radar Warning Receiver (RWR) display.  Displays received
//              R/F signal as a ray, with power as length, in the direction of
//              the angle of arrival.
// Factory name: DspRwr
//------------------------------------------------------------------------------
class DspRwr : public oe::graphics::Graphic
{
    DECLARE_SUBCLASS(DspRwr, oe::graphics::Graphic)

public:
    DspRwr();

    oe::models::Rwr* getRwr()               { return rwr; }
    const oe::models::Rwr* getRwr() const   { return rwr; }
    void setRwr(oe::models::Rwr* s)         { rwr = s; }

    virtual void drawFunc() override;

    virtual void updateData(const double dt = 0.0) override;

private:
    oe::models::Rwr* rwr {};     // The test RWR sensor
};

#endif
