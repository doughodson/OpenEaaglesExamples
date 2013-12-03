//------------------------------------------------------------------------------
// Class:	TestNozzle
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestNozzle
//
// Description:	Another example of using an analog dial.  This one is an F-16
// like nozzle gauge
//------------------------------------------------------------------------------
#ifndef	__TestNozzle_H__82BC298D_307C_4e35_876D_4508C4BDE61E
#define __TestNozzle_H__82BC298D_307C_4e35_876D_4508C4BDE61E

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestNozzle : public BasicGL::Page {
   DECLARE_SUBCLASS(TestNozzle,BasicGL::Page)

public:
    TestNozzle();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal nozPos;                  
    SendData nozPosSD;
    SendData nozPosROSD;       // sends our readout data (to a numeric readout)
    LCreal  nozRate;             
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif	/* __TestNozzle_H__82BC298D_307C_4e35_876D_4508C4BDE61E */

