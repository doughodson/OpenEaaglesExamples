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

    virtual void updateData(const double dt = 0.0) override;

private:
    // engine 1 n1
    double n1[instruments::EngPage::NUM_ENG];
    double n1Rate[instruments::EngPage::NUM_ENG];

    // engine 1 n2
    double n2[instruments::EngPage::NUM_ENG];
    double n2Rate[instruments::EngPage::NUM_ENG];

    // engine 1 tit
    double tit[instruments::EngPage::NUM_ENG];
    double titRate[instruments::EngPage::NUM_ENG];

    // engin1 1 fuel flow
    double ff[instruments::EngPage::NUM_ENG];
    double ffRate[instruments::EngPage::NUM_ENG];
};

}
}

#endif

