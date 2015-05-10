//------------------------------------------------------------------------------
// Class: TestGauge1
//
// Description: Example Analog Gauge Page
// This page will supply test data to a generic analog gauge
//
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestGauge1_H__
#define __Eaagles_Demo_TestGauge1_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestGauge1 : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestGauge1, BasicGL::Page)

public:
    TestGauge1();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal gaugePosition;       // our gauge position (inches)
    SendData gaugePositionSD;
    SendData gaugePositionROSD;
    LCreal  gaugeRate;          // rate which are going (up or down)
    LCreal tapePos;             // tape position
    LCreal tapeRate;
    SendData tapePosSD;
    SendData tapePosROSD;
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

