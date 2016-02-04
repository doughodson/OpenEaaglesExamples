//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStation_H__
#define __oe_test_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
   namespace basic { class Number; }
   namespace glut { class GlutDisplay; }

namespace test {

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

   // Step our "ownship" to the next local air vehicle
   void stepOwnshipPlayer();

   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

private:
   bool setSlotGlutDisplay(glut::GlutDisplay* const msg);

   basic::safe_ptr<glut::GlutDisplay> glutDisplay;
   bool glutDisplayInit;

   // Past (N-1) switches and values
   bool rstSw1;
   bool frzSw1;
   bool tgtStepSw1;
   bool wpnRelSw1;
   bool incTagPlayerSw1;
   LCreal bgAntenna;
};

} // End test namespace
} // End oe namespace

#endif
