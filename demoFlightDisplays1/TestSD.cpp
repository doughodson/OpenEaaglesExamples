
#define TEST_ND

#include "TestSD.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/units/angle_utils.hpp"
#include "SituationalDisplay.hpp"
#include "openeaagles/graphics/SymbolLoader.hpp"

using namespace oe;

static const double refLat =   41.1f;
static const double refLon =  111.9f;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestSD, "TestSD")
EMPTY_SERIALIZER(TestSD)
EMPTY_DELETEDATA(TestSD)

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

TestSD::TestSD()
{
    STANDARD_CONSTRUCTOR()

    // initialize our air tracks to test data
    {
        double trkX {};
        double trkY {};
        double hdg {};
        int myType {1};
        for (int i = 0; i < MAX_TRACKS; i++) {
            myTracks[i].x = trkX;
            myTracks[i].y = trkY;
            myTracks[i].hdg = hdg;
            myTracks[i].type = myType;
            base::utStrcpy(myTracks[i].id, sizeof(myTracks[i].id), "");
            trkX += 6.0;
            trkY -= 6.0;
            hdg += 45.0f;
            if (hdg > 360.0) hdg -= 360.0;
            if (myType < 4) myType++;
            else myType = 1;
        }
        tracksLoaded = false;
    }

    // initialize our airports to test data
    {
        double apLat {refLat + 0.1};
        double apLon {refLon};
        int myType {1};
        for (int i = 0; i < MAX_NAV_AIDS; i++) {
            myAP[i].x = apLat;
            myAP[i].y = apLon;
            myAP[i].hdg = 0;
            myAP[i].type = myType;
            if (i < 10) {
                base::utStrcpy(myAP[i].id, sizeof(myAP[i].id), apNames[i]);
            }
            else base::utStrcpy(myAP[i].id, sizeof(myAP[i].id), "");
            apLat += 0.1;
            //apLon += 0.1;
            if (myType < 4) myType++;
            else myType = 1;
        }
        airportsLoaded = false;
    }

    // initialize our navaids to test data
    {
        double navLat {refLat};
        double navLon {refLon + 0.1};
        int myType {1};
        for (int i = 0; i < MAX_NAV_AIDS; i++) {
            myNA[i].x = navLat;
            myNA[i].y = navLon;
            myNA[i].hdg = 0;
            myNA[i].type = myType;
            if (i < 10) {
                base::utStrcpy(myNA[i].id, sizeof(myNA[i].id), navNames[i]);
            }
            else base::utStrcpy(myNA[i].id, sizeof(myNA[i].id), "");
            //navLat += 0.1;
            navLon += 0.1;
            if (myType < 4) myType++;
            else myType = 1;
        }
        navAidsLoaded = false;
    }
}

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

void TestSD::updateData(const double dt)
{
    BaseClass::updateData(dt);

    heading += (headingRate * dt);
    if (heading > 360.0 || heading < 0.0) headingRate = -headingRate;
    bearing += (bearingRate * dt);
    if (bearing > 360.0 || bearing < 0.0) bearingRate = -bearingRate;


    nav1Brg += nav1BrgRate * dt;
    if (nav1Brg > 360.0) {
        nav1Brg = 360.0;
        nav1BrgRate = -nav1BrgRate;
    }
    if (nav1Brg < 0.0) {
        nav1Brg = 0.0;
        nav1BrgRate = -nav1BrgRate;
    }

    nav2Brg += nav2BrgRate * dt;
    if (nav2Brg > 360.0) {
        nav2Brg = 360.0;
        nav2BrgRate = -nav2BrgRate;
    }
    if (nav2Brg < 0.0) {
        nav2Brg = 0.0;
        nav2BrgRate = -nav2BrgRate;
    }

    // heading bug
    hdgBug += hdgBugRate *dt;
    if (hdgBug > 360.0) {
        hdgBug = 360.0;
        hdgBugRate = -hdgBugRate;
    }
    if (hdgBug < 0.0) {
        hdgBug = 0.0;
        hdgBugRate = -hdgBugRate;
    }

    // find our situational display (SD) - we do this because there are too many variables to be set
    // to use send commands for every one, so it's easier just to get a pointer to the object and
    // set the variables using member functions.
    {
    base::Pair* pair = findByType(typeid(SituationalDisplay));
        if (pair != nullptr) {
            const auto p = static_cast<SituationalDisplay*>(pair->object());
            if (p != nullptr) {
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
        base::Pair* pair = findByName("airTracks");
        if (pair != nullptr) {
            pair->ref();
            const auto myLoader = dynamic_cast<graphics::SymbolLoader*>(pair->object());
            if (myLoader != nullptr) {
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
        base::Pair* pair = findByName("airports");
        if (pair != nullptr) {
            pair->ref();
            const auto myLoader = dynamic_cast<graphics::SymbolLoader*>(pair->object());
            if (myLoader != nullptr) {
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
        base::Pair* pair = findByName("navaids");
        if (pair != nullptr) {
            pair->ref();
            const auto myLoader = dynamic_cast<graphics::SymbolLoader*>(pair->object());
            if (myLoader != nullptr) {
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
