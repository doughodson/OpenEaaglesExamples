//------------------------------------------------------------------------------
// Class:	TestGMeterDial
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestGMeterDial
//
// Description: This page will test the G meter, which is a dial showing 
// the min and max Gs as well as the current Gs being pulled.
//------------------------------------------------------------------------------
#ifndef	__TestGMeterDial_H__2FCA268E_B148_4d6d_B7DE_950FC8EDBBF3
#define __TestGMeterDial_H__2FCA268E_B148_4d6d_B7DE_950FC8EDBBF3

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz1 {

class TestGMeterDial : public BasicGL::Page {
   DECLARE_SUBCLASS(TestGMeterDial,BasicGL::Page)

public:
    TestGMeterDial();
    
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal currGs;      // current G's
    SendData currGsSD;
    SendData currGsROSD;
    LCreal gRate;
    LCreal timer;       // our timer for resetting the g meter
    LCreal timerRate;   
};

} // end of Mainz1 namespace
} // end of Eaagles namespace

#endif	/* __TestGMeterDial_H__2FCA268E_B148_4d6d_B7DE_950FC8EDBBF3 */

