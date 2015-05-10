#include "TestMechanical.h"

#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Demo {

// static slew rates
const LCreal TestMechanical::T1 = 120;
const LCreal TestMechanical::T2 = 0.40f;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestMechanical,"TestMechanical")
EMPTY_SERIALIZER(TestMechanical)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestMechanical::TestMechanical()
{
    STANDARD_CONSTRUCTOR()
    pitch = 0.0;
    pitchSD.empty();
    pitchRate = 20.0;
    roll = 0.0;
    rollSD.empty();
    rollRate = 10.0;
    slip = 0.0;
    slipSD.empty();
    slipRate = 5.0;
    cmdPitch = 0.0;
    cmdPitchSD.empty();
    cmdRoll = 0.0;
    cmdRollSD.empty();
    cmdPitchRate = 30.0;
    cmdRollRate = 5.0;
    inView = true;
    heading = 0.0;
    headingRate = 3.0;
    rtFail = false;
    // runway stuff
    rwFail = false;
    locDots = 0.0;
    locDotsSD.empty();
    locDotsRate = 0.2;
    rAlt = 0.0;
    rAltRate = 10.0;
    rAltSD.empty();
    // glideslope
    gsDots = 0.0;
    gsDotsSD.empty();
    gsDotsRate = 0.2;
    gsFail = false;
    // speed deviation
    sdFail = false;
    speedDots = 0.0;
    speedDotsRate = 0.4;
    speedDotsSD.empty();
    // ga stuff
    gaMode = 1;
    gaTimer = 0.0;
    // mda stuff
    mdaMode = 1;
    mdaTimer = 0.0;
    mdaModeSD.empty();
    // cmptr
    cmptrFail = false;
    cmptrFailSD.empty();
    gaModeSD.empty();
    // gryo
    gryoFail = false;
    gryoFailTimer = 0.0;
    gryoFailSD.empty();
    gsFail = false;
    gsFailVisSD.empty();
    gsFailSD.empty();
    isGSValid = false;
    isRWIndValid = false;
    isSDValid = false;
    // rate of turn
    rtFail = false;
    rtFailSD.empty();
    rollIndSD.empty();
    rwFailSD.empty();
    sdFailSD.empty();
    curRot = 0.0;
    rotRate = 0.5;
    curRotSD.empty();
}


//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestMechanical::copyData(const TestMechanical& org, const bool)
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
    cmdPitch = org.cmdPitch;
    cmdPitchSD.empty();
    cmdRoll = org.cmdRoll;
    cmdRollSD.empty();
    cmdPitchRate = org.cmdPitchRate;
    cmdRollRate = org.cmdRollRate;
    inView = org.inView;
    heading = org.heading;
    headingRate = org.headingRate;
    rtFail = org.rtFail;
    // runway stuff
    rwFail = org.rwFail;
    locDots = org.locDots;
    locDotsSD.empty();
    locDotsRate = org.locDotsRate;
    rAlt = org.rAlt;
    rAltRate = org.rAltRate;
    rAltSD.empty();
    // glideslope
    gsDots = org.gsDots;
    gsDotsSD.empty();
    gsDotsRate = org.gsDotsRate;
    gsFail = org.gsFail;
    // speed deviation
    sdFail = org.sdFail;
    speedDots = org.speedDots;
    speedDotsSD.empty();
    speedDotsRate = org.speedDotsRate;
    // ga light
    gaMode = org.gaMode;
    gaTimer = org.gaTimer;
    // mda light
    mdaMode = org.mdaMode;
    mdaTimer = org.mdaTimer;
    mdaModeSD.empty();
    // cmptr
    cmptrFail = org.cmptrFail;
    cmptrFailSD.empty();
    // galight
    gaMode = org.gaMode;
    gaModeSD.empty();
    // gryo
    gryoFail = org.gryoFail;
    gryoFailSD.empty();
    gsFail = org.gsFail;
    gsFailVisSD.empty();
    gsFailSD.empty();
    isGSValid = org.isGSValid;
    isRWIndValid = org.isRWIndValid;
    isSDValid = org.isSDValid;
    // rate of turn
    rtFail = org.rtFail;
    rtFailSD.empty();
    rollIndSD.empty();
    rwFailSD.empty();
    sdFailSD.empty();
    gryoFailTimer = org.gryoFailTimer;
    curRot = org.curRot;
    rotRate = org.rotRate;
    curRotSD.empty();
}

EMPTY_DELETEDATA(TestMechanical)


//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestMechanical::updateData(const LCreal dt)
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

    // test our commanded pitch and roll
    cmdPitch += (cmdPitchRate * dt);
    cmdRoll += (cmdRollRate * dt);

    if (cmdPitch > 90) {
        cmdPitch = 90;
        cmdPitchRate = -cmdPitchRate;
    }
    if (cmdPitch < -90) {
        cmdPitch = -90;
        cmdPitchRate = -cmdPitchRate;
    }
    if (cmdRoll > 30) {
        cmdRoll = 30;
        cmdRollRate = -cmdRollRate;
    }
    if (cmdRoll < -30) {
        cmdRoll = -30;
        cmdRollRate = -cmdRollRate;
    }

    // test our gryo flag
    //bool gryoFlag = false;
    //if (cmdRoll < 1) gryoFlag = true;

    // test our computer flag (cmptr)
    cmptrFail = false;
    if (pitch > 60 || pitch < -60) cmptrFail = true;

    // test our in view flag
    if (cmdPitch > 60 || cmdPitch < -60) inView = false;
    else inView = true;

    gryoFailTimer += dt;
    if (gryoFailTimer > 2) {
        gryoFail = !gryoFail;
        gryoFailTimer = 0;
    }

    // test our rate of turn stuff
    heading += (headingRate * dt);
    if (heading > 180) {
        heading = 180;
        headingRate = -headingRate;
    }
    if (heading < -180) {
        heading = -180;
        headingRate = -headingRate;
    }
    // test our heading rate of turn failure (rtfail)
    if (heading > 100) rtFail = true;
    else rtFail = false;
    if (heading < 20) rwFail = true;
    else rwFail = false;

    // runway indicator stuff
    rAlt += (rAltRate * dt);
    if (rAlt > 210) {
        rAlt = 210;
        rAltRate = -rAltRate;
    }
    if (rAlt < 0) {
        rAlt = 0;
        rAltRate = -rAltRate;
    }
    locDots += (locDotsRate * dt);
    if (locDots > 2.5) {
        locDots = 2.5;
        locDotsRate = -locDotsRate;
    }
    if (locDots < -2.5) {
        locDots = -2.5;
        locDotsRate = -locDotsRate;
    }

//    bool gsIsValid = true;
    gsFail = false;
    // glideslope stuff
    gsDots += (gsDotsRate * dt);
    if (gsDots > 2.5) {
        gsDots = 2.5;
        gsDotsRate = -gsDotsRate;
    }
    if (gsDots < -2.5) {
        gsDots = -2.5;
        gsDotsRate = -gsDotsRate;
    }
    // test our validity and flag
    if (gsDots < 1) gsFail = true;
//    if (gsDots < -2) gsIsValid = false;

    // speed dots
    sdFail = false;
//    bool sdIsValid = true;
    speedDots += speedDotsRate * dt;
    if (speedDots > 3) {
        speedDots = 3;
        speedDotsRate = -speedDotsRate;
    }
    if (speedDots < -3) {
        speedDots = -3;
        speedDotsRate = -speedDotsRate;
    }
    // validity and failure checks
//    if (speedDots < -2) sdIsValid = false;
    if (speedDots > 2) sdFail = true;

    // ga light
    gaTimer += dt;
    if (gaTimer > 5 ) {
        gaMode = !gaMode;
        gaTimer = 1;
    }

    // mda light
    mdaTimer += dt;
    if (mdaTimer > 6 ) {
        mdaMode = !mdaMode;
        mdaTimer = 1;
    }

    // send our command bars their pitch and roll
    send("cmdpitch", UPDATE_INSTRUMENTS, cmdPitch, cmdPitchSD);
    send("cmdroll", UPDATE_VALUE2, cmdRoll, cmdRollSD);


    // make up some rate of turn indicator (we assume rate of turn is deg/sec)
    curRot += (rotRate * dt);
    if (curRot > 2) {
        curRot = 2;
        rotRate = -rotRate;
    }
    if (curRot < -2) {
        curRot = -2;
        rotRate = -rotRate;
    }

    send("rtpointer", UPDATE_INSTRUMENTS, curRot, curRotSD);

    // glideslope dots
    send("glideslope", UPDATE_INSTRUMENTS, gsDots, gsDotsSD);

    // send pitch and roll to our adi
    send("adi", UPDATE_INSTRUMENTS, pitch, pitchSD);
    send("adi", UPDATE_VALUE, roll, rollSD);

    // send our ga light the proper mode
    send("galight", SELECT, gaMode, gaModeSD);

    // send the mda light the proper mode
    send("mdalight", SELECT, mdaMode, mdaModeSD);

    // send our localizer dots to our runway pointer
    send("rwpointer", UPDATE_INSTRUMENTS, locDots, locDotsSD);
    send("rwpointervert", UPDATE_INSTRUMENTS, rAlt, rAltSD);

    // send our speed dots down
    send("speeddots", UPDATE_INSTRUMENTS, speedDots, speedDotsSD);

    // Roll indicator
    // we have to roll negative in order to keep with the adi
    send("rollind", UPDATE_VALUE, -static_cast<float>(roll * Basic::Angle::D2RCC), rollIndSD);

    // send our visibility data down (for failure flags)
    send("rtfail", SET_VISIBILITY, rtFail, rtFailSD);
    send("gryo", SET_VISIBILITY, gryoFail, gryoFailSD);
    send("cmptr", SET_VISIBILITY, cmptrFail, cmptrFailSD);
    send("gslopefail", SET_VISIBILITY, gsFail, gsFailVisSD);
    send("rwfail", SET_VISIBILITY, rwFail, rwFailSD);
    send("sdevfail", SET_VISIBILITY, sdFail, sdFailSD);
}

} // end of Demo namespace
} // end of Eaagles namespace
