//------------------------------------------------------------------------------
// Class:	TestLandingGear
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestLandingGear
//
// Description: Tests our generic landing gear and lights
//
//------------------------------------------------------------------------------
#ifndef	__TestLandingGear_H__2EDE48F3_BC6E_4e03_9F77_EBD1E9FDC638
#define __TestLandingGear_H__2EDE48F3_BC6E_4e03_9F77_EBD1E9FDC638

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz2 {

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

} // end of Mainz2 namespace
} // end of Eaagles namespace

#endif	/* __TestLandingGear_H__2EDE48F3_BC6E_4e03_9F77_EBD1E9FDC638 */

