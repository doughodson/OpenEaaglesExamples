#include "TestButtons.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestButtons,"TestButtons")
EMPTY_SERIALIZER(TestButtons)

BEGIN_EVENT_HANDLER(TestButtons)
    ON_EVENT(500, regularButton);
    ON_EVENT(501, pushButtonMaintained);
    ON_EVENT(502, pushButtonMomentary);
    ON_EVENT(503, rotarySwitch);
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestButtons::TestButtons()
{
    STANDARD_CONSTRUCTOR()
    whichButton = -1;
    whichButtonSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestButtons::copyData(const TestButtons& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    whichButton = org.whichButton;
    whichButtonSD.empty();
}

EMPTY_DELETEDATA(TestButtons)


bool TestButtons::regularButton()
{
    whichButton = REGULAR;
    return true;
}

bool TestButtons::pushButtonMaintained()
{
    whichButton = PUSH_MAINTAINED;
    return true;
}

bool TestButtons::pushButtonMomentary()
{
    whichButton = PUSH_MOMENTARY;
    return true;
}

bool TestButtons::rotarySwitch()
{
    whichButton = ROTARY;
    return true;
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestButtons::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    if (whichButton == -1) send("whichbutton", UPDATE_VALUE, "Press A Button", whichButtonSD);
    else if (whichButton == REGULAR) send("whichbutton", UPDATE_VALUE, "Regular Button", whichButtonSD);
    else if (whichButton == PUSH_MAINTAINED) send("whichbutton", UPDATE_VALUE, "Push Button Maintained", whichButtonSD);
    else if (whichButton == PUSH_MOMENTARY) send("whichbutton", UPDATE_VALUE, "Push Button Momentary", whichButtonSD);
    else send("whichbutton", UPDATE_VALUE, "Rotary Switch", whichButtonSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
