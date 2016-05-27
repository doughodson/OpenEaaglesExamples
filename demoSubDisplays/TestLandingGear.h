
#ifndef __TestLandingGear_H__
#define __TestLandingGear_H__

#include "openeaagles/graphics/Page.h"

//------------------------------------------------------------------------------
// Class: TestLandingGear
//
// Description: Tests our generic landing gear and lights
//------------------------------------------------------------------------------
class TestLandingGear : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestLandingGear, oe::graphics::Page)

public:
   TestLandingGear();

   virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
   virtual void updateData(const double dt = 0.0) override;

private:
    // event functions
    bool onUpdateLandingGearTestLandingGear();

    double gearPosition;       // our landing gear position (0 is down, 1 is up)
    SendData gearPositionSD;
    SendData gearPositionROSD;
    double  gearRate;          // rate which are going (up or down)
};

#endif
