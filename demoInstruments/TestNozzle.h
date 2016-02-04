//------------------------------------------------------------------------------
// Class: TestNozzle
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestNozzle_H__
#define __oe_demo_TestNozzle_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestNozzle : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestNozzle, BasicGL::Page)

public:
    TestNozzle();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal nozPos;
    SendData nozPosSD;
    SendData nozPosROSD;       // sends our readout data (to a numeric readout)
    LCreal  nozRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

