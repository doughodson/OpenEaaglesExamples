//------------------------------------------------------------------------------
// Class: TestRpmDial
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestRpmDial_H__
#define __oe_demo_TestRpmDial_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestRpmDial : public graphics::Page
{
   DECLARE_SUBCLASS(TestRpmDial, graphics::Page)

public:
    TestRpmDial();

    void updateData(const double dt = 0) override;

private:
    double rpm;
    SendData rpmSD;
    SendData rpmROSD;       // sends our readout data (to a numeric readout)
    double  rpmRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

