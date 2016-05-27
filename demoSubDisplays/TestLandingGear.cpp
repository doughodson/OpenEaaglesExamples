
#include "TestLandingGear.h"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestLandingGear, "TestLandingGear")
EMPTY_SERIALIZER(TestLandingGear)
EMPTY_DELETEDATA(TestLandingGear)

BEGIN_EVENT_HANDLER(TestLandingGear)
    ON_EVENT('g', onUpdateLandingGearTestLandingGear)
END_EVENT_HANDLER()

TestLandingGear::TestLandingGear()
{
    STANDARD_CONSTRUCTOR()
    gearPosition = 0.0;
    gearPositionSD.empty();
    gearRate = 0.3;
    gearPositionROSD.empty();
}

void TestLandingGear::copyData(const TestLandingGear& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    gearPosition = org.gearPosition;
    gearPositionSD.empty();
    gearRate = org.gearRate;
    gearPositionROSD.empty();

}

bool TestLandingGear::onUpdateLandingGearTestLandingGear()
{
    // switch our gear rate
    gearRate = -gearRate;
    return true;
}

void TestLandingGear::updateData(const double dt)
{
    BaseClass::updateData(dt);

    gearPosition += (gearRate * dt);

    if (gearPosition > 1) gearPosition = 1;
    if (gearPosition < 0) gearPosition = 0;

    // here is the gauge display
    send("gear", UPDATE_INSTRUMENTS, gearPosition, gearPositionSD);
    // here is the readout
    send("gearRO", UPDATE_VALUE, gearPosition, gearPositionROSD);
}
