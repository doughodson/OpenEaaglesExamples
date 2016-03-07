//------------------------------------------------------------------------------
// Class: TestSD
//
// Description: Sends test data down to the situational display
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestSD_H__
#define __oe_demo_TestSD_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestSD : public graphics::Page
{
   DECLARE_SUBCLASS(TestSD, graphics::Page )

public:
    TestSD();

    void updateData(const double dt = 0.0) override;
    bool event(const int event, base::Object* const obj = nullptr) override;

    static const int MAX_TRACKS = 8;
    static const int MAX_AIRPORTS = 8;
    static const int MAX_NAV_AIDS = 8;

private:
    bool onToggleRange();

    double heading;             // our heading
    double headingRate;         // rate which are going (up or down)
    double bearing;             // goes to our bearing pointer
    double bearingRate;
    double range;               // our range
    double nav1Brg;             // navaid 1 bearing pointer
    double nav1BrgRate;
    double nav2Brg;             // waypoint bearing pointer
    double nav2BrgRate;
    double orbRange;            // our orbit range
    double hdgBug;              // selected heading bug
    double hdgBugRate;

    // Structure for our symbol loader
    struct mySymbols {
        double     x;       // X position or latitude
        double     y;       // Y position or longitude
        double     hdg;     // heading (degs)
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

} // end of demo namespace
} // end of oe namespace

#endif

