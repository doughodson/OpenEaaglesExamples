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
namespace Example {

IMPLEMENT_SUBCLASS(TestStation,"TestStation")

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "glutDisplay",
    "mapDisplay",
END_SLOTTABLE(TestStation)

//  Map slot table to handles 
BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, Glut::GlutDisplay)
    ON_SLOT(2, setSlotMapDisplay, Glut::GlutDisplay)
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
   mapDisplay = 0;
   mapDisplayInit = false;

}

// copy member data
void TestStation::copyData(const TestStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      glutDisplay = 0;
      mapDisplay = 0;
   }

   setSlotGlutDisplay(0);
   glutDisplayInit = false;
   setSlotMapDisplay(0);
   mapDisplayInit = false;
}

// delete member data
void TestStation::deleteData()
{
   setSlotGlutDisplay(0);
   setSlotMapDisplay(0);
}

//------------------------------------------------------------------------------
// updateTC() -- Update time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateTC(const LCreal dt)
{
   // manage the timers
   Basic::Timer::updateTimers(dt);
   BasicGL::Graphic::flashTimer(dt);

   if (glutDisplay != 0) glutDisplay->updateTC(dt);
   if (mapDisplay != 0) mapDisplay->updateTC(dt);

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

   // create the MAP window
   if (!mapDisplayInit && mapDisplay != 0) {
      mapDisplay->createWindow();
      mapDisplay->focus(mapDisplay);
      mapDisplayInit = true;
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

bool TestStation::setSlotMapDisplay(Glut::GlutDisplay* const d)
{
   mapDisplay = d;
   mapDisplay->container(this);
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

}
}
