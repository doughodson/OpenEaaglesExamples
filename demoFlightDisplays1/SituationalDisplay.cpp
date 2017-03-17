
#include "SituationalDisplay.hpp"
#include <cstring>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(SituationalDisplay, "SituationalDisplay")
EMPTY_SERIALIZER(SituationalDisplay)
EMPTY_DELETEDATA(SituationalDisplay)

SituationalDisplay::SituationalDisplay()
{
    STANDARD_CONSTRUCTOR()

    // navaid 1
    nav1Id[0] = ' ';
    nav1Id[1] = '\0';

    // navaid 2
    nav2Id[0] = ' ';
    nav2Id[1] = '\0';
}

void SituationalDisplay::copyData(const SituationalDisplay& org, const bool)
{
    // Always copy base class stuff first
    BaseClass::copyData(org);

    refLat = org.refLat;
    refLon = org.refLon;
    heading = org.heading;
    headingSD.empty();
    range = org.range;
    rangeSD.empty();
    orbRange = org.orbRange;
    // navaid 1
    nav1Brg = org.nav1Brg;
    nav1Dme = org.nav1Dme;
    std::strncpy(nav1Id, org.nav1Id, NCHAR_NAV1_ID);
    nav1BrgROSD.empty();
    nav1BrgSD.empty();
    nav1DmeSD.empty();
    nav1IdSD.empty();
    // navaid 2
    nav2Brg = org.nav2Brg;
    nav2Dme = org.nav2Dme;
    std::strncpy(nav2Id, org.nav2Id, NCHAR_NAV2_ID);
    nav2BrgROSD.empty();
    nav2BrgSD.empty();
    nav2DmeSD.empty();
    nav2IdSD.empty();
    // heading
    hdgBug = org.hdgBug;
    hdgBugSD.empty();
    hdgBugROSD.empty();
    // plane alt
    planeAlt = org.planeAlt;
    planeAltSD.empty();
    // map page
    headingROSD.empty();
    headingSD.empty();
    rangeROSD.empty();
    rangeSD.empty();
    refLatSD.empty();
    refLonSD.empty();
    centeredSD.empty();
    headingCRSD.empty();
}

bool SituationalDisplay::setReferenceLat(const double newL)
{
    refLat = newL;
    return true;
}
bool SituationalDisplay::setReferenceLon(const double newL)
{
    refLon = newL;
    return true;
}
bool SituationalDisplay::setHeading(const double newH)
{
    heading = newH;
    return true;
}
bool SituationalDisplay::setRange(const double newR)
{
    range = newR;
    return true;
}
bool SituationalDisplay::setOrbitRange(const double newOR)
{
    orbRange = newOR;
    return true;
}
bool SituationalDisplay::setHeadingBug(const double newHB)
{
    hdgBug = newHB;
    return true;
}
bool SituationalDisplay::setNav1Brg(const double newB)
{
    nav1Brg = newB;
    return true;
}
bool SituationalDisplay::setNav1Dme(const double newDME)
{
    nav1Dme = newDME;
    return true;
}
bool SituationalDisplay::setNav1Id(const char* const newId)
{
    bool ok = false;
    if (newId != nullptr) {
        std::strncpy(nav1Id,newId,NCHAR_NAV1_ID);
        nav1Id[NCHAR_NAV1_ID] = '\0';
        ok = true;
    }
    return ok;
}
bool SituationalDisplay::setNav2Brg(const double newB)
{
    nav2Brg = newB;
    return true;
}
bool SituationalDisplay::setNav2Dme(const double newDME)
{
    nav2Dme = newDME;
    return true;
}
bool SituationalDisplay::setNav2Id(const char* const newId)
{
    bool ok = false;
    if (newId != nullptr) {
        std::strncpy(nav2Id, newId, NCHAR_NAV2_ID);
        nav2Id[NCHAR_NAV2_ID] = '\0';
        ok = true;
    }
    return ok;
}

// Get functions
bool SituationalDisplay::getNav1Id(const int index, char* newString)
{
    bool ok = false;
    if (newString != nullptr && nav1Id[index] != 0) {
        base::utStrcpy(newString, sizeof(newString), &nav1Id[index]);
        ok = true;
    }
    return ok;
}
bool SituationalDisplay::getNav2Id(const int index, char* newString)
{
    bool ok = false;
    if (newString != nullptr && nav2Id[index] != 0) {
        base::utStrcpy(newString, sizeof(newString), &nav2Id[index]);
        ok = true;
    }
    return ok;
}

void SituationalDisplay::updateData(const double dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);

    // update our map page
    send("mainmap", UPDATE_VALUE, range, rangeSD);
    send("mainmap", UPDATE_VALUE2, heading, headingSD);
    send("mainmap", UPDATE_VALUE3, static_cast<double>(refLat), refLatSD);
    send("mainmap", UPDATE_VALUE4, static_cast<double>(refLon), refLonSD);
    send("mainmap", UPDATE_VALUE5, true, centeredSD);

    // update our compass rose
    send("compassrose", UPDATE_VALUE, heading, headingCRSD);

    // update our terrain follower
    send("tfollow", UPDATE_VALUE, planeAlt, planeAltSD);

    // update our readouts
    send("selhdg", UPDATE_VALUE6, -hdgBug, hdgBugSD);
    send("heading", UPDATE_VALUE, heading, headingROSD);
    send("range", UPDATE_VALUE, range, rangeROSD);
    send("hdgbug", UPDATE_VALUE, hdgBug, hdgBugROSD);

    send("nav1brgro", UPDATE_VALUE, nav1Brg, nav1BrgROSD);
    send("nav1dme", UPDATE_VALUE, nav1Dme, nav1DmeSD);
    send("nav1Id", UPDATE_VALUE, nav1Id, nav1IdSD);
    send("nav1brgptr", UPDATE_VALUE6, -nav1Brg, nav1BrgSD);

    send("nav2brgro", UPDATE_VALUE, nav2Brg, nav2BrgROSD);
    send("nav2dme", UPDATE_VALUE, nav2Dme, nav2DmeSD);
    send("nav2Id", UPDATE_VALUE, nav2Id, nav2IdSD);
    send("nav2brgptr", UPDATE_VALUE6, -nav2Brg, nav2BrgSD);

}
