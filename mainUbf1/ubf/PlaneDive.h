//
// Class: PlaneDive
//
// Description: Behavior class that dives
//

#ifndef __Eaagles_MainUbf1_PlaneDive_H__
#define __Eaagles_MainUbf1_PlaneDive_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneDive : public Ubf::Behavior
{
  DECLARE_SUBCLASS(PlaneDive, Ubf::Behavior)

public:

   PlaneDive();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif

