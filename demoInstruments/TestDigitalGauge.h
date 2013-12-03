//------------------------------------------------------------------------------
// Class: TestDigitalGauge
//
// Description: Example Digital AOA Gauge Page 
// This page will show an analog F16-like aoa gauge beside a digital aoa gauge
// 
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestDigitalGauge_H__
#define __Eaagles_Demo_TestDigitalGauge_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestDigitalGauge : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestDigitalGauge,BasicGL::Page)

public:
   TestDigitalGauge();
   
   // Basic::Component interface
   virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal aoa;
    SendData aoaSD;
    LCreal  aoaRate;        // rate which are going (up or down)
    SendData aoaROSD;       // aoa readout
    SendData aoaASD;        // analog readout 
};

} // end of Instruments namespace
} // end of Eaagles namespace

#endif

