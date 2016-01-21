//------------------------------------------------------------------------------
// Class: TestOilPressure
//
// Description: Another example of using an analog dial.  This one is an F-16
// like oil pressure gauge
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestOilPressure_H__
#define __oe_demo_TestOilPressure_H__

#include "openeaagles/basicGL/Page.h"

namespace oe {
namespace demo {

class TestOilPressure : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestOilPressure, BasicGL::Page)

public:
    TestOilPressure();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal oilPressure;
    SendData oilPressureSD;
    SendData oilPressureROSD;       // sends our readout data (to a numeric readout)
    LCreal  oilRate;
};

} // end of demo namespace
} // end of oe namespace

#endif

