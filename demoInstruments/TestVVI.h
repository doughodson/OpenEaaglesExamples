//------------------------------------------------------------------------------
// Class: TestVVI
//
// Description: Test the gauge slider
// This page will supply test data to a generic analog tape gauge
//
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestVVI_H__
#define __Eaagles_Demo_TestVVI_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestVVI : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestVVI,BasicGL::Page)

public:
   TestVVI();
   
   // Basic::Component interface
   virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal gaugePosition;       // our gauge position (inches)
    SendData gaugePositionSD;
    SendData gaugePositionROSD;
    LCreal  gaugeRate;          // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

