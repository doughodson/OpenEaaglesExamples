//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
#ifndef __oe_example_SimPlayer_H__
#define __oe_example_SimPlayer_H__

#include "openeaagles/simulation/AirVehicle.h"

namespace oe {
namespace example {

class SimPlayer : public Simulation::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, Simulation::Aircraft)

public:
    SimPlayer();

    void reset() override;

private:
};

} // End example namespace
} // End oe namespace

#endif
