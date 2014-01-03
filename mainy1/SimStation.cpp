//------------------------------------------------------------------------------
// Class: SimStation
//------------------------------------------------------------------------------

#include "SimStation.h"

#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/basic/Identifier.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Tables.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Times.h"
#include "openeaagles/basic/osg/Vec4"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(SimStation,"SimStation")
EMPTY_SERIALIZER(SimStation)

// slot table for this class type
BEGIN_SLOTTABLE(SimStation)
    "display",                  //  1) Main Display
    "autoResetTimer",           //  2: Auto RESET timer value (Basic::Time); default: zero (no auto reset)
END_SLOTTABLE(SimStation)

//  Map slot table to handles 
BEGIN_SLOT_MAP(SimStation)
    ON_SLOT( 1, setSlotMainDisplay,         Glut::GlutDisplay)
    ON_SLOT( 2, setSlotAutoResetTime,       Basic::Time)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SimStation::SimStation()
{
    STANDARD_CONSTRUCTOR()

    mainDisplay = 0;
    displayInit = false;

    autoResetTimer0 = 0;
    autoResetTimer = 0.0f;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void SimStation::copyData(const SimStation& org, const bool cc)
{
    BaseClass::copyData(org);
    if (cc) {
        autoResetTimer0 = 0;
    }    

    setSlotAutoResetTime(org.autoResetTimer0);
    autoResetTimer = org.autoResetTimer;
}


void SimStation::deleteData()
{
}

//------------------------------------------------------------------------------
// reset() -- Reset the station 
//------------------------------------------------------------------------------
void SimStation::reset()
{
    if (!displayInit && mainDisplay != 0) {
        mainDisplay->createWindow();
        Basic::Pair* p = mainDisplay->findByType(typeid(BasicGL::Page));
        if (p != 0) mainDisplay->focus((BasicGL::Graphic*)(p->object()));
        else mainDisplay->focus(0);
        displayInit = true;        
    }
    // reset all of our subcomponents
    if (mainDisplay != 0) mainDisplay->reset();

    // auto reset timer
    if (autoResetTimer0 != 0) {
        autoResetTimer = Basic::Seconds::convertStatic(*autoResetTimer0);
    }
    else {
        autoResetTimer = 0;
    }
    
    // reset our baseclass 
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void SimStation::updateTC(const LCreal dt)
{
    // First update the simulation
    BaseClass::updateTC(dt);

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);
    
    // Update any TC stuff in our main display
    if (mainDisplay != 0) mainDisplay->updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void SimStation::updateData(const LCreal dt)
{
    // ### Don't call updateData for our 'mainDisplay', which is derived from
    // BasicGL::GlutDisplay, because BasicGL::GlutDisplay handles calling updateData() for it's
    // own displays.

    // ---
    // Auto RESET/FREEZE timer --
    // ---
    if ( autoResetTimer > 0 && getSimulation()->isNotFrozen() ) {
       autoResetTimer -= dt;
       if (autoResetTimer <= 0) {
         Basic::Boolean newFrz(true);
         getSimulation()->event(FREEZE_EVENT, &newFrz);
         this->event(RESET_EVENT);
       }
    }

    BaseClass::updateData(dt);
} 

//------------------------------------------------------------------------------
// stepOwnshipPlayer() -- Step to the next local player
//------------------------------------------------------------------------------
void SimStation::stepOwnshipPlayer()
{
   Basic::PairStream* pl = getSimulation()->getPlayers();
   if (pl != 0) {

      Simulation::Player* f = 0;
      Simulation::Player* n = 0;
      bool found = false;

      // Find the next player
      Basic::List::Item* item = pl->getFirstItem();
      while (item != 0) {
         Basic::Pair* pair = (Basic::Pair*)(item->getValue());
         if (pair != 0) {
            Simulation::Player* ip = (Simulation::Player*)( pair->object() );
            if ( ip->isMode(Simulation::Player::ACTIVE) &&
               ip->isLocalPlayer() &&
               ip->isClassType(typeid(Simulation::AirVehicle))
               ) {
                  if (f == 0) { f = ip; }  // Remember the first
                  if (found) { n = ip; ; break; }
                  if (ip == getOwnship()) found = true;
            }
         }
         item = item->getNext();
      }
      if (found && n == 0) n = f;
      if (n != 0) setOwnshipPlayer(n);

      pl->unref();
    }
}

//------------------------------------------------------------------------------
// Set Slot Functions
//------------------------------------------------------------------------------

// Main Display
bool SimStation::setSlotMainDisplay(Glut::GlutDisplay* const d)
{
    if (mainDisplay != 0) mainDisplay->container(0);
    mainDisplay = d;
    if (mainDisplay != 0) mainDisplay->container(this);
    displayInit = false;
    return true;
}

// setSlotAutoResetTime() -- Sets the startup RESET pulse timer
bool SimStation::setSlotAutoResetTime(const Basic::Time* const num)
{
    if (autoResetTimer0 != 0) {
        autoResetTimer0->unref();
        autoResetTimer0 = 0;
        autoResetTimer = -1.0f;
    }
    autoResetTimer0 = num;
    if (autoResetTimer0 != 0) {
        autoResetTimer0->ref();
        autoResetTimer = Basic::Seconds::convertStatic(*autoResetTimer0);
    }
    return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for BasicGL::Page
//------------------------------------------------------------------------------
Basic::Object* SimStation::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

} // End Example namespace
} // End Eaagles namespace
