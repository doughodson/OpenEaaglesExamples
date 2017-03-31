
#ifndef __TestDisplay_H__
#define __TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

#include <array>

namespace oe {
namespace models { class Missile; class Player; }
namespace simulation { class Simulation; class Station; }
namespace graphics { class SymbolLoader; }
namespace xpanel { class DspRadar; class DspRwr; }
}

//------------------------------------------------------------------------------
// Class: TestDisplay
//
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
class TestDisplay : public oe::glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, oe::glut::GlutDisplay)

public:
    static const int MAX_TRACKS = 60;
    static const int NCHAR_NAV1_ID = 3;
    static const int NCHAR_NAV2_ID = 5;

public:
    TestDisplay();

    oe::models::Player* getOwnship();
    oe::simulation::Simulation* getSimulation();
    oe::simulation::Station* getStation();

    void maintainAirTrackSymbols(oe::graphics::SymbolLoader* loader, const double rng);

    virtual void mouseEvent(const int button, const int state, const int x, const int y) override;

    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
    virtual void updateData(const double dt = 0.0) override;

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

    void updatePfd(const double dt);

    // ---
    // RADAR, RWR and SA stuff
    // ---
    oe::xpanel::DspRadar* rdrDisplay {};     // Test RADAR display
    oe::xpanel::DspRwr*   rwrDisplay {};     // Test RWR display
    double range {40.0};                     // SD range

    SendData headingSD;
    SendData rangeSD;

    oe::base::safe_ptr<oe::simulation::Station> myStation;

    std::array<oe::models::Player*, MAX_TRACKS> tracks {};    // players that we're displaying
    std::array<int, MAX_TRACKS> trkIdx {};                    // Index of track symbols

    // ---
    // PFD stuff
    // ---

    // pitch and roll
    double pitch {};           // degs
    double pitchRate {10.0};   // degs/sec
    double roll {};            // degs
    double rollRate {-9.0};    // degs/sec

    // heading and nav stuff
    double trueHdg {};         // degs
    double tHdgRate {11};      // degs/sec
    double cmdHdg {};          // commanded heading (heading bug) (degs)
    double cmdHdgRate {3};     // degs/sec

    // airspeed
    double airSpd {};
    double airSpdRate {5};

    // altitude
    double alt {10000.0};
    double altRate {80.0};

    // side slip
    double slip {};            // degs
    double slipRate {10.0};    // degs/sec

    // glideslope (in dots)
    double gSlope {};
    double gSlopeRate {0.2};

    // Lateral dev
    double latDev {};
    double ldRate {0.3};

    // commanded speed
    double cmdSpd {200.0};

    // commanded alt
    double cmdAlt {6000.0};

    // vvi
    double vvi {};
    double vviRate {500.0};

    // flight director stuff (in inches)
    double fDirBank {};
    double fDirBankRate {4.0};
    double fDirPitch {};
    double fDirPitchRate {7.0};

    // barometric pressure
    double baro {};
    double baroRate {10.0};
};

#endif
