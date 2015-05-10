#define TEST_ND

#include "TestSD.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/units/Angles.h"
#include "SituationalDisplay.h"
#include "openeaagles/basicGL/SymbolLoader.h"

// disable all deprecation warnings for now, until we fix
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Demo {

static const LCreal refLat =   41.1f;
static const LCreal refLon =  111.9f;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestSD,"TestSD")
EMPTY_SERIALIZER(TestSD)

// Test event handler
BEGIN_EVENT_HANDLER(TestSD)
    ON_EVENT('r', onToggleRange)
END_EVENT_HANDLER()


// navaid names
static const char* navNames[TestSD::MAX_NAV_AIDS] = {
    "VOR1", "VTC1", "TCN1", "VDE1",
    "VOR2", "VTC2", "TCN2", "VDE2",
};

// airport names
static const char* apNames[TestSD::MAX_AIRPORTS] = {
    "AP1", "AP2", "AP3", "AP4",
    "AP5", "AP6", "AP7", "AP8",
};

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestSD::TestSD()
{
    STANDARD_CONSTRUCTOR()
    heading = 0.0;
    headingRate = static_cast<LCreal>(0.2f * Basic::Angle::R2DCC);
    bearing = 0.0;
    bearingRate = static_cast<LCreal>(0.4f * Basic::Angle::R2DCC);
    range = 80.0;
    // navaid bearings
    nav1Brg = 0.0;
    nav1BrgRate = 4.0;
    nav2Brg = 0.0;
    nav2BrgRate = 6.0;
    // orbit range
    orbRange = 5.0;
    // heading
    hdgBug = 0.0;
    hdgBugRate = 2.0;

    // initialize our air tracks to test data
    {
        double trkX = 0.0;
        double trkY = 0.0;
        LCreal hdg = 0.0;
        int myType = 1;
        for (int i = 0; i < MAX_TRACKS; i++) {
            myTracks[i].x = trkX;
            myTracks[i].y = trkY;
            myTracks[i].hdg = hdg;
            myTracks[i].type = myType;
            lcStrcpy(myTracks[i].id, sizeof(myTracks[i].id), "");
            trkX += 6.0;
            trkY -= 6.0;
            hdg += 45.0f;
            if (hdg > 360.0f) hdg -= 360.0f;
            if (myType < 4) myType++;
            else myType = 1;
        }
        tracksLoaded = false;
    }

    // initialize our airports to test data
    {
        double apLat = refLat + 0.1;
        double apLon = refLon;
        int myType = 1;
        for (int i = 0; i < MAX_NAV_AIDS; i++) {
            myAP[i].x = apLat;
            myAP[i].y = apLon;
            myAP[i].hdg = 0;
            myAP[i].type = myType;
            if (i < 10) {
                lcStrcpy(myAP[i].id, sizeof(myAP[i].id), apNames[i]);
            }
            else lcStrcpy(myAP[i].id, sizeof(myAP[i].id), "");
            apLat += 0.1;
            //apLon += 0.1;
            if (myType < 4) myType++;
            else myType = 1;
        }
        airportsLoaded = false;
    }

    // initialize our navaids to test data
    {
        double navLat = refLat;
        double navLon = refLon + 0.1;
        int myType = 1;
        for (int i = 0; i < MAX_NAV_AIDS; i++) {
            myNA[i].x = navLat;
            myNA[i].y = navLon;
            myNA[i].hdg = 0;
            myNA[i].type = myType;
            if (i < 10) {
                lcStrcpy(myNA[i].id, sizeof(myNA[i].id), navNames[i]);
            }
            else lcStrcpy(myNA[i].id, sizeof(myNA[i].id), "");
            //navLat += 0.1;
            navLon += 0.1;
            if (myType < 4) myType++;
            else myType = 1;
        }
        navAidsLoaded = false;
    }
}

//------------------------------------------------------------------------------
// copyData() -- copy this object's data
//------------------------------------------------------------------------------
void TestSD::copyData(const TestSD& org, const bool)
{
    // Always copy base class stuff first
    BaseClass::copyData(org);
    heading = org.heading;
    headingRate = org.headingRate;
    bearing = org.bearing;
    bearingRate = org.bearingRate;
    range = org.range;
    // tacan and waypoint course
    nav1Brg = org.nav1Brg;
    nav1BrgRate = org.nav1BrgRate;
    nav2Brg = org.nav2Brg;
    nav2BrgRate = org.nav2BrgRate;
    orbRange = org.orbRange;
    // heading
    hdgBug = org.hdgBug;
    hdgBugRate = org.hdgBugRate;
    navAidsLoaded = org.navAidsLoaded;
    airportsLoaded = org.airportsLoaded;
}

//------------------------------------------------------------------------------
//deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void TestSD::deleteData()
{
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void TestSD::updateData(const LCreal dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);

    heading += (headingRate * dt);
    if (heading > 360 || heading < 0) headingRate = -headingRate;
    bearing += (bearingRate * dt);
    if (bearing > 360 || bearing < 0) bearingRate = -bearingRate;


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

    // heading bug
    hdgBug += hdgBugRate *dt;
    if (hdgBug > 360) {
        hdgBug = 360;
        hdgBugRate = -hdgBugRate;
    }
    if (hdgBug < 0) {
        hdgBug = 0;
        hdgBugRate = -hdgBugRate;
    }

    // find our situational display (SD) - we do this because there are too many variables to be set
    // to use send commands for every one, so it's easier just to get a pointer to the object and
    // set the variables using member functions.
    {
    Basic::Pair* pair = findByType(typeid(SituationalDisplay));
        if (pair != 0) {
            SituationalDisplay* p = static_cast<SituationalDisplay*>(pair->object());
            if (p != 0) {
                p->setHeading(heading);
                p->setRange(range);
                p->setNav1Brg(nav1Brg);
                p->setNav2Brg(nav2Brg);
                p->setOrbitRange(orbRange);
                p->setHeadingBug(hdgBug);
                p->setReferenceLat(refLat);
                p->setReferenceLon(refLon);
            }
        }
    }

    // Load test tracks (once)
    if (!tracksLoaded) {
        Basic::Pair* pair = findByName("airTracks");
        if (pair != 0) {
            pair->ref();
            BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
            if (myLoader != 0) {
                for (int i = 0; i < MAX_TRACKS; i++) {
                    int idx = myLoader->addSymbol(myTracks[i].type, myTracks[i].id);
                    myLoader->updateSymbolPositionXY(idx, myTracks[i].x, myTracks[i].y);
                    myLoader->updateSymbolHeading(idx, myTracks[i].hdg);
                    //std::cout << "added track: " << myTracks[i].x << ", " <<  myTracks[i].y<< ", " <<  myTracks[i].hdg  << ", " <<  myTracks[i].type << ", " << myTracks[i].id << std::endl;
                }
            }
            pair->unref();
        }
        tracksLoaded = true;
    }

    // Load test airports (once)
    if (!airportsLoaded) {
        Basic::Pair* pair = findByName("airports");
        if (pair != 0) {
            pair->ref();
            BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
            if (myLoader != 0) {
                for (int i = 0; i < MAX_AIRPORTS; i++) {
                    int idx = myLoader->addSymbol(myAP[i].type, myAP[i].id);
                    myLoader->updateSymbolPositionLL(idx, myAP[i].x, myAP[i].y);
                    //std::cout << "added airport: " << myAP[i].x << ", " <<  myAP[i].y << ", " <<  myAP[i].type << ", " << myAP[i].id << std::endl;
                }
            }
            pair->unref();
        }
        airportsLoaded = true;
    }

    // Load test navaids (once)
    if (!navAidsLoaded) {
        Basic::Pair* pair = findByName("navaids");
        if (pair != 0) {
            pair->ref();
            BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
            if (myLoader != 0) {
                for (int i = 0; i < MAX_NAV_AIDS; i++) {
                    int idx = myLoader->addSymbol(myNA[i].type, myNA[i].id);
                    myLoader->updateSymbolPositionLL(idx, myNA[i].x, myNA[i].y);
                    //std::cout << "added navaid: " << myNA[i].x << ", " <<  myNA[i].y << ", " <<  myNA[i].type << ", " << myNA[i].id << std::endl;
                }
            }
            pair->unref();
        }
        navAidsLoaded = true;
    }
}

// Test event handler
bool TestSD::onToggleRange()
{
    if (range >= 160) range = 10;
    else range *= 2;
    return true;
}

} // end of Demo namespace
} // end of Eaagles namespace

