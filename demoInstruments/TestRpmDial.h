//------------------------------------------------------------------------------
// Class: TestRpmDial
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestRpmDial_H__
#define __oe_demo_TestRpmDial_H__

#include "openeaagles/basicGL/Page.h"

namespace oe {
namespace demo {

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

} // end of demo namespace
} // end of oe namespace

#endif

