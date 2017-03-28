
#ifndef __oe_xpanel_Pfd_H__
#define __oe_xpanel_Pfd_H__

#include "openeaagles/graphics/Page.hpp"
#include "openeaagles/base/units/angle_utils.hpp"

namespace oe {
namespace xpanel {

//------------------------------------------------------------------------------
// Class: Pfd
//
// Description: Tests the pfd.
//------------------------------------------------------------------------------
class Pfd : public graphics::Page
{
   DECLARE_SUBCLASS(Pfd, graphics::Page)

public:
    Pfd();

    // set functions
    virtual bool setPitchDeg(const double newP);        // Sets pitch angle (degs)
    virtual bool setPitchRad(const double newP);        // Sets pitch angle (rads)
    virtual bool setRollDeg(const double newR);         // Sets roll angle (degs)
    virtual bool setRollRad(const double newR);         // Sets roll angle (rads)
    virtual bool setTrueHeading(const double newTH);    // Sets true heading angle (degs)
    virtual bool setCmdHdg(const double newCH);         // Sets commanded heading (degs)
    virtual bool setAirSpeedKts(const double newAS);    // Sets airspeed (kts)
    virtual bool setCmdAirSpdKts(const double newCAS);  // Sets commanded airspeed (kts)
    virtual bool setAltitudeFt(const double newA);      // Sets pressure altitude (ft)
    virtual bool setCmdAltFt(const double newCA);       // Sets commanded altitude (ft)
    virtual bool setGlideslope(const double newGS);     // Sets glide slope deviation (dots)
    virtual bool setLatDev(const double newLD);         // Sets localizer deviation (dots)
    virtual bool setVVI(const double newVVI);           // Sets vertical velocity (ft/min)
    virtual bool setSideSlip(const double newSS);       // Sets side slip (degs)
    virtual bool setFltDirBankDeg(const double newFDB); // Sets flight directory commanded bank (deg)
    virtual bool setFltDirPitchDeg(const double newFDP);// Sets flight director commanded pitch (deg)
    virtual bool setFltDirBankRad(const double newFDB); // Sets flight directory commanded bank (rad)
    virtual bool setFltDirPitchRad(const double newFDP);// Sets flight director commanded pitch (rad)
    virtual bool setBaroPress(const double newBOP);     // Sets baro pressure (inches)
    virtual bool setRefLat(const double newRL);         // reference latitude
    virtual bool setRefLon(const double newRL);         // reference longitude
    virtual bool setRange(const double newR);           // range
    virtual bool setGLoad(const double newLoad);        // our g load
    virtual bool setMach(const double x);               // machine speed

    // get functions
    double getPitchDeg()            { return pitch; }
    double getPitchRad()            { return static_cast<double>(pitch * base::angle::D2RCC); }
    double getRollDeg()             { return roll; }
    double getRollRad()             { return static_cast<double>(roll * base::angle::D2RCC); }
    double getTrueHdg()             { return trueHdg; }
    double getCmdHdg()              { return cmdHdg; }
    double getAirSpdKts()           { return airSpd; }
    double getCmdAirSpdKts()        { return cmdSpd; }
    double getAltFeet()             { return alt; }
    double getCmdAltFeet()          { return cmdAlt; }
    double getGlideSlope()          { return gSlope; }
    double getLatDev()              { return latDev; }
    double getVVI()                 { return vvi; }
    double getSideSlip()            { return slip; }
    double getFltDirBankDeg()       { return fDirBank; }
    double getFltDirBankRad()       { return static_cast<double>(fDirBank * base::angle::R2DCC); }
    double getFltDirPitchDeg()      { return fDirPitch; }
    double getFltDirPitchRad()      { return static_cast<double>(fDirPitch * base::angle::R2DCC); }
    double getBaroPressure()        { return baro; }
    double getRefLat()              { return refLat; }
    double getRefLon()              { return refLon; }
    double getRange()               { return range; }
    double getGLoad()               { return gLoad; }
    double getMach()                { return mach; }

    virtual void updateData(const double dt = 0.0) override;

private:
    static const int NCHAR_NAV1_ID = 3;
    static const int NCHAR_NAV2_ID = 5;

    // pitch and roll
    double pitch {};           // Pitch angle (degs)
    SendData pitchSD;
    SendData hdgPitchSD;       // heading pitch for the heading tape
    double roll {};            // Roll angle (degs)
    SendData rollSD;

    // bank angle
    SendData baSD;
    SendData bascaleSD;

    // heading and nav stuff
    double trueHdg {};         // True heading (degs)
    SendData tHdgSD;

    double cmdHdg {};          // commanded heading (heading bug)
    SendData cmdHdgROSD;

    // airspeed
    double airSpd {100.0};     // Kts
    SendData airSpdTpSD;       // for the airspeed tape
    SendData onesSD;           // for the readout ones tape
    SendData spdRstSD;         // rest of the speed data

    // altitude
    double alt {1000.0};
    SendData alt1SD;
    SendData alt2SD;
    SendData alt3SD;
    SendData altTpSD;          // for the airspeed tape
    SendData altTensSD;
    SendData altSelectSD;      // to select the justification
    SendData altSD;            // for the actual altitude

    // side slip
    double slip {};            // Side slip angle (degs)
    SendData slipSD;

    // glideslope (in dots)
    double gSlope {};
    SendData gSlopeSD;

    // Lateral dev
    double latDev {};
    SendData latDevSD;

    // commanded speed
    double cmdSpd {};          // kts
    SendData aBugSD;
    SendData diffSD;

    // commanded alt
    double cmdAlt {5000.0};
    SendData altBugSD;
    SendData altDiffSD;

    // vvi
    double vvi {};             // ft/min
    SendData vviSD;
    SendData vviROSD;

    // flight director stuff (in inches)
    double fDirBank {};
    SendData fDirBankSD;
    double fDirPitch {};
    SendData fDirPitchSD;

    // barometric pressure
    double baro {};
    SendData baroSD;

    // Hsi send data
    SendData trueHdgSD;
    SendData hdgTapeSD;
    SendData cmdHdgSD;

    // lat and lon
    double refLat {};
    double refLon {};
    double range {};

    // Gs
    double gLoad {};

    // Mach
    double mach {};            // meter altitude
    SendData mAltSD;
    SendData cmdMAltSD;

    // ghost horizon
    SendData pitchGhostSD;
};

}
}

#endif
