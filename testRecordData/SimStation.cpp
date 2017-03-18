
#include "SimStation.hpp"

#include "openeaagles/simulation/Simulation.hpp"

#include "openeaagles/models/player/AirVehicle.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"

#include "openeaagles/base/Identifier.hpp"
#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/functors/Tables.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/base/units/Times.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(SimStation, "SimStation")
EMPTY_SERIALIZER(SimStation)
EMPTY_DELETEDATA(SimStation)

BEGIN_SLOTTABLE(SimStation)
    "display",                  //  1) Main Display
    "autoResetTimer",           //  2: Auto RESET timer value (base::Time); default: zero (no auto reset)
END_SLOTTABLE(SimStation)

BEGIN_SLOT_MAP(SimStation)
    ON_SLOT( 1, setSlotMainDisplay,         glut::GlutDisplay)
    ON_SLOT( 2, setSlotAutoResetTime,       base::Time)
END_SLOT_MAP()

SimStation::SimStation()
{
    STANDARD_CONSTRUCTOR()
}

void SimStation::copyData(const SimStation& org, const bool)
{
    BaseClass::copyData(org);

    setSlotAutoResetTime(org.autoResetTimer0);
    autoResetTimer = org.autoResetTimer;
}

void SimStation::reset()
{
    if (!displayInit && mainDisplay != nullptr) {
        mainDisplay->createWindow();
        base::Pair* p = mainDisplay->findByType(typeid(graphics::Page));
        if (p != nullptr) mainDisplay->focus(static_cast<graphics::Graphic*>(p->object()));
        else mainDisplay->focus(nullptr);
        displayInit = true;
    }
    // reset all of our subcomponents
    if (mainDisplay != nullptr) mainDisplay->reset();

    // auto reset timer
    if (autoResetTimer0 != nullptr) {
        autoResetTimer = base::Seconds::convertStatic(*autoResetTimer0);
    }
    else {
        autoResetTimer = 0;
    }

    // reset our baseclass
    BaseClass::reset();
}

void SimStation::updateTC(const double dt)
{
    // First update the simulation
    BaseClass::updateTC(dt);

    base::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);

    // Update any TC stuff in our main display
    if (mainDisplay != nullptr) mainDisplay->updateTC(dt);
}

void SimStation::updateData(const double dt)
{
    // ### Don't call updateData for our 'mainDisplay', which is derived from
    // graphics::GlutDisplay, because graphics::GlutDisplay handles calling updateData() for it's
    // own displays.

    // ---
    // Auto RESET/FREEZE timer --
    // ---
    if ( autoResetTimer > 0 && getSimulation()->isNotFrozen() ) {
       autoResetTimer -= dt;
       if (autoResetTimer <= 0) {
         base::Boolean newFrz(true);
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
   base::PairStream* pl = getSimulation()->getPlayers();
   if (pl != nullptr) {

      models::Player* f = nullptr;
      models::Player* n = nullptr;
      bool found = false;

      // Find the next player
      base::List::Item* item = pl->getFirstItem();
      while (item != nullptr) {
         const auto pair = static_cast<base::Pair*>(item->getValue());
         if (pair != nullptr) {
            const auto ip = static_cast<models::Player*>(pair->object());
            if ( ip->isMode(models::Player::ACTIVE) &&
               ip->isLocalPlayer() &&
               ip->isClassType(typeid(models::AirVehicle))
               ) {
                  if (f == nullptr) { f = ip; }  // Remember the first
                  if (found)        { n = ip; ; break; }
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

// Main Display
bool SimStation::setSlotMainDisplay(glut::GlutDisplay* const d)
{
    if (mainDisplay != nullptr) mainDisplay->container(nullptr);
    mainDisplay = d;
    if (mainDisplay != nullptr) mainDisplay->container(this);
    displayInit = false;
    return true;
}

// setSlotAutoResetTime() -- Sets the startup RESET pulse timer
bool SimStation::setSlotAutoResetTime(const base::Time* const num)
{
    if (autoResetTimer0 != nullptr) {
        autoResetTimer0->unref();
        autoResetTimer0 = nullptr;
        autoResetTimer = -1.0;
    }
    autoResetTimer0 = num;
    if (autoResetTimer0 != nullptr) {
        autoResetTimer0->ref();
        autoResetTimer = base::Seconds::convertStatic(*autoResetTimer0);
    }
    return true;
}

