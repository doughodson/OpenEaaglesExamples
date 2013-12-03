//------------------------------------------------------------------------------
// Class:	TestEngPage
// Base class:	... -> BasicGL::Page -> PfdPage -> TestEngPage
//
// Description:	Tests the engine page
//------------------------------------------------------------------------------
#ifndef	__TestEngPage_H_F2FEF423_7ECE_41ae_8A20_5A0B3D91E80C
#define __TestEngPage_H_F2FEF423_7ECE_41ae_8A20_5A0B3D91E80C

#include "openeaagles/basicGL/Page.h"
#include "openeaagles/instruments/eng/EngPage.h"

namespace Eaagles {
namespace Demo {

class TestEngPage : public Eaagles::BasicGL::Page {
   DECLARE_SUBCLASS(TestEngPage,Eaagles::BasicGL::Page )

public:
    TestEngPage();    
    
    // Basic::Component Interface
    virtual void updateData(const LCreal dt = 0.0);

private:
    // engine 1 n1 
    LCreal n1[Eaagles::Instruments::EngPage::NUM_ENG];          
    LCreal n1Rate[Eaagles::Instruments::EngPage::NUM_ENG];

    // engine 1 n2 
    LCreal n2[Eaagles::Instruments::EngPage::NUM_ENG];          
    LCreal n2Rate[Eaagles::Instruments::EngPage::NUM_ENG];

    // engine 1 tit
    LCreal tit[Eaagles::Instruments::EngPage::NUM_ENG];       
    LCreal titRate[Eaagles::Instruments::EngPage::NUM_ENG];

    // engin1 1 fuel flow
    LCreal ff[Eaagles::Instruments::EngPage::NUM_ENG];
    LCreal ffRate[Eaagles::Instruments::EngPage::NUM_ENG];
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif  /* __TestEngPage_H_F2FEF423_7ECE_41ae_8A20_5A0B3D91E80C */

