//------------------------------------------------------------------------------
// Class:	TestPfd
// Base class:	... -> BasicGL::Page -> PfdPage -> TestPfd
//
// Description:	Tests another pfd page
//------------------------------------------------------------------------------
#ifndef	__TestPfd_H_D7457E8A_6CA1_4912_A148_32823677FB38
#define __TestPfd_H_D7457E8A_6CA1_4912_A148_32823677FB38

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace MainFlightDisplay2 {

class TestPfd : public BasicGL::Page {
   DECLARE_SUBCLASS(TestPfd, BasicGL::Page )

public:
    TestPfd();    
    
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0.0);
    
private:
    // pitch and roll
    LCreal pitch;           // degs
    LCreal pitchRate;       // degs/sec
    LCreal roll;            // degs
    LCreal rollRate;        // degs/sec

    // heading and nav stuff
    LCreal trueHdg;         // degs
    LCreal tHdgRate;        // degs/sec
    LCreal cmdHdg;          // commanded heading (heading bug) (degs)
    LCreal cmdHdgRate;      // degs/sec

    // airspeed
    LCreal airSpd;
    LCreal airSpdRate;

    // altitude
    LCreal alt;
    LCreal altRate;

    // side slip
    LCreal slip;            // degs
    LCreal slipRate;        // degs/sec

    // glideslope (in dots)
    LCreal gSlope;
    LCreal gSlopeRate;

    // Lateral dev
    LCreal latDev;
    LCreal ldRate;

    // commanded speed
    LCreal cmdSpd;

    // commanded alt
    LCreal cmdAlt;

    // vvi
    LCreal vvi;
    LCreal vviRate;

    // flight director stuff (in inches)
    LCreal fDirBank;
    LCreal fDirBankRate;
    LCreal fDirPitch;
    LCreal fDirPitchRate;
    
    // barometric pressure
    LCreal baro;
    LCreal baroRate;
};

} // end of MainFlightDisplay2 namespace
} // end of Eaagles namespace

#endif  /* __TestPfd_H_D7457E8A_6CA1_4912_A148_32823677FB38 */

