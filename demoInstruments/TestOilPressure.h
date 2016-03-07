//------------------------------------------------------------------------------
// Class: TestOilPressure
//
// Description: Another example of using an analog dial.  This one is an F-16
// like oil pressure gauge
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestOilPressure_H__
#define __oe_demo_TestOilPressure_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestOilPressure : public graphics::Page
{
   DECLARE_SUBCLASS(TestOilPressure, graphics::Page)

public:
    TestOilPressure();

    void updateData(const double dt = 0) override;

private:
    double oilPressure;
    SendData oilPressureSD;
    SendData oilPressureROSD;       // sends our readout data (to a numeric readout)
    double  oilRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

