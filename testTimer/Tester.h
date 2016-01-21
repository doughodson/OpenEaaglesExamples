//------------------------------------------------------------------------------
// Class: Tester
//------------------------------------------------------------------------------
#ifndef __oe_test_Tester_H__
#define __oe_test_Tester_H__

#include "openeaagles/basic/Component.h"

namespace oe {
   namespace Basic { class PairStream; }

namespace test {

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

   void reset() override;

protected:
   bool setSlotTimers(const Basic::PairStream* const msg);

private:
   void initData();

   Basic::PairStream* timers;    // List of timers
};

} // namespace test
} // namespace oe

#endif

