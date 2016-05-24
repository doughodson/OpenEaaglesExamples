//------------------------------------------------------------------------------
// Class: TestButtons
//
// Description: Simply tests our buttons and prints out which one we hit
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestButtons_H__
#define __oe_demo_TestButtons_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestButtons : public graphics::Page
{
   DECLARE_SUBCLASS(TestButtons, graphics::Page)

public:
   TestButtons();

   enum { REGULAR = 0, PUSH_MAINTAINED, PUSH_MOMENTARY, ROTARY, KNOB, SOLENOID };

   virtual void updateData(const double dt = 0.0) override;
   virtual bool event(const int event, base::Object* const obj = nullptr) override;

private:
    bool regularButton();
    bool pushButtonMaintained();
    bool pushButtonMomentary();
    bool rotarySwitch();
    bool knobMoved();
    bool resetSolenoid();
    bool solenoidUp();
    bool solenoidDown();

    int whichButton;
    double value;

    SendData whichButtonSD;
    SendData valueSD;
    SendData latchedSD;
};

}
}

#endif

