#include "TestEngineDial.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestEngineDial,"TestEngineDial")
EMPTY_SERIALIZER(TestEngineDial)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestEngineDial::TestEngineDial()
{
    STANDARD_CONSTRUCTOR()
    engineRotation = 0;
    engineRotationSD.empty();
    engineRate = 10;
    engineReadoutSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestEngineDial::copyData(const TestEngineDial& org, const bool)
{
    BaseClass::copyData(org);
    engineRotation = org.engineRotation;
    engineRotationSD.empty();
    engineRate = org.engineRate;
    engineReadoutSD.empty();
}

EMPTY_DELETEDATA(TestEngineDial)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestEngineDial::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    engineRotation += (engineRate * dt);
    if (engineRotation > 120) {
        engineRotation = 120;
        engineRate = -engineRate;
    }
    if (engineRotation < 0) {
        engineRotation = 0;
        engineRate = -engineRate;
    }
                      
    // send the data down to our instruments and readouts
    send("enginedial", UPDATE_INSTRUMENTS, engineRotation, engineRotationSD);
    send("enginereadout", UPDATE_VALUE, engineRotation, engineReadoutSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
