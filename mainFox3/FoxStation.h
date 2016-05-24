
#ifndef __FoxStation_H__
#define __FoxStation_H__

#include "openeaagles/simulation/Station.h"

class FoxDisplay;

//------------------------------------------------------------------------------
// Class: FoxStation
//
// Description: Station class that can attach a FoxDisplay
//------------------------------------------------------------------------------
class FoxStation : public oe::simulation::Station
{
   DECLARE_SUBCLASS(FoxStation, oe::simulation::Station)

public:
   FoxStation();

   // display
   FoxDisplay* getMainDisplay()                     { return display; }

   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;

protected:

   bool setSlotMainDisplay(FoxDisplay* const msg);

private:

   oe::base::safe_ptr<FoxDisplay> display;
};

#endif
