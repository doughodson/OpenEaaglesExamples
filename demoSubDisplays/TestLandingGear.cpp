#include "TestLandingGear.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestLandingGear,"TestLandingGear")
EMPTY_SERIALIZER(TestLandingGear)

//------------------------------------------------------------------------------
// Event handler for TestLandingGear
//------------------------------------------------------------------------------
BEGIN_EVENT_HANDLER(TestLandingGear)
    ON_EVENT('g', onUpdateLandingGearTestLandingGear)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestLandingGear::TestLandingGear()
{
    STANDARD_CONSTRUCTOR()
    gearPosition = 0;
    gearPositionSD.empty();
    gearRate = 0.3f;
    gearPositionROSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestLandingGear::copyData(const TestLandingGear& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    gearPosition = org.gearPosition;
    gearPositionSD.empty();
    gearRate = org.gearRate;
    gearPositionROSD.empty();

}

EMPTY_DELETEDATA(TestLandingGear)


//------------------------------------------------------------------------------
// onLandinGearEvent()
//------------------------------------------------------------------------------
bool TestLandingGear::onUpdateLandingGearTestLandingGear() 
{
    // switch our gear rate
    gearRate = -gearRate;
    return true;
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestLandingGear::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    gearPosition += (gearRate * dt);
    
    if (gearPosition > 1) gearPosition = 1;
    if (gearPosition < 0) gearPosition = 0;
    
    // here is the gauge display 
    send("gear", UPDATE_INSTRUMENTS, gearPosition, gearPositionSD);
    // here is the readout
    send("gearRO", UPDATE_VALUE, gearPosition, gearPositionROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
