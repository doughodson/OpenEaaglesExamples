
#include "TestStation.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/Timers.hpp"

#include "openeaagles/models/player/AirVehicle.hpp"

#include "openeaagles/simulation/Simulation.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"

IMPLEMENT_SUBCLASS(TestStation, "TestStation")

BEGIN_SLOTTABLE(TestStation)
    "glutDisplay",
END_SLOTTABLE(TestStation)

BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, oe::glut::GlutDisplay)
END_SLOT_MAP()

TestStation::TestStation()
{
   STANDARD_CONSTRUCTOR()
}

void TestStation::copyData(const TestStation& org, const bool)
{
   BaseClass::copyData(org);

   setSlotGlutDisplay(nullptr);
   glutDisplayInit = false;
}

// delete member data
void TestStation::deleteData()
{
   setSlotGlutDisplay(nullptr);
}

//------------------------------------------------------------------------------
// updateTC() -- Update time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateTC(const double dt)
{
   if (glutDisplay != nullptr) {
      glutDisplay->updateTC(dt);
   }
   BaseClass::updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateData(const double dt)
{
   // ### Don't call updateData for our 'glutDisplay', which is derived from
   // graphics::GlutDisplay, because graphics::GlutDisplay handles calling updateData() for it's
   // own displays.

   // manage the timers
   oe::base::Timer::updateTimers(dt);
   oe::graphics::Graphic::flashTimer(dt);

   BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// reset() -- Reset the station
//------------------------------------------------------------------------------
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
   oe::base::PairStream* pl = getSimulation()->getPlayers();
   if (pl != nullptr) {

      oe::models::Player* f = nullptr;
      oe::models::Player* n = nullptr;
      bool found = false;

      // Find the next player
      oe::base::List::Item* item = pl->getFirstItem();
      while (item != nullptr) {
         const auto pair = static_cast<oe::base::Pair*>(item->getValue());
         if (pair != nullptr) {
            const auto ip = static_cast<oe::models::Player*>( pair->object() );
            if ( ip->isMode(oe::models::Player::ACTIVE) &&
               ip->isLocalPlayer()
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

bool TestStation::setSlotGlutDisplay(oe::glut::GlutDisplay* const d)
{
    glutDisplay = d;
    glutDisplay->container(this);
    return true;
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
