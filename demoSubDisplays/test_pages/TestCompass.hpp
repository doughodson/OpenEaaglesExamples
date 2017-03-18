
#ifndef __TestCompass_H__
#define __TestCompass_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestCompass
//
// Description: This page will test the CompassRose
//------------------------------------------------------------------------------
class TestCompass : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestCompass, oe::graphics::Page)

public:
    TestCompass();

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

    static const int MAX_TRACKS = 8;
    static const int MAX_AIRPORTS = 8;
    static const int MAX_NAV_AIDS = 8;

private:
    bool onToggleRangeTestCompass();
    bool onToggleCenteredTestCompass();
    bool onToggleViews();

    double heading {};           // our gauge position (inches)
    double  headingRate {10.0};  // rate which are going (up or down)
    SendData headingSD;
    SendData headingCRSD;        // compass rose send data
    SendData headingBRGSD;       // our bearing's heading value
    SendData headingROSD;        // our heading readout

    SendData isCenteredCRSD;     // compass rose is centered flag
    SendData isCenteredBRGSD;    // bearing is centered flag

    double bearing {};           // goes to our bearing pointer
    double bearingRate {0.4};
    SendData bearingBRGSD;
    SendData bearingROSD;

    double range {10.0};         // our range
    SendData rangeSD;
    SendData rangeROSD;

    bool centered {true};
    SendData centeredSD;

    struct mySymbols {
        double x {};       // X position or latitude
        double y {};       // Y position or longitude
        double hdg {};     // heading (degs)
        int    type {1};   // numeric type (for looking up in slottable)
        char   id[8] {};   // name of the airport (up to 8 characters)
    };

    // air track
    mySymbols myTracks[MAX_TRACKS];     // holds our track data
    bool tracksLoaded {};               // tracks have been loaded

    // airport
    mySymbols myAP[MAX_AIRPORTS];       // holds our airport data
    bool airportsLoaded {};             // airports have been loaded

    // navaid
    mySymbols myNA[MAX_NAV_AIDS];       // holds our navaid data
    bool navAidsLoaded {};              // navaids have been loaded
};

#endif
