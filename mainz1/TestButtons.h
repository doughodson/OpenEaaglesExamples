//------------------------------------------------------------------------------
// Class:	TestButtons
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestButtons
//
// Description:	Simply tests our buttons and prints out which one we hit
//
//------------------------------------------------------------------------------
#ifndef	__TestButtons_H__A5AD128B_E523_4277_A8AB_8C2CBC0B65E1
#define __TestButtons_H__A5AD128B_E523_4277_A8AB_8C2CBC0B65E1

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz1 {

class TestButtons : public BasicGL::Page {
   DECLARE_SUBCLASS(TestButtons,BasicGL::Page)

public:
   TestButtons();
   
   enum { REGULAR = 0, PUSH_MAINTAINED, PUSH_MOMENTARY, ROTARY, KNOB, SOLENOID };
   
   // Basic::Component interface
   virtual void updateData(const LCreal dt = 0);
  
   virtual bool event(const int event, Basic::Object* const obj = 0);
   
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

} // end of Mainz1 namespace
} // end of Eaagles namespace

#endif	/* __TestButtons_H__A5AD128B_E523_4277_A8AB_8C2CBC0B65E1 */

