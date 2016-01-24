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

namespace oe {
namespace example {

IMPLEMENT_SUBCLASS(TestStation,"TestStation")
EMPTY_SERIALIZER(TestStation)

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "display",
END_SLOTTABLE(TestStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(TestStation)
   ON_SLOT(1, setDisplay, example::Display)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestStation::TestStation()
{
    STANDARD_CONSTRUCTOR()

    display = nullptr;
    displayInit = false;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void TestStation::copyData(const TestStation& org, const bool)
{
    BaseClass::copyData(org);

    display = nullptr;
    displayInit = false;
}

EMPTY_DELETEDATA(TestStation)

//------------------------------------------------------------------------------
// updateTC() -- Update time critical stuff here
//------------------------------------------------------------------------------
void TestStation::updateTC(const LCreal dt)
{
   BaseClass::updateTC(dt);

   if (display != nullptr) display->updateTC(dt);
}

//------------------------------------------------------------------------------
// reset() -- Reset the station
//------------------------------------------------------------------------------
void TestStation::reset()
{
    BaseClass::reset();
    if (!displayInit && display != nullptr) {
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
basic::Object* TestStation::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

} // End example namespace
} // End oe namespace

