//------------------------------------------------------------------------------
// Class: TestSpeedBrake
//
// Description: Example Analog Dial Page
// This page will supply test data to the speed brake (generic)
//
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestSpeedBrake_H__
#define __oe_demo_TestSpeedBrake_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestSpeedBrake : public graphics::Page
{
   DECLARE_SUBCLASS(TestSpeedBrake, graphics::Page)

public:
    TestSpeedBrake();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal sbrakePosition;          // our speed brake position (1 - 100)
    SendData sbrakePositionSD;
    SendData sbrakePositionROSD;
    LCreal  sbrakeRate;             // rate which are going (up or down)
};

} // end of demo namespace
} // end of oe namespace

#endif

