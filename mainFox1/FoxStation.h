
#ifndef __oe_example_FoxStation_H__
#define __oe_example_FoxStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace example {

class FoxDisplay;

//------------------------------------------------------------------------------
// Class: FoxStation
//
// Description: Station class that can attach a FoxDisplay
//------------------------------------------------------------------------------
class FoxStation : public simulation::Station
{
   DECLARE_SUBCLASS(FoxStation, simulation::Station)

public:
   FoxStation();

   // display
   FoxDisplay* getMainDisplay()                     { return display; }

   void updateTC(const double dt = 0.0) override;
   void updateData(const double dt = 0.0) override;

protected:

   bool setSlotMainDisplay(FoxDisplay* const msg);

private:

   base::safe_ptr<FoxDisplay> display;
};

}
}

#endif
