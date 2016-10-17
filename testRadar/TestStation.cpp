
#include "TestStation.hpp"

#include "openeaagles/simulation/Antenna.hpp"
#include "openeaagles/simulation/AirVehicle.hpp"
#include "openeaagles/simulation/Simulation.hpp"
#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/base/Timers.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStation, "TestStation")

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "glutDisplay",
END_SLOTTABLE(TestStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, glut::GlutDisplay)
END_SLOT_MAP()

TestStation::TestStation()
{
   STANDARD_CONSTRUCTOR()

   glutDisplay = nullptr;
   glutDisplayInit = false;

   rstSw1 = false;
   frzSw1 = false;
   wpnRelSw1 = false;
   tgtStepSw1 = false;
   incTagPlayerSw1 = false;
   bgAntenna = 0.0;
}

void TestStation::copyData(const TestStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      glutDisplay = nullptr;
   }

   setSlotGlutDisplay(nullptr);
   glutDisplayInit = false;

   rstSw1 = org.rstSw1;
   frzSw1 = org.frzSw1;
   wpnRelSw1 = org.wpnRelSw1;
   tgtStepSw1 = org.tgtStepSw1;
   incTagPlayerSw1 = org.incTagPlayerSw1;
   bgAntenna = org.bgAntenna;
}

void TestStation::deleteData()
{
   setSlotGlutDisplay(nullptr);
}

void TestStation::updateTC(const double dt)
{
   // manage the timers
   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);

   if (glutDisplay != nullptr) {
      glutDisplay->updateTC(dt);
   }

   BaseClass::updateTC(dt);
}

void TestStation::updateData(const double dt)
{
   // ### Don't call updateData for our 'glutDisplay', which is derived from
   // graphics::GlutDisplay, because graphics::GlutDisplay handles calling updateData() for it's
   // own displays.

   BaseClass::updateData(dt);
}

void TestStation::reset()
{
   BaseClass::reset();

   // ---
   // Create the GLUT window
   // ---
   if (!glutDisplayInit && glutDisplay != nullptr) {
      glutDisplay->createWindow();
      glutDisplay->focus(glutDisplay);
      glutDisplayInit = true;
   }

}

//------------------------------------------------------------------------------
// stepOwnshipPlayer() -- Step to the next local player
//------------------------------------------------------------------------------
void TestStation::stepOwnshipPlayer()
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

bool TestStation::setSlotGlutDisplay(glut::GlutDisplay* const d)
{
   glutDisplay = d;
   glutDisplay->container(this);
   return true;
}

base::Object* TestStation::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

std::ostream& TestStation::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   if (glutDisplay != nullptr) {
      indent(sout,i+j);
      sout << "glutDisplay: ";
      glutDisplay->serialize(sout,i+j+4);
   }

   BaseClass::serialize(sout,i+j,true);

   if ( !slotsOnly ) {
      indent(sout,i);
      sout << ")" << std::endl;
   }

   return sout;
}
