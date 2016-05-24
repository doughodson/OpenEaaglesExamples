//------------------------------------------------------------------------------
// Timer Tester class
//------------------------------------------------------------------------------

#include "Tester.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"
#include "openeaagles/base/Timers.h"

#include <cstdio>

namespace oe {
namespace test {

IMPLEMENT_SUBCLASS(Tester,"Tester")
EMPTY_SERIALIZER(Tester)

// slot table
BEGIN_SLOTTABLE(Tester)
   "timers"            // 1: List of up/down timers to be tested
END_SLOTTABLE(Tester)

// slot map
BEGIN_SLOT_MAP(Tester)
   ON_SLOT(1, setSlotTimers, oe::base::PairStream)
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

      const base::List::Item* item = timers->getFirstItem();
      while (item != nullptr && on) {
         const base::Pair* pair = static_cast<const base::Pair*>(item->getValue());
         const base::Timer* timer = static_cast<const base::Timer*>(pair->object());
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

      const base::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         const base::Pair* pair = static_cast<const base::Pair*>(item->getValue());
         const base::Timer* timer = static_cast<const base::Timer*>(pair->object());

         printf("  timer(%s)", pair->slot()->getString());
         printf(" = %4.1f", timer->getCurrentTime());

         if (timer->getType() == base::Timer::UP) printf(", up");
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

      base::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         base::Pair* pair = static_cast<base::Pair*>(item->getValue());
         base::Timer* timer = static_cast<base::Timer*>(pair->object());
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

      base::List::Item* item = timers->getFirstItem();
      while (item != nullptr) {
         base::Pair* pair = static_cast<base::Pair*>(item->getValue());
         base::Timer* timer = static_cast<base::Timer*>(pair->object());
         timer->reset();
         item = item->getNext();
      }

   }
}

//------------------------------------------------------------------------------
// slot functions
//------------------------------------------------------------------------------

bool Tester::setSlotTimers(const base::PairStream* const msg)
{
   // Clear the old timer list
   if (timers != nullptr) timers->unref();
   timers = nullptr;

   // Copy the new timer list, and make sure we have only Timers
   if (msg != nullptr) {

      base::PairStream* newList = new base::PairStream();

      unsigned int n = 0;
      const base::List::Item* item = msg->getFirstItem();
      while (item != nullptr) {
         n++;
         const base::Pair* const pair = static_cast<const base::Pair*>(item->getValue());
         const base::Timer* const timer = dynamic_cast<const base::Timer*>(pair->object());
         if (timer != nullptr) {
            base::Pair* newPair = pair->clone();
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
base::Object* Tester::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}
}
