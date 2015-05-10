//------------------------------------------------------------------------------
// Class: TestDisplay
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestDisplay_H__
#define __Eaagles_Test_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Simulation { class Missile; class Player; class Simulation; class Station; }
   namespace BasicGL { class SymbolLoader; }

namespace Test {
   class DspRadar;
   class DspRwr;

//------------------------------------------------------------------------------
// Class: TestDisplay
// Description: Test GLUT-display that will manage a simple real-beam, b-scan radar
//              display, plus a Radar receiver display, which shows received
//              signal strength and angle of arrival, and a simple situation
//              display that shows the 'truth' location of the players.
//
// Factory name: TestDisplay
//
// Events: (all keyboard events)
//   'r' or 'R'   -- Reset simulation
//   'f' or 'F'   -- Toggle simulation freeze
//   'l' or 'L'   -- Launch weapon
//   'p' or 'P'   -- Prelaunch weapon
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
    TestDisplay();

    Simulation::Player* getOwnship();
    Simulation::Simulation* getSimulation();
    Simulation::Station* getStation();

    virtual void maintainAirTrackSymbols(BasicGL::SymbolLoader* loader, const LCreal rng);

    void mouseEvent(const int button, const int state, const int x, const int y) override;

    bool event(const int event, Basic::Object* const obj = nullptr) override;
    void updateData(const LCreal dt = 0.0) override;

private:
    // Key event handlers
    bool onResetKey();
    bool onFreezeKey();
    bool onWpnRelKey();
    bool onPreRelKey();
    bool onTgtStepKey();
    bool onRtn2SearchKey();
    bool onAir2AirKey();
    bool onAir2GndKey();
    bool onIncRngKey();
    bool onDecRngKey();
    bool onStepOwnshipKey();

    DspRadar*       rdrDisplay;     // Test RADAR display
    DspRwr*         rwrDisplay;     // Test RWR display

    LCreal          range;          // SD range

    SendData        headingSD;
    SendData        rangeSD;

    Basic::safe_ptr<Simulation::Station> myStation;

    static const unsigned int MAX_TRACKS = 200;
    Simulation::Player* tracks[MAX_TRACKS];    // players that we're displaying
    int              trkIdx[MAX_TRACKS];    // Index of track symbols
};

} // End Test namespace
} // End Eaagles namespace

#endif
