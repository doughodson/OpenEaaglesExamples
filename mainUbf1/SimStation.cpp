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
EMPTY_COPYDATA(SimStation)
EMPTY_DELETEDATA(SimStation)

// slot table for this class type
BEGIN_SLOTTABLE(SimStation)
    "display",                  //  1) Main Display
END_SLOTTABLE(SimStation)

//  Map slot table to handles 
BEGIN_SLOT_MAP(SimStation)
    ON_SLOT( 1, setSlotMainDisplay, Glut::GlutDisplay)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SimStation::SimStation()
{
    STANDARD_CONSTRUCTOR()

    mainDisplay = 0;
    displayInit = false;
}

//------------------------------------------------------------------------------
// reset() -- Reset the station 
//------------------------------------------------------------------------------
void SimStation::reset()
{
    // setup ownship player pointer
    setOwnshipByName( getOwnshipName()->getString() );

    if (!displayInit && mainDisplay != 0) {
        mainDisplay->createWindow();
        Basic::Pair* p = mainDisplay->findByType(typeid(BasicGL::Page));
        if (p != 0) mainDisplay->focus((BasicGL::Graphic*)(p->object()));
        else mainDisplay->focus(0);
        displayInit = true;        
    }
    // reset all of our subcomponents
    if (mainDisplay != 0) mainDisplay->reset();

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

// Main display
bool SimStation::setSlotMainDisplay(Glut::GlutDisplay* const d)
{
    if (mainDisplay != 0) mainDisplay->container(0);
    mainDisplay = d;
    if (mainDisplay != 0) mainDisplay->container(this);
    displayInit = false;
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
