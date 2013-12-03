//------------------------------------------------------------------------------
// Class:	TestSpeedBrake
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestSpeedBrake
//
// Description:	Example Analog Dial Page 
// This page will supply test data to the speed brake (generic)
//
//------------------------------------------------------------------------------
#ifndef	__TestSpeedBrake_H__7AB5AFEF_DEE1_4e26_8663_251F6EA56A75
#define __TestSpeedBrake_H__7AB5AFEF_DEE1_4e26_8663_251F6EA56A75

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestSpeedBrake : public BasicGL::Page {
   DECLARE_SUBCLASS(TestSpeedBrake,BasicGL::Page)

public:
    TestSpeedBrake();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal sbrakePosition;          // our speed brake position (1 - 100) 
    SendData sbrakePositionSD;
    SendData sbrakePositionROSD;
    LCreal  sbrakeRate;             // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif	/* __TestSpeedBrake_H__7AB5AFEF_DEE1_4e26_8663_251F6EA56A75 */

