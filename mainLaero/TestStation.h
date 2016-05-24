//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#ifndef __oe_example_TestStation_H__
#define __oe_example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace base { class Number; }
namespace glut { class GlutDisplay; }

namespace example {

//------------------------------------------------------------------------------
// Class: TestStation
// Description: Test station class that adds our graphics, which is managed by
//              a GlutDisplay, adds processing of the Hands On Throttle And Stick
//              (HOTAS) device, which is usually just a joystick, and adds stepping
//              of our ownship to the next local, air vehicle player.
//
// Factory name: TestStation
// Slots:
//   glutDisplay  <graphics::GlutDisplay>  ! All of our display components
//------------------------------------------------------------------------------
class TestStation : public simulation::Station
{
   DECLARE_SUBCLASS(TestStation,simulation::Station)

public:
   TestStation();

   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;
   virtual void reset() override;

private:
   bool setSlotGlutDisplay(glut::GlutDisplay* const msg);
   bool setSlotMapDisplay(glut::GlutDisplay* const msg);

   base::safe_ptr<glut::GlutDisplay> glutDisplay;
   base::safe_ptr<glut::GlutDisplay> mapDisplay;
   bool glutDisplayInit;
   bool mapDisplayInit;
};

}
}

#endif
