//------------------------------------------------------------------------------
// Class: TestPfd
//
// Description: Basic Pfd test page, stimulates the Pfd
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestPfd_H__
#define __Eaagles_Demo_TestPfd_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestPfd : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestPfd,BasicGL::Page)

public:
    TestPfd();

    void updateData(const LCreal dt = 0.0) override;

private:
    // pitch and roll
    LCreal pitch;           // degs
    LCreal pitchRate;       // degs/sec
    LCreal roll;            // degs
    LCreal rollRate;        // degs/sec

    // heading and nav stuff
    LCreal trueHdg;         // degs
    LCreal tHdgRate;        // degs/sec

    LCreal cmdCrs;          // degs -- commanded course
    LCreal cmdCrsRate;      // degs/sec

    LCreal cmdHdg;          // degs -- commanded heading (heading bug)
    LCreal cmdHdgRate;      // degs/sec

    // cdi
    LCreal cdiDots;         // dots
    LCreal cdiRate;         // dots/sec

    // to from
    LCreal toFrom;

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

    // master caution
    bool mstrCtn;

    // vvi
    LCreal vvi;
    LCreal vviRate;
    LCreal maxVvi;      // max vvi value
    LCreal minVvi;      // min vvi value

    // aoa
    LCreal aoa;
    LCreal aoaRate;

    // ground speed
    LCreal gSpd;
    LCreal gSpdRate;

    // flight director stuff (in inches)
    LCreal fDirBank;
    LCreal fDirBankRate;
    LCreal fDirPitch;
    LCreal fDirPitchRate;

    // barometric pressure
    LCreal baro;
    LCreal baroRate;

    // radar altitude
    LCreal rAlt;
    LCreal rAltRate;
    LCreal rAltMin;

    // navaid bearings
    LCreal nav1Brg;          // degs
    LCreal nav1BrgRate;      // degs/sec
    LCreal nav2Brg;          // degs
    LCreal nav2BrgRate;      // degs/sec

    // Flight path marker
    LCreal fpmX;
    LCreal fpmXRate;
    LCreal fpmY;
    LCreal fpmYRate;

    // Send datas
    SendData sixtyVisSD;    // sixty degree bank marker visibility
    SendData ninetyVisSD;   // ninety  "        "       "       "
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

