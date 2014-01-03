//------------------------------------------------------------------------------
// Class: Tester
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Tester_H__
#define __Eaagles_Test_Tester_H__

#include "openeaagles/basic/Component.h"

namespace Eaagles {
   namespace Basic { class PairStream; }

namespace Test {

//------------------------------------------------------------------------------
// Class: Tester
// Description: Container class for the interval timers being tested
//
// Factory name: Tester
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

} // namespace Test
} // namespace Eaagles

#endif

