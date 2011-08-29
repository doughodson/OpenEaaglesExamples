#include "TestGauge1.h"

namespace Eaagles {
namespace Mainz2 {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestGauge1,"TestGauge1")
EMPTY_SERIALIZER(TestGauge1)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestGauge1::TestGauge1()
{
    STANDARD_CONSTRUCTOR()
    gaugePosition = 0;
    gaugePositionSD.empty();
    gaugeRate = 10;
    gaugePositionROSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestGauge1::copyData(const TestGauge1& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    gaugePosition = org.gaugePosition;
    gaugePositionSD.empty();
    gaugeRate = org.gaugeRate;
    gaugePositionROSD.empty();

}

EMPTY_DELETEDATA(TestGauge1)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestGauge1::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    gaugePosition += (gaugeRate * dt);
    if (gaugePosition > 100) {
        gaugePosition = 100;
        gaugeRate = -gaugeRate;
    }
    if (gaugePosition < 0) {
        gaugePosition = 0;
        gaugeRate = -gaugeRate;
    }
    
    // here is the gauge display 
    send("gauge", UPDATE_INSTRUMENTS, gaugePosition, gaugePositionSD);
    // here is the readout
    send("gr", UPDATE_VALUE, gaugePosition, gaugePositionROSD);
}

} // end of Mainz2 namespace
} // end of Eaagles namespace
