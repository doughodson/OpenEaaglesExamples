//------------------------------------------------------------------------------
// Worms
//------------------------------------------------------------------------------

#include "Worm.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(Worm,"Worm")

// slot table
BEGIN_SLOTTABLE(Worm)
  "speed",            // 1: speed
  "startAngle",       // 2: starting angle (off X axis)
END_SLOTTABLE(Worm)
// slot map
BEGIN_SLOT_MAP(Worm)
  ON_SLOT(1, realSpeed, Eaagles::Basic::Number)
  ON_SLOT(2, setAngle, Eaagles::Basic::Angle)
  ON_SLOT(2, setAngle, Eaagles::Basic::Number)
END_SLOT_MAP()
// events
BEGIN_EVENT_HANDLER(Worm)
END_EVENT_HANDLER()

EMPTY_DELETEDATA(Worm)
EMPTY_SERIALIZER(Worm)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Worm::Worm()
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
void Worm::copyData(const Worm& org, const bool cc)
{
  BaseClass::copyData(org);

  if (cc) {
    iangle = 0;
  }

  if (iangle != 0) { iangle->unref(); iangle = 0; }
  if (org.iangle != 0) iangle = org.iangle->clone();
  
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

  for (int i = 0; i < nTrails; i++) {
    trail[i] = org.trail[i];
  }
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void Worm::reset()
{
  BaseClass::reset();

  xPos = 0;
  yPos =0;
  nTrails = 0;
  if (iangle != 0) {
    Eaagles::Basic::Radians radians;
    setStartAngle((Eaagles::LCreal)radians.convert(*iangle));
  }
}

//------------------------------------------------------------------------------
// setStartAngle() -- set starting angle
//------------------------------------------------------------------------------
void Worm::setStartAngle(const Eaagles::LCreal radians)
{
  sangle = radians;
  dx = lcCos(sangle) * speed;
  dy = lcSin(sangle) * speed;
}

//------------------------------------------------------------------------------
// setSpeed() -- set speed
//------------------------------------------------------------------------------
void Worm::setSpeed(const Eaagles::LCreal xx)
{
  speed = xx;
  dx = lcCos(sangle) * speed;
  dy = lcSin(sangle) * speed;
}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void Worm::updateTC(const Eaagles::LCreal dt)
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
void Worm::updateData(const Eaagles::LCreal dt)
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
void Worm::drawFunc()
{
  glBegin(GL_LINE_STRIP);
  int idx = index - 1;
  for (int i = 0; i < nTrails; i++) {
    if (idx < 0) idx = maxHist - 1;
    lcVertex2v(trail[idx--].ptr());
  }
  glEnd();
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Eaagles::Basic::Object* Worm::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

//SLOTTABLE FUNCTIONS//
//------------------------------------------------------------------------------
// realSpeed() -- sets the starting real speed
//------------------------------------------------------------------------------
bool Worm::realSpeed(const Eaagles::Basic::Number* const rsobj)
{
  bool ok = false;
  if (rsobj != 0) {
    setSpeed(rsobj->getReal());
    ok = true;
  }
  return ok;
}

//------------------------------------------------------------------------------
// setAngle() -- sets the starting angle using an Angle parameter
//------------------------------------------------------------------------------ 
bool Worm::setAngle(const Eaagles::Basic::Angle* const saobj)
{
  bool ok = false;
  if (saobj != 0) {
    Eaagles::Basic::Radians radians;
    setStartAngle((Eaagles::LCreal)radians.convert(*saobj));
    iangle = saobj;
    iangle->ref();
    ok = true;
  }
  return ok;
}

//------------------------------------------------------------------------------
// setAngle() -- sets the starting angle using an Number parameter
//------------------------------------------------------------------------------ 
bool Worm::setAngle(const Eaagles::Basic::Number* const saobj)
{
  bool ok = false;
  if (saobj != 0) {
    setStartAngle(saobj->getReal());
    ok = true;
  }
  return ok;
}

} // namespace Tutorial
} // namespace Eaagles

