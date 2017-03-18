
#ifndef __Tester_H__
#define __Tester_H__

#include "openeaagles/base/Component.hpp"

namespace oe {
namespace base { class PairStream; }
}

//------------------------------------------------------------------------------
// Class: Tester
// Description: Container class for the interval timers being tested
//
// Factory name: Tester
// Slots:
//    timers   <PairStream>   ! List of timers to be tested
//------------------------------------------------------------------------------
class Tester : public oe::base::Component
{
   DECLARE_SUBCLASS(Tester, oe::base::Component)

public:
   Tester();

   bool areAllActiveTimerAlarmsOn() const;

   void printTimers() const;

   // Restart all of the timers -- they're left in an active state
   void restartAllTimers();

   virtual void reset() override;

protected:
   bool setSlotTimers(const oe::base::PairStream* const msg);

private:
   oe::base::PairStream* timers {};    // List of timers
};

#endif
