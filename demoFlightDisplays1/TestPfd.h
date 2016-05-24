//------------------------------------------------------------------------------
// Class: TestPfd
//
// Description: Basic Pfd test page, stimulates the Pfd
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestPfd_H__
#define __oe_demo_TestPfd_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestPfd : public graphics::Page
{
   DECLARE_SUBCLASS(TestPfd,graphics::Page)

public:
    TestPfd();

    virtual void updateData(const double dt = 0.0) override;

private:
    // pitch and roll
    double pitch;           // degs
    double pitchRate;       // degs/sec
    double roll;            // degs
    double rollRate;        // degs/sec

    // heading and nav stuff
    double trueHdg;         // degs
    double tHdgRate;        // degs/sec

    double cmdCrs;          // degs -- commanded course
    double cmdCrsRate;      // degs/sec

    double cmdHdg;          // degs -- commanded heading (heading bug)
    double cmdHdgRate;      // degs/sec

    // cdi
    double cdiDots;         // dots
    double cdiRate;         // dots/sec

    // to from
    double toFrom;

    // airspeed
    double airSpd;
    double airSpdRate;

    // altitude
    double alt;
    double altRate;

    // side slip
    double slip;            // degs
    double slipRate;        // degs/sec

    // glideslope (in dots)
    double gSlope;
    double gSlopeRate;

    // Lateral dev
    double latDev;
    double ldRate;

    // commanded speed
    double cmdSpd;

    // commanded alt
    double cmdAlt;

    // master caution
    bool mstrCtn;

    // vvi
    double vvi;
    double vviRate;
    double maxVvi;      // max vvi value
    double minVvi;      // min vvi value

    // aoa
    double aoa;
    double aoaRate;

    // ground speed
    double gSpd;
    double gSpdRate;

    // flight director stuff (in inches)
    double fDirBank;
    double fDirBankRate;
    double fDirPitch;
    double fDirPitchRate;

    // barometric pressure
    double baro;
    double baroRate;

    // radar altitude
    double rAlt;
    double rAltRate;
    double rAltMin;

    // navaid bearings
    double nav1Brg;          // degs
    double nav1BrgRate;      // degs/sec
    double nav2Brg;          // degs
    double nav2BrgRate;      // degs/sec

    // Flight path marker
    double fpmX;
    double fpmXRate;
    double fpmY;
    double fpmYRate;

    // Send datas
    SendData sixtyVisSD;    // sixty degree bank marker visibility
    SendData ninetyVisSD;   // ninety  "        "       "       "
};

} // end of demo namespace
} // end of oe namespace

#endif

