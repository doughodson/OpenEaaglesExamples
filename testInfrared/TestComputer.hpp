
#ifndef __TestComputer_H__
#define __TestComputer_H__

#include "openeaagles/models/system/OnboardComputer.hpp"

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
class TestComputer : public oe::models::OnboardComputer
{
    DECLARE_SUBCLASS(TestComputer, oe::models::OnboardComputer)

public:
   TestComputer();
   bool haveTgt() const { return haveTarget; }

   virtual void updateShootList(const bool step = false) override;      // Updates the shoot list

   virtual void updateTC(const double dt = 0.0) override;

   virtual void reset() override;

protected:
   // process() subfunction, tells computer if we are tracking a target or not
   virtual bool processIr();

   virtual void process(const double dt) override;

private:
   bool uncaged {};      // flag that indicates whether gimbal is free to track target
   bool haveTarget {};   // flag indicating if we have a target track
};

#endif
