//------------------------------------------------------------------------------
// Class: TestStation
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestStation_H__
#define __Eaagles_Example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace Basic { class Number; }
namespace Glut { class GlutDisplay; }

namespace Example {

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

   // Basic::Component functions
   virtual void updateTC(const LCreal dt = 0.0f);
   virtual void updateData(const LCreal dt = 0.0f);
   virtual void reset();
    
private:
   bool setSlotGlutDisplay(Glut::GlutDisplay* const msg);
   bool setSlotMapDisplay(Glut::GlutDisplay* const msg);

   SPtr<Glut::GlutDisplay> glutDisplay;
   SPtr<Glut::GlutDisplay> mapDisplay;
   bool glutDisplayInit;
   bool mapDisplayInit;
};

}
}

#endif
