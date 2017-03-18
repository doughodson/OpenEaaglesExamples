
#include "TestAlt.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAlt, "TestAlt")
EMPTY_SERIALIZER(TestAlt)
EMPTY_DELETEDATA(TestAlt)

TestAlt::TestAlt()
{
    STANDARD_CONSTRUCTOR()
}

void TestAlt::copyData(const TestAlt& org, const bool)
{
    BaseClass::copyData(org);
    alt = org.alt;
    altSD.empty();
    altRate = org.altRate;
    altROSD.empty();
}

void TestAlt::updateData(const double dt)
{
    BaseClass::updateData(dt);

    alt += (altRate * dt);
    if (alt > 65000) {
        alt = 65000;
        altRate = -altRate;
    }
    if (alt < 0) {
        alt = 0;
        altRate = -altRate;
    }

    // send the data down
    send("alt", UPDATE_INSTRUMENTS, alt, altSD);
    send("altRO", UPDATE_VALUE, alt, altROSD);
}
