//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_SimPlayer_H_
#define __Eaagles_Example_SimPlayer_H__

#include "openeaagles/simulation/AirVehicle.h"

namespace Eaagles {
namespace Example {

class SimPlayer : public Simulation::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, Simulation::Aircraft)

public:
    SimPlayer();
    
    // Basic::Component interface
    virtual void reset();

private:
};

} // End Example namespace
} // End Eaagles namespace

#endif
