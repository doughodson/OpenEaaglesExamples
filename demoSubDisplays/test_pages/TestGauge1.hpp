
#ifndef __TestGauge1_H__
#define __TestGauge1_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestGauge1
//
// Description: Example Analog Gauge Page
// This page will supply test data to a generic analog gauge
//
//------------------------------------------------------------------------------
class TestGauge1 : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestGauge1, oe::graphics::Page)

public:
    TestGauge1();

    virtual void updateData(const double dt = 0) override;

private:
    double gaugePosition {};       // our gauge position (inches)
    double  gaugeRate {10.0};      // rate which are going (up or down)
    SendData gaugePositionSD;
    SendData gaugePositionROSD;

    double tapePos {};             // tape position
    double tapeRate {10.0};
    SendData tapePosSD;
    SendData tapePosROSD;
};

#endif
