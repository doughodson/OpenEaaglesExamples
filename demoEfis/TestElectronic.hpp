
#ifndef __TestElectronic_H__
#define __TestElectronic_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestElectronic
//
// Description: Rockwell-Collins Efis test page to stimulate arc mode.
//------------------------------------------------------------------------------
class TestElectronic : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestElectronic, oe::graphics::Page)

public:
    TestElectronic();

    virtual void updateData(const double dt = 0.0) override;

private:

    enum class NavType { VORTAC, TACAN, INAV, VORDME, VOR };
    enum class NavMode { DECLUTTER, MAP_MODE, NORMAL, HSI_MODE, ARC_MODE, ARC_MAP_MODE };
    enum class NavSource { PRIMARY=0, SECONDARY=1 };
    enum class Location { PILOT, COPILOT };
    // readout modes
    // ND_TTG  : time to go
    // ND_GSP  : ground speed/drift angle
    // ND_TAS  : true air speed
    // ND_ET   : elapsed time
    // ND_WIND : wind dir/speed, drift angle
    enum class ReadoutMode { ND_TTG=1, ND_GSP=2, ND_TAS=3, ND_ET=4, ND_WIND=5 };

    void updateTestValues(const double dt);    // update our data

    double heading {};              // our compass heading
    double headingRate {3.0};
    double headingBug {};           // our heading indicator bug
    SendData headingSD;
    SendData headingBugSD;          // for sending to our heading indicator

    double bearing {};              // our bearing
    double secBearing {};           // secondary bearing
    double brgRate {5.0};
    bool brgVis {true};             // bearing visibility

    // nav
    NavSource navSource {NavSource::PRIMARY};
    NavType navType {NavType::TACAN};
    NavType secNavType {NavType::VORTAC};
    NavMode navMode {NavMode::ARC_MODE};
    NavMode secNavMode {NavMode::ARC_MODE};

    // course and course validity checks
    double course {};               // primary course
    double secCourse {};            // secondary course
    bool   vhfReceive {true};
    bool   vhfDIC {true};
    bool   vhfLocValid {true};
    bool   vhfLGS {true};
    bool   dmeValid {true};
    bool   secVhfReceive {true};
    bool   secVhfDIC {true};
    bool   secVhfLocValid {true};
    bool   secVhfLGS {true};
    bool   secDmeValid {true};
    double cdi {};
    double cdiRate {0.3};
    double secCdi {};

    Location loc {Location::PILOT}; // cockpit location (PILOT or COPILOT)

    double dist {};                 // distance (miles) to our next navaid
    double distRate {3.0};

    // data
    double timeToGo {};
    double ttgRate {50.0};
    double groundSpeed {};
    double driftAngle {};
    double daRate {10.0};
    double trueAirSpeed {};
    double tasRate {10.0};
    double elapsedTime {3500.0};
    double etRate {20.0};
    double windDir {};
    double windSpeed {};
    ReadoutMode readoutMode {ReadoutMode::ND_TTG};    // primary or secondary

    // glideslope
    double gsDots {};
    double gsDotsRate {0.2};
    bool   vhfGSValid {true};
    bool   vhfGSOOV {true};

    // SLS - transfer from Electronic HSI class
    double curHdg {};               // current slewed heading
    double curBug {};               // current heading bug
    SendData hdgBugROMoveXSD;       // where to move our heading bug readout
    SendData hdgBugROSD;            // heading bug readout
    SendData distTypeSD;            // type of distance data we are using
    SendData distVisSD;             // distance data readout visibility
    SendData curDistSD;             // current distance to navaid
    SendData courseSD;              // our course
    SendData roLabelSD;             // which readout label to display
    SendData roWhichSD;             // actual readout to display
    SendData ttgSD;                 // time to go
    SendData groundSpeedSD;         // ground speed
    SendData driftAngleSD;          // drift angle
    SendData driftAngSideSD;        // drift angle side
    SendData trueAirSpeedSD;        // true air speed
    SendData elapsedTimeSD;         // elapsed time (minutes)
    SendData elapsedTimeHRSD;       // elapsed time (hours)
    SendData whichETSD;             // which elapsed time readout
    SendData driftAngleWindSD;      // drift angle for the wind
    SendData whichSideDAWindSD;     // drift angle side for the wind
    SendData windDirectionSD;       // wind direction
    SendData windSpeedSD;           // wind speed
    SendData brgSourceSD;           // bearing source
    SendData brgROSD;               // bearing readout
    SendData secBrgROSD;            // secondary bearing readout
    SendData glideSlopeSD;          // glide slope deviation
    SendData centeredSD;            // compass centered (will always be here)
    SendData compassHdgSD;          // compass heading
    SendData hdgBugSD;              // heading bug
    SendData priCourseDevSD;        // primary course deviation
    double curCdi {};               // current course deviation
    SendData crsPntrSD;             // course pointer rotation
    SendData whichCrsPtrSD;         // which course pointer (primary or secondary)
    double curCourse {};            // current course (for slewing)
    SendData priCrsPtrColorSD;      // primary course pointer color
    SendData secCrsPntrSD;          // secondary course pointer rotation
    SendData secCourseDevSD;        // secondary course pointer deviation
    SendData secCrsPtrColorSD;      // secondary course pointer color
    SendData whichNavSrcSD;         // which nav source are we using (asterisk)
    SendData primaryPosSD;          // primary nav position
    SendData secondaryPosSD;        // secondary nav position
    SendData primaryCrsVisSD;       // primary course visibility
    SendData secondaryCrsVisSD;     // secondary course visibility
    double curToFrom {};            // current to / from
    SendData toOrFromSD;            // to or from flag
    SendData toFromSD;              // to from translation
};

#endif
