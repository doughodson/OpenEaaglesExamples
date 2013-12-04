#include "TestVVI.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestVVI,"TestVVI")
EMPTY_SERIALIZER(TestVVI)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestVVI::TestVVI()
{
    STANDARD_CONSTRUCTOR()
    gaugePosition = 0;
    gaugePositionSD.empty();
    gaugeRate = 500;
    gaugePositionROSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestVVI::copyData(const TestVVI& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    gaugePosition = org.gaugePosition;
    gaugePositionSD.empty();
    gaugeRate = org.gaugeRate;
    gaugePositionROSD.empty();

}

EMPTY_DELETEDATA(TestVVI)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestVVI::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    gaugePosition += (gaugeRate * dt);
    if (gaugePosition > 6000) {
        gaugePosition = 6000;
        gaugeRate = -gaugeRate;
    }
    if (gaugePosition < -6000) {
        gaugePosition = -6000;
        gaugeRate = -gaugeRate;
    }
    
    // here is the gauge display 
    send("vvi", UPDATE_INSTRUMENTS, gaugePosition, gaugePositionSD);
    // here is the readout
    send("vviro", UPDATE_VALUE, gaugePosition, gaugePositionROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
