
#ifndef __oe_example_Station_H__
#define __oe_example_Station_H__

#include "openeaagles/simulation/Station.h"

namespace oe {

namespace glut { class GlutDisplay; }

namespace example {

// -------------------------------------------------------------------------------
// Class: Station
//
// Description:
//      Derived Station that will know it has a display and can be accessed through
//      it.  This also runs the simulation, and acts as the interface between the
//      graphics and simulation.
// -------------------------------------------------------------------------------
class Station : public simulation::Station
{
    DECLARE_SUBCLASS(Station, simulation::Station)

public:
    Station();

    void reset() override;

protected:
    // slot methods
    bool setSlotDisplay(glut::GlutDisplay*);

private:
    glut::GlutDisplay* display;     // this is our main display that
    bool displayInit;               // is our display created?
};

}
}

#endif

