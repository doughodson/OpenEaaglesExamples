
#include "TestButtons.hpp"
#include "openeaagles/instruments/buttons/Knob.hpp"
#include "openeaagles/base/Pair.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestButtons, "TestButtons")
EMPTY_SERIALIZER(TestButtons)
EMPTY_DELETEDATA(TestButtons)

BEGIN_EVENT_HANDLER(TestButtons)
    ON_EVENT(500, regularButton);
    ON_EVENT(501, pushButtonMaintained);
    ON_EVENT(502, pushButtonMomentary);
    ON_EVENT(503, rotarySwitch);
    ON_EVENT(504, knobMoved);
    ON_EVENT(505, resetSolenoid);
    ON_EVENT(506, solenoidUp);
    ON_EVENT(507, solenoidDown);
END_EVENT_HANDLER()

TestButtons::TestButtons()
{
    STANDARD_CONSTRUCTOR()
}

void TestButtons::copyData(const TestButtons& org, const bool)
{
    BaseClass::copyData(org);
    whichButton = org.whichButton;
    whichButtonSD.empty();
    value = org.value;
    valueSD.empty();
}

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

bool TestButtons::knobMoved()
{
    whichButton = KNOB;
    // get our knob real quick and find our value
    const auto pair = static_cast<base::Pair*>(findByName("knob"));
    if (pair != nullptr) {
        const auto k = dynamic_cast<instruments::Knob*>(pair->object());
        if (k != nullptr) {
            value = k->getValue();
        }
    }
    return true;
}

bool TestButtons::resetSolenoid()
{
    whichButton = SOLENOID;
    //std::cout << "RESET SOLENOID" << std::endl;
    return true;
}

bool TestButtons::solenoidUp()
{
    whichButton = SOLENOID;
    //std::cout << "SOLENOID UP" << std::endl;
    send("solenoid", SELECT, true, latchedSD);
    return true;
}

bool TestButtons::solenoidDown()
{
    whichButton = SOLENOID;
    //std::cout << "SOLENOID DOWN" << std::endl;
    send("solenoid", SELECT, false, latchedSD);
    return true;
}

void TestButtons::updateData(const double dt)
{
    BaseClass::updateData(dt);

    if (whichButton == -1) send("whichbutton", UPDATE_VALUE, "Press A Button", whichButtonSD);
    else if (whichButton == REGULAR) send("whichbutton", UPDATE_VALUE, "Regular Button", whichButtonSD);
    else if (whichButton == PUSH_MAINTAINED) send("whichbutton", UPDATE_VALUE, "Push Button Maintained", whichButtonSD);
    else if (whichButton == PUSH_MOMENTARY) send("whichbutton", UPDATE_VALUE, "Push Button Momentary", whichButtonSD);
    else if (whichButton == KNOB) send("whichbutton", UPDATE_VALUE, "Knob", whichButtonSD);
    else if (whichButton == SOLENOID) send("whichbutton", UPDATE_VALUE, "Solenoid", whichButtonSD);
    else send("whichbutton", UPDATE_VALUE, "Rotary Switch", whichButtonSD);

    // send our value out
    send("value", UPDATE_VALUE, value, valueSD);
}
