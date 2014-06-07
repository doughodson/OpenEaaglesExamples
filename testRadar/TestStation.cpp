//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#include "TestStation.h"

#include "openeaagles/simulation/Antenna.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/Timers.h"

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStation,"TestStation")

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "glutDisplay",
END_SLOTTABLE(TestStation)

//  Map slot table to handles 
BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, Glut::GlutDisplay)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor
TestStation::TestStation()
{
   STANDARD_CONSTRUCTOR()

   glutDisplay = 0;
   glutDisplayInit = false;

   rstSw1 = false;
   frzSw1 = false;
   wpnRelSw1 = false;
   tgtStepSw1 = false;
   incTagPlayerSw1 = false;
   bgAntenna = 0.0;
}

// copy member data
void TestStation::copyData(const TestStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      glutDisplay = 0;
   }

   setSlotGlutDisplay(0);
   glutDisplayInit = false;

   rstSw1 = org.rstSw1;
   frzSw1 = org.frzSw1;
   wpnRelSw1 = org.wpnRelSw1;
   tgtStepSw1 = org.tgtStepSw1;
   incTagPlayerSw1 = org.incTagPlayerSw1;
   bgAntenna = org.bgAntenna;
}

// delete member data
void TestStation::deleteData()
{
   setSlotGlutDisplay(0);
}

//------------------------------------------------------------------------------
// updateTC() -- Update time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateTC(const LCreal dt)
{
   // manage the timers
   Basic::Timer::updateTimers(dt);
   BasicGL::Graphic::flashTimer(dt);

   if (glutDisplay != 0) {
      glutDisplay->updateTC(dt);
   }

   BaseClass::updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateData(const LCreal dt)
{
   // ### Don't call updateData for our 'glutDisplay', which is derived from
   // BasicGL::GlutDisplay, because BasicGL::GlutDisplay handles calling updateData() for it's
   // own displays.

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
   if (!glutDisplayInit && glutDisplay != 0) {
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
   Basic::PairStream* pl = getSimulation()->getPlayers();
   if (pl != 0) {

      Simulation::Player* f = 0;
      Simulation::Player* n = 0;
      bool found = false;

      // Find the next player
      Basic::List::Item* item = pl->getFirstItem();
      while (item != 0) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         if (pair != 0) {
            Simulation::Player* ip = static_cast<Simulation::Player*>(pair->object());
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
// Set slot functions
//------------------------------------------------------------------------------

bool TestStation::setSlotGlutDisplay(Glut::GlutDisplay* const d)
{
   glutDisplay = d;
   glutDisplay->container(this);
   return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* TestStation::getSlotByIndex(const int si)
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

   if (glutDisplay != 0) {
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

} // End Test namespace
} // End Eaagles namespace
