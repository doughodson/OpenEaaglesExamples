
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
    "mapDisplay",
END_SLOTTABLE(TestStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(TestStation)
    ON_SLOT(1, setSlotGlutDisplay, glut::GlutDisplay)
    ON_SLOT(2, setSlotMapDisplay, glut::GlutDisplay)
END_SLOT_MAP()

TestStation::TestStation()
{
   STANDARD_CONSTRUCTOR()

   glutDisplay = nullptr;
   glutDisplayInit = false;
   mapDisplay = nullptr;
   mapDisplayInit = false;

}

void TestStation::copyData(const TestStation& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      glutDisplay = nullptr;
      mapDisplay = nullptr;
   }

   setSlotGlutDisplay(nullptr);
   glutDisplayInit = false;
   setSlotMapDisplay(nullptr);
   mapDisplayInit = false;
}

void TestStation::deleteData()
{
   setSlotGlutDisplay(nullptr);
   setSlotMapDisplay(nullptr);
}

void TestStation::updateTC(const double dt)
{
   // manage the timers
   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);

   if (glutDisplay != nullptr) glutDisplay->updateTC(dt);
   if (mapDisplay != nullptr) mapDisplay->updateTC(dt);

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

   // create the MAP window
   if (!mapDisplayInit && mapDisplay != nullptr) {
      mapDisplay->createWindow();
      mapDisplay->focus(mapDisplay);
      mapDisplayInit = true;
   }
}

bool TestStation::setSlotGlutDisplay(glut::GlutDisplay* const d)
{
   glutDisplay = d;
   glutDisplay->container(this);
   return true;
}

bool TestStation::setSlotMapDisplay(glut::GlutDisplay* const d)
{
   mapDisplay = d;
   mapDisplay->container(this);
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
