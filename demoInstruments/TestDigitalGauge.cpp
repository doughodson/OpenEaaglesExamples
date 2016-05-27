
#include "TestDigitalGauge.h"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestDigitalGauge, "TestDigitalGauge")
EMPTY_SERIALIZER(TestDigitalGauge)
EMPTY_DELETEDATA(TestDigitalGauge)

TestDigitalGauge::TestDigitalGauge()
{
    STANDARD_CONSTRUCTOR()
    aoa = 0.0;
    aoaSD.empty();
    aoaRate = 2.0;
    aoaROSD.empty();
    aoaASD.empty();
}

void TestDigitalGauge::copyData(const TestDigitalGauge& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);

    aoa = org.aoa;
    aoaSD.empty();
    aoaRate = org.aoaRate;
    aoaROSD.empty();
    aoaASD.empty();
}

void TestDigitalGauge::updateData(const double dt)
{
    BaseClass::updateData(dt);

    aoa += (aoaRate * dt);
    if (aoa > 40) {
        aoa = 40;
        aoaRate = -aoaRate;
    }
    if (aoa < -5) {
        aoa = -5;
        aoaRate = -aoaRate;
    }

    //aoa = 12;

    send("aoa", UPDATE_VALUE, aoa, aoaROSD);
    // digital version of the aoa indexer (F16)
    send("aoagauge", UPDATE_INSTRUMENTS, aoa, aoaSD);
    // analog version of the aoa
    send("analogaoa", UPDATE_INSTRUMENTS, aoa, aoaASD);
}
