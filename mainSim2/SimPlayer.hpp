
#ifndef __SimPlayer_H__
#define __SimPlayer_H__

#include "openeaagles/simulation/AirVehicle.hpp"

//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
class SimPlayer : public oe::simulation::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, oe::simulation::Aircraft)

public:
    SimPlayer();

    virtual void reset() override;

private:
};

#endif
