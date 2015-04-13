//------------------------------------------------------------------------------
// Class: TestEngPage
//
// Description: Tests the engine page
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestEngPage_H__
#define __Eaagles_Demo_TestEngPage_H__

#include "openeaagles/basicGL/Page.h"
#include "openeaagles/instruments/eng/EngPage.h"

namespace Eaagles {
namespace Demo {

class TestEngPage : public Eaagles::BasicGL::Page
{
   DECLARE_SUBCLASS(TestEngPage, Eaagles::BasicGL::Page )

public:
    TestEngPage();

    void updateData(const LCreal dt = 0.0) override;

private:
    // engine 1 n1
    LCreal n1[Instruments::EngPage::NUM_ENG];
    LCreal n1Rate[Instruments::EngPage::NUM_ENG];

    // engine 1 n2
    LCreal n2[Instruments::EngPage::NUM_ENG];
    LCreal n2Rate[Instruments::EngPage::NUM_ENG];

    // engine 1 tit
    LCreal tit[Instruments::EngPage::NUM_ENG];
    LCreal titRate[Instruments::EngPage::NUM_ENG];

    // engin1 1 fuel flow
    LCreal ff[Instruments::EngPage::NUM_ENG];
    LCreal ffRate[Instruments::EngPage::NUM_ENG];
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

