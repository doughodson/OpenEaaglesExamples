
#include "TestOne.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(TestOne,"TestOne")

//------------------------------------------------------------------------------
// slot table for this class type
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(TestOne)
    "speed",       // speed
    "startAngle",  // starting angle (off X axis)
END_SLOTTABLE(TestOne)

//------------------------------------------------------------------------------
// slot mapping for this class type - replaces setSlotByIndex() using a macro
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(TestOne)
    ON_SLOT(1, realSpeed, Basic::Number)
    ON_SLOT(2, setAngle, Basic::Angle)
    ON_SLOT(2, setAngle, Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// event handler macro - takes place of event() using a macro
//------------------------------------------------------------------------------
BEGIN_EVENT_HANDLER(TestOne)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestOne::TestOne()
{
    STANDARD_CONSTRUCTOR()

    leftLimit(-10.0);
    rightLimit(10.0);
    bottomLimit(-10.0);
    topLimit(10.0);
    setPosition(0.0, 0.0);
    xOld = 0.0;
    yOld = 0.0;
    nTrails = 0;
    index  = 0;
    sangle = 0.0;
    setSpeed(10.0);
    iangle = 0;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void TestOne::copyData(const TestOne& org, const bool)
{
    int i = 0;

    BaseClass::copyData(org);

    if (iangle != 0) iangle->unref();
    if (org.iangle != 0) iangle = org.iangle->clone();
    else iangle = 0;

    left = org.left;
    right = org.right;
    bottom = org.bottom;
    top = org.top;
    xPos = org.xPos;
    yPos = org.yPos;
    xOld = org.xOld;
    yOld = org.yOld;
    dx = org.dx;
    dy = org.dy;
    speed = org.speed;
    sangle = org.sangle;
    nTrails = org.nTrails;
    index   = org.index;
    for (i = 0; i < nTrails; i++) {
        trail[i] = org.trail[i];
    }
}

EMPTY_DELETEDATA(TestOne)

//------------------------------------------------------------------------------
// reset() -- 
//------------------------------------------------------------------------------
void TestOne::reset()
{
    BaseClass::reset();
    xPos = 0;
    yPos =0;
    nTrails = 0;
    if (iangle != 0) {
        Basic::Radians radians;
        setStartAngle(static_cast<LCreal>(radians.convert(*iangle)));
    }
}

//------------------------------------------------------------------------------
// setStartAngle() -- set starting angle
//------------------------------------------------------------------------------
void TestOne::setStartAngle(const LCreal radians)
{
    sangle = radians;
    dx = lcCos(sangle) * speed;
    dy = lcSin(sangle) * speed;
}

//------------------------------------------------------------------------------
// setSpeed() -- set speed
//------------------------------------------------------------------------------
void TestOne::setSpeed(const LCreal xx)
{
    speed = xx;
    dx = lcCos(sangle) * speed;
    dy = lcSin(sangle) * speed;
}


//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void TestOne::updateTC(const LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateTC(dt);

    // ---
    // Move
    // ---

    xPos += dx*dt;
    if (xPos > right) {
        xPos = right - (xPos - right);
        dx = -dx;
    }
    else if (xPos < left) {
        xPos = left - (xPos - left);
        dx = -dx;
    }

    yPos += dy*dt;
    if (yPos > top) {
        yPos = top - (yPos - top);
        dy = -dy;
    }
    else if (yPos < bottom) {
        yPos = bottom - (yPos - bottom);
        dy = -dy;
    }

}


//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestOne::updateData(const LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateData(dt);

    // ---
    // Save the point every pass (if it has changed)
    // ---
    if (nTrails == 0 || xPos != xOld || yPos != yOld) {
        trail[index++].set(xPos, yPos);
        if (index >= maxHist) index = 0;
        if (nTrails < maxHist) nTrails++;
        xOld = xPos;
        yOld = yPos;
    }
}


//------------------------------------------------------------------------------
// drawFunc() -- 
//------------------------------------------------------------------------------
void TestOne::drawFunc()
{
    glBegin(GL_LINE_STRIP);
    int idx = index - 1;
    int i = 0;
    while (i < nTrails) {
        if (idx < 0) idx = maxHist - 1;
        lcVertex2v(trail[idx--].ptr());
        i++;
    }
    glEnd();
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Rgb
//------------------------------------------------------------------------------
Basic::Object* TestOne::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize() -- print functions
//------------------------------------------------------------------------------
std::ostream& TestOne::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
    int j = 0;
    if ( !slotsOnly ) {
        sout << "( " << getFactoryName() << std::endl;
        j = 4;
    }

    indent(sout,i+j);
    sout << "speed: " << speed << std::endl;

    if (iangle != 0) {
        indent(sout,i+j);
        sout << "startAngle: " << *iangle << std::endl;
    }

    BaseClass::serialize(sout,i+j,true);

    if ( !slotsOnly ) {
        indent(sout,i);
        sout << ")" << std::endl;
    }
    return sout;
}


//SLOTTABLE FUNCTIONS//
//------------------------------------------------------------------------------
// realSpeed() -- sets the starting real speed
//------------------------------------------------------------------------------
bool TestOne::realSpeed(const Basic::Number* const rsobj)
{
    if (rsobj != 0) setSpeed(rsobj->getReal());
    return true;
}

//------------------------------------------------------------------------------
// setAngle() -- sets the starting angle using an Basic::Angle parameter
//------------------------------------------------------------------------------ 
bool TestOne::setAngle(Basic::Angle* saobj)
{
    if (saobj != 0) {
        Basic::Radians radians;
        setStartAngle(static_cast<LCreal>(radians.convert(*saobj)));
        iangle = saobj;
        iangle->ref();
    }
    return true;
}

//------------------------------------------------------------------------------
// setAngle() -- sets the starting angle using an Basic::Number parameter
//------------------------------------------------------------------------------ 
bool TestOne::setAngle(const Basic::Number* const saobj)
{
    setStartAngle(saobj->getReal());
    return true;
}

} // End Example namespace
} // End Eaagles namespace
