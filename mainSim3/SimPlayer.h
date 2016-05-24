
#ifndef __oe_example_SimPlayer_H__
#define __oe_example_SimPlayer_H__

#include "openeaagles/simulation/AirVehicle.h"

namespace oe {
namespace example {

//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
class SimPlayer : public simulation::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, simulation::Aircraft)

public:
    SimPlayer();

    virtual void reset() override;

private:
};

}
}

#endif
