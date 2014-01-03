// -------------------------------------------------------------------------------
// Class: Station
//
// Description:
//      Derived Station that will know it has a display and can be accessed through
//      it.  This also runs the simulation, and acts as the interface between the
//      graphics and simulation.
// -------------------------------------------------------------------------------
#ifndef __Eaagles_Example_Station_H__
#define __Eaagles_Example_Station_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {

namespace Glut { class GlutDisplay; }

namespace Example {

class Station : public Simulation::Station
{
    DECLARE_SUBCLASS(Station, Simulation::Station)

public:
    Station();
    
    // Basic::Component interface
    virtual void reset();

protected:
    // SLOT function(s)
    // set our display
    bool setSlotDisplay(Glut::GlutDisplay* dis);

private:
    Glut::GlutDisplay* display;     // this is our main display that 
    bool displayInit;               // is our display created?
};

}  // end of Example namespace
}  // end of Eaagles namespace

#endif

