
#include "TestCompass.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/graphics/MapPage.hpp"
#include "openeaagles/graphics/SymbolLoader.hpp"
#include "openeaagles/base/Rgb.hpp"

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestCompass, "TestCompass")
EMPTY_SERIALIZER(TestCompass)
EMPTY_DELETEDATA(TestCompass)

BEGIN_EVENT_HANDLER(TestCompass)
    ON_EVENT('r', onToggleRangeTestCompass)
    ON_EVENT('d', onToggleCenteredTestCompass)
END_EVENT_HANDLER()

static const double refLat = 0;
static const double refLon = 0;

// navaid names
static const char* navNames[TestCompass::MAX_NAV_AIDS] = {
    "VOR1", "VTC1", "TCN1", "VDE1",
    "VOR2", "VTC2", "TCN2", "VDE2",
};

// airport names
static const char* apNames[TestCompass::MAX_AIRPORTS] = {
    "AP1", "AP2", "AP3", "AP4",
    "AP5", "AP6", "AP7", "AP8",
};

TestCompass::TestCompass()
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
            if (hdg > 360.0f) hdg -= 360.0f;
            if (myType < 4) myType++;
            else myType = 1;
        }
        tracksLoaded = false;
    }

    // initialize our airport to test data
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

void TestCompass::copyData(const TestCompass& org, const bool)
{
    // copy our baseclass stuff first
    BaseClass::copyData(org);
    heading = org.heading;
    headingSD.empty();
    headingRate = org.headingRate;
    headingROSD.empty();
    bearing = org.bearing;
    bearingRate = org.bearingRate;
    bearingBRGSD.empty();
    bearingROSD.empty();
    range = org.range;
    rangeSD.empty();
    rangeROSD.empty();
    centered = org.centered;
    headingCRSD.empty();
    isCenteredCRSD.empty();
    navAidsLoaded = org.navAidsLoaded;
    airportsLoaded = org.airportsLoaded;
    headingBRGSD.empty();
    isCenteredBRGSD.empty();
}

void TestCompass::updateData(const double dt)
{
    BaseClass::updateData(dt);

    heading += (headingRate * dt);
    if (heading > 360.0 || heading < 0.0) headingRate = -headingRate;
    bearing += (bearingRate * dt);
    if (bearing > 6.28 || bearing < 0.0) bearingRate = -bearingRate;

    // Load test tracks (once) - load the default (0)
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
                    myLoader->updateSymbolText(idx, "name", myAP[i].id);
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
                    myLoader->updateSymbolText(idx, "name", myNA[i].id);
                    //std::cout << "added navaid: " << myNA[i].x << ", " <<  myNA[i].y << ", " <<  myNA[i].type << ", " << myNA[i].id << std::endl;
                }
            }
            pair->unref();
        }
        navAidsLoaded = true;
    }

    // send our data down to our map page parent, who will update the rest of the map pages
    // UPDATE_VALUE = range, UPDATE_VALUE2 = heading, UPDATE_VALUE3 = centered
    send("mappage", UPDATE_VALUE, range, rangeSD);
    send("mappage", UPDATE_VALUE2, heading, headingSD);
    send("mappage", UPDATE_VALUE5, centered, centeredSD);

    // send our bearing and compass rose the same values
    send("bearing", UPDATE_VALUE7, bearing, bearingBRGSD);
    send("bearing", UPDATE_VALUE6, centered, isCenteredBRGSD);

    // send our data down to our compass rose, if we have one
    send("compassrose", UPDATE_VALUE, heading, headingCRSD);
    send("compassrose", UPDATE_VALUE6, centered, isCenteredCRSD);

    // here is the compass rose display readouts
    send("compassRO", UPDATE_VALUE, heading, headingROSD);
//    send("bearingRO", UPDATE_VALUE, bearing * base::Angle::R2DCC, bearingROSD);
    send("rangeRO", UPDATE_VALUE, range, rangeROSD);
}

// Test event handler
bool TestCompass::onToggleRangeTestCompass()
{
    if (range >= 160.0) range = 10.0;
    else range *= 2.0;
    return true;
}
bool TestCompass::onToggleCenteredTestCompass()
{
    centered = !centered;
    return true;
}
