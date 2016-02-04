//------------------------------------------------------------------------------
// Class: TestLandingGear
//
// Description: Tests our generic landing gear and lights
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestLandingGear_H__
#define __oe_demo_TestLandingGear_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestLandingGear : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestLandingGear, BasicGL::Page)

public:
   TestLandingGear();

   bool event(const int event, basic::Object* const obj = nullptr) override;
   void updateData(const LCreal dt = 0.0) override;

private:
    // event functions
    bool onUpdateLandingGearTestLandingGear();

    LCreal gearPosition;       // our landing gear position (0 is down, 1 is up)
    SendData gearPositionSD;
    SendData gearPositionROSD;
    LCreal  gearRate;          // rate which are going (up or down)
};

} // end of demo namespace
} // end of oe namespace

#endif

