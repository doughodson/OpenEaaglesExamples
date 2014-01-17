//------------------------------------------------------------------------------
// Class: SituationalDisplay
//------------------------------------------------------------------------------
#include "SituationalDisplay.h"

// disable all deprecation warnings for now, until we fix
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(SituationalDisplay,"SituationalDisplay")
EMPTY_SERIALIZER(SituationalDisplay)
                           
//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SituationalDisplay::SituationalDisplay()
{
    STANDARD_CONSTRUCTOR()

    refLat = 0;
    refLon = 0;
    heading = 0;
    headingSD.empty();
    range = 80;
    rangeSD.empty();
    // navaid 1 
    nav1Brg = 0;
    nav1Dme = 0; 
    nav1Id[0] = ' ';
    nav1Id[1] = '\0';
    nav1BrgROSD.empty();
    nav1BrgSD.empty();
    nav1DmeSD.empty();
    nav1IdSD.empty();
    // navaid 2 
    nav2Brg = 0;
    nav2Dme = 0; 
    nav2Id[0] = ' ';
    nav2Id[1] = '\0';
    nav2BrgROSD.empty();
    nav2BrgSD.empty();
    nav2DmeSD.empty();
    nav2IdSD.empty();
    // orbit range
    orbRange = 5;
    // heading
    hdgBug = 0;
    hdgBugSD.empty();
    hdgBugROSD.empty();
    // plane alt
    planeAlt = 1000;
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

//------------------------------------------------------------------------------
// copyData() -- copy this object's data
//------------------------------------------------------------------------------
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
    strncpy(nav1Id, org.nav1Id, NCHAR_NAV1_ID);
    nav1BrgROSD.empty();
    nav1BrgSD.empty();
    nav1DmeSD.empty();
    nav1IdSD.empty();
    // navaid 2 
    nav2Brg = org.nav2Brg;
    nav2Dme = org.nav2Dme;
    strncpy(nav2Id, org.nav2Id, NCHAR_NAV2_ID);
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

//------------------------------------------------------------------------------
//deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void SituationalDisplay::deleteData()
{
}

//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
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
bool SituationalDisplay::setHeading(const LCreal newH)
{
    heading = newH;
    return true;
}
bool SituationalDisplay::setRange(const LCreal newR)
{
    range = newR;
    return true;
}
bool SituationalDisplay::setOrbitRange(const LCreal newOR)
{
    orbRange = newOR;
    return true;
}
bool SituationalDisplay::setHeadingBug(const LCreal newHB)
{
    hdgBug = newHB;
    return true;
}
bool SituationalDisplay::setNav1Brg(const LCreal newB)
{
    nav1Brg = newB;
    return true;
}
bool SituationalDisplay::setNav1Dme(const LCreal newDME)
{
    nav1Dme = newDME;
    return true;
}
bool SituationalDisplay::setNav1Id(const char* const newId)
{
    bool ok = false;
    if (newId != 0) {
        strncpy(nav1Id,newId,NCHAR_NAV1_ID);
        nav1Id[NCHAR_NAV1_ID] = '\0';
        ok = true;
    }
    return ok;
}
bool SituationalDisplay::setNav2Brg(const LCreal newB)
{
    nav2Brg = newB;
    return true;
}
bool SituationalDisplay::setNav2Dme(const LCreal newDME)
{
    nav2Dme = newDME;
    return true;
}
bool SituationalDisplay::setNav2Id(const char* const newId)
{
    bool ok = false;
    if (newId != 0) {
        strncpy(nav2Id,newId,NCHAR_NAV2_ID);
        nav2Id[NCHAR_NAV2_ID] = '\0';
        ok = true;
    }
    return ok;
}

// Get functions
bool SituationalDisplay::getNav1Id(const int index, char* newString)
{
    bool ok = false;
    if (newString != 0 && nav1Id[index] != 0) {
        lcStrcpy(newString, sizeof(newString), &nav1Id[index]);
        ok = true;
    }
    return ok;
}
bool SituationalDisplay::getNav2Id(const int index, char* newString)
{
    bool ok = false;
    if (newString != 0 && nav2Id[index] != 0) {
        lcStrcpy(newString, sizeof(newString), &nav2Id[index]);
        ok = true;
    }
    return ok;
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void SituationalDisplay::updateData(const LCreal dt)
{
    // update our BaseClass
    BaseClass::updateData(dt);
        
    // update our map page 
    send("mainmap", UPDATE_VALUE, range, rangeSD);
    send("mainmap", UPDATE_VALUE2, heading, headingSD);
    send("mainmap", UPDATE_VALUE3, (LCreal)refLat, refLatSD);
    send("mainmap", UPDATE_VALUE4, (LCreal)refLon, refLonSD);
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

}; // end of Demo namespace
}; // end of Eaagles Namespace

