//
// Class: PlaneFire
//
// Base class: Basic::Component -> Ubf::Behavior -> PlaneFire
//
// Description: Behavior class that shoots missiles at enemy planes
//

#ifndef __Eaagles_MainUbf1_PlaneFire_H__
#define __Eaagles_MainUbf1_PlaneFire_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneFire : public Ubf::Behavior
{
  DECLARE_SUBCLASS(PlaneFire, Ubf::Behavior)

public:

	PlaneFire();

	Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);
};

}
}

#endif

