
#ifndef __SimPlayer_H__
#define __SimPlayer_H__

#include "openeaagles/models/players/AirVehicle.hpp"

//------------------------------------------------------------------------------
// Class: SimPlayer
//
// Description: Simulation player
//------------------------------------------------------------------------------
class SimPlayer : public oe::models::Aircraft
{
    DECLARE_SUBCLASS(SimPlayer, oe::models::Aircraft)

public:
    SimPlayer();

    virtual void reset() override;

private:
};

#endif
