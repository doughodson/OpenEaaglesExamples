
#include "TestFtitDial.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestFtitDial, "TestFtitDial")
EMPTY_SERIALIZER(TestFtitDial)
EMPTY_DELETEDATA(TestFtitDial)

TestFtitDial::TestFtitDial()
{
    STANDARD_CONSTRUCTOR()
}

void TestFtitDial::copyData(const TestFtitDial& org, const bool)
{
    BaseClass::copyData(org);
    ftitRotation = org.ftitRotation;
    ftitRotationSD.empty();
    ftitRate = org.ftitRate;
    ftitRotationROSD.empty();
}

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
