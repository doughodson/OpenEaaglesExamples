
#include "Worm.h"
#include "openeaagles/base/units/Angles.h"

#include <cmath>

IMPLEMENT_SUBCLASS(Worm, "Worm")

// slot table
BEGIN_SLOTTABLE(Worm)
   "speed",            // 1: speed
   "startAngle",       // 2: starting angle (off X axis)
END_SLOTTABLE(Worm)
// slot map
BEGIN_SLOT_MAP(Worm)
   ON_SLOT(1, realSpeed, oe::base::Number)
   ON_SLOT(2, setAngle, oe::base::Angle)
   ON_SLOT(2, setAngle, oe::base::Number)
END_SLOT_MAP()
// events
BEGIN_EVENT_HANDLER(Worm)
END_EVENT_HANDLER()

EMPTY_DELETEDATA(Worm)
EMPTY_SERIALIZER(Worm)

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
   iangle = nullptr;
}

void Worm::copyData(const Worm& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      iangle = nullptr;
   }

   if (iangle != nullptr) { iangle->unref(); iangle = nullptr; }
   if (org.iangle != nullptr) iangle = org.iangle->clone();

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

void Worm::reset()
{
   BaseClass::reset();

   xPos = 0;
   yPos =0;
   nTrails = 0;
   if (iangle != nullptr) {
      oe::base::Radians radians;
      setStartAngle(static_cast<double>(radians.convert(*iangle)));
   }
}

void Worm::setStartAngle(const double radians)
{
   sangle = radians;
   dx = std::cos(sangle) * speed;
   dy = std::sin(sangle) * speed;
}

void Worm::setSpeed(const double xx)
{
   speed = xx;
   dx = std::cos(sangle) * speed;
   dy = std::sin(sangle) * speed;
}

void Worm::updateTC(const double dt)
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

void Worm::updateData(const double dt)
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

oe::base::Object* Worm::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

bool Worm::realSpeed(const oe::base::Number* const rsobj)
{
   bool ok = false;
   if (rsobj != nullptr) {
      setSpeed(rsobj->getReal());
      ok = true;
   }
   return ok;
}

bool Worm::setAngle(const oe::base::Angle* const saobj)
{
   bool ok = false;
   if (saobj != nullptr) {
      oe::base::Radians radians;
      setStartAngle(static_cast<double>(radians.convert(*saobj)));
      iangle = saobj;
      iangle->ref();
      ok = true;
   }
   return ok;
}

bool Worm::setAngle(const oe::base::Number* const saobj)
{
   bool ok = false;
   if (saobj != nullptr) {
      setStartAngle(saobj->getReal());
      ok = true;
   }
   return ok;
}
