//------------------------------------------------------------------------------
// Class:	TestAdi
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestAdi
//
// Description:	Tests our core ADI graphic
//
//------------------------------------------------------------------------------
#ifndef	__TestAdi_H__59B86CA4_3AF0_4a56_8C65_CD9FE8982A83
#define __TestAdi_H__59B86CA4_3AF0_4a56_8C65_CD9FE8982A83

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz2 {

class TestAdi : public BasicGL::Page {
   DECLARE_SUBCLASS(TestAdi,BasicGL::Page)

public:
    TestAdi();
    
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:                            
    LCreal pitch;           // our pitch (90 to -90)
    SendData pitchSD;
    LCreal  pitchRate;
    LCreal roll;            // our roll (3.14 to -3.14)
    SendData rollSD;
    LCreal rollRate;
    LCreal slip;            // our side slip (20 to -20)
    SendData slipSD;
    LCreal slipRate;
};

} // end of Mainz2 namespace
} // end of Eaagles namespace

#endif	/* __TestAdi_H__59B86CA4_3AF0_4a56_8C65_CD9FE8982A83 */

