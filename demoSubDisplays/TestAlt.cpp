#include "TestAlt.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAlt,"TestAlt")
EMPTY_SERIALIZER(TestAlt)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestAlt::TestAlt()
{
    STANDARD_CONSTRUCTOR()
    // altitude (feet)
    alt = 0;
    altSD.empty();
    altRate = 500;
    altROSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestAlt::copyData(const TestAlt& org, const bool)
{
    BaseClass::copyData(org);
    alt = org.alt;
    altSD.empty();
    altRate = org.altRate;
    altROSD.empty();
}

EMPTY_DELETEDATA(TestAlt)

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestAlt::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    alt += (altRate * dt);
    if (alt > 65000) {
        alt = 65000;
        altRate = -altRate;
    }
    if (alt < 0) {
        alt = 0;
        altRate = -altRate;
    }

    // send the data down          
    send("alt", UPDATE_INSTRUMENTS, alt, altSD);
    send("altRO", UPDATE_VALUE, alt, altROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace

