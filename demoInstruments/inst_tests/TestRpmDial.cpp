
#include "TestRpmDial.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestRpmDial, "TestRpmDial")
EMPTY_SERIALIZER(TestRpmDial)
EMPTY_DELETEDATA(TestRpmDial)

TestRpmDial::TestRpmDial()
{
    STANDARD_CONSTRUCTOR()
}

void TestRpmDial::copyData(const TestRpmDial& org, const bool)
{
    BaseClass::copyData(org);
    rpm = org.rpm;
    rpmRate = org.rpmRate;
    rpmSD.empty();
    rpmROSD.empty();
}

void TestRpmDial::updateData(const double dt)
{
    BaseClass::updateData(dt);

    rpm += (rpmRate * dt);
    if (rpm > 110) {
        rpm = 110;
        rpmRate = -rpmRate;
    }
    if (rpm < 0) {
        rpm = 0;
        rpmRate = -rpmRate;
    }

    //rpm = 100;

    send("rpm", UPDATE_INSTRUMENTS, rpm, rpmSD);
    send("rpmRO", UPDATE_VALUE, rpm, rpmROSD);
}
