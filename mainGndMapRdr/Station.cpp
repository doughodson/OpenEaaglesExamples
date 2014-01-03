//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#include "Station.h"
#include "Display.h"

#include "openeaagles/simulation/Gimbal.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/Simulation.h"

#include "openeaagles/basic/Identifier.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/osg/Vec4"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(TestStation,"TestStation")
EMPTY_SERIALIZER(TestStation)

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "display",
END_SLOTTABLE(TestStation)

//  Map slot table to handles 
BEGIN_SLOT_MAP(TestStation)
   ON_SLOT(1, setDisplay, Example::Display)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestStation::TestStation()
{
    STANDARD_CONSTRUCTOR()

    display = 0;
    displayInit = false;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void TestStation::copyData(const TestStation& org, const bool)
{
    BaseClass::copyData(org);

    display = 0;
    displayInit = false;
}

EMPTY_DELETEDATA(TestStation)

//------------------------------------------------------------------------------
// updateTC() -- Update time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateTC(const LCreal dt)
{
   BaseClass::updateTC(dt);

   if (display != 0) display->updateTC(dt);
}

//------------------------------------------------------------------------------
// reset() -- Reset the station 
//------------------------------------------------------------------------------
void TestStation::reset()
{
    BaseClass::reset();
    if (!displayInit && display != 0) {
        display->createWindow();
        display->focus(display);
        displayInit = true;
    }
}

//------------------------------------------------------------------------------
// setDisplay() -- Set the Display
//------------------------------------------------------------------------------
bool TestStation::setDisplay(Display* const d)
{
    display = d;
    display->container(this);
    return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Page
//------------------------------------------------------------------------------
Basic::Object* TestStation::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

} // End Example namespace
} // End Eaagles namespace

