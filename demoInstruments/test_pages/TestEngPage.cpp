
#include "TestEngPage.hpp"
#include "openeaagles/base/Pair.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestEngPage, "TestEngPage")
EMPTY_SERIALIZER(TestEngPage)
EMPTY_DELETEDATA(TestEngPage)

TestEngPage::TestEngPage()
{
    STANDARD_CONSTRUCTOR()

    const double n1rates[oe::instruments::EngPage::NUM_ENG]  = {    5,   10,   2,   15 };
    const double n2rates[oe::instruments::EngPage::NUM_ENG]  = {    2,    6,   8,   14 };
    const double titrates[oe::instruments::EngPage::NUM_ENG] = {   50,   30,  12,   23 };
    const double ffrates[oe::instruments::EngPage::NUM_ENG]  = { 1000, 5000, 500, 2000 };

    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        n1[i] = 0.0;
        n1Rate[i] = n1rates[i];

        n2[i] = 0.0;
        n2Rate[i] = n2rates[i];

        tit[i] = 0.0;
        titRate[i] = titrates[i];

        ff[i] = 0.0;
        ffRate[i] = ffrates[i];
    }
}

void TestEngPage::copyData(const TestEngPage& org, const bool)
{
    BaseClass::copyData(org);

    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        n1[i] = org.n1[i];
        n1Rate[i] = org.n1Rate[i];

        n2[i] = org.n2[i];
        n2Rate[i] = org.n2Rate[i];

        tit[i] = org.tit[i];
        titRate[i] = org.titRate[i];

        ff[i] = org.ff[i];
        ffRate[i] = org.ffRate[i];
    }
}

void TestEngPage::updateData(const double dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);

    // engine N1
    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        n1[i] += n1Rate[i] * dt;
        if (n1[i] > 115) {
            n1[i] = 115;
            n1Rate[i] = -n1Rate[i];
        }
        if (n1[i] < 0) {
            n1[i] = 0;
            n1Rate[i] = -n1Rate[i];
        }
    }

    // engine N2
    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        n2[i] += n2Rate[i] * dt;
        if (n2[i] > 115) {
            n2[i] = 115;
            n2Rate[i] = -n2Rate[i];
        }
        if (n2[i] < 0) {
            n2[i] = 0;
            n2Rate[i] = -n2Rate[i];
        }
    }

    // engine TIT
    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        tit[i] += titRate[i] * dt;
        if (tit[i] > 1005) {
            tit[i] = 1005;
            titRate[i] = -titRate[i];
        }
        if (tit[i] < 0) {
            tit[i] = 0;
            titRate[i] = -titRate[i];
        }
    }


    // engine fuel flow (pph)
    for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
        ff[i] += ffRate[i] * dt;
        if (ff[i] > 16000) {
            ff[i] = 16000;
            ffRate[i] = -ffRate[i];
        }
        if (ff[i] < 0) {
            ff[i] = 0;
            ffRate[i] = -ffRate[i];
        }
    }

    {
        // Set to the engine display
        base::Pair* pair = findByType(typeid(oe::instruments::EngPage));
        if (pair != nullptr) {
            const auto p = static_cast<oe::instruments::EngPage*>(pair->object());
            if (p != nullptr) {
                for (int i = 0; i < oe::instruments::EngPage::NUM_ENG; i++) {
                    int idx = (i + 1);
                    p->setEngN1(idx, n1[i]);
                    p->setEngN2(idx, n2[i]);
                    p->setEngTit(idx, tit[i]);
                    p->setEngFF(idx, ff[i]);
                }
            }
        }
    }
}
