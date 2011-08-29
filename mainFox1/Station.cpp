
#include "Station.h"
#include "Display.h"

#include "openeaagles/basic/Timers.h"

namespace Eaagles {
namespace mainFox {

IMPLEMENT_SUBCLASS(Station,"FoxStation")
EMPTY_SERIALIZER(Station)

// slot table for this class type
BEGIN_SLOTTABLE(Station)
    "maindisplay",      // 1) sets our main display
END_SLOTTABLE(Station)

//  Map slot table to handles 
BEGIN_SLOT_MAP(Station)
    ON_SLOT(1, setSlotMainDisplay, Display)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Station::Station() 
{
  STANDARD_CONSTRUCTOR()
  display = 0;
//   app = 0;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void Station::copyData(const Station& org, const bool cc)
{
    BaseClass::copyData(org);

    if (cc) {
        display = 0;
//        app = 0;
    }
    
    if (display != 0) display->unref();
    if (org.display != 0) {
        display = (Display*)org.display->clone();
        display->ref();
    }
//    app = 0;
//    app = org.app;
}

void Station::deleteData()
{
   if (display != 0)
     display->unref();
   display = 0;
//   app = 0;

}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void Station::updateTC(const LCreal dt)
{
    // First update the simulation
    BaseClass::updateTC(dt);

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);

    // Update any TC stuff in our main display
    if (display != 0) display->updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void Station::updateData(const LCreal dt)
{
   // Update any stuff in our main display
   if (display != 0) display->updateData(dt);
   
   BaseClass::updateData(dt);
} 

//------------------------------------------------------------------------------
// Set Slot Functions
//------------------------------------------------------------------------------
// Display
bool Station::setSlotMainDisplay(Display* const msg)
{
    if (display != 0) {
        display->container(0);
        display->unref();
    }
    display = msg;
    if (display != 0) {
        display->container(this);
        display->ref();
    }
    return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Page
//------------------------------------------------------------------------------
Basic::Object* Station::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

} // end mainFox namespace
} // end Eaagles namespace
