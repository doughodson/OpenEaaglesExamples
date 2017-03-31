
#ifndef __Station_H__
#define __Station_H__

#include "openeaagles/simulation/Station.hpp"

namespace oe {
   namespace glut { class GlutDisplay; }
}

// -------------------------------------------------------------------------------
// Class: Station
//
// Description:
//      Derived Station that will know it has a display and can be accessed through
//      it.  This also runs the simulation, and acts as the interface between the
//      graphics and simulation.
// -------------------------------------------------------------------------------
class Station : public oe::simulation::Station
{
    DECLARE_SUBCLASS(Station, oe::simulation::Station)

public:
    Station();

    virtual void reset() override;

protected:
    // slot methods
    bool setSlotDisplay(oe::glut::GlutDisplay*);

private:
    oe::glut::GlutDisplay* display {}; // this is our main display that
    bool displayInit {};               // is our display created?
};

#endif
