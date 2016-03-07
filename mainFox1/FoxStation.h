//------------------------------------------------------------------------------
// Class: FoxStation
//
// Description: Station class that a FoxDisplay can be attached
//------------------------------------------------------------------------------
#ifndef __oe_example_FoxStation_H__
#define __oe_example_FoxStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace example {

class FoxDisplay;

class FoxStation : public simulation::Station
{
   DECLARE_SUBCLASS(FoxStation, simulation::Station)

public:
   FoxStation();

   // Displays
   FoxDisplay* getMainDisplay()                     { return display; }

   void updateTC(const double dt = 0.0) override;
   void updateData(const double dt = 0.0) override;

protected:
   // Slot functions
   bool setSlotMainDisplay(FoxDisplay* const msg);

private:

   base::safe_ptr<FoxDisplay> display;
};

} // End example namespace
} // End oe namespace

#endif
