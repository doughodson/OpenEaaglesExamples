//------------------------------------------------------------------------------
// Class: TestGauge1
//
// Description: Example Analog Gauge Page
// This page will supply test data to a generic analog gauge
//
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestGauge1_H__
#define __oe_demo_TestGauge1_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestGauge1 : public graphics::Page
{
   DECLARE_SUBCLASS(TestGauge1, graphics::Page)

public:
    TestGauge1();

    void updateData(const double dt = 0) override;

private:
    double gaugePosition;       // our gauge position (inches)
    SendData gaugePositionSD;
    SendData gaugePositionROSD;
    double  gaugeRate;          // rate which are going (up or down)
    double tapePos;             // tape position
    double tapeRate;
    SendData tapePosSD;
    SendData tapePosROSD;
};

} // end of demo namespace
} // end of oe namespace

#endif

