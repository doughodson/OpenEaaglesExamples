//------------------------------------------------------------------------------
// Class: TestGMeterDial
//
// Description: This page will test the G meter, which is a dial showing
// the min and max Gs as well as the current Gs being pulled.
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestGMeterDial_H__
#define __Eaagles_Demo_TestGMeterDial_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

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

} // end of Demo namespace
} // end of Eaagles namespace

#endif

