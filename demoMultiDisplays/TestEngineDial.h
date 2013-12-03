//------------------------------------------------------------------------------
// Class:	TestEngineDial
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestEngineDial
//
// Description:	Example Analog Dial Page 
// This page will supply test data to the engine dial (F22-like)
//
//------------------------------------------------------------------------------
#ifndef	__TestEngineDial_H__7C9A015F3_724D_4ee3_AD58_0C918B7BECD7
#define __TestEngineDial_H__7C9A015F3_724D_4ee3_AD58_0C918B7BECD7

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestEngineDial : public BasicGL::Page {
   DECLARE_SUBCLASS(TestEngineDial,BasicGL::Page)

public:
    TestEngineDial();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal engineRotation;          // our engine rpm position (1 - 100) 
    SendData engineRotationSD;
    SendData engineReadoutSD;       // sends our readout data (to a numeric readout)
    LCreal  engineRate;             // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif	/* __TestEngineDial_H__7C9A015F3_724D_4ee3_AD58_0C918B7BECD7 */

