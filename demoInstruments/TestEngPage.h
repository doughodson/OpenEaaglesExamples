//------------------------------------------------------------------------------
// Class: TestEngPage
//
// Description: Tests the engine page
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestEngPage_H__
#define __oe_demo_TestEngPage_H__

#include "openeaagles/graphics/Page.h"
#include "openeaagles/instruments/eng/EngPage.h"

namespace oe {
namespace demo {

class TestEngPage : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestEngPage, oe::graphics::Page )

public:
    TestEngPage();

    void updateData(const LCreal dt = 0.0) override;

private:
    // engine 1 n1
    LCreal n1[instruments::EngPage::NUM_ENG];
    LCreal n1Rate[instruments::EngPage::NUM_ENG];

    // engine 1 n2
    LCreal n2[instruments::EngPage::NUM_ENG];
    LCreal n2Rate[instruments::EngPage::NUM_ENG];

    // engine 1 tit
    LCreal tit[instruments::EngPage::NUM_ENG];
    LCreal titRate[instruments::EngPage::NUM_ENG];

    // engin1 1 fuel flow
    LCreal ff[instruments::EngPage::NUM_ENG];
    LCreal ffRate[instruments::EngPage::NUM_ENG];
};

} // end of demo namespace
} // end of oe namespace

#endif

