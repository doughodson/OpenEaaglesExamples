#include "TestAdi.h"

namespace Eaagles {
namespace Mainz2 {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAdi,"TestAdi")
EMPTY_SERIALIZER(TestAdi)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestAdi::TestAdi()
{
    STANDARD_CONSTRUCTOR()
    
    // pitch of our adi
    pitch = 0;
    pitchSD.empty();
    pitchRate = 20;
    // roll of our adi
    roll = 0;
    rollSD.empty();
    rollRate = 25;
    // side slip value
    slip = 0;
    slipSD.empty();
    slipRate = 5;
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestAdi::copyData(const TestAdi& org, const bool)
{
    BaseClass::copyData(org);
    pitch = org.pitch;
    pitchSD.empty();
    pitchRate = org.pitchRate;
    roll = org.roll;
    rollSD.empty();
    rollRate = org.rollRate;
    slip = org.slip;
    slipSD.empty();
    slipRate = org.slipRate;
}

EMPTY_DELETEDATA(TestAdi)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestAdi::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    // pitch
    pitch += (pitchRate * dt);
    if (pitch > 90) {
        pitch = 90;
        pitchRate = -pitchRate;
    }
    if (pitch < -90) {
        pitch = -90;
        pitchRate = -pitchRate;
    }
    // roll
    roll += (rollRate * dt);
    if (roll > 180) {
        roll = 180;
        rollRate = -rollRate;
    }
    if (roll <  -180) {
        roll = -180;
        rollRate = -rollRate;
    }
    // side slip
    slip += (slipRate * dt);
    if (slip > 20) {
        slip = 20;
        slipRate = -slipRate;
    }
    if (slip <  -20) {
        slip = -20;
        slipRate = -slipRate;
    }
    
    // notice that we can either get a pointer to our Adi by using findByType() or findByName(), 
    // or we can use the send command that will send the event message down
    /*
    // get a pointer to our Adi, and send it the data
    Basic::Pair* pair = findByType(typeid(Eaagles::Adi));
    if (pair != 0) {
        pair->ref();
            Eaagles::Adi* myAdi = dynamic_cast<Eaagles::Adi*>(pair->object());
            if (myAdi != 0) {
                myAdi->setPitch(pitch);
                myAdi->setRoll(roll);
            }
        pair->unref();
    }
    */
    
    // send our sideslip 
    send("sideslip", UPDATE_INSTRUMENTS, slip, slipSD);
    // send our pitch(1) and roll(2)
    send("adi", UPDATE_INSTRUMENTS, pitch, pitchSD);
    send("adi", UPDATE_VALUE, roll, rollSD);
}

} // end of Mainz2 namespace
} // end of Eaagles namespace

