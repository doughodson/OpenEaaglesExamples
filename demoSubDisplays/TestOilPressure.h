//------------------------------------------------------------------------------
// Class: TestOilPressure
//
// Description: Another example of using an analog dial.  This one is an F-16
// like oil pressure gauge
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestOilPressure_H__
#define __Eaagles_Demo_TestOilPressure_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

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

} // end of Demo namespace
} // end of Eaagles namespace

#endif

