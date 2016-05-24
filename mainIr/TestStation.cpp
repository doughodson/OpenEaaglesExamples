
#include "TestStation.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"
#include "openeaagles/base/Timers.h"

#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Simulation.h"

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace example {

IMPLEMENT_SUBCLASS(TestStation,"TestStation")

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "glutDisplay",
END_SLOTTABLE(TestStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, glut::GlutDisplay)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor
TestStation::TestStation()
{
   STANDARD_CONSTRUCTOR()

   glutDisplay = nullptr;
   glutDisplayInit = false;
}

// copy member data
void TestStation::copyData(const TestStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      glutDisplay = nullptr;
   }

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
   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);

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
            simulation::Player* ip = static_cast<simulation::Player*>( pair->object() );
            if ( ip->isMode(simulation::Player::ACTIVE) &&
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

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

bool TestStation::setSlotGlutDisplay(glut::GlutDisplay* const d)
{
    glutDisplay = d;
    glutDisplay->container(this);
    return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
base::Object* TestStation::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
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

}
}
