//------------------------------------------------------------------------------
// Class: SimStation
//------------------------------------------------------------------------------
#ifndef __oe_example_SimStation_H__
#define __oe_example_SimStation_H__

//#include "agent/AgentStation.h"
#include "openeaagles/simulation/Station.h"

namespace oe {

namespace base { class Table1; class PairStream; }
namespace glut { class GlutDisplay; }
namespace simulation { class AirVehicle; }

namespace example {

//------------------------------------------------------------------------------
// Class: SimStation
//
// Description: Example station class that adds our graphics, which is managed by
//              a GlutDisplay, adds processing of the Hands On Throttle And Stick
//              (HOTAS) device, which is usually just a joystick, and adds stepping
//              of our ownship to the next local, air vehicle player.
//
// Factory name: SimStation
// Slots:
//      display       <graphics::GlutDisplay>  ! Main graphics display
//
//------------------------------------------------------------------------------
class SimStation : public simulation::Station
{
   DECLARE_SUBCLASS(SimStation, simulation::Station)

public:
    SimStation();

   // Step our "ownship" to the next local air vehicle
   void stepOwnshipPlayer();

   // Slot functions
   virtual bool setSlotMainDisplay(glut::GlutDisplay* const d);

   void updateTC(const LCreal dt = 0.0) override;
   void reset() override;

private:

    // Main Display
    base::safe_ptr<glut::GlutDisplay> mainDisplay;
    bool displayInit;

};

} // End example namespace
} // End oe namespace

#endif
