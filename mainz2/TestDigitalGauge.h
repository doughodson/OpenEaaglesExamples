//------------------------------------------------------------------------------
// Class:	TestDigitalGauge
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestDigitalGauge
//
// Description:	Example Digital AOA Gauge Page 
// This page will show an analog F16-like aoa gauge beside a digital aoa gauge
// 
//------------------------------------------------------------------------------
#ifndef	__TestDigitalGauge_H__014C3D58_1C51_4c86_A842_9A8122F29C55
#define __TestDigitalGauge_H__014C3D58_1C51_4c86_A842_9A8122F29C55

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz2 {

class TestDigitalGauge : public BasicGL::Page {
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

#endif	/* __TestDigitalGauge_H__014C3D58_1C51_4c86_A842_9A8122F29C55 */

