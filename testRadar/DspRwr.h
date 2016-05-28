
#ifndef __DspRwr_H__
#define __DspRwr_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
   namespace simulation { class Rwr; }
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

    oe::simulation::Rwr* getRwr()               { return rwr; }
    const oe::simulation::Rwr* getRwr() const   { return rwr; }
    void setRwr(oe::simulation::Rwr* s)         { rwr = s; }

    virtual void drawFunc() override;

    virtual void updateData(const double dt = 0.0) override;

private:
    oe::simulation::Rwr* rwr;     // The test RWR sensor
};

#endif
