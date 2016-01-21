//------------------------------------------------------------------------------
// Class: TestGMeterDial
//
// Description: This page will test the G meter, which is a dial showing
// the min and max Gs as well as the current Gs being pulled.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestGMeterDial_H__
#define __oe_demo_TestGMeterDial_H__

#include "openeaagles/basicGL/Page.h"

namespace oe {
namespace demo {

class TestGMeterDial : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestGMeterDial, BasicGL::Page)

public:
    TestGMeterDial();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal currGs;      // current G's
    SendData currGsSD;
    SendData currGsROSD;
    LCreal gRate;
    LCreal timer;       // our timer for resetting the g meter
    LCreal timerRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

