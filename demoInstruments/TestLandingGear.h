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

class TestLandingGear : public graphics::Page
{
   DECLARE_SUBCLASS(TestLandingGear, graphics::Page)

public:
   TestLandingGear();

   virtual virtual bool event(const int event, base::Object* const obj = nullptr) override;
   virtual virtual void updateData(const double dt = 0.0) override;

private:
    // event functions
    bool onUpdateLandingGearTestLandingGear();

    double gearPosition;       // our landing gear position (0 is down, 1 is up)
    SendData gearPositionSD;
    SendData gearPositionROSD;
    double  gearRate;          // rate which are going (up or down)
};

} // end of demo namespace
} // end of oe namespace

#endif

