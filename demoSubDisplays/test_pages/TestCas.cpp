
#include "TestCas.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestCas, "TestCas")
EMPTY_SERIALIZER(TestCas)
EMPTY_DELETEDATA(TestCas)

TestCas::TestCas()
{
    STANDARD_CONSTRUCTOR()
}

void TestCas::copyData(const TestCas& org, const bool)
{
    BaseClass::copyData(org);
    tas = org.tas;
    tasSD.empty();
    tasRate = org.tasRate;
    tasPointerRotationSD.empty();
    tasROSD.empty();
}

void TestCas::updateData(const double dt)
{
    BaseClass::updateData(dt);

    tas += (tasRate * dt);
    if (tas > 900) {
        tas = 900;
        tasRate = -tasRate;
    }
    if (tas < 0) {
        tas = 0;
        tasRate = -tasRate;
    }

    //tas = 661.74;

    // send the data down to the instruments and to the readouts
    send("tas", UPDATE_INSTRUMENTS, tas, tasSD);
    send("tasRO", UPDATE_VALUE, tas, tasROSD);
}
