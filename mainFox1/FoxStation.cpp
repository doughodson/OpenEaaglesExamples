
#include "FoxStation.h"
#include "FoxDisplay.h"

#include "openeaagles/basic/Timers.h"

namespace oe {
namespace example {

IMPLEMENT_SUBCLASS(FoxStation, "FoxStation")
EMPTY_SERIALIZER(FoxStation)
EMPTY_DELETEDATA(FoxStation)

// slot table for this class type
BEGIN_SLOTTABLE(FoxStation)
   "maindisplay",         // 1) main display
END_SLOTTABLE(FoxStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(FoxStation)
   ON_SLOT(1, setSlotMainDisplay, FoxDisplay)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
FoxStation::FoxStation()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void FoxStation::copyData(const FoxStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (org.display != nullptr)
      setSlotMainDisplay( org.display->clone() );
   else
      setSlotMainDisplay(nullptr);
}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void FoxStation::updateTC(const LCreal dt)
{
   // First update the simulation
   BaseClass::updateTC(dt);

   Basic::Timer::updateTimers(dt);
   BasicGL::Graphic::flashTimer(dt);

   // Update any TC stuff in our main display
   if (display != nullptr) display->updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void FoxStation::updateData(const LCreal dt)
{
   // Update any stuff in our main display
   if (display != nullptr) display->updateData(dt);

   BaseClass::updateData(dt);
}

//
//
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

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* FoxStation::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

} // end example namespace
} // end oe namespace

