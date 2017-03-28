
#include "Pfd.hpp"

#include "SituationalDisplay.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/units/angle_utils.hpp"

#include <cstring>
#include <cmath>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Pfd, "Pfd")
EMPTY_SERIALIZER(Pfd)
EMPTY_DELETEDATA(Pfd)

Pfd::Pfd()
{
    STANDARD_CONSTRUCTOR()

    // tacan and waypoint course
    nav1Id[0] = ' ';
    nav1Id[1] = '\0';
    nav2Id[0] = ' ';
    nav2Id[1] = '\0';
}

void Pfd::copyData(const Pfd& org, const bool)
{
    // Always copy base class stuff first
    BaseClass::copyData(org);
    // pitch and roll
    pitch = org.pitch;
    pitchSD.empty();
    hdgPitchSD.empty();
    roll = org.roll;
    rollSD.empty();
    // bank angle
    baSD.empty();
    bascaleSD.empty();
    // hdg and nav
    trueHdg = org.trueHdg;
    tHdgSD.empty();
    hdgTapeSD.empty();
    cmdCrs = org.cmdCrs;
    cmdCrsROSD.empty();
    cmdHdg = org.cmdHdg;
    cmdHdgROSD.empty();
    // cdi
    cdiDots = org.cdiDots;
    // to from
    toFrom = org.toFrom;
    // airspeed
    airSpd = org.airSpd;
    airSpdSD.empty();
    airSpdHundSD.empty();
    airSpdTpSD.empty();
    onesSD.empty();
    tensSD.empty();
    spdRstSD.empty();
    // altitude
    alt = org.alt;
    altSD.empty();
    alt1SD.empty();
    alt2SD.empty();
    alt3SD.empty();
    altTpSD.empty();
    altTensSD.empty();
    altSelectSD.empty();
    altHundredsSD.empty();
    altThouSD.empty();
    // side slip
    slip = org.slip;
    slipSD.empty();
    // glideslope
    gSlope = org.gSlope;
    gSlopeSD.empty();
    // lateral deviation
    latDev = org.latDev;
    latDevSD.empty();
    // commanded speed
    cmdSpd = org.cmdSpd;
    aBugSD.empty();
    diffSD.empty();
    // commanded alt
    cmdAlt = org.cmdAlt;
    altBugSD.empty();
    altDiffSD.empty();
    // master caution
    mstrCtn = false;
    mstrCtnSD.empty();
    // vvi
    vvi = org.vvi;
    vviSD.empty();
    maxVvi = org.minVvi;
    minVvi = org.minVvi;
    maxVviSD.empty();
    minVviSD.empty();
    vviROSD.empty();
    maxVviROSD.empty();
    minVviROSD.empty();
    // aoa
    aoa = org.aoa;
    aoaSD.empty();
    // ground speed
    gSpd = org.gSpd;
    gSpdSD.empty();
    // flight director (command bars)
    fDirBank = org.fDirBank;
    fDirBankSD.empty();
    fDirPitch = org.fDirPitch;
    fDirPitchSD.empty();
    // selected barometric pressure
    baro = org.baro;
    baroSD.empty();
    // radar alt
    rAlt = org.rAlt;
    rAltMin = org.rAltMin;
    // tacan and waypoint course
    nav1Brg = org.nav1Brg;
    nav1Dme = org.nav1Dme;
    std::strncpy(nav1Id, org.nav1Id, NCHAR_NAV1_ID);
    nav1DmeSD.empty();
    nav1IdSD.empty();
    nav2Brg = org.nav2Brg;
    nav2Dme = org.nav2Dme;
    std::strncpy(nav2Id, org.nav2Id, NCHAR_NAV2_ID);
    nav2DmeSD.empty();
    nav2IdSD.empty();
    // Hsi send data
    trueHdgSD.empty();
    cmdHdgSD.empty();
    cmdCrsSD.empty();
    cdiDotsSD.empty();
    toFromSD.empty();
    nav1BrgSD.empty();
    nav2BrgSD.empty();
    // Radar alt
    rAltSD.empty();
    rAltMinSD.empty();
    // lat and lon
    refLat = org.refLat;
    refLon = org.refLon;
    range = org.range;
    // FPM
    fpmX = org.fpmX;
    fpmY = org.fpmY;
    fpmXSD.empty();
    fpmYSD.empty();
    // Gs
    gLoad = org.gLoad;
    // mach
    mach = org.mach;
}

//------------------------------------------------------------------------------
// Set functions --
//------------------------------------------------------------------------------

bool Pfd::setPitchDeg(const double newP)
{
    pitch = newP;
    return true;
}

bool Pfd::setPitchRad(const double newP)
{
    // convert to degrees
    pitch = static_cast<double>(newP * base::angle::R2DCC);
    return true;
}

bool Pfd::setRollDeg(const double newR)
{
    roll = newR;
    return true;
}

bool Pfd::setRollRad(const double newR)
{
    // convert to degrees
    roll = static_cast<double>(newR * base::angle::R2DCC);
    return true;
}

bool Pfd::setTrueHeading(const double newTH)
{
    trueHdg = newTH;
    return true;
}

bool Pfd::setCmdCourse(const double newCC)
{
    cmdCrs = newCC;
    return true;
}

bool Pfd::setCmdHdg(const double newCH)
{
    cmdHdg = newCH;
    return true;
}

bool Pfd::setCdiDots(const double newCD)
{
    cdiDots = newCD;
    return true;
}

bool Pfd::setToFrom(const double newTF)
{
    toFrom = newTF;
    return true;
}

bool Pfd::setAirSpeedKts(const double newAS)
{
    airSpd = newAS;
    return true;
}

bool Pfd::setAltitudeFt(const double newA)
{
    alt = newA;
    return true;
}

bool Pfd::setSideSlip(const double newSS)
{
    slip = newSS;
    return true;
}

bool Pfd::setGlideslope(const double newGS)
{
    gSlope = newGS;
    return true;
}

bool Pfd::setLatDev(const double newLD)
{
    latDev = newLD;
    return true;
}

bool Pfd::setCmdAirSpdKts(const double newCAS)
{
    cmdSpd = newCAS;
    return true;
}

bool Pfd::setCmdAltFt(const double newCA)
{
    cmdAlt = newCA;
    return true;
}

bool Pfd::setMstrCtn(const bool newMC)
{
    mstrCtn = newMC;
    return true;
}

bool Pfd::setVVI(const double newVVI)
{
    vvi = newVVI;
    return true;
}

bool Pfd::setAOA(const double newAOA)
{
    aoa = newAOA;
    return true;
}

bool Pfd::setGroundSpdKts(const double newGS)
{
    gSpd = newGS;
    return true;
}

bool Pfd::setFltDirBankDeg(const double newFDB)
{
    fDirBank = newFDB;
    return true;
}

bool Pfd::setFltDirBankRad(const double newFDB)
{
    fDirBank = static_cast<double>(newFDB * base::angle::R2DCC);
    return true;
}

bool Pfd::setFltDirPitchDeg(const double newFDP)
{
    fDirPitch = newFDP;
    return true;
}

bool Pfd::setFltDirPitchRad(const double newFDP)
{
    fDirPitch = static_cast<double>(newFDP * base::angle::R2DCC);
    return true;
}

bool Pfd::setBaroPress(const double newBOP)
{
    baro = newBOP;
    return true;
}

bool Pfd::setRdrAltFt(const double newRA)
{
    rAlt = newRA;
    return true;
}

bool Pfd::setNav1Brg(const double newB)
{
    nav1Brg = newB;
    return true;
}

bool Pfd::setNav1DME(const double newDME)
{
    nav1Dme = newDME;
    return true;
}

bool Pfd::setNav1Id(const char* const newId)
{
    bool ok = false;
    if (newId != nullptr) {
        std::strncpy(nav1Id, newId, NCHAR_NAV1_ID);
        nav1Id[NCHAR_NAV1_ID] = '\0';
        ok = true;
    }
    return ok;
}

bool Pfd::setNav2Brg(const double newB)
{
    nav2Brg = newB;
    return true;
}

bool Pfd::setNav2DME(const double newDME)
{
    nav2Dme = newDME;
    return true;
}

bool Pfd::setNav2Id(const char* const newId)
{
    bool ok = false;
    if (newId != nullptr) {
        std::strncpy(nav2Id, newId, NCHAR_NAV2_ID);
        nav2Id[NCHAR_NAV2_ID] = '\0';
        ok = true;
    }
    return ok;
}
bool Pfd::setFPMX(const double newX)
{
    fpmX = newX;
    return true;
}
bool Pfd::setFPMY(const double newY)
{
    fpmY = newY;
    return true;
}
bool Pfd::setMach(const double x)
{
    mach = x;
    return true;
}

// get functions
bool Pfd::getNav1Id(const int index, char* newString)
{
    bool ok = false;
    if (nav1Id[index] != 0) {
        base::utStrcpy(newString, sizeof(newString), &nav1Id[index]);
        ok = true;
    }
    return ok;
}
bool Pfd::getNav2Id(const int index, char* newString)
{
    bool ok = false;
    if (nav2Id[index] != 0) {
        base::utStrcpy(newString, sizeof(newString), &nav2Id[index]);
        ok = true;
    }
    return ok;
}
bool Pfd::setRefLat(const double newRL)
{
    refLat = newRL;
    return true;
}
bool Pfd::setRefLon(const double newRL)
{
    refLon = newRL;
    return true;
}
bool Pfd::setRange(const double newR)
{
    range = newR;
    return true;
}
bool Pfd::setGLoad(const double newLoad)
{
    gLoad = newLoad;
    return true;
}
//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void Pfd::updateData(const double dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);

    double temp = 0;

    // local variables
    double tHdg = trueHdg;
    if (tHdg < 0.5f) tHdg += 360.0f;

    // find the last digit for the readout tape
    double ones = ((airSpd / 10) - static_cast<int>(airSpd / 10)) * 10;
    // find the 100s value for the dynamic arc segment
    double airSpdHunds = ((airSpd/1000) - static_cast<int>(airSpd/1000)) * 10;
    temp = airSpdHunds - static_cast<int>(airSpdHunds);
    if (temp < 8.5f) airSpdHunds = static_cast<double>(static_cast<int>(airSpdHunds));
    // fine the tens value for the air speed
    double asTens = ((airSpd/100.0f) - static_cast<int>(airSpd/100.0f)) * 10.0f;
    //std::cout << "AIR SPEED = " << airSpd << std::endl;
    //std::cout << "air speed tens = " << asTens << std::endl;
    //std::cout << "air speed hunds = " << airSpdHunds << std::endl;

    const auto rest = static_cast<int>(airSpd / 10.0);

    //cmdSpd = 450;
    //airSpd += (dt * 10);
    const double diff = airSpd - cmdSpd;
    //std::cout << "AIRSPEED = " << airSpd << std::endl;
    //std::cout << "CMD SPEED = " << cmdSpd << std::endl;
    //std::cout << "DIFF = " << diff << std::endl;

    const double altDiff = alt - cmdAlt;
    // let's break the altitude down into ones and tens, so we can
    // send that data to the tape gauge
    const double altTens = ((alt/100) - static_cast<int>(alt/100)) * 10;
    // now figure the rest of the number
    const auto altRest = static_cast<int>(alt/99.9999);
    // also, for our dynamic dial arcs, we need the hundreds value of the altitude
    double altHundreds = 0;
    // find the thousands value too
    if (alt > 99 && alt <= 999) {
        altHundreds = (alt/100);
    }
    else if (alt > 999 && alt <= 99999) {
        altHundreds = ((alt/1000) - static_cast<int>(alt/1000)) * 10;
    }
    double altThousands = alt/1000;
    temp = altThousands - static_cast<int>(altThousands);
    if (temp < 8.5f) altThousands = static_cast<double>(static_cast<int>(altThousands));

    // vvi max and min test
    double maxVviColorRO = 0;
    if (vvi > 6000) maxVviColorRO = vvi;
    else maxVviColorRO = 3000;

    double minVviColorRO = 0;
    if (vvi < -6000) minVviColorRO = -vvi;
    else minVviColorRO = 3000;

    // now for the vvi readouts
    double maxVviRO = 0;
    if (vvi > 3000) maxVviRO = vvi/1000;
    else maxVviRO = 3.0;

    double minVviRO = 0;
    if (vvi < -3000) minVviRO = -vvi/1000;
    else minVviRO = 3.0;

    // all the sends are here
    // radar alt
    send("ralt", UPDATE_VALUE, rAlt, rAltSD);
    send("ralt", UPDATE_VALUE2, rAltMin, rAltMinSD);
    // hsi
    send("cmdcrs", UPDATE_VALUE, cmdCrs, cmdCrsROSD);
    send("cmdhdg", UPDATE_VALUE, cmdHdg, cmdHdgROSD);
    send("hsi", UPDATE_VALUE6, trueHdg, trueHdgSD);

    send("hsi", UPDATE_VALUE7, cmdHdg, cmdHdgSD);
    send("hsi", UPDATE_VALUE8, cmdCrs, cmdCrsSD);
    send("hsi", UPDATE_VALUE9, nav1Brg, nav1BrgSD);
    send("hsi", USER_EVENTS + 1, nav2Brg, nav2BrgSD);
    send("hsi", USER_EVENTS + 2, cdiDots, cdiDotsSD);
    send("hsi", USER_EVENTS + 3, toFrom, toFromSD);

    send("spdtape", UPDATE_INSTRUMENTS, ones, onesSD);
    send("spdrest", UPDATE_VALUE, rest, spdRstSD);
    send("spdtens", UPDATE_INSTRUMENTS, asTens, tensSD);
    send("fdirbnkang", UPDATE_INSTRUMENTS, fDirBank, fDirBankSD);
    send("baro", UPDATE_VALUE, baro, baroSD);
    send("fdirpitch", UPDATE_INSTRUMENTS, fDirPitch, fDirPitchSD);
    send("gspd", UPDATE_VALUE, gSpd, gSpdSD);
    send("maxvvi", UPDATE_VALUE, maxVviRO, maxVviROSD);
    send("minvvi", UPDATE_VALUE, minVviRO, minVviROSD);
    // send our instrument readouts the value, so they can update the color (green on amber)
    send("maxvvicolor", UPDATE_INSTRUMENTS, maxVviColorRO, maxVviSD);
    send("minvvicolor", UPDATE_INSTRUMENTS, minVviColorRO, minVviSD);
    send("aoaro", UPDATE_VALUE, aoa, aoaSD);
    send("vvi", UPDATE_INSTRUMENTS, vvi, vviSD);
    send("vvi", UPDATE_VALUE, vvi / 1000, vviROSD);
    send("mstrctn", SET_VISIBILITY, mstrCtn, mstrCtnSD);
    send("latdev", UPDATE_INSTRUMENTS, latDev, latDevSD);
    // send our heading and nav data
    send("thdg", UPDATE_VALUE, tHdg, tHdgSD);
    if (altRest < 10) {
        send("altsel", SELECT, 1, altSelectSD);
        send("altrest1", UPDATE_VALUE, altRest, alt1SD);
    }
    else if (altRest < 100) {
        send("altsel", SELECT, 2, altSelectSD);
        send("altrest2", UPDATE_VALUE, altRest, alt2SD);
    }
    else {
        send("altsel", SELECT, 3, altSelectSD);
        send("altrest3", UPDATE_VALUE, altRest, alt3SD);
    }
    // gslope
    send("glideslope", UPDATE_INSTRUMENTS, gSlope, gSlopeSD);
    send("alttens", UPDATE_INSTRUMENTS, altTens, altTensSD);
   send("alttape", UPDATE_INSTRUMENTS, alt, altTpSD);
    send("alt", UPDATE_INSTRUMENTS, altHundreds, altHundredsSD);
    send("althun", UPDATE_VALUE, altHundreds, altSD);
    send("altthou", UPDATE_INSTRUMENTS, altThousands, altThouSD);
    //send("althun", UPDATE_VALUE, altHun
    send("altbug", UPDATE_INSTRUMENTS, altDiff, altDiffSD);
    send("cmdalt", UPDATE_VALUE, cmdAlt, altBugSD);
    send("spdbug", UPDATE_INSTRUMENTS, diff, diffSD);
    send("cmdspd", UPDATE_VALUE, cmdSpd, aBugSD);
    // actual airspeed tape, not just the readout
    send("airspd", UPDATE_INSTRUMENTS, airSpd, airSpdTpSD);
    send("airspdhund", UPDATE_INSTRUMENTS, airSpdHunds, airSpdHundSD);
    send("airspdro", UPDATE_VALUE, airSpd, airSpdSD);
    send("spd", UPDATE_VALUE, airSpd, airSpdSD);

    send("nav1dme", UPDATE_VALUE, nav1Dme, nav1DmeSD);
    send("nav1Id", UPDATE_VALUE, nav1Id, nav1IdSD);

    send("nav2dme", UPDATE_VALUE, nav2Dme, nav2DmeSD);
    send("nav2Id", UPDATE_VALUE, nav2Id, nav2IdSD);

    // send our pitch(1) and roll(2) to our adi
    send("adi", UPDATE_INSTRUMENTS, pitch, pitchSD);

    send("adi", UPDATE_VALUE, roll, rollSD);
    // send our bank scale the roll value, so it can display properly
    send("bankscale", UPDATE_INSTRUMENTS, roll, bascaleSD);
    // send our bank angle the roll
    send("bankangle", UPDATE_INSTRUMENTS, -roll, baSD);
    // send our sideslip down
    send("sideslip", UPDATE_INSTRUMENTS, slip, slipSD);
    // send our ghost horizon data
    send("ghosthorizonbar", UPDATE_INSTRUMENTS, pitch, pitchGhostSD);
    // send our flight path marker it's data
    // positive pitch
    fpmY = pitch - (aoa * std::cos(static_cast<float>(roll * base::angle::D2RCC)));
    // determine our flight path marker
    //std::cout << "ANGLE OF ATTACK = " << aoa << std::endl;
    //std::cout << "PITCH = " << pitch << std::endl;
    //std::cout << "FPM Y = " << fpmY << std::endl;

    send("fpm", UPDATE_VALUE, fpmX, fpmXSD);
    // SLS - changed to an instrument 10/16/06
    send("fpm", UPDATE_INSTRUMENTS, fpmY, fpmYSD);

    // heading tape
    send("hdgtape", UPDATE_INSTRUMENTS, tHdg, hdgTapeSD);
    send("hdgtape", UPDATE_VALUE, pitch, hdgPitchSD);

    // If we have a SituationalDisplay as a component, (which we do in one instance) then we will send it the proper data
    {
        base::Pair* pair = findByType(typeid(SituationalDisplay));
        if (pair != nullptr) {
            pair->ref();
            // give the SituationalDisplay all the appropriate map page data
            const auto myPage = dynamic_cast<SituationalDisplay*>(pair->object());
            if (myPage != nullptr) {
                myPage->setReferenceLat(refLat);
                myPage->setReferenceLon(refLon);
                myPage->setHeading(trueHdg);
                myPage->setRange(range);
            }
            pair->unref();
        }
    }
}
