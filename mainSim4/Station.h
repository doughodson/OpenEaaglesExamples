// -------------------------------------------------------------------------------
// Class: Station
//
// Description:
//      Derived Station that will know it has a display and can be accessed through
//      it.  This also runs the simulation, and acts as the interface between the
//      graphics and simulation.
// -------------------------------------------------------------------------------
#ifndef __oe_Example_Station_H__
#define __oe_Example_Station_H__

#include "openeaagles/simulation/Station.h"

namespace oe {

namespace Glut { class GlutDisplay; }

namespace Example {

class Station : public Simulation::Station
{
    DECLARE_SUBCLASS(Station, Simulation::Station)

public:
    Station();

    void reset() override;

protected:
    // slot methods
    bool setSlotDisplay(Glut::GlutDisplay*);

private:
    Glut::GlutDisplay* display;     // this is our main display that
    bool displayInit;               // is our display created?
};

}  // end of Example namespace
}  // end of oe namespace

#endif

