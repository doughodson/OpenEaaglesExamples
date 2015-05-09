//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStation_H__
#define __Eaagles_Test_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
   namespace Basic { class Number; }
   namespace Glut { class GlutDisplay; }

namespace Test {

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
   DECLARE_SUBCLASS(TestStation,Simulation::Station)

public:
   TestStation();

   // Step our "ownship" to the next local air vehicle
   void stepOwnshipPlayer();

   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

private:
   bool setSlotGlutDisplay(Glut::GlutDisplay* const msg);

   Basic::safe_ptr<Glut::GlutDisplay> glutDisplay;
   bool glutDisplayInit;

   // Past (N-1) switches and values
   bool rstSw1;
   bool frzSw1;
   bool tgtStepSw1;
   bool wpnRelSw1;
   bool incTagPlayerSw1;
   LCreal bgAntenna;
};

} // End Test namespace
} // End Eaagles namespace

#endif
