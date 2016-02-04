//------------------------------------------------------------------------------
// Class: TestEngineDial
//
// Description: Example Analog Dial Page
// This page will supply test data to the engine dial
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestEngineDial_H__
#define __oe_demo_TestEngineDial_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestEngineDial : public graphics::Page
{
   DECLARE_SUBCLASS(TestEngineDial, graphics::Page)

public:
    TestEngineDial();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal engineRotation;          // our engine rpm position (1 - 100)
    SendData engineRotationSD;
    SendData engineReadoutSD;       // sends our readout data (to a numeric readout)
    LCreal  engineRate;             // rate which are going (up or down)
};

} // end of demo namespace
} // end of oe namespace

#endif

