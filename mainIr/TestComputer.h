//------------------------------------------------------------------------------
// Class: TestComputer
//
// Description:
//    Onboard computer for IrMissile, provides basic functionality
//    Controls a TrackManager, IrSensor, & IrSeeker.
//    Updates gimbal to point at predicted az/el of strongest signal in IFOV
//    Provides these methods in public i/f mainly for IrMissile
//       haveTgt()   true if computer/seeker currently tracking a target
//
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestComputer_H__
#define __Eaagles_Example_TestComputer_H__

#include "openeaagles/simulation/OnboardComputer.h"

namespace Eaagles {
namespace Example {

class TestComputer : public Simulation::OnboardComputer  
{
    DECLARE_SUBCLASS(TestComputer, Simulation::OnboardComputer)
   
public:
   TestComputer();
   bool haveTgt() const { return haveTarget; }

   // Tracks
   virtual void updateShootList(const bool step = false);      // Updates the shoot list

// the updateTC interface is re-implemented only to
//  override the System:: version so that we can get process call to our 
// components (our TM) before we do our own processing
   void updateTC(const LCreal dt = 0.0) override;

   // Basic::Component interface
   void reset() override;

protected:
   // process() subfunction, tells computer if we are tracking a target or not
   virtual bool processIr();

   // System class Interface -- phase() callbacks
   void process(const LCreal dt) override;     // Phase 3

private:
   bool uncaged;      // flag that indicates whether gimbal is free to track target
   bool haveTarget;   // flag indicating if we have a target track
};

} // End Example namespace
} // End Eaagles namespace

#endif


