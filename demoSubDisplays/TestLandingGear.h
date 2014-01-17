//------------------------------------------------------------------------------
// Class: TestLandingGear
//
// Description: Tests our generic landing gear and lights
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestLandingGear_H__
#define __Eaagles_Demo_TestLandingGear_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestLandingGear : public BasicGL::Page {
   DECLARE_SUBCLASS(TestLandingGear,BasicGL::Page)

public:
   TestLandingGear();
   
   // Basic::Component interface
   virtual bool event(const int event, Basic::Object* const obj = 0);
   virtual void updateData(const LCreal dt = 0);
   
private:
    // event functions
    bool onUpdateLandingGearTestLandingGear();
    
    LCreal gearPosition;       // our landing gear position (0 is down, 1 is up)
    SendData gearPositionSD;
    SendData gearPositionROSD;
    LCreal  gearRate;          // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

