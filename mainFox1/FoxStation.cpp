
#include "FoxStation.h"
#include "FoxDisplay.h"

#include "openeaagles/base/Timers.h"

namespace oe {
namespace example {

IMPLEMENT_SUBCLASS(FoxStation, "FoxStation")
EMPTY_SERIALIZER(FoxStation)
EMPTY_DELETEDATA(FoxStation)

BEGIN_SLOTTABLE(FoxStation)
   "maindisplay",         // 1) main display
END_SLOTTABLE(FoxStation)

// map slot table to handles
BEGIN_SLOT_MAP(FoxStation)
   ON_SLOT(1, setSlotMainDisplay, FoxDisplay)
END_SLOT_MAP()

FoxStation::FoxStation()
{
   STANDARD_CONSTRUCTOR()
}

void FoxStation::copyData(const FoxStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (org.display != nullptr)
      setSlotMainDisplay( org.display->clone() );
   else
      setSlotMainDisplay(nullptr);
}

// update time critical stuff here
void FoxStation::updateTC(const double dt)
{
   // update the simulation
   BaseClass::updateTC(dt);

   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);

   // update TC associated with display
   if (display != nullptr) display->updateTC(dt);
}

// update non-time critical stuff here
void FoxStation::updateData(const double dt)
{
   // update our display
   if (display != nullptr) display->updateData(dt);

   BaseClass::updateData(dt);
}

bool FoxStation::setSlotMainDisplay(FoxDisplay* const msg)
{
   if (display != nullptr) {
      display->container(nullptr);
   }
   display = msg;
   if (display != nullptr) {
      display->container(this);
   }
   return true;
}

base::Object* FoxStation::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

}
}

