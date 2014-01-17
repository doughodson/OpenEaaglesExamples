//------------------------------------------------------------------------------
// Class: FoxStation
//
// Description: Station class that a FoxDisplay can be attached
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_FoxStation_H__
#define __Eaagles_Example_FoxStation_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace Example {

class FoxDisplay;

class FoxStation : public Simulation::Station
{
   DECLARE_SUBCLASS(FoxStation, Simulation::Station)

public:

   FoxStation();

   // Displays
   FoxDisplay* getMainDisplay()    { return display; }

   // Component Interface
   virtual void updateTC(const LCreal dt = 0.0f);
   virtual void updateData(const LCreal dt = 0.0f);

protected:

   // Slot functions
   bool setSlotMainDisplay(FoxDisplay* const msg);

private:

   SPtr<FoxDisplay> display;
};

} // End Example namespace
} // End Eaagles namespace

#endif
