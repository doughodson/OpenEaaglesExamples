
#include "TestNozzle.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestNozzle, "TestNozzle")
EMPTY_SERIALIZER(TestNozzle)
EMPTY_DELETEDATA(TestNozzle)

TestNozzle::TestNozzle()
{
    STANDARD_CONSTRUCTOR()
}

void TestNozzle::copyData(const TestNozzle& org, const bool)
{
    BaseClass::copyData(org);
    nozPos = org.nozPos;
    nozPosSD.empty();
    nozRate = org.nozRate;
    nozPosROSD.empty();
}

void TestNozzle::updateData(const double dt)
{
    BaseClass::updateData(dt);

    nozPos += (nozRate * dt);
    if (nozPos > 100) {
        nozPos = 100;
        nozRate = -nozRate;
    }
    if (nozPos < 0) {
        nozPos = 0;
        nozRate = -nozRate;
    }

    // send the data down
    send("noz", UPDATE_INSTRUMENTS, nozPos, nozPosSD);
    send("nozRO", UPDATE_VALUE, nozPos, nozPosROSD);
}
