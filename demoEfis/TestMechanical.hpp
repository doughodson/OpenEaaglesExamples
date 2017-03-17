
#ifndef __TestMechanical_H__
#define __TestMechanical_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestMechanical
//
// Description: Simulates a rockwell collins type EFIS Mechanical ADI graphic
//------------------------------------------------------------------------------
class TestMechanical : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestMechanical, oe::graphics::Page)

public:
    TestMechanical();

    virtual void updateData(const double dt = 0.0) override;

private:
    static const double T1;     // heading slew rate (deg/sec)
    static const double T2;     // rate of slew rate (pointer_widths/sec)

    double pitch {};            // actual pitch
    SendData pitchSD;
    double pitchRate {20.0};
    double roll {};             // actual roll
    SendData rollSD;
    double rollRate {10.0};
    double slip {};
    SendData slipSD;
    double slipRate {5.0};
    double cmdPitch {};         // commanded pitch
    SendData cmdPitchSD;
    double cmdRoll {};          // commanded roll
    SendData cmdRollSD;
    double cmdPitchRate {30.0};
    double cmdRollRate {5.0};
    bool inView {true};         // when our commanded pitch is in view
    double heading {};          // heading of our ownship (for rate of turn)
    double headingRate {3.0};
    bool rtFail {};             // our rate of turn indicator failure flag
    // runway stuff
    bool rwFail {};             // runway failure flag
    double locDots {};          // localizer dots
    double locDotsRate {0.2};
    SendData locDotsSD;         // localizer dots
    double rAlt {};             // radio altitude
    double rAltRate {10.0};
    SendData rAltSD;
    // glideslope stuff
    double gsDots {};           // glideslope dots
    double gsDotsRate {0.2};
    SendData gsDotsSD;
    bool gsFail {};
    // speed deviation stuff
    bool sdFail {};
    double speedDots {};        // speed dots
    double speedDotsRate {0.4};
    SendData speedDotsSD;
    // gaLight stuff
    int gaMode {true};
    double gaTimer {};
    // mdaLight stuff
    int mdaMode {true};
    double mdaTimer {};
    // cmptr stuff
    bool cmptrFail {};          // our computer fail flag (on = true)
    SendData cmptrFailSD;
    // GA Light stuff
    SendData gaModeSD;
    // gryo stuff
    bool gryoFail {};           // our gryo fail flag (on = true)
    double gryoFailTimer {};
    SendData gryoFailSD;
    SendData gsFailSD;
    SendData gsFailVisSD;
    bool isGSValid {};          // is our glideslope value valid?
    bool isRWIndValid {};       // is our runway data valid?
    bool isSDValid {};          // validity check
    SendData mdaModeSD;
    SendData rtFailSD;
    SendData rollIndSD;         // for our roll indicator (which is a rotator)
    SendData rwFailSD;
    SendData sdFailSD;
    double curRot {};           // current rate of turn
    double rotRate {0.5};
    SendData curRotSD;
};

#endif
