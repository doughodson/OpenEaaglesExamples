#include "TestFtitDial.h"

namespace oe {
namespace demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestFtitDial, "TestFtitDial")
EMPTY_SERIALIZER(TestFtitDial)
EMPTY_DELETEDATA(TestFtitDial)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestFtitDial::TestFtitDial()
{
    STANDARD_CONSTRUCTOR()
    ftitRotation = 0.0;
    ftitRotationSD.empty();
    ftitRate = 100.0;
    ftitRotationROSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestFtitDial::copyData(const TestFtitDial& org, const bool)
{
    BaseClass::copyData(org);
    ftitRotation = org.ftitRotation;
    ftitRotationSD.empty();
    ftitRate = org.ftitRate;
    ftitRotationROSD.empty();
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestFtitDial::updateData(const double dt)
{
    BaseClass::updateData(dt);

    ftitRotation += (ftitRate * dt);
    if (ftitRotation > 1200) {
        ftitRotation = 1200;
        ftitRate = -ftitRate;
    }
    if (ftitRotation < 0) {
        ftitRotation = 0;
        ftitRate = -ftitRate;
    }

    send("ftit", UPDATE_INSTRUMENTS, ftitRotation, ftitRotationSD);
    send("ftitRO", UPDATE_VALUE, ftitRotation, ftitRotationROSD);
}

} // end of demo namespace
} // end of oe namespace

