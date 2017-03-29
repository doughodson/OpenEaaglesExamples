
#ifndef __Pfd_H__
#define __Pfd_H__

#include "openeaagles/graphics/Page.hpp"
#include "openeaagles/base/units/angle_utils.hpp"

//------------------------------------------------------------------------------
// Class: Pfd
//
// Description: Sends data down to the Pfd
// Inputs: Use public member functions instead of send commands here
//------------------------------------------------------------------------------
class Pfd : public oe::graphics::Page
{
   DECLARE_SUBCLASS(Pfd, oe::graphics::Page)

public:
   Pfd();

   // set functions
   virtual bool setPitchDeg(const double newP);        // Sets pitch angle (degs)
   virtual bool setPitchRad(const double newP);        // Sets pitch angle (rads)
   virtual bool setRollDeg(const double newR);         // Sets roll angle (degs)
   virtual bool setRollRad(const double newR);         // Sets roll angle (rads)
   virtual bool setTrueHeading(const double newTH);    // Sets true heading angle (degs)
   virtual bool setCmdCourse(const double newCC);      // Sets Commanded course (degs)
   virtual bool setCmdHdg(const double newCH);         // Sets commanded heading (degs)
   virtual bool setCdiDots(const double newCD);        // Sets CDI deflection (dots)
   virtual bool setToFrom(const double newTF);         // Sets to/from [ +1(to) .. 0(from) ]
   virtual bool setAirSpeedKts(const double newAS);    // Sets airspeed (kts)
   virtual bool setCmdAirSpdKts(const double newCAS);  // Sets commanded airspeed (kts)
   virtual bool setAltitudeFt(const double newA);      // Sets pressure altitude (ft)
   virtual bool setCmdAltFt(const double newCA);       // Sets commanded altitude (ft)
   virtual bool setGlideslope(const double newGS);     // Sets glide slope deviation (dots)
   virtual bool setLatDev(const double newLD);         // Sets localizer deviation (dots)
   virtual bool setMstrCtn(const bool newMC);          // Sets "master caution" flag
   virtual bool setVVI(const double newVVI);           // Sets vertical velocity (ft/min)
   virtual bool setAOA(const double newAOA);           // Sets angle of attack (degs)
   virtual bool setSideSlip(const double newSS);       // Sets side slip (degs)
   virtual bool setGroundSpdKts(const double newGS);   // Sets ground speed (kts)
   virtual bool setFltDirBankDeg(const double newFDB); // Sets flight directory commanded bank (deg)
   virtual bool setFltDirPitchDeg(const double newFDP);// Sets flight director commanded pitch (deg)
   virtual bool setFltDirBankRad(const double newFDB); // Sets flight directory commanded bank (rad)
   virtual bool setFltDirPitchRad(const double newFDP);// Sets flight director commanded pitch (rad)
   virtual bool setBaroPress(const double newBOP);     // Sets baro pressure (inches)
   virtual bool setRdrAltFt(const double newRA);       // Sets radar altitude (ft)
   virtual bool setNav1Brg(const double newB);         // Sets our first nav aid bearing (degs)
   virtual bool setNav1DME(const double newDME);       // Sets our first nav aid DME (NM)
   virtual bool setNav1Id(const char* const newId);    // Sets our first nav aid identifier
   virtual bool setNav2Brg(const double newB);         // Sets our second nav aid bearing (degs)
   virtual bool setNav2DME(const double newDME);       // Sets our second nav aid DME (NM)
   virtual bool setNav2Id(const char* const newId);    // Sets our second nav aid identifier
   virtual bool setRefLat(const double newRL);         // reference latitude
   virtual bool setRefLon(const double newRL);         // reference longitude
   virtual bool setRange(const double newR);           // range
   virtual bool setFPMX(const double newX);            // flight path marker x
   virtual bool setFPMY(const double newY);            // flight path marker y
   virtual bool setGLoad(const double newLoad);        // our g load
   virtual bool setMach(const double x);               // machine speed

   // get functions
   double getPitchDeg()            { return pitch; }
   double getPitchRad()            { return static_cast<double>(pitch * oe::base::angle::D2RCC); }
   double getRollDeg()             { return roll; }
   double getRollRad()             { return static_cast<double>(roll * oe::base::angle::D2RCC); }
   double getTrueHdg()             { return trueHdg; }
   double getCmdCourse()           { return cmdCrs; }
   double getCmdHdg()              { return cmdHdg; }
   double getCdiDots()             { return cdiDots; }
   double getToFrom()              { return toFrom; }
   double getAirSpdKts()           { return airSpd; }
   double getCmdAirSpdKts()        { return cmdSpd; }
   double getAltFeet()             { return alt; }
   double getCmdAltFeet()          { return cmdAlt; }
   double getGlideSlope()          { return gSlope; }
   double getLatDev()              { return latDev; }
   bool getMasterCtn()             { return mstrCtn; }
   double getVVI()                 { return vvi; }
   double getAOA()                 { return aoa; }
   double getSideSlip()            { return slip; }
   double getGndSpdKts()           { return gSpd; }
   double getFltDirBankDeg()       { return fDirBank; }
   double getFltDirBankRad()       { return static_cast<double>(fDirBank * oe::base::angle::R2DCC); }
   double getFltDirPitchDeg()      { return fDirPitch; }
   double getFltDirPitchRad()      { return static_cast<double>(fDirPitch * oe::base::angle::R2DCC); }
   double getBaroPressure()        { return baro; }
   double getRdrAltFt()            { return rAlt; }
   double getNav1Brg()             { return nav1Brg; }
   double getNav1Dme()             { return nav1Dme; }
   bool getNav1Id(const int index, char* newString);
   double getNav2Brg()             { return nav2Brg; }
   double getNav2Dme()             { return nav2Dme; }
   bool getNav2Id(const int index, char* newString);
   double getRefLat()              { return refLat; }
   double getRefLon()              { return refLon; }
   double getRange()               { return range; }
   double getFPMX()                { return fpmX; }
   double getFPMY()                { return fpmY; }
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

   double cmdCrs {};          // commanded course (degs)
   SendData cmdCrsROSD;

   double cmdHdg {};          // commanded heading (heading bug)
   SendData cmdHdgROSD;

   // cdi
   double cdiDots {};         // dots

   // to from
   double toFrom {-1.0};      // to(1); from(0)

   // airspeed
   double airSpd {100.0};     // Kts
   SendData airSpdSD;
   SendData airSpdTpSD;       // for the airspeed tape
   SendData onesSD;           // for the readout ones tape
   SendData tensSD;           // for the readout tens tape
   SendData spdRstSD;         // rest of the speed data
   SendData airSpdHundSD;     // our hundreds value

   // altitude
   double alt {1000.0};
   SendData alt1SD;
   SendData alt2SD;
   SendData alt3SD;
   SendData altTpSD;          // for the airspeed tape
   SendData altTensSD;
   SendData altSelectSD;      // to select the justification
   SendData altHundredsSD;    // for the dynamic dial arc segment
   SendData altSD;            // for the actual altitude
   SendData altThouSD;        // for the thousands

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

   // master caution
   bool mstrCtn {};
   SendData mstrCtnSD;

   // vvi
   double vvi {};             // ft/min
   SendData vviSD;
   double maxVvi {3.0};       // max vvi value
   double minVvi {3.0};       // min vvi value
   SendData maxVviSD;         // for the instrument color
   SendData minVviSD;
   SendData maxVviROSD;       // for the readout itself
   SendData minVviROSD;
   SendData vviROSD;

   // aoa
   double aoa {};             // degs
   SendData aoaSD;

   // ground speed
   double gSpd {};            // Kts
   SendData gSpdSD;

   // flight director stuff (in inches)
   double fDirBank {};
   SendData fDirBankSD;
   double fDirPitch {};
   SendData fDirPitchSD;

   // barometric pressure
   double baro {};
   SendData baroSD;

   // radar altitude
   double rAlt {};
   double rAltMin {500.0};

   // tacan and waypoint course

   // navaid 1 and 2 data
   double nav1Brg {};                     // degs
   double nav1Dme {};                     // Nm
   char   nav1Id[NCHAR_NAV1_ID + 1] {};   // NAV 1 IDs
   SendData nav1DmeSD;
   SendData nav1IdSD;

   double nav2Brg {};                     // degs
   double nav2Dme {};                     // Nm
   char   nav2Id[NCHAR_NAV2_ID + 1] {};   // NAV 2 IDs
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

   double refLat {};
   double refLon {};
   double range {};

   // Flight path marker x and y position
   double fpmX {};
   double fpmY {};
   SendData fpmXSD;
   SendData fpmYSD;
   // Gs
   double gLoad {};
   // Mach
   double mach {};
   // ghost horizon
   SendData pitchGhostSD;
};

#endif
