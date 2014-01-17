#define TEST_PFD

#include "TestPfd.h"
#include "openeaagles/basic/Pair.h"
#include "Pfd.h"
#include "openeaagles/basicGL/Display.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestPfd,"TestPfd")
EMPTY_SERIALIZER(TestPfd)
                            
//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestPfd::TestPfd()
{
    STANDARD_CONSTRUCTOR()
    // pitch and roll
    pitch = 0;
    pitchRate = 10;
    roll = 0;
    rollRate = -9.0;

    // heading and nav stuff
    trueHdg = 0;  
    tHdgRate = 11;
    cmdCrs = 0;
    cmdCrsRate = 2;
    cmdHdg = 0;
    cmdHdgRate = 3;

    // cdi
    cdiDots = 0;
    cdiRate = 0.15f;

    // to from
    toFrom = -1;

    // airspeed
    airSpd = 0;
    airSpdRate = 5;

    // altitude
    alt = 0;
    altRate = 300;
    
    // side slip
    slip = 0;
    slipRate = 10;
    
    // glideslope
    gSlope = 0;
    gSlopeRate = 0.2f;
    
    // lateral deviation
    latDev = 0;
    ldRate = 0.3f;

    // commanded speed
    cmdSpd = 150;

    // commanded alt
    cmdAlt = 5000;

    // master caution
    mstrCtn = false;

    // vvi
    vvi = 0;
    vviRate = 500;
    maxVvi = 3.0f;      
    minVvi = 3.0f;      

    // aoa
    aoa = 0;
    aoaRate = -1;

    // ground speed
    gSpd = 0;
    gSpdRate = 1.5f;

    // flight director (command bars)
    fDirBank = 0;
    fDirBankRate = 10;
    fDirPitch = 0;
    fDirPitchRate = 5;

    // selected barometric pressure
    baro = 0;
    baroRate = 0.5f;

    // radar alt
    rAlt = 0;
    rAltRate = 50;
    rAltMin = 500;

    // navaid bearings
    nav1Brg = 0;
    nav1BrgRate = 4;
    nav2Brg = 0;
    nav2BrgRate = 10;

    // FPM
    fpmX = 0;
    fpmY = 0;
    fpmXRate = 0.05f;
    fpmYRate = 0.05f;
    
    // Visibility flags
    sixtyVisSD.empty();
    ninetyVisSD.empty();
}

//------------------------------------------------------------------------------
// copyData() -- copy this object's data
//------------------------------------------------------------------------------
void TestPfd::copyData(const TestPfd& org, const bool)
{
    // Always copy base class stuff first
    BaseClass::copyData(org);
    
    // pitch and roll
    pitch = org.pitch;
    pitchRate = org.pitchRate;
    roll = org.roll;
    rollRate = org.rollRate;
    
    // hdg and nav
    trueHdg = org.trueHdg;
    tHdgRate = org.tHdgRate;
    cmdCrs = org.cmdCrs;
    cmdCrsRate = org.cmdCrsRate;
    cmdHdg = org.cmdHdg;
    cmdHdgRate = org.cmdHdgRate;

    // cdi
    cdiDots = org.cdiDots;
    cdiRate = org.cdiRate;

    // to from
    toFrom = org.toFrom;

    // airspeed
    airSpd = org.airSpd;
    airSpdRate = org.airSpdRate;

    // altitude
    alt = 0;
    altRate = 10;

    // side slip
    slip = org.slip;
    slipRate = org.slipRate;

    // glideslope
    gSlope = org.gSlope;
    gSlopeRate = org.gSlopeRate;

    // lateral deviation
    latDev = org.latDev;
    ldRate = org.ldRate;

    // commanded speed
    cmdSpd = org.cmdSpd;

    // commanded alt
    cmdAlt = org.cmdAlt;

    // master caution
    mstrCtn = false;

    // vvi
    vvi = org.vvi;
    vviRate = org.vviRate;
    maxVvi = org.minVvi;      
    minVvi = org.minVvi;      

    // aoa
    aoa = org.aoa;
    aoaRate = org.aoaRate;

    // ground speed
    gSpd = org.gSpd;
    gSpdRate = org.gSpdRate;

    // flight director (command bars)
    fDirBank = org.fDirBank;
    fDirBankRate = org.fDirBankRate;
    fDirPitch = org.fDirPitch;
    fDirPitchRate = org.fDirPitchRate;

    // selected barometric pressure
    baro = org.baro;
    baroRate = org.baroRate;

    // radar alt
    rAlt = org.rAlt;
    rAltRate = org.rAltRate;
    rAltMin = org.rAltMin;

    // tacan and waypoint course
    nav1Brg = org.nav1Brg;
    nav1BrgRate = org.nav1BrgRate;
    nav2Brg = org.nav2Brg;
    nav2BrgRate = org.nav2BrgRate;

    // FPM
    fpmX = org.fpmX;
    fpmY = org.fpmY;
    fpmXRate = org.fpmXRate;
    fpmYRate = org.fpmYRate;
    
    sixtyVisSD.empty();
    ninetyVisSD.empty();

}

//------------------------------------------------------------------------------
//deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void TestPfd::deleteData()
{
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void TestPfd::updateData(const LCreal dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);

#ifdef TEST_PFD
    // pitch
    pitch += pitchRate * dt;
    if (pitch > 90) {
        pitch = 90;
        pitchRate = -pitchRate;
    }
    if (pitch < -90) {
        pitch = -90;
        pitchRate = -pitchRate;
    }

    // roll
    roll  += rollRate * dt;
    if (roll > 90) {
        roll = 90;
        rollRate = -rollRate;
    }
    if (roll < -90) {
        roll = -90;
        rollRate = -rollRate;
    }

    // heading
    trueHdg += tHdgRate * dt;
    if (trueHdg > 360) {
        trueHdg = 0;
    }

    // selected heading
    cmdHdg += cmdHdgRate * dt;
    if (cmdHdg > 360) {
        cmdHdg = 0;
    }

    // selected course
    cmdCrs += cmdCrsRate * dt;
    if (cmdCrs > 360) {
        cmdCrs = 0;
    }

    // course deviation test
    cdiDots += cdiRate * dt;
    if (cdiDots > 2) {
        cdiDots = 2;
        cdiRate = -cdiRate;
    }
    if (cdiDots < -2) {
        cdiDots = -2;
        cdiRate = -cdiRate;
    }

    LCreal temp = (cmdCrs - trueHdg);
    if (temp > 50) toFrom = 0;
    else  if (temp < -50) toFrom = 1;
    else toFrom = -1;

    // here is sideslip
    slip += slipRate * dt;
    if (slip > 21) {
        slip = 21;
        slipRate = -slipRate;
    }
    if (slip < -21) {
        slip = -21;
        slipRate = -slipRate;
    }

    nav1Brg += nav1BrgRate * dt;
    if (nav1Brg > 360) {
        nav1Brg = 360;
        nav1BrgRate = -nav1BrgRate;
    }
    if (nav1Brg < 0) {
        nav1Brg = 0;
        nav1BrgRate = -nav1BrgRate;
    }

    nav2Brg += nav2BrgRate * dt;
    if (nav2Brg > 360) {
        nav2Brg = 360;
        nav2BrgRate = -nav2BrgRate;
    }
    if (nav2Brg < 0) {
        nav2Brg = 0;
        nav2BrgRate = -nav2BrgRate;
    }     

    // airspeed
    airSpd += airSpdRate * dt;
    if (airSpd > 200) {
        airSpd = 200;
        airSpdRate = -airSpdRate;
    }
    if (airSpd < 50) {
        airSpd = 50;
        airSpdRate = -airSpdRate;
    }

    // commanded speed
    cmdSpd = 150;

    // altitude
    alt += altRate * dt;
    if (alt > 55800) {
        alt = 55800;
        altRate = -altRate;
    }
    if (alt < 0) {
        alt = 0;
        altRate = -altRate;
    }

    // commanded alt
    cmdAlt = 1500;

    // glideslope
    gSlope += gSlopeRate * dt;
    if (gSlope > 2) {
        gSlope = 2;
        gSlopeRate = -gSlopeRate;
    }
    if (gSlope < -2) {
        gSlope = -2;
        gSlopeRate = -gSlopeRate;
    }

    // lat dev
    latDev += ldRate * dt;
    if (latDev > 2) {
        latDev = 2;
        ldRate = -ldRate;
    }
    if (latDev < -2) {
        latDev = -2;
        ldRate = -ldRate;
    }

    // master caution stuff
    if (pitch > 70 || pitch < -70 ) mstrCtn = true;
    else mstrCtn = false;

    // vvi tape gauge test
    vvi += vviRate * dt;
    if (vvi > 7000) {
        vvi = 7000;
        vviRate = -vviRate;
    }
    if (vvi < -7000) {
        vvi = -7000;
        vviRate = -vviRate;
    }

    // angle of attack
    aoa += aoaRate * dt;
    if (aoa > 60) {
        aoa = 60;
        aoaRate = -aoaRate;
    }
    if (aoa < -30) {
        aoa = -30;
        aoaRate = -aoaRate;
    }

    // ground speed
    gSpd += gSpdRate * dt;
    if (gSpd > 60) {
        gSpd = 60;
        gSpdRate = -gSpdRate;
    }
    if (gSpd < -30) {
        gSpd = -30;
        gSpdRate = -gSpdRate;
    }

    // flight director stuff (limit to 0.56 inches each way)
    // flight diretor bank angle
    fDirBank += fDirBankRate * dt;
    if (fDirBank > 90) {
        fDirBank = 90;
        fDirBankRate = -fDirBankRate;
    }
    if (fDirBank < -90) {
        fDirBank = -90;
        fDirBankRate = -fDirBankRate;
    }

    // flight director pitch angle
    fDirPitch += fDirPitchRate * dt;
    if (fDirPitch > 90) {
        fDirPitch = 90;
        fDirPitchRate = -fDirPitchRate;
    }
    if (fDirPitch < -90) {
        fDirPitch = -90;
        fDirPitchRate = -fDirPitchRate;
    }

    // barometric pressure (selected)
    baro += baroRate * dt;
    if (baro > 99.99) {
        baro = 99.99f;
        baroRate = -baroRate;
    }
    if (baro < 0) {
        baro = 0;
        baroRate = -baroRate;
    }

    // radar altitude and minimums
    rAlt += rAltRate * dt;
    if (rAlt > 50000) {
        rAlt = 50000;
        rAltRate = -rAltRate;
    }
    if (rAlt < 0) {
        rAlt = 0;
        rAltRate = -rAltRate;
    }

    // flight path pitch marker
    fpmX += (fpmXRate * dt);
    if (fpmX > 5) {
        fpmX = 5;
        fpmXRate = -fpmXRate;
    }
    if (fpmX < -5) {
        fpmX = -5;
        fpmXRate = -fpmXRate;
    }
    // flight path roll marker
    fpmY += (fpmYRate * dt);
    if (fpmY > 8.28) {
        fpmY = 8.28f;
        fpmYRate = -fpmYRate;
    }
    if (fpmY < -8.28) {
        fpmY = -8.28f;
        fpmYRate = -fpmYRate;
    }
#endif
    
    // Since we have so much data to send, it
    // is easier to get a pointer and use
    // member functions than to just send
    // it using the send function.
    Basic::Pair* pair = findByType(typeid(Pfd));
    if (pair != 0) {
        Pfd* p = (Pfd*)(pair->object());
        if (p != 0) {
            p->setPitchDeg(pitch);
            p->setRollDeg(roll);
            p->setTrueHeading(trueHdg);
            p->setCmdCourse(cmdCrs);
            p->setCmdHdg(cmdHdg);
            p->setCdiDots(cdiDots);
            p->setToFrom(toFrom);
            p->setAirSpeedKts(airSpd);
            p->setAltitudeFt(alt);
            p->setSideSlip(slip);
            p->setGlideslope(gSlope);
            p->setLatDev(latDev);
            p->setCmdAirSpdKts(cmdSpd);
            p->setCmdAltFt(cmdAlt);
            p->setMstrCtn(mstrCtn);
            p->setVVI(vvi);
            p->setAOA(aoa);
            p->setGroundSpdKts(gSpd);
            p->setFltDirBankDeg(fDirBank);
            p->setFltDirPitchDeg(fDirPitch);
            p->setBaroPress(baro);
            p->setRdrAltFt(rAlt);
            p->setNav1Brg(nav1Brg);
            p->setNav2Brg(nav2Brg);
            p->setFPMX(fpmX);
            p->setFPMY(fpmY);
        }
    }
    
    // we only display the 60 and 90 degree marks if we are past 45 and 60 degrees,
    // respectively
    bool sixtyVis = false, ninetyVis = false;
    if (roll > 45 || roll < -45) {
        sixtyVis = true;
    }
    
    if (roll > 60 || roll < -60) {
        ninetyVis = true;
    }

    send("60indices", SET_VISIBILITY, sixtyVis, sixtyVisSD);
    send("90indices", SET_VISIBILITY, ninetyVis, ninetyVisSD);
    
}

} // end of Demo namespace
} // end of Eaagles namespace
