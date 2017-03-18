
#include "DspRwr.hpp"

#include "openeaagles/models/system/Rwr.hpp"

namespace oe {
namespace xpanel {

IMPLEMENT_SUBCLASS(DspRwr, "DspRwr")
EMPTY_SLOTTABLE(DspRwr)
EMPTY_SERIALIZER(DspRwr)
EMPTY_DELETEDATA(DspRwr)

DspRwr::DspRwr()
{
   STANDARD_CONSTRUCTOR()
}

void DspRwr::copyData(const DspRwr& org, const bool)
{
   BaseClass::copyData(org);
   rwr = nullptr;
}

void DspRwr::updateData(const double dt)
{
   // Update base classes stuff
   BaseClass::updateData(dt);
}

void DspRwr::drawFunc()
{
   // Need a RWR to draw; if not, just draw a big X
   if (rwr == nullptr) {
      glBegin(GL_LINES);
         glVertex3d(-1.0, -1.0, 0.0);
         glVertex3d( 1.0,  1.0, 0.0);
         glVertex3d(-1.0,  1.0, 0.0);
         glVertex3d( 1.0, -1.0, 0.0);
      glEnd();
      return;
   }

   // ---
   // Draw the RWR signal rays
   // ---

   GLdouble  ocolor[4];
   glGetDoublev(GL_CURRENT_COLOR,ocolor);

   glColor3d(0.0, 1.0, 0.0);

   unsigned int n = rwr->getNumberOfRays();
   for (unsigned int i = 0; i < n; i++) {
      GLdouble azr = (base::angle::D2RCC *  rwr->getRayAzimuth(i) );
      GLdouble pwr = rwr->getRay(i);
      GLdouble up = cos(azr) * pwr;
      GLdouble right = sin(azr) * pwr;
      glBegin(GL_LINES);
         glVertex3d( 0.0,  0.0, 0.0);
         glVertex3d( right, up, 0.0);
      glEnd();
   }

   glColor4dv(ocolor);
}

}
}
