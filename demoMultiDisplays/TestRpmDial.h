//------------------------------------------------------------------------------
// Class:	TestRpmDial
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestRpmDial
//
// Description:	Another example of using an analog dial.  This one is an F-16
// like rpm analog gauge
//------------------------------------------------------------------------------
#ifndef	__TestRpmDial_H__3FCF149A_1260_4478_8184_2F03F1E6FF0D
#define __TestRpmDial_H__3FCF149A_1260_4478_8184_2F03F1E6FF0D

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestRpmDial : public BasicGL::Page {
   DECLARE_SUBCLASS(TestRpmDial,BasicGL::Page)

public:
    TestRpmDial();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal rpm;                  
    SendData rpmSD;
    SendData rpmROSD;       // sends our readout data (to a numeric readout)
    LCreal  rpmRate;             
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif	/* __TestRpmDial_H__3FCF149A_1260_4478_8184_2F03F1E6FF0D */

