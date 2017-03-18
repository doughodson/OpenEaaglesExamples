
#ifndef __TestEngPage_H__
#define __TestEngPage_H__

#include "openeaagles/graphics/Page.hpp"
#include "openeaagles/instruments/engines/EngPage.hpp"

//------------------------------------------------------------------------------
// Class: TestEngPage
//
// Description: Tests the engine page
//------------------------------------------------------------------------------
class TestEngPage : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestEngPage, oe::graphics::Page )

public:
    TestEngPage();

    virtual void updateData(const double dt = 0.0) override;

private:
    // engine 1 n1
    double n1[oe::instruments::EngPage::NUM_ENG] {};
    double n1Rate[oe::instruments::EngPage::NUM_ENG] {};

    // engine 1 n2
    double n2[oe::instruments::EngPage::NUM_ENG] {};
    double n2Rate[oe::instruments::EngPage::NUM_ENG] {};

    // engine 1 tit
    double tit[oe::instruments::EngPage::NUM_ENG] {};
    double titRate[oe::instruments::EngPage::NUM_ENG] {};

    // engin1 1 fuel flow
    double ff[oe::instruments::EngPage::NUM_ENG] {};
    double ffRate[oe::instruments::EngPage::NUM_ENG] {};
};

#endif
