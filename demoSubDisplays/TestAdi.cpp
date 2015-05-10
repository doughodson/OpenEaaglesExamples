#include "TestAdi.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAdi, "TestAdi")
EMPTY_SERIALIZER(TestAdi)
EMPTY_DELETEDATA(TestAdi)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestAdi::TestAdi()
{
    STANDARD_CONSTRUCTOR()

    // pitch of our adi
    pitch = 0.0;
    pitchSD.empty();
    pitchRate = 10.0;
    // roll of our adi
    roll = 0.0;
    rollSD.empty();
    rollRate = 25.0;
    // side slip value
    slip = 0.0;
    slipSD.empty();
    slipRate = 5.0;
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestAdi::updateData(const LCreal dt)
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

} // end of Demo namespace
} // end of Eaagles namespace

