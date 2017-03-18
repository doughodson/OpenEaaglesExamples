
#include "TestAdi.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAdi, "TestAdi")
EMPTY_SERIALIZER(TestAdi)
EMPTY_DELETEDATA(TestAdi)

TestAdi::TestAdi()
{
    STANDARD_CONSTRUCTOR()
}

void TestAdi::copyData(const TestAdi& org, const bool)
{
    BaseClass::copyData(org);
    pitch = org.pitch;
    pitchSD.empty();
    pitchRate = org.pitchRate;
    roll = org.roll;
    rollSD.empty();
    rollRate = org.rollRate;
    slip = org.slip;
    slipSD.empty();
    slipRate = org.slipRate;
}

void TestAdi::updateData(const double dt)
{
    BaseClass::updateData(dt);

    // pitch
    pitch += (pitchRate * dt);
    if (pitch > 90) {
        pitch = 90;
        pitchRate = -pitchRate;
    }
    if (pitch < -90) {
        pitch = -90;
        pitchRate = -pitchRate;
    }
    // roll
    roll += (rollRate * dt);
    if (roll > 180) {
        roll = 180;
        rollRate = -rollRate;
    }
    if (roll <  -180) {
        roll = -180;
        rollRate = -rollRate;
    }
    // side slip
    slip += (slipRate * dt);
    if (slip > 20) {
        slip = 20;
        slipRate = -slipRate;
    }
    if (slip <  -20) {
        slip = -20;
        slipRate = -slipRate;
    }

    // send our sideslip
    send("sideslip", UPDATE_INSTRUMENTS, slip, slipSD);
    // send our pitch(1) and roll(2)
    send("adi", UPDATE_INSTRUMENTS, pitch, pitchSD);
    send("adi", UPDATE_VALUE, roll, rollSD);
}
