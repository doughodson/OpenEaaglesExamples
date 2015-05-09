//------------------------------------------------------------------------------
// Class: TestDisplay
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestDisplay_H__
#define __Eaagles_Example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Simulation { class Missile; class Player; class Simulation; class Station; }
   namespace BasicGL { class SymbolLoader; }

namespace Example {

//------------------------------------------------------------------------------
// Class: TestDisplay
//
// Factory name: TestDisplay
//
// Events: (all keyboard events)
//   'r' or 'R'   -- Reset simulation
//   'f' or 'F'   -- Toggle simulation freeze
//   'l' or 'L'   -- Launch Missile
//   'p' or 'P'   -- Prelaunch weapon
//   's' or 'S'   -- Target step
//   'i' or 'I'   -- Increase Range
//   'd' or 'D'   -- Decrease Range
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

    bool event(const int event, Basic::Object* const obj = nullptr) override;
    void updateData(const LCreal dt = 0.0) override;

private:
    // Key event handlers
    bool onToggleTimeKey();
    bool onResetKey();
    bool onFreezeKey();
    bool onWpnRelKey();
    bool onPreRelKey();
    bool onIncRngKey();
    bool onDecRngKey();
    bool onStepOwnshipKey();

    LCreal          range;          // SD range

    SendData        headingSD;
    SendData        rangeSD;

    Basic::safe_ptr<Simulation::Station> myStation;

    static const unsigned int MAX_TRACKS = 200;
    Simulation::Player* tracks[MAX_TRACKS];    // players that we're displaying
    int trkIdx[MAX_TRACKS];    // Index of track symbols
};

} // End Example namespace
} // End Eaagles namespace

#endif

