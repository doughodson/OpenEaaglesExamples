//------------------------------------------------------------------------------
// Class: TestDisplay
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestDisplay_H__
#define __Eaagles_Example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Simulation { class Missile; class Player; class Simulation; class Station; }
   namespace BasicGL { class SymbolLoader; }
   namespace xPanel { class DspRadar; class DspRwr; }

namespace Example {

//------------------------------------------------------------------------------
// Class: TestDisplay
// Description: Test GLUT-display that will manage a simple real-beam, b-scan radar
//              display, plus a Radar receiver display, which shows received
//              signal strength and angle of arrival, a simple situation
//              display that shows the 'truth' location of the players, and
//              Primary Flight Display (PFD).
//
// Factory name: TestDisplay
//
// Events: (all keyboard events)
//   'r' or 'R'   -- Reset simulation
//   'f' or 'F'   -- Toggle simulation freeze
//   'l' or 'L'   -- Launch Missile
//   'a' or 'A'   -- A/A mode (TWS)
//   'g' or 'G'   -- A/G mode (GMTI)
//   's' or 'S'   -- Target step
//   'i' or 'I'   -- Increase Range
//   'd' or 'D'   -- Decrease Range
//   '+'          -- Ownship step (to next local air vehicle)
//------------------------------------------------------------------------------
class TestDisplay : public Glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, Glut::GlutDisplay)

public:
    enum { MAX_TRACKS = 60 };

    enum { NCHAR_NAV1_ID = 3, NCHAR_NAV2_ID = 5 };

public:
    TestDisplay();

    Simulation::Player* getOwnship();
    Simulation::Simulation* getSimulation();
    Simulation::Station* getStation();

    void maintainAirTrackSymbols(BasicGL::SymbolLoader* loader, const LCreal rng);

    void mouseEvent(const int button, const int state, const int x, const int y) override;

    bool event(const int event, Basic::Object* const obj = nullptr) override;
    void updateData(const LCreal dt = 0.0) override;

protected:
   bool shutdownNotification() override;

private:
    // Key event handlers
    bool onResetKey();
    bool onFreezeKey();
    bool onWpnRelKey();
    bool onTgtStepKey();
    bool onRtn2SearchKey();
    bool onAir2AirKey();
    bool onAir2GndKey();
    bool onIncRngKey();
    bool onDecRngKey();
    bool onStepOwnshipKey();

    void updatePfd(const LCreal dt);

    xPanel::DspRadar*   rdrDisplay;     // Test RADAR display
    xPanel::DspRwr*     rwrDisplay;     // Test RWR display
    LCreal              range;          // SD range

    SendData        headingSD;
    SendData        rangeSD;

    Basic::safe_ptr<Simulation::Station> myStation;

    Simulation::Player* tracks[MAX_TRACKS];    // players that we're displaying
    int                 trkIdx[MAX_TRACKS];    // Index of track symbols

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

} // End Example namespace
} // End Eaagles namespace

#endif

