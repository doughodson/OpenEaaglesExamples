//------------------------------------------------------------------------------
// Class: DspRwr
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_DspRwr_H__
#define __Eaagles_Test_DspRwr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Simulation { class Rwr; }

namespace Test {

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

    Simulation::Rwr* getRwr()             { return rwr; }
    const Simulation::Rwr* getRwr() const { return rwr; }
    void setRwr(Simulation::Rwr* s)       { rwr = s; }

    void drawFunc() override;

    void updateData(const LCreal dt = 0.0) override;

private:
    Simulation::Rwr* rwr;     // The test RWR sensor
};

} // End Test namespace
} // End Eaagles namespace

#endif
