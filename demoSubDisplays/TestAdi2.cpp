#include "TestAdi2.h"
#include "openeaagles/basic/units/Angles.h"

#include <cmath>

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAdi2, "TestAdi2")
EMPTY_SERIALIZER(TestAdi2)
EMPTY_DELETEDATA(TestAdi2)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestAdi2::TestAdi2()
{
    STANDARD_CONSTRUCTOR()
    pitch = 0.0;
    pitchSD.empty();
    pitchRate = 15.0;
    roll = 0.0;
    rollSD.empty();
    rollBASD.empty();
    rollRate = 10.0;
    slip = 0.0;
    slipSD.empty();
    slipRate = 5.0;
    calAS = 0.0;
    calASRate = 20.0;
    calASSD.empty();
    alt = 0.0;
    altRate = 100.0;
    altSD.empty();
    mag = 0.0;
    magRate = 15.0;
    magSD.empty();
    cdmX = 0.0;
    cdmY = 0.0;
    cdmXSD.empty();
    cdmYSD.empty();
    cdmRollSD.empty();
    ghostPitchSD.empty();
    ghostRollSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestAdi2::copyData(const TestAdi2& org, const bool)
{
    BaseClass::copyData(org);
    pitch = org.pitch;
    pitchSD.empty();
    pitchRate = org.pitchRate;
    roll = org.roll;
    rollSD.empty();
    rollBASD.empty();
    rollRate = org.rollRate;
    slip = org.slip;
    slipSD.empty();
    slipRate = org.slipRate;
    calAS = org.calAS;
    calASRate = org.calASRate;
    calASSD.empty();
    alt = org.alt;
    altSD.empty();
    altRate = org.altRate;
    mag = org.mag;
    magRate = org.magRate;
    magSD.empty();
    cdmX = org.cdmX;
    cdmY = org.cdmY;
    cdmXSD.empty();
    cdmYSD.empty();
    cdmRollSD.empty();
    ghostPitchSD.empty();
    ghostRollSD.empty();
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestAdi2::updateData(const LCreal dt)
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
    // side slip (degrees)
    slip += (slipRate * dt);
    if (slip > 20) {
        slip = 20;
        slipRate = -slipRate;
    }
    if (slip <  -20) {
        slip = -20;
        slipRate = -slipRate;
    }

    // airspeed
    calAS += (calASRate * dt);
    if (calAS > 999 || calAS < 0) calASRate = -calASRate;
    // altitude
    alt += (altRate * dt);
    if (alt > 99999 || alt < 0) altRate = -altRate;
    // magnetic heading
    mag += (magRate * dt);
    if (mag > 999 || calAS < 0) magRate = -magRate;

    // climb dive marker stuff
    //cdmX += (cdmXRate * dt);
    //if (cdmX > 1) {
    //    cdmX = 1;
    //    cdmXRate = -cdmXRate;
    //}
    //if (cdmX < -1) {
    //    cdmX = -1;
    //    cdmXRate = -cdmXRate;
    //}
    //cdmY += (cdmYRate * dt);
    //if (cdmY > 2) {
    //    cdmY = 2;
    //    cdmYRate = -cdmYRate;
    //}
    //if (cdmY < -2) {
    //    cdmY = -2;
    //    cdmYRate = -cdmYRate;
    //}


    // we'll assume an aoa of 2.5degress
    LCreal aoaRad = static_cast<LCreal>(5.0 * Basic::Angle::D2RCC);
    LCreal rollRad = static_cast<LCreal>(roll * Basic::Angle::D2RCC);
    LCreal tempAoaDiff = aoaRad * lcCos(rollRad);

    //std::cout << "ANGLE OF ATTACK = " << aoa << std::endl;
    //std::cout << "PITCH = " << pitch << std::endl;

    // determine exact positioning of our Climb dive
    cdmX = tempAoaDiff * std::sin(rollRad);
    cdmY = -tempAoaDiff * std::cos(rollRad);

    //std::cout << "FPM Y = " << fpmY << std::endl;
    // convert to screen coordinates

    LCreal ratio = 20/(PI/2);
    //LCreal myTest = (aoaRad * lcCos(rollRad)) * ratio;

    cdmX *= ratio;
    cdmY *= ratio;


    // send our data down (including pitch and roll)
    send("mfdadi", UPDATE_INSTRUMENTS, pitch, pitchSD);
    // send roll as degrees
    send("mfdadi", UPDATE_VALUE, roll, rollSD);
    //// send the cdm to the mfd adi
    send("climbdivemarker", UPDATE_VALUE, cdmX, cdmXSD);
    send("climbdivemarker", UPDATE_VALUE2, cdmY, cdmYSD);
    send("climbdivemarkerroll", UPDATE_VALUE2, -roll, cdmRollSD);
    //
    //
    send("sideslip", UPDATE_INSTRUMENTS, -(slip + roll), slipSD);
    send("calibratedreadout", UPDATE_VALUE, calAS, calASSD);
    send("altreadout", UPDATE_VALUE, alt, altSD);
    send("magreadout", UPDATE_VALUE, mag, magSD);
    send("bankangle", UPDATE_INSTRUMENTS, -roll, rollBASD);
    send("ghosthorizon", UPDATE_INSTRUMENTS, pitch, ghostPitchSD);
    send("ghosthorizon", UPDATE_VALUE, roll, ghostRollSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
