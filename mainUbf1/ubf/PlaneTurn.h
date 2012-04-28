//
// Class: PlaneTurn
//
// Description: Behavior class that periodaically turns right
//

#ifndef __Eaagles_MainUbf1_PlaneTurn_H__
#define __Eaagles_MainUbf1_PlaneTurn_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class UbfState; class UbfAction; class PlaneAction; }

namespace MainUbf1 {

class PlaneTurn : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneTurn, Ubf::Behavior)

public:

   PlaneTurn();

   // generates the turn behavior
   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

private:

   double prevAlt;

};

}
}

#endif

