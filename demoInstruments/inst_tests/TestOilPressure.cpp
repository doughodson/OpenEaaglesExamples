
#include "TestOilPressure.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestOilPressure, "TestOilPressure")
EMPTY_SERIALIZER(TestOilPressure)
EMPTY_DELETEDATA(TestOilPressure)

TestOilPressure::TestOilPressure()
{
    STANDARD_CONSTRUCTOR()
}

void TestOilPressure::copyData(const TestOilPressure& org, const bool)
{
    BaseClass::copyData(org);
    oilPressure = org.oilPressure;
    oilPressureSD.empty();
    oilRate = org.oilRate;
    oilPressureROSD.empty();
}

void TestOilPressure::updateData(const double dt)
{
    BaseClass::updateData(dt);

    oilPressure += (oilRate * dt);
    if (oilPressure > 120) {
        oilPressure = 120;
        oilRate = -oilRate;
    }
    if (oilPressure < 0) {
        oilPressure = 0;
        oilRate = -oilRate;
    }

    // send our data down
    send("oil", UPDATE_INSTRUMENTS, oilPressure, oilPressureSD);
    send("oilRO", UPDATE_VALUE, oilPressure, oilPressureROSD);
}
