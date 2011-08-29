//------------------------------------------------------------------------------
// Class:	TestOilPressure
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestOilPressure
//
// Description:	Another example of using an analog dial.  This one is an F-16
// like oil pressure gauge
//------------------------------------------------------------------------------
#ifndef	__TestOilPressure_H__B73F2155_38FD_4040_9A64_EB4C7BCCA130
#define __TestOilPressure_H__B73F2155_38FD_4040_9A64_EB4C7BCCA130

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz2 {

class TestOilPressure : public Eaagles::BasicGL::Page {
   DECLARE_SUBCLASS(TestOilPressure,Eaagles::BasicGL::Page)

public:
    TestOilPressure();
   
    // Basic::Component interface
    virtual void updateData(const Eaagles::LCreal dt = 0);
   
private:
    Eaagles::LCreal oilPressure;                  
    SendData oilPressureSD;
    SendData oilPressureROSD;       // sends our readout data (to a numeric readout)
    Eaagles::LCreal  oilRate;             
};

} // end of Mainz2 namespace
} // end of Eaagles namespace

#endif	/* __TestOilPressure_H__B73F2155_38FD_4040_9A64_EB4C7BCCA130 */

