//------------------------------------------------------------------------------
// Class:  InstrumentPanel
// Base class:  Basic::Object -> ... -> BasicGL::Display -> -> GlutDisplay -> InstrumentPanel
//
// Description: Sim3 Main Instrument Panel
//------------------------------------------------------------------------------
#ifndef __InstrumentPanel_H__
#define __InstrumentPanel_H__

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/simulation/Player.h"

namespace Eaagles {

   namespace Simulation {
      class Player;
      class Simulation;
      class Station;
   }

namespace Sim3 {

class DedDisplay;
class MfdDisplay;

class InstrumentPanel : public Glut::GlutDisplay {
   DECLARE_SUBCLASS(InstrumentPanel, Glut::GlutDisplay)

public:
    InstrumentPanel();

    Simulation::Player* getOwnship();
    Simulation::Simulation* getSimulation();
    Simulation::Station* getStation();

    // BasicGL::Display Interface
    virtual void keyboardEvent(const int key);
#if 0
    virtual void mouseEvent(const int button, const int state, const int x, const int y);
    
    virtual void buttonEvent(const int b);
#endif

    // Basic::Component Interface
    virtual void updateData(const LCreal dt = 0.0f);
    
    
private:
    SPtr<Simulation::Station> myStation;
    
    // ALT Stuff
    LCreal altitude;             // our current altitude 
    SendData altitudeSD;
    
    // VVI Stuff
    osg::Vec3 vvi;              // velocity vector
    SendData vviSD;
    LCreal pastVvi;              // our past vvi value (to create a linear filter)
    
    // AOA Stuff
    LCreal aoa;                  // angle of attack 
    SendData aoaSD;
    SendData aoaDigSD;            // angle of attack (digital)
    
    // HSI Stuff - sends this to our Sim3Hsi class
    LCreal heading;             // our heading (in degrees)
    SendData headingSD;
    LCreal bpAngle;              // our bearing pointer angle (degrees)
    SendData bpAngleSD;
    LCreal dme;                 // dme (miles)
    SendData dmeSD;
    
    
    // CAS Stuff
    LCreal airSpeed;             // our air speed (in knots)
    SendData airSpeedSD;
    
    // G Stuff                  
    LCreal gForce;               // g's we are pulling
    SendData gForceSD;
    SendData gForce2SD;         // this is for the analog meter

    // ADI
    LCreal pitch;               // pitch (degrees)
    SendData pitchSD;
    LCreal roll;                // roll (degrees)
    SendData rollSD;
    LCreal slip;                // slip (degrees)
    SendData slipSD;

    // Mach
    LCreal mach;                // mach number
    SendData machSD;

    // G
    LCreal gload;                // G
    SendData gloadSD;
};

} // end of Sim3 namespace
} // end Eaagles namespace

#endif // __InstrumentPanel_H__
