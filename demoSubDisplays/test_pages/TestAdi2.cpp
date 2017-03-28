
#include "TestAdi2.hpp"
#include "openeaagles/base/units/angle_utils.hpp"

#include <cmath>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestAdi2, "TestAdi2")
EMPTY_SERIALIZER(TestAdi2)
EMPTY_DELETEDATA(TestAdi2)

TestAdi2::TestAdi2()
{
    STANDARD_CONSTRUCTOR()
}

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

void TestAdi2::updateData(const double dt)
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
    const auto aoaRad = static_cast<double>(5.0 * base::angle::D2RCC);
    const auto rollRad = static_cast<double>(roll * base::angle::D2RCC);
    double tempAoaDiff = aoaRad * std::cos(rollRad);

    //std::cout << "ANGLE OF ATTACK = " << aoa << std::endl;
    //std::cout << "PITCH = " << pitch << std::endl;

    // determine exact positioning of our Climb dive
    cdmX = tempAoaDiff * std::sin(rollRad);
    cdmY = -tempAoaDiff * std::cos(rollRad);

    //std::cout << "FPM Y = " << fpmY << std::endl;
    // convert to screen coordinates

    double ratio = 20/(base::PI/2);
    //double myTest = (aoaRad * std::cos(rollRad)) * ratio;

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
