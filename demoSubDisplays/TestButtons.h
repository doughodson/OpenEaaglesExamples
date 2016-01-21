//------------------------------------------------------------------------------
// Class: TestButtons
//
// Description: Simply tests our buttons and prints out which one we hit
//------------------------------------------------------------------------------
#ifndef __Eaagles_demo_TestButtons_H__
#define __Eaagles_demo_TestButtons_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace demo {

class TestButtons : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestButtons, BasicGL::Page)

public:
   TestButtons();

   enum { REGULAR = 0, PUSH_MAINTAINED, PUSH_MOMENTARY, ROTARY, KNOB, SOLENOID };

   void updateData(const LCreal dt = 0.0) override;
   bool event(const int event, Basic::Object* const obj = nullptr) override;

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
    LCreal value;

    SendData whichButtonSD;
    SendData valueSD;
    SendData latchedSD;
};

} // end of demo namespace
} // end of Eaagles namespace

#endif

