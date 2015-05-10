//------------------------------------------------------------------------------
// Class: SimStation
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_SimStation_H__
#define __Eaagles_Test_SimStation_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
   namespace Basic { class Table1; }
   namespace Glut  { class GlutDisplay; }
   namespace Simulation { class AirVehicle; }

namespace Test {

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
//      display                 <BasicGL::GlutDisplay> ! Main graphics display
//      autoResetTimer          <Time>               ! Auto RESET timer value (Basic::Time); default: 0
//------------------------------------------------------------------------------
class SimStation : public Simulation::Station
{
    DECLARE_SUBCLASS(SimStation, Simulation::Station)

public:
    SimStation();

   // Step our "ownship" to the next local air vehicle
   void stepOwnshipPlayer();

   // Slot functions
   virtual bool setSlotMainDisplay(Glut::GlutDisplay* const d);
   virtual bool setSlotAutoResetTime(const Basic::Time* const num);     // Sets the auto RESET timer

   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

private:
    // Main Display
    Basic::safe_ptr<Glut::GlutDisplay> mainDisplay;
    bool displayInit;

    // Auto reset timer
    LCreal      autoResetTimer;      // Auto RESET timer (sends a RESET_EVENT after timeout)
    const Basic::Time* autoResetTimer0;   // Init value of the Auto RESET timer
};

} // End Test namespace
} // End Eaagles namespace

#endif

