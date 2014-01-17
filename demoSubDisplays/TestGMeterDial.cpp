#include "TestGMeterDial.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/instruments/dials/GMeterDial.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestGMeterDial,"TestGMeterDial")
EMPTY_SERIALIZER(TestGMeterDial)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestGMeterDial::TestGMeterDial()
{
    STANDARD_CONSTRUCTOR()
    currGs = 0;
    currGsSD.empty();
    currGsROSD.empty();
    gRate = 2;
    timer = 0;
    timerRate = 0.2f;
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestGMeterDial::copyData(const TestGMeterDial& org, const bool)
{
    currGs = org.currGs;
    currGsSD.empty();
    currGsROSD.empty();
    gRate = org.gRate;
    timer = org.timer;
    timerRate = org.timerRate;
}

EMPTY_DELETEDATA(TestGMeterDial)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestGMeterDial::updateData(const LCreal dt)
{
    currGs += (gRate * dt);
    if (currGs > 11) {
        currGs = 11;
        gRate = -gRate;
    }
    if (currGs < -4) {
        currGs = -4;
        gRate = -gRate;
    }
    
    //std::cout << "TIMER = " << timer << std::endl;
    // we test the reset pulse here
    timer += (timerRate * dt);
    if (timer > 5) {
        timer = 0;
        currGs = 0;
        /*
        {
            Basic::Pair* p = findByType(typeid(Eaagles::GMeterDial));
            if (p != 0) {
                    Eaagles::GMeterDial* myDial = (Eaagles::GMeterDial*)(p->object());
                    if (myDial != 0) myDial->resetMe();
            }
        }
        */
        // use the send command to reset
        //std::cout << "RESET EVENT SENT!" << std::endl;
        send("gdial", RESET_EVENT);
    }
    
    send("gdial", UPDATE_INSTRUMENTS, currGs, currGsSD);
    send("gs", UPDATE_VALUE, currGs, currGsROSD);
    
    BaseClass::updateData(dt);
}

} // end of Demo namespace
} // end of Eaagles namespace

