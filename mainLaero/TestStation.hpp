
#ifndef __TestStation_H__
#define __TestStation_H__

#include "openeaagles/simulation/Station.hpp"

namespace oe {
namespace base { class Number; }
namespace glut { class GlutDisplay; }
}

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
class TestStation : public oe::simulation::Station
{
   DECLARE_SUBCLASS(TestStation, oe::simulation::Station)

public:
   TestStation();

   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;
   virtual void reset() override;

private:
   bool setSlotGlutDisplay(oe::glut::GlutDisplay* const msg);
   bool setSlotMapDisplay(oe::glut::GlutDisplay* const msg);

   oe::base::safe_ptr<oe::glut::GlutDisplay> glutDisplay;
   oe::base::safe_ptr<oe::glut::GlutDisplay> mapDisplay;
   bool glutDisplayInit {};
   bool mapDisplayInit {};
};

#endif
