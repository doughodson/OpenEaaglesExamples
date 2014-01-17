//------------------------------------------------------------------------------
// Class: TestSD
//
// Description: Sends test data down to the situational display
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestSD_H__
#define __Eaagles_Demo_TestSD_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestSD : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestSD, BasicGL::Page )

public:
    TestSD();     

    // Basic::Component Interface
    virtual void updateData(const LCreal dt = 0);
    virtual bool event(const int event, Basic::Object* const obj = 0);

    static const int MAX_TRACKS = 8;
    static const int MAX_AIRPORTS = 8;
    static const int MAX_NAV_AIDS = 8;
    
private:
    bool onToggleRange();

    LCreal heading;             // our heading
    LCreal headingRate;         // rate which are going (up or down)
    LCreal bearing;             // goes to our bearing pointer
    LCreal bearingRate;
    LCreal range;               // our range
    LCreal nav1Brg;             // navaid 1 bearing pointer
    LCreal nav1BrgRate;
    LCreal nav2Brg;             // waypoint bearing pointer
    LCreal nav2BrgRate;
    LCreal orbRange;            // our orbit range
    LCreal hdgBug;              // selected heading bug
    LCreal hdgBugRate;
    
    // Structure for our symbol loader
    struct mySymbols {
        double     x;       // X position or latitude
        double     y;       // Y position or longitude
        LCreal     hdg;     // heading (degs)
        int       type;     // numeric type (for looking up in slottable)
        char     id[8];     // name of the airport (up to 8 characters)
    };

    // air track stuff
    mySymbols myTracks[MAX_TRACKS];     // holds our track data 
    bool tracksLoaded;                  // tracks have been loaded

    // airport stuff
    mySymbols myAP[MAX_AIRPORTS];       // holds our airport data 
    bool airportsLoaded;                // airports have been loaded

    // navaid stuff
    mySymbols myNA[MAX_NAV_AIDS];       // holds our navaid data 
    bool navAidsLoaded;                 // navaids have been loaded
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

