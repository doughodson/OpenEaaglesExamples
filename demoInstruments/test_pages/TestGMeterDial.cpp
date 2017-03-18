
#include "TestGMeterDial.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/instruments/dials/GMeterDial.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestGMeterDial, "TestGMeterDial")
EMPTY_SERIALIZER(TestGMeterDial)
EMPTY_DELETEDATA(TestGMeterDial)

TestGMeterDial::TestGMeterDial()
{
    STANDARD_CONSTRUCTOR()
}

void TestGMeterDial::copyData(const TestGMeterDial& org, const bool)
{
    currGs = org.currGs;
    currGsSD.empty();
    currGsROSD.empty();
    gRate = org.gRate;
    timer = org.timer;
    timerRate = org.timerRate;
}

void TestGMeterDial::updateData(const double dt)
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
            base::Pair* p = findByType(typeid(oe::GMeterDial));
            if (p != 0) {
                    oe::GMeterDial* myDial = (oe::GMeterDial*)(p->object());
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
