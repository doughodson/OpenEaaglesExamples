
#include "TestVVI.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestVVI, "TestVVI")
EMPTY_SERIALIZER(TestVVI)
EMPTY_DELETEDATA(TestVVI)

TestVVI::TestVVI()
{
    STANDARD_CONSTRUCTOR()
}

void TestVVI::copyData(const TestVVI& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    gaugePosition = org.gaugePosition;
    gaugePositionSD.empty();
    gaugeRate = org.gaugeRate;
    gaugePositionROSD.empty();

}

void TestVVI::updateData(const double dt)
{
    BaseClass::updateData(dt);

    gaugePosition += (gaugeRate * dt);
    if (gaugePosition > 6000) {
        gaugePosition = 6000;
        gaugeRate = -gaugeRate;
    }
    if (gaugePosition < -6000) {
        gaugePosition = -6000;
        gaugeRate = -gaugeRate;
    }

    // here is the gauge display
    send("vvi", UPDATE_INSTRUMENTS, gaugePosition, gaugePositionSD);
    // here is the readout
    send("vviro", UPDATE_VALUE, gaugePosition, gaugePositionROSD);
}
