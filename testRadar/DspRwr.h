//------------------------------------------------------------------------------
// Class: DspRwr
//------------------------------------------------------------------------------
#ifndef __oe_test_DspRwr_H__
#define __oe_test_DspRwr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
   namespace simulation { class Rwr; }

namespace test {

//------------------------------------------------------------------------------
// Class: DspRwr
// Description: Simple Radar Warning Receiver (RWR) display.  Displays received
//              R/F signal as a ray, with power as length, in the direction of
//              the angle of arrival.
// Factory name: DspRwr
//------------------------------------------------------------------------------
class DspRwr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(DspRwr, BasicGL::Graphic)

public:
    DspRwr();

    simulation::Rwr* getRwr()             { return rwr; }
    const simulation::Rwr* getRwr() const { return rwr; }
    void setRwr(simulation::Rwr* s)       { rwr = s; }

    void drawFunc() override;

    void updateData(const LCreal dt = 0.0) override;

private:
    simulation::Rwr* rwr;     // The test RWR sensor
};

} // End test namespace
} // End oe namespace

#endif
