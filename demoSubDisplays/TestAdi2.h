//------------------------------------------------------------------------------
// Class: TestAdi2
//
// Description: Tests an MFD version of the ADI
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestAdi2_H__
#define __oe_demo_TestAdi2_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestAdi2 : public graphics::Page
{
   DECLARE_SUBCLASS(TestAdi2, graphics::Page)

public:
    TestAdi2();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal pitch;           // our pitch (90 to -90)
    SendData pitchSD;
    LCreal  pitchRate;
    LCreal roll;            // our roll (180 to -180)
    SendData rollSD;
    SendData rollBASD;      // bank angle roll value
    LCreal rollRate;
    LCreal slip;            // our side slip (20 to -20)
    SendData slipSD;
    LCreal slipRate;
    LCreal calAS;           // calibrated airspeed
    LCreal calASRate;
    SendData calASSD;
    LCreal alt;             // altitude
    SendData altSD;
    LCreal altRate;
    LCreal mag;             // magnetic heading
    SendData magSD;
    LCreal magRate;
    LCreal cdmX;            // x (pitch) value of our climb dive marker (inches)
    LCreal cdmY;            // y (slip) value of our climb dive marker (inches)
    SendData cdmXSD;
    SendData cdmYSD;
    SendData cdmRollSD;
    SendData ghostPitchSD;  // ghost horizon pitch
    SendData ghostRollSD;   // ghost horizon roll
};

} // end of demo namespace
} // end of oe namespace

#endif
