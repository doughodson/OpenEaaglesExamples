//------------------------------------------------------------------------------
// Class: TestPfd
//
// Description: Tests another pfd page
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestPfd_H__
#define __oe_demo_TestPfd_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestPfd : public graphics::Page
{
   DECLARE_SUBCLASS(TestPfd, graphics::Page )

public:
    TestPfd();

    void updateData(const double dt = 0.0) override;

private:
    // pitch and roll
    double pitch;           // degs
    double pitchRate;       // degs/sec
    double roll;            // degs
    double rollRate;        // degs/sec

    // heading and nav stuff
    double trueHdg;         // degs
    double tHdgRate;        // degs/sec
    double cmdHdg;          // commanded heading (heading bug) (degs)
    double cmdHdgRate;      // degs/sec

    // airspeed
    double airSpd;
    double airSpdRate;

    // altitude
    double alt;
    double altRate;

    // side slip
    double slip;            // degs
    double slipRate;        // degs/sec

    // glide slope (in dots)
    double gSlope;
    double gSlopeRate;

    // Lateral dev
    double latDev;
    double ldRate;

    // commanded speed
    double cmdSpd;

    // commanded alt
    double cmdAlt;

    // vvi
    double vvi;
    double vviRate;

    // flight director stuff (in inches)
    double fDirBank;
    double fDirBankRate;
    double fDirPitch;
    double fDirPitchRate;

    // barometric pressure
    double baro;
    double baroRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

