
#ifndef __TestDisplay_H__
#define __TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <array>

namespace oe {
namespace models { class Missile; class Player; }
namespace simulation { class Simulation; class Station; }
namespace graphics { class SymbolLoader; }
}

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
class TestDisplay : public oe::glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, oe::glut::GlutDisplay)

public:
    TestDisplay();

    oe::models::Player* getOwnship();
    oe::simulation::Simulation* getSimulation();
    oe::simulation::Station* getStation();

    virtual void maintainAirTrackSymbols(oe::graphics::SymbolLoader* loader, const double rng);

    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
    virtual void updateData(const double dt = 0.0) override;

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

    double range {40.0};          // SD range

    SendData headingSD;
    SendData rangeSD;

    oe::base::safe_ptr<oe::simulation::Station> myStation;

    static const unsigned int MAX_TRACKS = 200;
    std::array<oe::models::Player*, MAX_TRACKS> tracks {};  // players that we're displaying
    std::array<int, MAX_TRACKS> trkIdx {};                  // Index of track symbols
};

#endif
