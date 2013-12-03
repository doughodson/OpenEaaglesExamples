#include "TestElectronic.h"
#include "navdefs.h"

#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/LinearVelocity.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestElectronic,"TestElectronic")
EMPTY_SERIALIZER(TestElectronic)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestElectronic::TestElectronic()
{

    STANDARD_CONSTRUCTOR()
    // compass heading and heading bug
    heading = 0;
    headingRate = 3;
    headingBug = 0;
    headingSD.empty();
    headingBugSD.empty();
    // bearing
    bearing = 0;
    brgRate = 5;
    secBearing = 0;
    brgVis = true;
    // nav stuff
    navSource = PRIMARY;
    navType = TACAN;
    navMode = ARC_MODE;
    secNavType = VORTAC;
    secNavMode = ARC_MODE; 
    // course and validity checks
    course = 0;
    secCourse = 0;
    vhfReceive = true;
    secVhfReceive = true;
    vhfDIC = true;
    secVhfDIC = true;
    vhfLocValid = true;
    secVhfLocValid = true;
    vhfLGS = true;
    secVhfLGS = true;
    dmeValid = true;
    secDmeValid = true;
    cdi = 0;
    cdiRate = 0.3f;
    secCdi = 0;
    // location
    loc = PILOT;
    // distance
    dist = 0;
    distRate = 3;
    // made up data
    timeToGo = 0;            
    ttgRate = 50;
    groundSpeed = 0;
    driftAngle = 0;
    daRate = 10;
    trueAirSpeed = 0;
    tasRate = 10;
    elapsedTime = 3500;
    etRate = 20;
    windDir = 0;
    windSpeed = 0;
    readoutMode = ND_TTG;    
    // glideslope
    gsDots = 0;
    gsDotsRate = 0.2f;
    vhfGSValid = true;
    vhfGSOOV = true;

    curHdg = 0;
    curBug = 0;
    hdgBugROMoveXSD.empty();
    distTypeSD.empty();
    distVisSD.empty();
    curDistSD.empty();
    courseSD.empty();
    roLabelSD.empty();
    roWhichSD.empty();
    ttgSD.empty();
    groundSpeedSD.empty();
    driftAngleSD.empty();
    driftAngSideSD.empty();
    trueAirSpeedSD.empty();
    elapsedTimeSD.empty();
    elapsedTimeHRSD.empty();
    whichETSD.empty();
    driftAngleWindSD.empty();
    whichSideDAWindSD.empty();
    windDirectionSD.empty();
    windSpeedSD.empty();
    brgSourceSD.empty();
    brgROSD.empty();
    secBrgROSD.empty();
    glideSlopeSD.empty();
    centeredSD.empty();
    compassHdgSD.empty();
    hdgBugSD.empty();
    priCourseDevSD.empty();
    curCdi = 0;
    crsPntrSD.empty();
    whichCrsPtrSD.empty();
    curCourse = 0;
    priCrsPtrColorSD.empty();
    secCourseDevSD.empty();
    secCrsPntrSD.empty();
    secCrsPtrColorSD.empty();
    whichNavSrcSD.empty();
    primaryPosSD.empty();
    secondaryPosSD.empty();
    primaryCrsVisSD.empty();
    secondaryCrsVisSD.empty();
    curToFrom = 0;
    toOrFromSD.empty();
    toFromSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestElectronic::copyData(const TestElectronic& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    // compass
    heading = org.heading;
    headingRate = org.headingRate;
    headingBug = org.headingBug;
    headingSD.empty();
    headingBugSD.empty();
    // bearing
    bearing = org.bearing;
    secBearing = org.secBearing;
    brgRate = org.brgRate;
    brgVis = org.brgVis;
    // nav stuff
    navSource =org.navSource;
    navType = org.navType;
    secNavType = org.secNavType;
    navMode = org.navMode;
    secNavMode = org.secNavMode;
    // course and validity
    course = org.course;
    secCourse = org.secCourse;
    vhfReceive = org.vhfReceive;
    secVhfReceive = org.secVhfReceive;
    vhfDIC = org.vhfDIC;
    secVhfDIC = org.secVhfDIC;
    vhfLocValid = org.vhfLocValid;
    secVhfLocValid = org.secVhfLocValid;
    vhfLGS = org.vhfLGS;
    secVhfLGS = org.secVhfLGS;
    dmeValid = org.dmeValid;
    secDmeValid = org.secDmeValid;
    cdi = org.cdi;
    cdiRate = org.cdiRate;
    secCdi = 0;
    // location
    loc = org.loc;
    dist = org.dist;
    distRate = org.distRate;
    // made up data
    timeToGo = org.timeToGo;            
    ttgRate = org.ttgRate;
    groundSpeed = org.groundSpeed;
    driftAngle = org.driftAngle;
    daRate = org.daRate;
    trueAirSpeed = org.trueAirSpeed;
    tasRate = org.tasRate;
    elapsedTime = org.elapsedTime;
    etRate = org.etRate;
    windDir = org.windDir;
    windSpeed = org.windSpeed;
    readoutMode = org.readoutMode;    
    // glideslope
    gsDots = org.gsDots;
    gsDotsRate = org.gsDotsRate;
    vhfGSValid = org.vhfGSValid;
    vhfGSOOV = org.vhfGSOOV;


    // SLS
    curHdg = org.curHdg;
    curBug = org.curBug;
    hdgBugROMoveXSD.empty();
    hdgBugROSD.empty();
    curDistSD.empty();
    courseSD.empty();
    roLabelSD.empty();
    roWhichSD.empty();
    ttgSD.empty();
    groundSpeedSD.empty();
    driftAngleSD.empty();
    driftAngSideSD.empty();
    trueAirSpeedSD.empty();
    elapsedTimeSD.empty();
    elapsedTimeHRSD.empty();
    whichETSD.empty();
    driftAngleWindSD.empty();
    whichSideDAWindSD.empty();
    windDirectionSD.empty();
    windSpeedSD.empty();
    brgROSD.empty();
    secBrgROSD.empty();
    glideSlopeSD.empty();
    centeredSD.empty();
    compassHdgSD.empty();
    hdgBugSD.empty();
    priCourseDevSD.empty();
    curCdi = org.curCdi;
    crsPntrSD.empty();
    whichCrsPtrSD.empty();
    curCourse = org.curCourse;
    priCrsPtrColorSD.empty();
    secCourseDevSD.empty();
    secCrsPntrSD.empty();
    secCrsPtrColorSD.empty();
    whichNavSrcSD.empty();
    primaryPosSD.empty();
    secondaryPosSD.empty();
    primaryCrsVisSD.empty();
    secondaryCrsVisSD.empty();
    curToFrom = org.curToFrom;
    toOrFromSD.empty();
    toFromSD.empty();
}

EMPTY_DELETEDATA(TestElectronic)

//------------------------------------------------------------------------------
// updateTestValues() -- update our test data
//------------------------------------------------------------------------------
void TestElectronic::updateTestValues(const LCreal dt)
{
    // heading and heading bug
    heading += headingRate * dt;
    headingBug += 2 * dt;
    // rotate our compass by heading (make sure to limit to 180 degrees
    if (heading > 180) {
        heading = 180;
        headingRate = -headingRate;
    }
    if (heading < -180) {
        heading = -180;
        headingRate = -headingRate;
    }
    if (headingBug > 360) headingBug = 0;
    
    // bearing 
    bearing += brgRate * dt;
    if (bearing > 180) {
        bearing = 180;
        brgRate = -brgRate;
    }
    if (bearing < -180) {
        bearing = -180;
        brgRate = -brgRate;
    }
    // testing the secondary bearing
    secBearing = bearing * 0.9f;
    
    // course && nav type
    course += 10 * dt;
    if (course > 360) course = 0;
    // testing the secondary course
    secCourse = course * 0.9f;
    
    // course deviation
    cdi += cdiRate * dt;
    if (cdi > 2) {
        cdi = 2;
        cdiRate = -cdiRate;
    }
    if (cdi < -2) {
        cdi = -2;
        cdiRate = -cdiRate;
    }
    secCdi = cdi * 1.1f;

    dist += distRate * dt;
    if (dist > 999.9) {
        dist = 999.9f;
        distRate = -distRate;
    }
    if (dist < 0) {
        dist = 0;
        distRate = -distRate;
    }

    // test data
    timeToGo += ttgRate * dt;
    if (timeToGo > 6500) {
        timeToGo = 6500;
        ttgRate = -ttgRate;
    }
    if (timeToGo < 0) {
        timeToGo = 0;
        ttgRate = -ttgRate;
    }
    
    // ground speed
    groundSpeed += 3 * dt;
    if (groundSpeed > 999) groundSpeed = 0;
    
    // da
    driftAngle += daRate * dt;
    if (driftAngle > 90) {
        driftAngle = 90;
        daRate = -daRate;
    }
    if (driftAngle < -90) {
        driftAngle = -90;
        daRate = -daRate;
    }
    
    // tas
    trueAirSpeed += tasRate * dt;
    if (trueAirSpeed > 1500) {
        trueAirSpeed = 1500;
        tasRate = -tasRate;
    }
    if (trueAirSpeed < 0) {
        trueAirSpeed = 0;
        tasRate = -tasRate;
    }
    
    // et
    elapsedTime += etRate * dt;
    if (elapsedTime > 20000) {
        elapsedTime = 20000;
        etRate = -etRate;
    }
    if (elapsedTime < 0) {
        elapsedTime = 0;
        etRate = -etRate;
    }
    
    // wind speed and direction
    windDir += 10 * dt;
    if (windDir > 360) windDir = 0;
    
    windSpeed += 20 * dt;
    if (windSpeed > 800) windSpeed = 0;
    
    // change the readout modes and bearing source here
    if (windSpeed > 500) {
        readoutMode = ND_TTG;
        // change our nav type here, just to test
        navType = VORTAC;
        secNavType = TACAN;
    }
    else if (windSpeed > 400) {
        readoutMode = ND_GSP;
        // change our nav type here, just to test
        navType = TACAN;
        secNavType = INAV;
    }
    else if (windSpeed > 300) {
        readoutMode = ND_TAS;
        // change our nav type here, just to test
        navType = INAV;
        secNavType = VORTAC;
    }
    else if (windSpeed > 200) {
        readoutMode = ND_ET;
        // change our nav type here, just to test
        navType = VORDME;
        secNavType = VOR;
    }
    else if (windSpeed > 100) {
        readoutMode = ND_WIND;
        // change our nav type here, just to test
        navType = VOR;
        secNavType = TACAN;
    }
    else {
        readoutMode = ND_TTG;    
        navType = VORTAC;
        secNavType = TACAN;
    }
    
    // glideslope dots
    gsDots += gsDotsRate * dt;
    if (gsDots > 2.5) {
        gsDots = 2.5;
        gsDotsRate = -gsDotsRate;
    }
    if (gsDots < -2.5) {
        gsDots = -2.5;
        gsDotsRate = -gsDotsRate;
    }
    if (gsDots > 2.1) vhfGSValid = false;
    else vhfGSValid = true;

    //navSource = SECONDARY;
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical stuff here
//------------------------------------------------------------------------------
void TestElectronic::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);

    updateTestValues(dt);

    // current heading / current heading bug
    { 
        // max rate here is 120 degs / second
        LCreal delta = alim(lcAepcDeg(heading - curHdg), 120 * dt);
        curHdg = lcAepcDeg(curHdg + delta);

        // now figure our heading bug
        delta = alim(lcAepcDeg(headingBug - curBug), 120 * dt);
        curBug = lcAepcDeg(curBug + delta);  

        if (navMode == ARC_MODE) {
            // we either move it to the left or right, depending on how far
            // off our slew is.
            LCreal diff = lcAepcDeg(curHdg - curBug);
            LCreal moveX = -1.8f;
            if (diff >= -36 && diff < 36) {
                if (diff > 0) moveX = 1.53f;
                else moveX = -1.8f;
            }

            int tempCurBug = int(curBug);
            if (tempCurBug < 0) tempCurBug += 360;
        
            // heading bug readout value and x position.
            send("bugro", UPDATE_VALUE, tempCurBug, hdgBugROSD);
            send("headingbugro", UPDATE_VALUE, moveX, hdgBugROMoveXSD);
            // heading bug actual position
            send("headingbug", UPDATE_VALUE6, heading - curBug, headingBugSD);
        }
    }

    // distance data / DME
    {
        // are we a distance type or DME type?
        bool distType = true;   // initial type is DME
        bool distVis = true;    // initial visibility is true
        LCreal curDist = alim(dist, 999.9f);    // current distance to DME

        if (navSource == PRIMARY) {
            // valid DME makes our label visible
            distVis = dmeValid;
            if (navType == INAV) distType = false;
        }
        else if (navSource == SECONDARY) {
            // valid DME makes our label visible
            distVis = secDmeValid;
            if (secNavType == INAV) distType = false;
            else distVis = true;
        }

        send("distlabel", SELECT, distType, distTypeSD);
        send("distval", SET_VISIBILITY, distVis, distVisSD);
        send("distval", UPDATE_VALUE, curDist, curDistSD);
    }

    // course data
    {
        // which course pointer are we using?
        send("whichcourseptr", SELECT, navSource, whichCrsPtrSD);

        int curIntCourse = 0;
        LCreal tempCDI = 0;
        LCreal tempCourse = 0;
        // primary nav course
        if (navSource == PRIMARY) {
            curIntCourse = nint(course);
            tempCDI = cdi;
            tempCourse = course;
        }
        // secondary nav course
        else {
            curIntCourse = nint(secCourse);
            tempCDI = secCdi;
            tempCourse = secCourse;
        }

        if (curIntCourse < 0) curIntCourse += 360;                    
        // send the course readout
        send("course", UPDATE_VALUE, curIntCourse, courseSD);

        // here is the course deviation
        LCreal delta = alim (lcAepcDeg(tempCDI - curCdi), 4 * dt);
        curCdi = alim (curCdi + delta, 2.0);
        
        // now find our inches to translate the cdi
        LCreal cdiInch = curCdi * 0.43f;   

        // now figure our course slew
        delta = alim(lcAepcDeg(tempCourse - curCourse), 120 * dt);
        curCourse = (lcAepcDeg(curCourse + delta));

        // ok, do our color determination for the course pointer - primary first
        if (navSource == PRIMARY) {
            // dealing with our primary course pointer here
            bool vis = true;
            if (navMode == MAP_MODE || navMode == DECLUTTER) vis = false;
            send("primarycoursepointer", SET_VISIBILITY, vis, primaryCrsVisSD);
            // course pointer deviation and rotation
            send("primarycoursedev", UPDATE_VALUE, cdiInch, priCourseDevSD);
            send("primarycoursepointer", UPDATE_VALUE6, heading - curCourse, crsPntrSD);

            // course pointer color
            Basic::String* string = new Basic::String("white");
            if (navType == VORTAC) {
                if ((vhfReceive && !(vhfDIC || vhfLGS)) || (vhfLocValid && vhfLGS)) string->setStr("green");
                else string->setStr("yellow");
            }
            else {
                if (dmeValid) string->setStr("green");
                else string->setStr("yellow");
            }

            send("primarycoursepointer", SET_COLOR, string->getString(), priCrsPtrColorSD);
            // get rid of our string
            string->unref();
        }
        else {
            // secondary course pointer
            bool vis = true;
            if (secNavMode == MAP_MODE || secNavMode == DECLUTTER) vis = false;
            send("secondarycoursepointer", SET_VISIBILITY, vis, secondaryCrsVisSD);
            // course pointer deviation and rotation
            send("secondarycoursedev", UPDATE_VALUE, cdiInch, secCourseDevSD);
            send("secondarycoursepointer", UPDATE_VALUE2, curCourse - heading, secCrsPntrSD);

            // course pointer color
            Basic::String* string = new Basic::String("white");
            if (secNavType == VORTAC) {
                if ((secVhfReceive && !(secVhfDIC || secVhfLGS)) || (secVhfLocValid && secVhfLGS)) string->setStr("green");
                else string->setStr("yellow");
            }
            else {
                if (secDmeValid) string->setStr("green");
                else string->setStr("yellow");
            }

            send("secondarycoursepointer", SET_COLOR, string->getString(), secCrsPtrColorSD);
            // get rid of our string
            string->unref();
        }
    }

    // our data readouts (TTG, Gs, etc...)
    {
        // which readout are we using
        send("whichlabel", SELECT, readoutMode, roLabelSD);
        // send which readout we are going to use
        send("whichreadout", SELECT, readoutMode, roWhichSD);

        // first readout, which is our time to go
        if (readoutMode == ND_TTG) {
            LCreal curTTG = timeToGo / 60;
            send("ttg", UPDATE_VALUE, curTTG, ttgSD);
        }
        // ground speed, drift angle, drift angle side.
        else if (readoutMode == ND_GSP) {
            // ground speed
            send("groundspeed", UPDATE_VALUE, groundSpeed, groundSpeedSD);
            // drift angle
            send("driftangle", UPDATE_VALUE, abs(driftAngle), driftAngleSD);
            if (driftAngle < 0) send("driftangleside", SELECT, true, driftAngSideSD);
            else send("driftangleside", SELECT, false, driftAngSideSD);
        }
        // true air speed
        else if (readoutMode == ND_TAS) {
            int curTAS = nintd(trueAirSpeed * Basic::LinearVelocity::FPS2KTSCC);
            send("trueairspeed", UPDATE_VALUE, curTAS, trueAirSpeedSD);
        }
        // elapsed time
        else if (readoutMode == ND_ET) {
            int hour = int(elapsedTime / 3600);
            bool isMin = false;    // default to show hours
            if (hour < 1) {
                isMin = true; // show in minutes
                send("elapsedtimemin", UPDATE_VALUE, elapsedTime, elapsedTimeSD);
            }
            else send("elapsedtimehour", UPDATE_VALUE, elapsedTime, elapsedTimeHRSD);
            
            // send which readout
            send("whichelapsedtimero", SELECT, isMin, whichETSD);
        }
        // wind speed, direction, and drift angle (again)
        else if (readoutMode == ND_WIND) {
            // wind direction
            send("winddirection", UPDATE_VALUE, windDir, windDirectionSD);
            // wind speed
            send("windspeed", UPDATE_VALUE, windSpeed, windSpeedSD);
            // wind drift angle (same as drift angle for test purposes)
            send("driftanglewind", UPDATE_VALUE, abs(driftAngle), driftAngleWindSD);
            bool left = false;  // false is right side, true is left
            // drift angle side
            if (driftAngle < 0) left = true;
            send("driftanglewindside", SELECT, left, whichSideDAWindSD);
        }
    }

    // bearing readouts
    {
        // determine the source of our bearing
        int brgSrc = 1; // default to INAV
        if (navSource == PRIMARY) {
            if (navType == VORTAC) brgSrc = 2;  // primary vortac
            else if (navType == TACAN) brgSrc = 3; // primary tacan 
            send("bearingro", UPDATE_VALUE, bearing, brgROSD);
        }
        else {
            if (secNavType == VORTAC) brgSrc = 4; // secondary vortac
            else brgSrc = 5; // secondary tacan
            send("bearingro", UPDATE_VALUE, secBearing, secBrgROSD);
        }

        send("bearingsource", SELECT, brgSrc, brgSourceSD);
    }

    // glide slope
    { 
        LCreal gsDev = LCreal(alim (gsDots, 2.1f) * 0.35f);
        send("glideslopedev", UPDATE_VALUE2, gsDev, glideSlopeSD);
    }

    // compass
    {
        // let's do decentered for both, and hsi mode will just set displacement to 0
        send("compass", UPDATE_VALUE6, false, centeredSD);
        // send our compass heading
        send("compass", UPDATE_VALUE, curHdg, compassHdgSD);
    }

    // primary and secondary readout indicators (with asterisk)
    {
        // first of all, which position is the asterisk going in (primary or secondary?)
        send("whichnavsource", SELECT, navSource, whichNavSrcSD);

        // primary nav source selection
        int primaryPos = 1;     // 1 is INAV
        if (navType == VORTAC) {
            // pilot
            if (loc == PILOT) {
                if (vhfLGS) primaryPos = 2;
                else primaryPos = 3;
            }
            // copilot
            else {
                if (vhfLGS) primaryPos = 4;
                else primaryPos = 5;
            }
        }
        else if (navType == TACAN) primaryPos = 6;

        send("whichprimaryreadout", SELECT, primaryPos, primaryPosSD);

        // now do our secondary source selections
        int secondaryPos = 1;

        if (secNavType == VORTAC) {
            // pilot
            if (loc == PILOT) {
                if (secVhfLGS) secondaryPos = 2;
                else secondaryPos = 3;
            }
            // copilot
            else {
                if (secVhfLGS) secondaryPos = 4;
                else secondaryPos = 5;
            }
        }
        else if (secNavType == TACAN) secondaryPos = 6;
        send("whichsecondaryreadout", SELECT, secondaryPos, secondaryPosSD);
    }

    // TO / FROM arrow - HSI mode only
    { 
        LCreal toFrom = 0;
        if (navSource == PRIMARY) toFrom = 1 - lcAbs(lcAepcDeg(bearing - course)) / 90;
        else toFrom = 1 - lcAbs(lcAepcDeg(secBearing - secCourse)) / 90;

        LCreal delta = alim(toFrom - curToFrom, dt);
        curToFrom = alim(curToFrom + delta, 0.65f);
    
        // if we are positive, we are to, negative, from
        bool whichToFrom = (curToFrom > 0);
        send("toorfrom", SELECT, whichToFrom, toOrFromSD);
        
        // now send down where to translate
        send("tofrom", UPDATE_VALUE2, curToFrom, toFromSD);
    }
}

} // end of Demo namespace
} // end of Eaagles namespace
