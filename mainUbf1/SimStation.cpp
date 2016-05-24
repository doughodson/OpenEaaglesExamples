//------------------------------------------------------------------------------
// Class: SimStation
//------------------------------------------------------------------------------

#include "SimStation.h"

#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/base/Identifier.h"
#include "openeaagles/base/Boolean.h"
#include "openeaagles/base/NetHandler.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"
#include "openeaagles/base/functors/Tables.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/units/Angles.h"
#include "openeaagles/base/units/Times.h"
#include "openeaagles/base/osg/Vec4"

namespace oe {
namespace example {

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
    ON_SLOT( 1, setSlotMainDisplay, glut::GlutDisplay)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SimStation::SimStation()
{
    STANDARD_CONSTRUCTOR()

    mainDisplay = nullptr;
    displayInit = false;
}

//------------------------------------------------------------------------------
// reset() -- Reset the station
//------------------------------------------------------------------------------
void SimStation::reset()
{
    // setup ownship player pointer
    setOwnshipByName( getOwnshipName()->getString() );

    if (!displayInit && mainDisplay != nullptr) {
        mainDisplay->createWindow();
        base::Pair* p = mainDisplay->findByType(typeid(graphics::Page));
        if (p != nullptr) mainDisplay->focus(static_cast<graphics::Graphic*>(p->object()));
        else mainDisplay->focus(nullptr);
        displayInit = true;
    }
    // reset all of our subcomponents
    if (mainDisplay != nullptr) mainDisplay->reset();

    // reset our baseclass
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void SimStation::updateTC(const double dt)
{
    // First update the simulation
    BaseClass::updateTC(dt);

    base::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);

    // Update any TC stuff in our main display
    if (mainDisplay != nullptr) mainDisplay->updateTC(dt);
}

//------------------------------------------------------------------------------
// stepOwnshipPlayer() -- Step to the next local player
//------------------------------------------------------------------------------
void SimStation::stepOwnshipPlayer()
{
   base::PairStream* pl = getSimulation()->getPlayers();
   if (pl != nullptr) {

      simulation::Player* f = nullptr;
      simulation::Player* n = nullptr;
      bool found = false;

      // Find the next player
      base::List::Item* item = pl->getFirstItem();
      while (item != nullptr) {
         base::Pair* pair = static_cast<base::Pair*>(item->getValue());
         if (pair != nullptr) {
            simulation::Player* ip = static_cast<simulation::Player*>(pair->object());
            if ( ip->isMode(simulation::Player::ACTIVE) &&
               ip->isLocalPlayer() &&
               ip->isClassType(typeid(simulation::AirVehicle))
               ) {
                  if (f == nullptr) { f = ip; }  // Remember the first
                  if (found) { n = ip; ; break; }
                  if (ip == getOwnship()) found = true;
            }
         }
         item = item->getNext();
      }
      if (found && n == nullptr) n = f;
      if (n != nullptr) setOwnshipPlayer(n);

      pl->unref();
    }
}

//------------------------------------------------------------------------------
// Set Slot Functions
//------------------------------------------------------------------------------

// Main display
bool SimStation::setSlotMainDisplay(glut::GlutDisplay* const d)
{
    if (mainDisplay != nullptr) mainDisplay->container(nullptr);
    mainDisplay = d;
    if (mainDisplay != nullptr) mainDisplay->container(this);
    displayInit = false;
    return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for graphics::Page
//------------------------------------------------------------------------------
base::Object* SimStation::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}
}
