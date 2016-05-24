//------------------------------------------------------------------------------
// Class: TestMechanical
//
// Description: Simulates a rockwell collins type EFIS Mechanical ADI graphic
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestMechanical_H__
#define __oe_demo_TestMechanical_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestMechanical : public graphics::Page
{
   DECLARE_SUBCLASS(TestMechanical, graphics::Page)

public:
    TestMechanical();

    virtual void updateData(const double dt = 0.0) override;

private:
    static const double T1;     // heading slew rate (deg/sec)
    static const double T2;     // rate of slew rate (pointer_widths/sec)

    double pitch;           // actual pitch
    SendData pitchSD;
    double  pitchRate;
    double roll;            // actual roll
    SendData rollSD;
    double rollRate;
    double slip;
    SendData slipSD;
    double slipRate;
    double cmdPitch;        // commanded pitch
    SendData cmdPitchSD;
    double cmdRoll;         // commanded roll
    SendData cmdRollSD;
    double cmdPitchRate;
    double cmdRollRate;
    bool inView;            // when our commanded pitch is in view
    double heading;         // heading of our ownship (for rate of turn)
    double headingRate;
    bool rtFail;            // our rate of turn indicator failure flag
    // runway stuff
    bool rwFail;            // runway failure flag
    double locDots;         // localizer dots
    double locDotsRate;
    SendData locDotsSD;     // localizer dots
    double rAlt;            // radio altitude
    double rAltRate;
    SendData rAltSD;
    // glideslope stuff
    bool gsFail;
    double gsDots;          // glideslope dots
    double gsDotsRate;
    SendData gsDotsSD;
    // speed deviation stuff
    bool sdFail;
    double speedDots;       // speed dots
    double speedDotsRate;
    SendData speedDotsSD;
    // gaLight stuff
    int gaMode;
    double gaTimer;
    // mdaLight stuff
    int mdaMode;
    double mdaTimer;
    // cmptr stuff
    bool cmptrFail;         // our computer fail flag (on = true)
    SendData cmptrFailSD;
    // GA Light stuff
    SendData gaModeSD;
    // gryo stuff
    bool gryoFail;          // our gryo fail flag (on = true)
    double gryoFailTimer;
    SendData gryoFailSD;
    SendData gsFailSD;
    SendData gsFailVisSD;
    bool isGSValid;         // is our glideslope value valid?
    bool isRWIndValid;      // is our runway data valid?
    bool isSDValid;         // validity check
    SendData mdaModeSD;
    SendData rtFailSD;
    SendData rollIndSD;     // for our roll indicator (which is a rotator)
    SendData rwFailSD;
    SendData sdFailSD;
    double curRot;          // current rate of turn
    double rotRate;
    SendData curRotSD;
};

}
}

#endif


