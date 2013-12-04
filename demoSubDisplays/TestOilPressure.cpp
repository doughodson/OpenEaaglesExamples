#include "TestOilPressure.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestOilPressure,"TestOilPressure")
EMPTY_SERIALIZER(TestOilPressure)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestOilPressure::TestOilPressure()
{
    STANDARD_CONSTRUCTOR()
    oilPressure = 0;
    oilPressureSD.empty();
    oilRate = 10;
    oilPressureROSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestOilPressure::copyData(const TestOilPressure& org, const bool)
{
    BaseClass::copyData(org);
    oilPressure = org.oilPressure;
    oilPressureSD.empty();
    oilRate = org.oilRate;
    oilPressureROSD.empty();
}

EMPTY_DELETEDATA(TestOilPressure)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestOilPressure::updateData(const Eaagles::LCreal dt)
{
    BaseClass::updateData(dt);
    
    oilPressure += (oilRate * dt);
    if (oilPressure > 120) {
        oilPressure = 120;
        oilRate = -oilRate;
    }
    if (oilPressure < 0) {
        oilPressure = 0;
        oilRate = -oilRate;
    }

    // send our data down                        
    send("oil", UPDATE_INSTRUMENTS, oilPressure, oilPressureSD);
    send("oilRO", UPDATE_VALUE, oilPressure, oilPressureROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
