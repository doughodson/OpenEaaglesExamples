//------------------------------------------------------------------------------
// Class: TestElectronic
//
// Description: Rockwell-Collins Efis test page to stimulate arc mode.
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestElectronic_H__
#define __oe_demo_TestElectronic_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestElectronic : public graphics::Page
{
   DECLARE_SUBCLASS(TestElectronic, graphics::Page)

public:
    TestElectronic();

    virtual void updateData(const double dt = 0.0) override;

private:
    void updateTestValues(const double dt);    // update our data

    double heading;         // our compass heading
    double headingRate;
    double headingBug;      // our heading indicator bug
    SendData headingSD;
    SendData headingBugSD;  // for sending to our heading indicator
    double bearing;         // our bearing
    double secBearing;      // secondary bearing
    double brgRate;
    bool brgVis;            // bearing visibility
    // nav stuff
    int navSource;
    int navType;
    int secNavType;
    int navMode;
    int secNavMode;
    // course and course validity checks
    double course;          // primary course
    double secCourse;       // secondary course
    bool   vhfReceive;
    bool   vhfDIC;
    bool   vhfLocValid;
    bool   vhfLGS;
    bool   dmeValid;
    bool   secVhfReceive;
    bool   secVhfDIC;
    bool   secVhfLocValid;
    bool   secVhfLGS;
    bool   secDmeValid;
    double cdi;
    double cdiRate;
    double secCdi;
    int loc;                // cockpit location (PILOT or COPILOT)
    double dist;               // distance (miles) to our next navaid
    double distRate;
    // data
    double timeToGo;
    double ttgRate;
    double groundSpeed;
    double driftAngle;
    double daRate;
    double trueAirSpeed;
    double tasRate;
    double elapsedTime;
    double etRate;
    double windDir;
    double windSpeed;
    int    readoutMode;         // primary or secondary
    // glideslope
    double gsDots;
    double gsDotsRate;
    bool   vhfGSValid;
    bool   vhfGSOOV;

    // SLS - transfer from Electronic HSI class
    double curHdg;              // current slewed heading
    double curBug;              // current heading bug
    SendData hdgBugROMoveXSD;   // where to move our heading bug readout
    SendData hdgBugROSD;        // heading bug readout
    SendData distTypeSD;        // type of distance data we are using
    SendData distVisSD;         // distance data readout visibility
    SendData curDistSD;         // current distance to navaid
    SendData courseSD;          // our course
    SendData roLabelSD;         // which readout label to display
    SendData roWhichSD;         // actual readout to display
    SendData ttgSD;             // time to go
    SendData groundSpeedSD;     // ground speed
    SendData driftAngleSD;      // drift angle
    SendData driftAngSideSD;    // drift angle side
    SendData trueAirSpeedSD;    // true air speed
    SendData elapsedTimeSD;     // elapsed time (minutes)
    SendData elapsedTimeHRSD;   // elapsed time (hours)
    SendData whichETSD;         // which elapsed time readout
    SendData driftAngleWindSD;  // drift angle for the wind
    SendData whichSideDAWindSD; // drift angle side for the wind
    SendData windDirectionSD;   // wind direction
    SendData windSpeedSD;       // wind speed
    SendData brgSourceSD;       // bearing source
    SendData brgROSD;           // bearing readout
    SendData secBrgROSD;        // secondary bearing readout
    SendData glideSlopeSD;      // glide slope deviation
    SendData centeredSD;        // compass centered (will always be here)
    SendData compassHdgSD;      // compass heading
    SendData hdgBugSD;          // heading bug
    SendData priCourseDevSD;    // primary course deviation
    double curCdi;              // current course deviation
    SendData crsPntrSD;         // course pointer rotation
    SendData whichCrsPtrSD;     // which course pointer (primary or secondary)
    double curCourse;           // current course (for slewing)
    SendData priCrsPtrColorSD;  // primary course pointer color
    SendData secCrsPntrSD;      // secondary course pointer rotation
    SendData secCourseDevSD;    // secondary course pointer deviation
    SendData secCrsPtrColorSD;  // secondary course pointer color
    SendData whichNavSrcSD;     // which nav source are we using (asterisk)
    SendData primaryPosSD;      // primary nav position
    SendData secondaryPosSD;    // secondary nav position
    SendData primaryCrsVisSD;   // primary course visibility
    SendData secondaryCrsVisSD; // secondary course visibility
    double curToFrom;           // current to / from
    SendData toOrFromSD;        // to or from flag
    SendData toFromSD;          // to from translation
};

} // end of demo namespace
} // end of oe namespace

#endif

