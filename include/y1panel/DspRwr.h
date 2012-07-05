//------------------------------------------------------------------------------
// Class: DspRwr
//------------------------------------------------------------------------------
#ifndef __DspRwr_H_1EEBEC96_B088_4b58_A323_429F26B1CF7B__
#define __DspRwr_H_1EEBEC96_B088_4b58_A323_429F26B1CF7B__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Simulation { class Rwr; }

namespace Y1 {

//------------------------------------------------------------------------------
// Class: DspRwr
// Description: Simple Radar Warning Receiver (RWR) display.  Displays received
//              R/F signal as a ray, with power as length, in the direction of
//              the angle of arrival.
// Form Name: DspRwr
//------------------------------------------------------------------------------
class DspRwr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(DspRwr,BasicGL::Graphic)

public:
    DspRwr();

    Simulation::Rwr* getRwr()             { return rwr; }
    const Simulation::Rwr* getRwr() const { return rwr; }
    void setRwr(Simulation::Rwr* s)       { rwr = s; }

    // BasicGL::Graphic class functions
    virtual void drawFunc();

    // Basic::Component class functions 
    virtual void updateData(const LCreal dt = 0.0);

private:
    Simulation::Rwr* rwr;     // The test RWR sensor
};

} // End Y1 namespace
} // End Eaagles namespace

#endif
