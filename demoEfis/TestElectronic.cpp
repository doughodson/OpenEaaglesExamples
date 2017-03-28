
#include "TestElectronic.hpp"

#include "openeaagles/base/util/enum_utils.hpp"
#include "openeaagles/base/units/LinearVelocity.hpp"

#include "openeaagles/base/util/math_utils.hpp"
#include "openeaagles/base/units/angle_utils.hpp"

#include <cmath>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestElectronic, "TestElectronic")
EMPTY_SERIALIZER(TestElectronic)
EMPTY_DELETEDATA(TestElectronic)

TestElectronic::TestElectronic()
{
    STANDARD_CONSTRUCTOR()
}

void TestElectronic::copyData(const TestElectronic& org, const bool)
{
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

void TestElectronic::updateTestValues(const double dt)
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
    secBearing = bearing * 0.9;

    // course && nav type
    course += 10 * dt;
    if (course > 360) course = 0;
    // testing the secondary course
    secCourse = course * 0.9;

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
    secCdi = cdi * 1.1;

    dist += distRate * dt;
    if (dist > 999.9) {
        dist = 999.9;
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
        readoutMode = ReadoutMode::ND_TTG;
        // change our nav type here, just to test
        navType = NavType::VORTAC;
        secNavType = NavType::TACAN;
    }
    else if (windSpeed > 400) {
        readoutMode = ReadoutMode::ND_GSP;
        // change our nav type here, just to test
        navType = NavType::TACAN;
        secNavType = NavType::INAV;
    }
    else if (windSpeed > 300) {
        readoutMode = ReadoutMode::ND_TAS;
        // change our nav type here, just to test
        navType = NavType::INAV;
        secNavType = NavType::VORTAC;
    }
    else if (windSpeed > 200) {
        readoutMode = ReadoutMode::ND_ET;
        // change our nav type here, just to test
        navType = NavType::VORDME;
        secNavType = NavType::VOR;
    }
    else if (windSpeed > 100) {
        readoutMode = ReadoutMode::ND_WIND;
        // change our nav type here, just to test
        navType = NavType::VOR;
        secNavType = NavType::TACAN;
    }
    else {
        readoutMode = ReadoutMode::ND_TTG;
        navType = NavType::VORTAC;
        secNavType = NavType::TACAN;
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

void TestElectronic::updateData(const double dt)
{
    BaseClass::updateData(dt);

    updateTestValues(dt);

    // current heading / current heading bug
    {
        // max rate here is 120 degs / second
        double delta = oe::base::alim(oe::base::angle::aepcdDeg(heading - curHdg), 120 * dt);
        curHdg = oe::base::angle::aepcdDeg(curHdg + delta);

        // now figure our heading bug
        delta = oe::base::alim(oe::base::angle::aepcdDeg(headingBug - curBug), 120 * dt);
        curBug = oe::base::angle::aepcdDeg(curBug + delta);

        if (navMode == NavMode::ARC_MODE) {
            // we either move it to the left or right, depending on how far
            // off our slew is.
            double diff = oe::base::angle::aepcdDeg(curHdg - curBug);
            double moveX = -1.8f;
            if (diff >= -36 && diff < 36) {
                if (diff > 0) moveX = 1.53;
                else moveX = -1.8;
            }

            auto tempCurBug = static_cast<int>(curBug);
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
        double curDist = oe::base::alim(dist, 999.9);    // current distance to DME

        if (navSource == NavSource::PRIMARY) {
            // valid DME makes our label visible
            distVis = dmeValid;
            if (navType == NavType::INAV) distType = false;
        }
        else if (navSource == NavSource::SECONDARY) {
            // valid DME makes our label visible
            distVis = secDmeValid;
            if (secNavType == NavType::INAV) distType = false;
            else distVis = true;
        }

        send("distlabel", SELECT, distType, distTypeSD);
        send("distval", SET_VISIBILITY, distVis, distVisSD);
        send("distval", UPDATE_VALUE, curDist, curDistSD);
    }

    // course data
    {
        // which course pointer are we using?
        send("whichcourseptr", SELECT, base::as_integer(navSource), whichCrsPtrSD);

        int curIntCourse = 0;
        double tempCDI = 0.0;
        double tempCourse = 0.0;
        // primary nav course
        if (navSource == NavSource::PRIMARY) {
            curIntCourse = oe::base::nint(course);
            tempCDI = cdi;
            tempCourse = course;
        }
        // secondary nav course
        else {
            curIntCourse = oe::base::nint(secCourse);
            tempCDI = secCdi;
            tempCourse = secCourse;
        }

        if (curIntCourse < 0) curIntCourse += 360;
        // send the course readout
        send("course", UPDATE_VALUE, curIntCourse, courseSD);

        // here is the course deviation
        double delta = oe::base::alim (oe::base::angle::aepcdDeg(tempCDI - curCdi), 4 * dt);
        curCdi = oe::base::alim (curCdi + delta, 2.0);

        // now find our inches to translate the cdi
        double cdiInch = curCdi * 0.43f;

        // now figure our course slew
        delta = oe::base::alim(oe::base::angle::aepcdDeg(tempCourse - curCourse), 120 * dt);
        curCourse = (oe::base::angle::aepcdDeg(curCourse + delta));

        // ok, do our color determination for the course pointer - primary first
        if (navSource == NavSource::PRIMARY) {
            // dealing with our primary course pointer here
            bool vis = true;
            if (navMode == NavMode::MAP_MODE || navMode == NavMode::DECLUTTER) vis = false;
            send("primarycoursepointer", SET_VISIBILITY, vis, primaryCrsVisSD);
            // course pointer deviation and rotation
            send("primarycoursedev", UPDATE_VALUE, cdiInch, priCourseDevSD);
            send("primarycoursepointer", UPDATE_VALUE6, heading - curCourse, crsPntrSD);

            // course pointer color
            const auto string = new oe::base::String("white");
            if (navType == NavType::VORTAC) {
                if ((vhfReceive && !(vhfDIC || vhfLGS)) || (vhfLocValid && vhfLGS)) {
                    string->setStr("green");
                } else {
                    string->setStr("yellow");
                }
            }
            else {
                if (dmeValid) {
                    string->setStr("green");
                } else {
                    string->setStr("yellow");
                }
            }

            send("primarycoursepointer", SET_COLOR, string->getString(), priCrsPtrColorSD);
            // get rid of our string
            string->unref();
        }
        else {
            // secondary course pointer
            bool vis = true;
            if (secNavMode == NavMode::MAP_MODE || secNavMode == NavMode::DECLUTTER) {
                vis = false;
            }
            send("secondarycoursepointer", SET_VISIBILITY, vis, secondaryCrsVisSD);
            // course pointer deviation and rotation
            send("secondarycoursedev", UPDATE_VALUE, cdiInch, secCourseDevSD);
            send("secondarycoursepointer", UPDATE_VALUE2, curCourse - heading, secCrsPntrSD);

            // course pointer color
            const auto string = new oe::base::String("white");
            if (secNavType == NavType::VORTAC) {
                if ((secVhfReceive && !(secVhfDIC || secVhfLGS)) || (secVhfLocValid && secVhfLGS)) string->setStr("green");
                else string->setStr("yellow");
            }
            else {
                if (secDmeValid) {
                    string->setStr("green");
                } else {
                    string->setStr("yellow");
                }
            }

            send("secondarycoursepointer", SET_COLOR, string->getString(), secCrsPtrColorSD);
            // get rid of our string
            string->unref();
        }
    }

    // our data readouts (TTG, Gs, etc...)
    {
        // which readout are we using
        send("whichlabel", SELECT, base::as_integer(readoutMode), roLabelSD);
        // send which readout we are going to use
        send("whichreadout", SELECT, base::as_integer(readoutMode), roWhichSD);

        // first readout, which is our time to go
        if (readoutMode == ReadoutMode::ND_TTG) {
            const double curTTG = timeToGo / 60.0;
            send("ttg", UPDATE_VALUE, curTTG, ttgSD);
        }
        // ground speed, drift angle, drift angle side.
        else if (readoutMode == ReadoutMode::ND_GSP) {
            // ground speed
            send("groundspeed", UPDATE_VALUE, groundSpeed, groundSpeedSD);
            // drift angle
            send("driftangle", UPDATE_VALUE, std::abs(driftAngle), driftAngleSD);
            if (driftAngle < 0) send("driftangleside", SELECT, true, driftAngSideSD);
            else send("driftangleside", SELECT, false, driftAngSideSD);
        }
        // true air speed
        else if (readoutMode == ReadoutMode::ND_TAS) {
            int curTAS = oe::base::nintd(trueAirSpeed * oe::base::LinearVelocity::FPS2KTSCC);
            send("trueairspeed", UPDATE_VALUE, curTAS, trueAirSpeedSD);
        }
        // elapsed time
        else if (readoutMode == ReadoutMode::ND_ET) {
            const auto hour = static_cast<int>(elapsedTime / 3600);
            bool isMin = false;    // default to show hours
            if (hour < 1) {
                isMin = true; // show in minutes
                send("elapsedtimemin", UPDATE_VALUE, elapsedTime, elapsedTimeSD);
            } else
                send("elapsedtimehour", UPDATE_VALUE, elapsedTime, elapsedTimeHRSD);

            // send which readout
            send("whichelapsedtimero", SELECT, isMin, whichETSD);
        }
        // wind speed, direction, and drift angle (again)
        else if (readoutMode == ReadoutMode::ND_WIND) {
            // wind direction
            send("winddirection", UPDATE_VALUE, windDir, windDirectionSD);
            // wind speed
            send("windspeed", UPDATE_VALUE, windSpeed, windSpeedSD);
            // wind drift angle (same as drift angle for test purposes)
            send("driftanglewind", UPDATE_VALUE, std::abs(driftAngle), driftAngleWindSD);
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
        if (navSource == NavSource::PRIMARY) {
            if (navType == NavType::VORTAC) brgSrc = 2;     // primary vortac
            else if (navType == NavType::TACAN) brgSrc = 3; // primary tacan
            send("bearingro", UPDATE_VALUE, bearing, brgROSD);
        }
        else {
            if (secNavType == NavType::VORTAC) brgSrc = 4; // secondary vortac
            else brgSrc = 5; // secondary tacan
            send("bearingro", UPDATE_VALUE, secBearing, secBrgROSD);
        }

        send("bearingsource", SELECT, brgSrc, brgSourceSD);
    }

    // glide slope
    {
        const auto gsDev = static_cast<double>(oe::base::alim (gsDots, 2.1f) * 0.35f);
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
        send("whichnavsource", SELECT, base::as_integer(navSource), whichNavSrcSD);

        // primary nav source selection
        int primaryPos = 1;     // 1 is INAV
        if (navType == NavType::VORTAC) {
            // pilot
            if (loc == Location::PILOT) {
                if (vhfLGS) primaryPos = 2;
                else primaryPos = 3;
            }
            // copilot
            else {
                if (vhfLGS) primaryPos = 4;
                else primaryPos = 5;
            }
        }
        else if (navType == NavType::TACAN) primaryPos = 6;

        send("whichprimaryreadout", SELECT, primaryPos, primaryPosSD);

        // now do our secondary source selections
        int secondaryPos = 1;

        if (secNavType == NavType::VORTAC) {
            // pilot
            if (loc == Location::PILOT) {
                if (secVhfLGS) secondaryPos = 2;
                else secondaryPos = 3;
            }
            // copilot
            else {
                if (secVhfLGS) secondaryPos = 4;
                else secondaryPos = 5;
            }
        }
        else if (secNavType == NavType::TACAN) secondaryPos = 6;
        send("whichsecondaryreadout", SELECT, secondaryPos, secondaryPosSD);
    }

    // TO / FROM arrow - HSI mode only
    {
        double toFrom = 0;
        if (navSource == NavSource::PRIMARY) toFrom = 1 - std::fabs(oe::base::angle::aepcdDeg(bearing - course)) / 90;
        else toFrom = 1 - std::fabs(oe::base::angle::aepcdDeg(secBearing - secCourse)) / 90;

        double delta = oe::base::alim(toFrom - curToFrom, dt);
        curToFrom = oe::base::alim(curToFrom + delta, 0.65);

        // if we are positive, we are to, negative, from
        bool whichToFrom = (curToFrom > 0);
        send("toorfrom", SELECT, whichToFrom, toOrFromSD);

        // now send down where to translate
        send("tofrom", UPDATE_VALUE2, curToFrom, toFromSD);
    }
}
