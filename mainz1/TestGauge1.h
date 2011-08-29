//------------------------------------------------------------------------------
// Class:	TestGauge1
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestGauge1
//
// Description:	Example Analog Gauge Page 
// This page will supply test data to a generic analog gauge
//
//------------------------------------------------------------------------------
#ifndef	__TestGauge1_H__664174BC_7E33_4e43_BC2D_42D0324178F5
#define __TestGauge1_H__664174BC_7E33_4e43_BC2D_42D0324178F5

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz1 {

class TestGauge1 : public BasicGL::Page {
   DECLARE_SUBCLASS(TestGauge1,BasicGL::Page)

public:
    TestGauge1();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
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

} // end of Mainz1 namespace
} // end of Eaagles namespace

#endif	/* __TestGauge1_H__664174BC_7E33_4e43_BC2D_42D0324178F5 */

