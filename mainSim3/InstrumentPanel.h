//------------------------------------------------------------------------------
// Class:  InstrumentPanel
//
// Description: Sim3 Main Instrument Panel
//
// Events: (all keyboard events)
//   'r' or 'R'   -- Reset simulation
//   'f' or 'F'   -- Toggle simulation freeze
//   '+'          -- Ownship step (to next local air vehicle)
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_InstrumentPanel_H__
#define __Eaagles_Example_InstrumentPanel_H__

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/simulation/Player.h"

namespace Eaagles {

   namespace Simulation {
      class Player;
      class Simulation;
      class Station;
   }

namespace Example {

   class DedDisplay;
   class MfdDisplay;

class InstrumentPanel : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(InstrumentPanel, Glut::GlutDisplay)

public:
   InstrumentPanel();

   Simulation::Player* getOwnship();
   Simulation::Simulation* getSimulation();
   Simulation::Station* getStation();

   bool event(const int event, Basic::Object* const obj = nullptr) override;
   void updateData(const LCreal dt = 0.0) override;

protected:
   // Key event handlers
   bool onResetKey();
   bool onFreezeKey();
   bool onStepOwnshipKey();

private:
   Basic::safe_ptr<Simulation::Station> myStation;

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

} // end Example namespace
} // end Eaagles namespace

#endif
