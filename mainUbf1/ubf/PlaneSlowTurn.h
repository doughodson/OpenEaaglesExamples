//
// Class: PlaneTurn
//
// Description: Behavior class that periodically turns right
//

#ifndef __Eaagles_MainUbf1_PlaneSlowTurn_H__
#define __Eaagles_MainUbf1_PlaneSlowTurn_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneSlowTurn : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneSlowTurn, Ubf::Behavior)

public:

   PlaneSlowTurn();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif

