#include "TestCas.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestCas,"TestCas")
EMPTY_SERIALIZER(TestCas)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestCas::TestCas()
{
    STANDARD_CONSTRUCTOR()
    tas = 0;
    tasSD.empty();
    tasRate = 50;
    tasPointerRotationSD.empty();
    tasROSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestCas::copyData(const TestCas& org, const bool)
{
    BaseClass::copyData(org);
    tas = org.tas;
    tasSD.empty();
    tasRate = org.tasRate;
    tasPointerRotationSD.empty();
    tasROSD.empty();
}

EMPTY_DELETEDATA(TestCas)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestCas::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    tas += (tasRate * dt);
    if (tas > 900) {
        tas = 900;
        tasRate = -tasRate;
    }
    if (tas < 0) {
        tas = 0;
        tasRate = -tasRate;
    }
    
    //tas = 661.74;
            
    // send the data down to the instruments and to the readouts
    send("tas", UPDATE_INSTRUMENTS, tas, tasSD);
    send("tasRO", UPDATE_VALUE, tas, tasROSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
