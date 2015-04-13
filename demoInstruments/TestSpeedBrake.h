//------------------------------------------------------------------------------
// Class: TestSpeedBrake
//
// Description: Example Analog Dial Page
// This page will supply test data to the speed brake (generic)
//
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestSpeedBrake_H__
#define __Eaagles_Demo_TestSpeedBrake_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestSpeedBrake : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestSpeedBrake, BasicGL::Page)

public:
    TestSpeedBrake();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal sbrakePosition;          // our speed brake position (1 - 100)
    SendData sbrakePositionSD;
    SendData sbrakePositionROSD;
    LCreal  sbrakeRate;             // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

