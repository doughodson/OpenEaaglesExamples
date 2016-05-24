//------------------------------------------------------------------------------
// Class: TestCompass
//
// Description: This page will test the CompassRose
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestCompass_H__
#define __oe_demo_TestCompass_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestCompass : public graphics::Page
{
   DECLARE_SUBCLASS(TestCompass, graphics::Page)

public:
    TestCompass();

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, base::Object* const obj = nullptr) override;

    static const int MAX_TRACKS = 8;
    static const int MAX_AIRPORTS = 8;
    static const int MAX_NAV_AIDS = 8;

private:
    bool onToggleRangeTestCompass();
    bool onToggleCenteredTestCompass();
    bool onToggleViews();

    double heading;             // our gauge position (inches)
    SendData headingSD;
    SendData headingCRSD;       // compass rose send data
    SendData headingBRGSD;      // our bearing's heading value
    SendData isCenteredCRSD;    // compass rose is centered flag
    SendData isCenteredBRGSD;   // bearing is centered flag
    double  headingRate;        // rate which are going (up or down)
    double bearing;             // goes to our bearing pointer
    SendData bearingBRGSD;
    SendData bearingROSD;
    double bearingRate;
    SendData headingROSD;       // our heading readout
    double range;               // our range
    SendData rangeSD;
    SendData rangeROSD;

    bool centered;
    SendData centeredSD;
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

}
}

#endif

