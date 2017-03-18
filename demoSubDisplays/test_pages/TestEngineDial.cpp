
#include "TestEngineDial.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestEngineDial, "TestEngineDial")
EMPTY_SERIALIZER(TestEngineDial)
EMPTY_DELETEDATA(TestEngineDial)

TestEngineDial::TestEngineDial()
{
    STANDARD_CONSTRUCTOR()
}

void TestEngineDial::copyData(const TestEngineDial& org, const bool)
{
    BaseClass::copyData(org);
    engineRotation = org.engineRotation;
    engineRotationSD.empty();
    engineRate = org.engineRate;
    engineReadoutSD.empty();
}

void TestEngineDial::updateData(const double dt)
{
    BaseClass::updateData(dt);

    engineRotation += (engineRate * dt);
    if (engineRotation > 120) {
        engineRotation = 120;
        engineRate = -engineRate;
    }
    if (engineRotation < 0) {
        engineRotation = 0;
        engineRate = -engineRate;
    }

    // send the data down to our instruments and readouts
    send("enginedial", UPDATE_INSTRUMENTS, engineRotation, engineRotationSD);
    send("enginereadout", UPDATE_VALUE, engineRotation, engineReadoutSD);
}
