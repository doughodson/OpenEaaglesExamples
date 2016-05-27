
#include "TestStation.h"
#include "Display.h"

#include "openeaagles/simulation/Gimbal.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/Simulation.h"

#include "openeaagles/base/Identifier.h"
#include "openeaagles/base/Boolean.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"
#include "openeaagles/base/units/Angles.h"
#include "openeaagles/base/osg/Vec4"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStation,"TestStation")
EMPTY_SERIALIZER(TestStation)
EMPTY_DELETEDATA(TestStation)

// slot table for this class type
BEGIN_SLOTTABLE(TestStation)
    "display",
END_SLOTTABLE(TestStation)

//  Map slot table to handles
BEGIN_SLOT_MAP(TestStation)
   ON_SLOT(1, setDisplay, Display)
END_SLOT_MAP()

TestStation::TestStation()
{
    STANDARD_CONSTRUCTOR()

    display = nullptr;
    displayInit = false;
}

void TestStation::copyData(const TestStation& org, const bool)
{
    BaseClass::copyData(org);

    display = nullptr;
    displayInit = false;
}

void TestStation::updateTC(const double dt)
{
   BaseClass::updateTC(dt);

   if (display != nullptr) display->updateTC(dt);
}

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

base::Object* TestStation::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}
