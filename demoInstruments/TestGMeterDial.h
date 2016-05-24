//------------------------------------------------------------------------------
// Class: TestGMeterDial
//
// Description: This page will test the G meter, which is a dial showing
// the min and max Gs as well as the current Gs being pulled.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestGMeterDial_H__
#define __oe_demo_TestGMeterDial_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestGMeterDial : public graphics::Page
{
   DECLARE_SUBCLASS(TestGMeterDial, graphics::Page)

public:
    TestGMeterDial();

    virtual void updateData(const double dt = 0) override;

private:
    double currGs;      // current G's
    SendData currGsSD;
    SendData currGsROSD;
    double gRate;
    double timer;       // our timer for resetting the g meter
    double timerRate;
};

}
}

#endif

