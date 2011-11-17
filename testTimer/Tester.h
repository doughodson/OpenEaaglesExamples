//------------------------------------------------------------------------------
// Class: Tester
//------------------------------------------------------------------------------
#ifndef _TIMER_TESTER_INCLUDE
#define _TIMER_TESTER_INCLUDE

#include "openeaagles/basic/Component.h"

namespace Eaagles {
   namespace Basic { class PairStream; }

namespace TestTimer {

//------------------------------------------------------------------------------
// Class: Tester
// Description: Container class for the interval timers being tested
//
// Form name: Tester
// Slots:
//    timers   <PairStream>   ! List of timers to be tested
//------------------------------------------------------------------------------
class Tester : public Basic::Component
{
   DECLARE_SUBCLASS(Tester, Basic::Component)

public:
   Tester();

   bool areAllActiveTimerAlarmsOn() const;

   void printTimers() const;

   // Restart all of the timers -- they're left in an active state
   void restartAllTimers();

   // Component class Interface
   virtual void reset();

protected:
   bool setSlotTimers(const Basic::PairStream* const msg);

private:
   void initData();

   Basic::PairStream* timers;    // List of timers
};

} // namespace TestTimer
} // namespace Eaagles

#endif

