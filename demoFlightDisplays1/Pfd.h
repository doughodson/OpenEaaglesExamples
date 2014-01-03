//------------------------------------------------------------------------------
// Class: Pfd
//
// Description: Sends data down to the Pfd
// Inputs: Use public member functions instead of send commands here
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_Pfd_H__
#define __Eaagles_Demo_Pfd_H__

#include "openeaagles/basicGL/Page.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Demo {

class Pfd : public BasicGL::Page
{
   DECLARE_SUBCLASS(Pfd,BasicGL::Page)

public:
    Pfd();

    enum { NCHAR_NAV1_ID = 3, NCHAR_NAV2_ID = 5 };

    // set functions
    virtual bool setPitchDeg(const LCreal newP);        // Sets pitch angle (degs) 
    virtual bool setPitchRad(const LCreal newP);        // Sets pitch angle (rads)
    virtual bool setRollDeg(const LCreal newR);         // Sets roll angle (degs)
    virtual bool setRollRad(const LCreal newR);         // Sets roll angle (rads)
    virtual bool setTrueHeading(const LCreal newTH);    // Sets true heading angle (degs)
    virtual bool setCmdCourse(const LCreal newCC);      // Sets Commanded course (degs)
    virtual bool setCmdHdg(const LCreal newCH);         // Sets commanded heading (degs)
    virtual bool setCdiDots(const LCreal newCD);        // Sets CDI deflection (dots)
    virtual bool setToFrom(const LCreal newTF);         // Sets to/from [ +1(to) .. 0(from) ]
    virtual bool setAirSpeedKts(const LCreal newAS);    // Sets airspeed (kts)
    virtual bool setCmdAirSpdKts(const LCreal newCAS);  // Sets commanded airspeed (kts)
    virtual bool setAltitudeFt(const LCreal newA);      // Sets pressure altitude (ft)
    virtual bool setCmdAltFt(const LCreal newCA);       // Sets commanded altitude (ft)
    virtual bool setGlideslope(const LCreal newGS);     // Sets glide slope deviation (dots)
    virtual bool setLatDev(const LCreal newLD);         // Sets localizer deviation (dots)
    virtual bool setMstrCtn(const bool newMC);          // Sets "master caution" flag
    virtual bool setVVI(const LCreal newVVI);           // Sets vertical velocity (ft/min)
    virtual bool setAOA(const LCreal newAOA);           // Sets angle of attack (degs)
    virtual bool setSideSlip(const LCreal newSS);       // Sets side slip (degs)
    virtual bool setGroundSpdKts(const LCreal newGS);   // Sets ground speed (kts)
    virtual bool setFltDirBankDeg(const LCreal newFDB); // Sets flight directory commanded bank (deg)
    virtual bool setFltDirPitchDeg(const LCreal newFDP);// Sets flight director commanded pitch (deg)
    virtual bool setFltDirBankRad(const LCreal newFDB); // Sets flight directory commanded bank (rad)
    virtual bool setFltDirPitchRad(const LCreal newFDP);// Sets flight director commanded pitch (rad)
    virtual bool setBaroPress(const LCreal newBOP);     // Sets baro pressure (inches)
    virtual bool setRdrAltFt(const LCreal newRA);       // Sets radar altitude (ft)
    virtual bool setNav1Brg(const LCreal newB);         // Sets our first nav aid bearing (degs)
    virtual bool setNav1DME(const LCreal newDME);       // Sets our first nav aid DME (NM)
    virtual bool setNav1Id(const char* const newId);    // Sets our first nav aid identifier
    virtual bool setNav2Brg(const LCreal newB);         // Sets our second nav aid bearing (degs)
    virtual bool setNav2DME(const LCreal newDME);       // Sets our second nav aid DME (NM)
    virtual bool setNav2Id(const char* const newId);    // Sets our second nav aid identifier
    virtual bool setRefLat(const double newRL);         // reference latitude 
    virtual bool setRefLon(const double newRL);         // reference longitude 
    virtual bool setRange(const LCreal newR);           // range 
    virtual bool setFPMX(const LCreal newX);            // flight path marker x
    virtual bool setFPMY(const LCreal newY);            // flight path marker y
    virtual bool setGLoad(const LCreal newLoad);        // our g load
    virtual bool setMach(const LCreal x);               // machine speed

    // get functions
    LCreal getPitchDeg()            { return pitch; }
    LCreal getPitchRad()            { return (LCreal)(pitch * Basic::Angle::D2RCC); }
    LCreal getRollDeg()             { return roll; }
    LCreal getRollRad()             { return (LCreal)(roll * Basic::Angle::D2RCC); }
    LCreal getTrueHdg()             { return trueHdg; }
    LCreal getCmdCourse()           { return cmdCrs; }
    LCreal getCmdHdg()              { return cmdHdg; }
    LCreal getCdiDots()             { return cdiDots; }
    LCreal getToFrom()              { return toFrom; }
    LCreal getAirSpdKts()           { return airSpd; }
    LCreal getCmdAirSpdKts()        { return cmdSpd; }
    LCreal getAltFeet()             { return alt; }
    LCreal getCmdAltFeet()          { return cmdAlt; }
    LCreal getGlideSlope()          { return gSlope; }
    LCreal getLatDev()              { return latDev; }
    bool getMasterCtn()             { return mstrCtn; }
    LCreal getVVI()                 { return vvi; }
    LCreal getAOA()                 { return aoa; }
    LCreal getSideSlip()            { return slip; }
    LCreal getGndSpdKts()           { return gSpd; }
    LCreal getFltDirBankDeg()       { return fDirBank; }
    LCreal getFltDirBankRad()       { return (LCreal)(fDirBank * Basic::Angle::R2DCC); }
    LCreal getFltDirPitchDeg()      { return fDirPitch; }
    LCreal getFltDirPitchRad()      { return (LCreal)(fDirPitch * Basic::Angle::R2DCC); }
    LCreal getBaroPressure()        { return baro; }
    LCreal getRdrAltFt()            { return rAlt; }
    LCreal getNav1Brg()             { return nav1Brg; }
    LCreal getNav1Dme()             { return nav1Dme; }
    bool getNav1Id(const int index, char* newString);
    LCreal getNav2Brg()             { return nav2Brg; }
    LCreal getNav2Dme()             { return nav2Dme; }
    bool getNav2Id(const int index, char* newString); 
    double getRefLat()              { return refLat; }
    double getRefLon()              { return refLon; }
    LCreal getRange()               { return range; }
    LCreal getFPMX()                { return fpmX; }
    LCreal getFPMY()                { return fpmY; }
    LCreal getGLoad()               { return gLoad; }
    LCreal getMach()                { return mach; }

    // Component interface
    virtual void updateData(const LCreal dt = 0.0);

private:
    // pitch and roll
    LCreal pitch;           // Pitch angle (degs)
    SendData pitchSD;
    SendData hdgPitchSD;    // heading pitch for the heading tape
    LCreal roll;            // Roll angle (degs)
    SendData rollSD;

    // bank angle
    SendData baSD;
    SendData bascaleSD;

    // heading and nav stuff
    LCreal trueHdg;         // True heading (degs)
    SendData tHdgSD;

    LCreal cmdCrs;          // commanded course (degs)
    SendData cmdCrsROSD;
    
    LCreal cmdHdg;          // commanded heading (heading bug)
    SendData cmdHdgROSD;

    // cdi
    LCreal cdiDots;         // dots

    // to from
    LCreal toFrom;          // to(1); from(0)

    // airspeed
    LCreal airSpd;          // Kts
    SendData airSpdSD;
    SendData airSpdTpSD;    // for the airspeed tape
    SendData onesSD;        // for the readout ones tape
    SendData tensSD;        // for the readout tens tape
    SendData spdRstSD;      // rest of the speed data
    SendData airSpdHundSD;  // our hundreds value

    // altitude
    LCreal alt;
    SendData alt1SD;
    SendData alt2SD;
    SendData alt3SD;
    SendData altTpSD;       // for the airspeed tape
    SendData altTensSD;
    SendData altSelectSD;   // to select the justification
    SendData altHundredsSD; // for the dynamic dial arc segment
    SendData altSD;         // for the actual altitude
    SendData altThouSD;     // for the thousands

    // side slip
    LCreal slip;             // Side slip angle (degs)
    SendData slipSD;

    // glideslope (in dots)
    LCreal gSlope;
    SendData gSlopeSD;

    // Lateral dev
    LCreal latDev;
    SendData latDevSD;

    // commanded speed
    LCreal cmdSpd;          // kts
    SendData aBugSD;
    SendData diffSD;

    // commanded alt
    LCreal cmdAlt;
    SendData altBugSD;
    SendData altDiffSD;

    // master caution
    bool mstrCtn;
    SendData mstrCtnSD;

    // vvi
    LCreal vvi;         // ft/min
    SendData vviSD;
    LCreal maxVvi;      // max vvi value
    LCreal minVvi;      // min vvi value
    SendData maxVviSD;  // for the instrument color
    SendData minVviSD;
    SendData maxVviROSD;// for the readout itself
    SendData minVviROSD;
    SendData vviROSD;

    // aoa
    LCreal aoa;         // degs
    SendData aoaSD;

    // ground speed
    LCreal gSpd;        // Kts
    SendData gSpdSD;

    // flight director stuff (in inches)
    LCreal fDirBank;
    SendData fDirBankSD;
    LCreal fDirPitch;
    SendData fDirPitchSD;

    // barometric pressure
    LCreal baro;
    SendData baroSD;

    // radar altitude
    LCreal rAlt;
    LCreal rAltMin;

    // navaid 1 and 2 data
    LCreal nav1Brg;       // degs
    LCreal nav1Dme;       // Nm
    char   nav1Id[NCHAR_NAV1_ID+1];   // NAV 1 IDs
    SendData nav1DmeSD;
    SendData nav1IdSD;

    LCreal nav2Brg;       // degs
    LCreal nav2Dme;       // Nm
    char   nav2Id[NCHAR_NAV2_ID+1];   // NAV 2 IDs
    SendData nav2DmeSD;
    SendData nav2IdSD;

    // Hsi send data
    SendData trueHdgSD;
    SendData hdgTapeSD;
    SendData cmdHdgSD;
    SendData cmdCrsSD;
    SendData cdiDotsSD;
    SendData toFromSD;
    SendData nav1BrgSD;
    SendData nav2BrgSD;
    // Radar alt send
    SendData rAltSD;
    SendData rAltMinSD;

    double refLat;
    double refLon;
    LCreal range;

    // Flight path marker x and y position
    LCreal fpmX;
    LCreal fpmY;
    SendData fpmXSD;
    SendData fpmYSD;
    // Gs
    LCreal gLoad;
    // Mach
    LCreal mach;
    // ghost horizon
    SendData pitchGhostSD;
};

}; // end of Demo namespace
}; // end of Eaagles namespace

#endif

