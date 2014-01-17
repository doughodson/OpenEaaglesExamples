//------------------------------------------------------------------------------
// Class: SituationalDisplay
//
// Description: Situational Display
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_SituationalDisplay_H__
#define __Eaagles_Demo_SituationalDisplay_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class SituationalDisplay : public BasicGL::Page
{
   DECLARE_SUBCLASS(SituationalDisplay,BasicGL::Page)

    enum { NCHAR_NAV1_ID = 3, NCHAR_NAV2_ID = 5 };

public:
    SituationalDisplay(); 

    // set functions
    virtual bool setReferenceLat(const double newL);      // Sets latitude (degs)
    virtual bool setReferenceLon(const double newL);      // Sets longitude (degs)
    virtual bool setHeading(const LCreal newH);         // Sets heading (degs)
    virtual bool setRange(const LCreal newR);           // Sets Range (NM)
    virtual bool setOrbitRange(const LCreal newOR);     // Orbit range
    virtual bool setHeadingBug(const LCreal newHB);     // Sets heading bug (degs)
    virtual bool setNav1Brg(const LCreal newB);         // Sets navaid 1 bearing (degs)
    virtual bool setNav1Dme(const LCreal newDME);       // Sets navaid 1 DME (NM)
    virtual bool setNav1Id(const char* const newId);    // Sets navaid 1 identifier
    virtual bool setNav2Brg(const LCreal newB);         // Sets navaid 2 bearing (degs)
    virtual bool setNav2Dme(const LCreal newDME);       // Sets navaid 2 DME (NM)
    virtual bool setNav2Id(const char* const newId);    // Sets navaid 2 identifier

    // get functions
    double getOwnshipLat()      { return refLat; }
    double getOwnshipLon()      { return refLon; }
    LCreal getHeading()         { return heading; }
    LCreal getRange()           { return range; }
    LCreal getOrbitRange()      { return orbRange; }
    LCreal getHdgBug()          { return hdgBug; }
    LCreal getNav1Brg()         { return nav1Brg; }
    LCreal getNav1Dme()         { return nav1Dme; }
    bool getNav1Id(const int index, char* newString);
    LCreal getNav2Brg()         { return nav2Brg; }
    LCreal getNav2Dme()         { return nav2Dme; }
    bool getNav2Id(const int index, char* newString);

    // Basic::Component Interface
    virtual void updateData(const LCreal dt = 0);

private:
    double refLat;              // latitude
    double refLon;              // longitude
    
    LCreal heading;             // our heading (degs)
    SendData headingROSD;
    LCreal range;               // our range (NM)
    SendData rangeROSD;
    LCreal orbRange;            // our orbit range

    // Heading bug
    LCreal hdgBug;              // selected heading bug (degs)
    SendData hdgBugSD;
    SendData hdgBugROSD;

    // navaid 1 
    LCreal nav1Brg;       // degs
    LCreal nav1Dme;       // Nm
    char   nav1Id[NCHAR_NAV1_ID+1];   // ID
    SendData nav1DmeSD;
    SendData nav1BrgROSD;
    SendData nav1BrgSD;
    SendData nav1IdSD;

    // map page stuff
    SendData headingSD;
    SendData rangeSD;
    SendData refLatSD;
    SendData refLonSD;
    SendData centeredSD;

    // navaid 2 
    LCreal nav2Brg;       // degs
    LCreal nav2Dme;       // Nm
    char   nav2Id[NCHAR_NAV2_ID+1];   // TACAN ID
    SendData nav2DmeSD;
    SendData nav2BrgROSD;
    SendData nav2BrgSD;
    SendData nav2IdSD;

    // Terrain follower
    LCreal planeAlt;   
    SendData planeAltSD;
    SendData headingCRSD;    
};

}; // end of Demo namespace
}; // end of Eaagles namespace

#endif

