//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#ifndef __oe_example_TestStation_H__
#define __oe_example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
   namespace Glut  { class GlutDisplay; }

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
//   glutDisplay  <BasicGL::GlutDisplay>  ! All of our display components
//------------------------------------------------------------------------------
class TestStation : public Simulation::Station
{
   DECLARE_SUBCLASS(TestStation, Simulation::Station)

public:
   TestStation();

   // Step our "ownship" to the next local air vehicle
   void stepOwnshipPlayer();

   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

private:
   bool setSlotGlutDisplay(Glut::GlutDisplay* const msg);

   basic::safe_ptr<Glut::GlutDisplay> glutDisplay;
   bool glutDisplayInit;
};

} // End example namespace
} // End oe namespace

#endif
