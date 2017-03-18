
#include "TestHsi.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestHsi, "TestHsi")
EMPTY_SERIALIZER(TestHsi)
EMPTY_DELETEDATA(TestHsi)

TestHsi::TestHsi()
{
    STANDARD_CONSTRUCTOR()
}

void TestHsi::copyData(const TestHsi& org, const bool)
{
    BaseClass::copyData(org);
    heading = org.heading;
    headingSD.empty();
    headingRate = org.headingRate;
    headingROSD.empty();
    dme = org.dme;
    dmeROSD.empty();
}

void TestHsi::updateData(const double dt)
{
    BaseClass::updateData(dt);

    heading += (headingRate * dt);
    if (heading > 360) {
        heading = 360;
        headingRate = -headingRate;
    }
    if (heading < 0) {
        heading = 0;
        headingRate = -headingRate;
    }

    dme += dt;
    if (dme > 100) dme = 0;

    send("hsi", UPDATE_VALUE6, heading, headingSD);
    send("hsiRO", UPDATE_VALUE, heading, headingROSD);
    send("dmeRO", UPDATE_VALUE, dme, dmeROSD);
}
