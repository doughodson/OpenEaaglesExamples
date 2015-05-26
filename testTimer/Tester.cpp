//------------------------------------------------------------------------------
// Timer Tester class
//------------------------------------------------------------------------------

#include "Tester.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Timers.h"

#include <cstdio>

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(Tester,"Tester")
EMPTY_SERIALIZER(Tester)

// slot table
BEGIN_SLOTTABLE(Tester)
   "timers"            // 1: List of up/down timers to be tested
END_SLOTTABLE(Tester)

// slot map
BEGIN_SLOT_MAP(Tester)
   ON_SLOT(1, setSlotTimers, Eaagles::Basic::PairStream)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------
Tester::Tester()
{
   STANDARD_CONSTRUCTOR()

   initData();
}

void Tester::initData()
{
   timers = nullptr;
}

void Tester::copyData(const Tester& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   setSlotTimers(org.timers);
}

void Tester::deleteData()
{
   setSlotTimers(nullptr);
}

//------------------------------------------------------------------------------
// Return true if all alarms are set
//------------------------------------------------------------------------------
bool Tester::areAllActiveTimerAlarmsOn() const
{
   bool on = true;

   if (timers != nullptr) {

      const Basic::List::Item* item = timers->getFirstItem();
      while (item != nullptr && on) {
         const Basic::Pair* pair = static_cast<const Basic::Pair*>(item->getValue());
         const Basic::Timer* timer = static_cast<const Basic::Timer*>(pair->object());
         on = timer->alarm() || timer->isNotRunning();
         item = item->getNext();
      }

   }

   return on;
}


//------------------------------------------------------------------------------
// Print the alarm status
//------------------------------------------------------------------------------
void Tester::printTimers() const
{
   if (timers != nullptr) {

      const Basic::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         const Basic::Pair* pair = static_cast<const Basic::Pair*>(item->getValue());
         const Basic::Timer* timer = static_cast<const Basic::Timer*>(pair->object());

         printf("  timer(%s)", pair->slot()->getString());
         printf(" = %4.1f", timer->getCurrentTime());

         if (timer->getType() == Basic::Timer::UP) printf(", up");
         else std::printf(", down");

         if (timer->isRunning()) printf(", active");
         else std::printf(", inactive");

         std::printf(", alarm(%4.1f", timer->getAlarmTime());
         if (timer->alarm()) printf(", ON)");
         std::printf(", OFF);");

         std::printf("\n");

         item = item->getNext();
      }

   }
}


//------------------------------------------------------------------------------
// Restart all of the timers -- they're left in an active state
//------------------------------------------------------------------------------
void Tester::restartAllTimers()
{
   if (timers != nullptr) {

      Basic::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         Basic::Timer* timer = static_cast<Basic::Timer*>(pair->object());
         timer->restart();
         item = item->getNext();
      }

   }
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void Tester::reset()
{
   BaseClass::reset();

   if (timers != nullptr) {

      Basic::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         Basic::Timer* timer = static_cast<Basic::Timer*>(pair->object());
         timer->reset();
         item = item->getNext();
      }

   }
}

//------------------------------------------------------------------------------
// slot functions
//------------------------------------------------------------------------------

bool Tester::setSlotTimers(const Basic::PairStream* const msg)
{
   // Clear the old timer list
   if (timers != nullptr) timers->unref();
   timers = nullptr;

   // Copy the new timer list, and make sure we have only Timers
   if (msg != nullptr) {

      Basic::PairStream* newList = new Basic::PairStream();

      unsigned int n = 0;
      const Basic::List::Item* item = msg->getFirstItem();
      while (item != nullptr) {
         n++;
         const Basic::Pair* const pair = static_cast<const Basic::Pair*>(item->getValue());
         const Basic::Timer* const timer = dynamic_cast<const Basic::Timer*>(pair->object());
         if (timer != nullptr) {
            Basic::Pair* newPair = pair->clone();
            newList->put(newPair);
         }
         else {
            std::cerr << "Tester::setSlotTimers() rejecting item# " << n << "; not a valid Timer object" << std::endl;
         }
         item = item->getNext();
      }

      if (newList->entries() > 0) {
         timers = newList;
         timers->ref();
      }
      newList->unref();
   }
   return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Rgb
//------------------------------------------------------------------------------
Basic::Object* Tester::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

} // namespace Test
} // namespace Eaagles
