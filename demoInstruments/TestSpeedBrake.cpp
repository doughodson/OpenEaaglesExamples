#include "TestSpeedBrake.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestSpeedBrake, "TestSpeedBrake")
EMPTY_SERIALIZER(TestSpeedBrake)
EMPTY_DELETEDATA(TestSpeedBrake)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestSpeedBrake::TestSpeedBrake()
{
    STANDARD_CONSTRUCTOR()

    sbrakePosition = 0.0;
    sbrakePositionSD.empty();
    sbrakePositionROSD.empty();
    sbrakeRate = 3.0;
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestSpeedBrake::copyData(const TestSpeedBrake& org, const bool)
{
    BaseClass::copyData(org);
    sbrakePosition = org.sbrakePosition;
    sbrakePositionSD.empty();
    sbrakePositionROSD.empty();
    sbrakeRate = org.sbrakeRate;
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestSpeedBrake::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);

    // Each time update data is called, we are just incrementing our speedbrake position
    sbrakePosition += (sbrakeRate * dt);
    if (sbrakePosition > 60) {
        sbrakePosition = 60;
        sbrakeRate = -sbrakeRate;
    }
    if (sbrakePosition < 0) {
        sbrakePosition = 0;
        sbrakeRate = -sbrakeRate;
    }

    // Send our values to our components that need to be updated
    // Update our speedbrake instruments and it's components
    send("sbrake", UPDATE_INSTRUMENTS, sbrakePosition, sbrakePositionSD);
    // Update the numeric readout of the speedbrake position
    send("sbrakeRO", UPDATE_VALUE, sbrakePosition, sbrakePositionROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
