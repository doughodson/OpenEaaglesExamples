//------------------------------------------------------------------------------
// Class: TestAdi
//
// Description: Tests our core ADI graphic
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestAdi_H__
#define __Eaagles_Demo_TestAdi_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

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

} // end of Demo namespace
} // end of Eaagles namespace

#endif

