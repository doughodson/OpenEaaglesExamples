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

class TestNozzle : public graphics::Page
{
   DECLARE_SUBCLASS(TestNozzle, graphics::Page)

public:
    TestNozzle();

    void updateData(const double dt = 0) override;

private:
    double nozPos;
    SendData nozPosSD;
    SendData nozPosROSD;       // sends our readout data (to a numeric readout)
    double  nozRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

