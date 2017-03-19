
#include "Worm.hpp"
#include "openeaagles/base/units/Angles.hpp"

#include <cmath>

IMPLEMENT_SUBCLASS(Worm, "Worm")
EMPTY_DELETEDATA(Worm)
EMPTY_SERIALIZER(Worm)

BEGIN_SLOTTABLE(Worm)
   "speed",            // 1: speed
   "startAngle",       // 2: starting angle (off X axis)
END_SLOTTABLE(Worm)

BEGIN_SLOT_MAP(Worm)
   ON_SLOT(1, realSpeed, oe::base::Number)
   ON_SLOT(2, setAngle, oe::base::Angle)
   ON_SLOT(2, setAngle, oe::base::Number)
END_SLOT_MAP()

BEGIN_EVENT_HANDLER(Worm)
END_EVENT_HANDLER()

Worm::Worm()
{
   STANDARD_CONSTRUCTOR()
   setSpeed(10.0);
}

void Worm::copyData(const Worm& org, const bool)
{
   BaseClass::copyData(org);

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
      if (index >= MAX_HIST) index = 0;
      if (nTrails < MAX_HIST) nTrails++;
      xOld = xPos;
      yOld = yPos;
   }
}

void Worm::drawFunc()
{
   glBegin(GL_LINE_STRIP);
   int idx = index - 1;
   for (int i = 0; i < nTrails; i++) {
      if (idx < 0) idx = MAX_HIST - 1;
      lcVertex2v(trail[idx--].ptr());
   }
   glEnd();
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
