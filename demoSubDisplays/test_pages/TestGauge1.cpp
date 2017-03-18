
#include "TestGauge1.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestGauge1, "TestGauge1")
EMPTY_SERIALIZER(TestGauge1)
EMPTY_DELETEDATA(TestGauge1)

TestGauge1::TestGauge1()
{
    STANDARD_CONSTRUCTOR()
}

void TestGauge1::copyData(const TestGauge1& org, const bool)
{
    BaseClass::copyData(org);
    gaugePosition = org.gaugePosition;
    gaugePositionSD.empty();
    gaugeRate = org.gaugeRate;
    gaugePositionROSD.empty();
    tapePos = org.tapePos;
    tapeRate = org.tapeRate;
    tapePosSD.empty();
    tapePosROSD.empty();
}

void TestGauge1::updateData(const double dt)
{
    BaseClass::updateData(dt);

    gaugePosition += (gaugeRate * dt);
    tapePos += (tapeRate * dt);
    if (tapePos > 500) {
        tapePos = 500;
        tapeRate = -tapeRate;
    }
    if (tapePos < 0) {
        tapePos = 0;
        tapeRate = -tapeRate;
    }

    if (gaugePosition > 100) {
        gaugePosition = 100;
        gaugeRate = -gaugeRate;
    }
    if (gaugePosition < 0) {
        gaugePosition = 0;
        gaugeRate = -gaugeRate;
    }

    // here is the gauge display
    send("gauge", UPDATE_INSTRUMENTS, gaugePosition, gaugePositionSD);
    // here is the readout
    send("gr", UPDATE_VALUE, gaugePosition, gaugePositionROSD);
    // here is our tape
    send("tape", UPDATE_INSTRUMENTS, tapePos, tapePosSD);
    send("tapero", UPDATE_VALUE, tapePos, tapePosROSD);
}
