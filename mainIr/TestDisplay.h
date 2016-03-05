//------------------------------------------------------------------------------
// Class: TestDisplay
//------------------------------------------------------------------------------
#ifndef __oe_example_TestDisplay_H__
#define __oe_example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
   namespace simulation { class Missile; class Player; class Simulation; class Station; }
   namespace graphics { class SymbolLoader; }

namespace example {

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
class TestDisplay : public glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, glut::GlutDisplay)

public:
    TestDisplay();

    simulation::Player* getOwnship();
    simulation::Simulation* getSimulation();
    simulation::Station* getStation();

    virtual void maintainAirTrackSymbols(graphics::SymbolLoader* loader, const LCreal rng);

    bool event(const int event, base::Object* const obj = nullptr) override;
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

    base::safe_ptr<simulation::Station> myStation;

    static const unsigned int MAX_TRACKS = 200;
    simulation::Player* tracks[MAX_TRACKS];    // players that we're displaying
    int trkIdx[MAX_TRACKS];    // Index of track symbols
};

} // End example namespace
} // End oe namespace

#endif

