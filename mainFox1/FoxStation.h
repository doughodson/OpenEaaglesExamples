//------------------------------------------------------------------------------
// Class: FoxStation
//
// Description: Station class that a FoxDisplay can be attached
//------------------------------------------------------------------------------
#ifndef __oe_Example_FoxStation_H__
#define __oe_Example_FoxStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace Example {

class FoxDisplay;

class FoxStation : public Simulation::Station
{
   DECLARE_SUBCLASS(FoxStation, Simulation::Station)

public:
   FoxStation();

   // Displays
   FoxDisplay* getMainDisplay()                     { return display; }

   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;

protected:
   // Slot functions
   bool setSlotMainDisplay(FoxDisplay* const msg);

private:

   Basic::safe_ptr<FoxDisplay> display;
};

} // End Example namespace
} // End oe namespace

#endif
