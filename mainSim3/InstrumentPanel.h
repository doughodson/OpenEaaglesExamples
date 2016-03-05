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
#ifndef __oe_example_InstrumentPanel_H__
#define __oe_example_InstrumentPanel_H__

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/simulation/Player.h"

namespace oe {

   namespace simulation {
      class Player;
      class Simulation;
      class Station;
   }

namespace example {

   class DedDisplay;
   class MfdDisplay;

class InstrumentPanel : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(InstrumentPanel, glut::GlutDisplay)

public:
   InstrumentPanel();

   simulation::Player* getOwnship();
   simulation::Simulation* getSimulation();
   simulation::Station* getStation();

   bool event(const int event, base::Object* const obj = nullptr) override;
   void updateData(const LCreal dt = 0.0) override;

protected:
   // Key event handlers
   bool onResetKey();
   bool onFreezeKey();
   bool onStepOwnshipKey();

private:
   base::safe_ptr<simulation::Station> myStation;

   // ALT Stuff
   LCreal altitude;            // our current altitude
   SendData altitudeSD;

   // VVI Stuff
   osg::Vec3 vvi;              // velocity vector
   SendData vviSD;
   LCreal pastVvi;             // our past vvi value (to create a linear filter)

   // AOA Stuff
   LCreal aoa;                 // angle of attack
   SendData aoaSD;
   SendData aoaDigSD;          // angle of attack (digital)

   // HSI Stuff - sends this to our Sim3Hsi class
   LCreal heading;             // our heading (in degrees)
   SendData headingSD;
   LCreal bpAngle;             // our bearing pointer angle (degrees)
   SendData bpAngleSD;
   LCreal dme;                 // dme (miles)
   SendData dmeSD;


   // CAS Stuff
   LCreal airSpeed;            // our air speed (in knots)
   SendData airSpeedSD;

   // G Stuff
   LCreal gForce;              // g's we are pulling
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
   LCreal gload;               // G
   SendData gloadSD;
};

} // end example namespace
} // end oe namespace

#endif
