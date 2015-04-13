//------------------------------------------------------------------------------
// Class: TestRpmDial
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestRpmDial_H__
#define __Eaagles_Demo_TestRpmDial_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestRpmDial : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestRpmDial, BasicGL::Page)

public:
    TestRpmDial();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal rpm;
    SendData rpmSD;
    SendData rpmROSD;       // sends our readout data (to a numeric readout)
    LCreal  rpmRate;
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

