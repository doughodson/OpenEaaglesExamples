
#ifndef __TestDigitalGauge_H__
#define __TestDigitalGauge_H__

#include "openeaagles/graphics/Page.h"

//------------------------------------------------------------------------------
// Class: TestDigitalGauge
//
// Description: Example Digital AOA Gauge Page
// This page will show an analog F16-like aoa gauge beside a digital aoa gauge
//
//------------------------------------------------------------------------------
class TestDigitalGauge : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestDigitalGauge, oe::graphics::Page)

public:
   TestDigitalGauge();

   virtual void updateData(const double dt = 0) override;

private:
    double aoa;
    SendData aoaSD;
    double  aoaRate;        // rate which are going (up or down)
    SendData aoaROSD;       // aoa readout
    SendData aoaASD;        // analog readout
};

#endif
