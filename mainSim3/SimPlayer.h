//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
#ifndef __oe_Example_SimPlayer_H__
#define __oe_Example_SimPlayer_H__

#include "openeaagles/simulation/AirVehicle.h"

namespace oe {
namespace Example {

class SimPlayer : public Simulation::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, Simulation::Aircraft)

public:
    SimPlayer();

    void reset() override;

private:
};

} // End Example namespace
} // End oe namespace

#endif
